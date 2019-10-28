import Types::*;
import ProcTypes::*;
import CReg::*;
import ConfigReg::*;
import Fifo::*;

typedef enum {Ctr, Mem} InstCntType deriving(Bits, Eq);

/* TODO: Replace dummies to implement incMissInstTypeCnt */
typedef enum {M_Call, M_Ret, M_Jmp, N_Call, N_Ret, N_Jmp} InstMissCntType deriving(Bits, Eq);

interface Cop;
    method Action start;
    method Bool started;
    method Data rd(RIndx idx);
    method Action wr(Maybe#(FullIndx) idx, Data val);
    method Action incInstTypeCnt(InstCntType inst);
    method Action incBPMissCnt();
    method Action incMissInstTypeCnt(InstMissCntType inst);
    method ActionValue#(Tuple3#(RIndx, Data, Data)) cpuToHost;
endinterface

(* synthesize *)
module mkCop(Cop);
    Reg#(Bool) startReg <- mkConfigReg(False);
    Reg#(Data) numInsts <- mkConfigReg(0);
    Reg#(Data) timeReg <- mkConfigReg(?);
    Reg#(Bool) finishReg <- mkConfigReg(False);
    Reg#(Data) finishCode <- mkConfigReg(0);

    Reg#(Data) numMem    <- mkConfigReg(0);
    Reg#(Data) numCtr    <- mkConfigReg(0);
    Reg#(Data) numBPMiss <- mkConfigReg(0);

    Reg#(Data) numCall    <- mkConfigReg(0);
    Reg#(Data) numRet    <- mkConfigReg(0);
    Reg#(Data) numJmp <- mkConfigReg(0);
    Reg#(Data) misCall    <- mkConfigReg(0);
    Reg#(Data) misRet    <- mkConfigReg(0);
    Reg#(Data) misJmp <- mkConfigReg(0);

    Fifo#(2, Tuple3#(RIndx, Data, Data)) copFifo <- mkCFFifo;

    Reg#(Data) cycles <- mkReg(0);

    rule count;
        cycles <= cycles + 1;
        $display("\nCycle %d ----------------------------------------------------", cycles);
    endrule

    method Action start;
        startReg <= True;
    endmethod

    method Bool started;
        return startReg;
    endmethod

    method Data rd(RIndx idx);
        return (case(idx)
            10: cycles;
            11: numInsts;
            14: finishCode;
        endcase);
    endmethod

    /*
        Register 10: (Read only) current time
        Register 11: (Read only) returns current number of instructions
        Register 12: (Write only) Write an integer to stderr
        Register 13: (Write only) Write a char to stderr
        Register 14: Finish code
        Register 22: (Write only) Finished executing
    */
    method Action wr(Maybe#(FullIndx) idx, Data val);
        if(isValid(idx) && validValue(idx).regType == CopReg)
        begin
            case (validRegValue(idx))
                12: copFifo.enq(tuple3(12, val, numInsts+1));
                13: copFifo.enq(tuple3(13, val, numInsts+1));
		        14: begin
	    			$fwrite(stderr, "==========================================\n");
				    $fwrite(stderr, "Specific type of executed instructions\n");
			    	$fwrite(stderr, "Ctr 		            : %d\n", numCtr);
			    	$fwrite(stderr, "Mem 		            : %d\n", numMem);
			    	$fwrite(stderr, "Mispredicted	            : %d\n", numBPMiss);
			    	$fwrite(stderr, "==========================================\n");

			    	/* TODO: Implement below to output counted values */
			    	$fwrite(stderr, "Misprediction detail\n");
				    $fwrite(stderr, "Call 		            : %d / %d\n", misCall, misCall + numCall);
			    	$fwrite(stderr, "Ret 		            : %d / %d\n", misRet, misRet + numRet);
			    	$fwrite(stderr, "Jmp 		            : %d / %d\n", misJmp, misJmp + numJmp);
	    			$fwrite(stderr, "==========================================\n");
			    	copFifo.enq(tuple3(14, val, numInsts+1));
			    end
            endcase
        end
        numInsts <= numInsts + 1;
    endmethod

    method Action incInstTypeCnt(InstCntType inst);
	    case(inst)
		    Ctr : numCtr <= numCtr + 1;
            Mem : numMem <= numMem + 1; // rmmovq, mrmovq, push, pop
        endcase
    endmethod

    method Action incMissInstTypeCnt(InstMissCntType inst);
        case(inst)
		M_Call : misCall <= misCall + 1;
		N_Call : numCall <= numCall + 1;
                M_Ret : misRet <= misRet + 1;
                N_Ret : numRet <= numRet + 1;
                M_Jmp : misJmp <= misJmp + 1;
                N_Jmp : numJmp <= numJmp + 1;
	endcase
    endmethod

    method Action incBPMissCnt();
	    numBPMiss <= numBPMiss + 1;
    endmethod

    method ActionValue#(Tuple3#(RIndx, Data, Data)) cpuToHost;
        copFifo.deq;
        return copFifo.first;
    endmethod
endmodule
