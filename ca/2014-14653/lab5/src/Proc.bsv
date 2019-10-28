import Types::*;
import ProcTypes::*;
import MemTypes::*;
import RFile::*;
import IMemory::*;
import DMemory::*;
import Decode::*;
import Exec::*;
import Cop::*;
import Fifo::*;

typedef struct {
	Inst inst;
	Addr pc;
	Addr ppc;
	Bool epoch;
} Fetch2Decode deriving(Bits, Eq);

typedef struct {
	Inst inst;
	Addr pc;
	Addr ppc;
	Bool epoch;
	DecodedInst dInst;
} Decode2Execute deriving(Bits, Eq);

(*synthesize*)
module mkProc(Proc);
	Reg#(Addr)		pc	<- mkRegU;
	RFile				 rf	<- mkRFile;
	IMemory		 iMem	<- mkIMemory;
	DMemory		 dMem	<- mkDMemory;
	Cop					cop	<- mkCop;

	Reg#(CondFlag) 			condFlag	 <- mkRegU;
	Reg#(ProcStatus)			stat		 <- mkRegU;

	Fifo#(1, Addr)				 execRedirect <- mkCFFifo;
	Fifo#(1, ProcStatus)	 statRedirect <- mkBypassFifo;

	Fifo#(2, Fetch2Decode)	f2d <- mkCFFifo;
	Fifo#(2, Decode2Execute)  d2e <- mkCFFifo;

	Reg#(Bool) fEpoch <- mkRegU;
	Reg#(Bool) eEpoch <- mkRegU;

	rule doFetch(cop.started && stat == AOK);

		/* TODO: Remove 1-cycle inefficiency when execRedirect is used. */
		let mypc = (fEpoch != eEpoch)? execRedirect.first : pc;
		let myEpoch = (fEpoch != eEpoch)? !fEpoch : fEpoch;
		let inst = iMem.req(mypc);
		let iCode = getICode(inst);
		let ppc = nextAddr(mypc, iCode);

		if(execRedirect.notEmpty) execRedirect.deq;

		pc <= ppc;
		fEpoch <= myEpoch;

		f2d.enq(Fetch2Decode{inst:inst, pc:mypc, ppc:ppc, epoch:myEpoch});
		$display("Fetch : from Pc %d , expanded inst : %x, \n", pc, inst, showInst(inst));
	endrule

	rule doDecode(cop.started && stat == AOK);
		let inst = f2d.first.inst;
		let pc = f2d.first.pc;
		let ppc = f2d.first.ppc;
		let iEpoch = f2d.first.epoch;
		d2e.enq(Decode2Execute{inst:inst, pc:pc, ppc:ppc, epoch:iEpoch, dInst:decode(inst, pc)});
		f2d.deq;
	endrule

	rule doRest(cop.started && stat == AOK);
		/* TODO: Divide the doRest rule into doDecode, doRest rules to implement 3-stage pipelined processor */
		let inst = d2e.first.inst;
		let pc = d2e.first.pc;
		let ppc = d2e.first.ppc;
		let iEpoch = d2e.first.epoch;
		let dInst = d2e.first.dInst;
		d2e.deq;
			if(iEpoch == eEpoch)
			begin
			/* Register Read */
			dInst.valA	 = isValid(dInst.regA)? tagged Valid rf.rdA(validRegValue(dInst.regA)) : Invalid;
	 		dInst.valB	 = isValid(dInst.regB)? tagged Valid rf.rdB(validRegValue(dInst.regB)) : Invalid;
			dInst.copVal = isValid(dInst.regA)? tagged Valid cop.rd(validRegValue(dInst.regA)) : Invalid;


			/* Exec */
			let eInst = exec(dInst, condFlag, ppc);
			condFlag <= eInst.condFlag;


			/* Memory */
			let iType = eInst.iType;
			case(iType)
	 		MRmov, Pop, Ret :
	 		begin
		 		let ldData <- (dMem.req(MemReq{op: Ld, addr: eInst.memAddr, data:?}));
				eInst.valM = Valid(little2BigEndian(ldData));
				if(iType == Ret)//Return address is known here
				begin
					eInst.nextPc = eInst.valM;
				end
		 	end

			RMmov, Call, Push :
			begin
				let stData = (iType == Call)? eInst.valP : validValue(eInst.valA);
				let dummy <- dMem.req(MemReq{op: St, addr: eInst.memAddr, data: big2LittleEndian(stData)});
			end
			endcase

			/* State Update */
			let newStatus = case(iType)
				Unsupported: INS;
				Hlt 	   : HLT;
				default	   : AOK;
			endcase;
			statRedirect.enq(newStatus);

			if(eInst.mispredict)
			begin
				eEpoch <= !eEpoch;
				let redirPc = validValue(eInst.nextPc);
				$display("mispredicted, redirect %d ", redirPc);
				execRedirect.enq(redirPc);
	 		end


			/* WriteBack */
			if(isValid(eInst.dstE))
			begin
				rf.wrE(validRegValue(eInst.dstE), validValue(eInst.valE));
			end
			if(isValid(eInst.dstM))
			begin
				rf.wrM(validRegValue(eInst.dstM), validValue(eInst.valM));
			end
			cop.wr(eInst.dstE, validValue(eInst.valE));

			/* TODO: Exercise 3
				1. Use cop.incInstTypeCnt(instType) to count number of each instruciton type
					 - instType list
					Ctr(Control) 	 : call, ret, jump
					Mem(Memory)		 : mrmovq, rmmovq, push, pop
				2. Use cop.incBPMissCnt() to count number of mispredictions.
			*/
			
			if(eInst.mispredict) begin
				cop.incBPMissCnt();
				case(iType)
					Call : begin
						cop.incInstTypeCnt(Ctr);
						cop.incMissInstTypeCnt(M_Call);
					end
					Ret : begin
						cop.incInstTypeCnt(Ctr);
						cop.incMissInstTypeCnt(M_Ret);
					end
					Jmp : begin
						cop.incInstTypeCnt(Ctr);
						cop.incMissInstTypeCnt(M_Jmp);
					end
					MRmov, RMmov, Push, Pop : cop.incInstTypeCnt(Mem);
				endcase
			end
			else begin
				case(iType)
					Call : begin
						cop.incInstTypeCnt(Ctr);
						cop.incMissInstTypeCnt(N_Call);
					end
					Ret : begin
                	                        cop.incInstTypeCnt(Ctr);
                        	                cop.incMissInstTypeCnt(N_Ret);
	                                end
					Jmp : begin
                	                        cop.incInstTypeCnt(Ctr);
                        	                cop.incMissInstTypeCnt(N_Jmp);
                                	end
					MRmov, RMmov, Push, Pop : cop.incInstTypeCnt(Mem);
				endcase
			end

			/*	TODO: Excercise 4
				1. Implement incInstTypeCnt(InstCntType inst) method in Cop.bsv
				2. Use cop.incInstTypeCnt(inst) to count number of mispredictions for each instruction types.
			*/

		end
	endrule

	rule upd_Stat(cop.started);
		statRedirect.deq;
		stat <= statRedirect.first;
	endrule

	rule statHLT(cop.started && stat == HLT);
		$fwrite(stderr, "Program Finished by halt\n");
		$finish;
	endrule

	rule statINS(cop.started && stat == INS);
		$fwrite(stderr, "Executed unsupported instruction. Exiting\n");
		$finish;
	endrule

	method ActionValue#(Tuple3#(RIndx, Data, Data)) cpuToHost;
		let retV <- cop.cpuToHost;
		return retV;
	endmethod

	method Action hostToCpu(Addr startpc) if (!cop.started);
		cop.start;
		eEpoch <= False;
		fEpoch <= False;
		pc <= startpc;
		stat <= AOK;
	endmethod

endmodule
