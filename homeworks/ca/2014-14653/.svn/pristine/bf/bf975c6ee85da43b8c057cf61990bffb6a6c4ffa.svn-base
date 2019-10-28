import Types::*;
import ProcTypes::*;
import MemTypes::*;
import BypassRFile::*;
import Scoreboard::*;
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
	DecodedInst dInst;
	Addr ppc;
	Bool epoch;
} Decode2Exec deriving(Bits, Eq);

(*synthesize*)
module mkProc(Proc);
	Reg#(Addr)    pc  <- mkRegU;
	RFile         rf  <- mkBypassRFile;
	IMemory     iMem  <- mkIMemory;
	DMemory     dMem  <- mkDMemory;
	Cop          cop  <- mkCop;

	Reg#(CondFlag) 	 	condFlag	<- mkRegU;
	Reg#(ProcStatus)   	stat		<- mkRegU;

	Fifo#(1, Addr)       execRedirect <- mkBypassFifo;
	Fifo#(1, ProcStatus) statRedirect <- mkBypassFifo;

	Fifo#(2, Fetch2Decode)	   f2d <- mkPipelineFifo;
	Fifo#(2, Decode2Exec)      d2e <- mkPipelineFifo;
	Fifo#(2, Maybe#(ExecInst)) e2m <- mkPipelineFifo;
	Fifo#(2, Maybe#(ExecInst)) m2w <- mkPipelineFifo;

	Reg#(Bool) fEpoch <- mkRegU;
	Reg#(Bool) eEpoch <- mkRegU;

	Scoreboard#(4) sb <- mkPipelineScoreboard;

	/* TODO: Lab 6-1: Implement 5-stage pipelined processor, using given scoreboard.
			 Lab 6-2: Implement 5-stage pipelined processor, using bypassing. */

	rule doFetch(cop.started && stat == AOK);
		/* Fetch */
		if(execRedirect.notEmpty)
		begin
			fEpoch <= !fEpoch;
			execRedirect.deq;
			pc <= execRedirect.first;
		end
		else
		begin
			let inst = iMem.req(pc);
			let ppc = nextAddr(pc, getICode(inst));

			$display("Fetch : from Pc %d , expanded inst : %x, \n", pc, inst, showInst(inst));

			pc <= ppc;
			f2d.enq(Fetch2Decode{inst:inst, pc:pc, ppc:ppc, epoch:fEpoch});
		end

	endrule

	rule doDecode(cop.started && stat == AOK);
		let inst   = f2d.first.inst;
		let ipc    = f2d.first.pc;
		let ppc    = f2d.first.ppc;
		let iEpoch = f2d.first.epoch;
		//f2d.deq;

		/* Decode */
		let dInst = decode(inst, ipc);
		$display("Decode : from Pc %d , expanded inst : %x, \n", ipc, inst, showInst(inst));

		let stall = sb.search1(dInst.regA) || sb.search2(dInst.regB) || sb.search3(dInst.dstE) || sb.search4(dInst.dstM);

		if((iEpoch == eEpoch) && (!stall))
		begin
			dInst.valA   = isValid(dInst.regA)? tagged Valid rf.rdA(validRegValue(dInst.regA)) : Invalid;
			dInst.valB   = isValid(dInst.regB)? tagged Valid rf.rdB(validRegValue(dInst.regB)) : Invalid;
			dInst.copVal = isValid(dInst.regA)? tagged Valid cop.rd(validRegValue(dInst.regA)) : Invalid;

			d2e.enq(Decode2Exec{dInst:dInst, ppc:ppc, epoch:iEpoch});
			f2d.deq;
			sb.insertE(dInst.dstE);
			sb.insertM(dInst.dstM);
		end
	endrule

	rule doExecute(cop.started && stat == AOK);
			/* Execute */
			let x = d2e.first;
			let dInst = x.dInst;
			let ppc = x.ppc;
			let inEp = x.epoch;
			//d2e.deq;

			if(inEp == eEpoch) begin
				let eInst = exec(dInst, condFlag, ppc);
				condFlag <= eInst.condFlag;
				e2m.enq(Valid(eInst));
				d2e.deq;

			if(eInst.mispredict)
                        begin
                                eEpoch <= !eEpoch;
                                let redirPc = validValue(eInst.nextPc);
                                $display("mispredicted, redirect %d ", redirPc);
                                execRedirect.enq(redirPc);
                        end
			end

			else e2m.enq(Invalid);
	endrule

	rule doMemory(cop.started && stat == AOK);
			/* Memory */
			if (isValid(e2m.first)) begin
			let eInst = validValue(e2m.first);
			let iType = eInst.iType;
			case(iType)
				MRmov, Pop, Ret :
				begin
					let ldData <- (dMem.req(MemReq{op: Ld, addr: eInst.memAddr, data:?}));
					eInst.valM = Valid(little2BigEndian(ldData));
					$display("Loaded %d from %d", little2BigEndian(ldData), eInst.memAddr);
					if(iType == Ret)
					begin
						eInst.nextPc = eInst.valM;
						execRedirect.enq(validValue(eInst.nextPc));
					end
				end

				RMmov, Call, Push :
				begin
					let stData = (iType == Call)? eInst.valP : validValue(eInst.valA);
					let dummy <- dMem.req(MemReq{op: St, addr: eInst.memAddr, data: big2LittleEndian(stData)});
					$display("Stored %d into %d", stData, eInst.memAddr);
				end
			endcase

			/* Update Status */
			let newStatus = case(iType)
								Unsupported : INS;
								Hlt 		  : HLT;
								default     : AOK;
							endcase;
			statRedirect.enq(newStatus);

			m2w.enq(Valid(eInst));
			e2m.deq;
			end
			else m2w.enq(Invalid);
			//e2m.deq;
	endrule

	rule doWriteBack(cop.started && stat == AOK);
			/* WriteBack */
			if(isValid(m2w.first)) begin
			let eInst = validValue(m2w.first);

			if(isValid(eInst.dstE))
			begin
				$display("On %d, writes %d   (wrE)", validRegValue(eInst.dstE), validValue(eInst.valE));
				rf.wrE(validRegValue(eInst.dstE), validValue(eInst.valE));
			end
			if(isValid(eInst.dstM))
			begin
				$display("On %d, writes %d   (wrM)", validRegValue(eInst.dstM), validValue(eInst.valM));
				rf.wrM(validRegValue(eInst.dstM), validValue(eInst.valM));
			end

			cop.wr(eInst.dstE, validValue(eInst.valE));
			m2w.deq;
			end
			//m2w.deq;
			sb.remove;
	endrule

	rule upd_Stat(cop.started);
		$display("Stat update");
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
