import BarrelShifterRight::*;

interface BarrelShifterLeft;
	method ActionValue#(Bit#(64)) leftShift(Bit#(64) val, Bit#(6) shiftAmt);
endinterface

module mkBarrelShifterLeft(BarrelShifterLeft);
	let bsr <- mkBarrelShifterRightLogical;
	method ActionValue#(Bit#(64)) leftShift(Bit#(64) val, Bit#(6) shiftAmt);
		/* TODO: Implement a left shifter using the given logical right shifter */
		Bit#(64) result;
		for (Integer i = 0; i < 64; i = i + 1)
			result[i] = val[i];
		result = reverseBits(result);
		result <- bsr.rightShift(result, shiftAmt);
		result = reverseBits(result);
		return result;
	endmethod
endmodule
