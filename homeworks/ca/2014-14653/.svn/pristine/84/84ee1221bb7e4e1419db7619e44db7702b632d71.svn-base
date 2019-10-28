import Multiplexer::*;
import FIFO::*;
import FIFOF::*;
import Vector::*;
import SpecialFIFOs::*;

function (Bit#(71)) r_shift(Bit#(71) op, Integer amt);  // 70~7 : op, 6~1 : amt, 0 : val
	Bit#(64) result;
	Integer tmp = 2**amt;
	for (Integer i = 0; i < 64; i = i + 1) begin
		if (i < (64 - tmp)) result[i] = op[i + tmp + 7];
		else result[i] = op[0];
	end
	return {multiplexer64(op[amt + 1], op[70:7], result), op[6:0]};
endfunction

/* Interface of the basic right shifter module */
interface BarrelShifterRightPipelined;
	method Action shift_request(Bit#(64) operand, Bit#(6) shamt, Bit#(1) val);
	method ActionValue#(Bit#(64)) shift_response();
endinterface

module mkBarrelShifterRightPipelined(BarrelShifterRightPipelined);
	let inFifo <- mkFIFOF;
	let outFifo <- mkFIFOF;
	let fifo1 <-mkFIFOF;
	let fifo2 <-mkFIFOF;
	let fifo3 <-mkFIFOF;
	let fifo4 <-mkFIFOF;
	let fifo5 <-mkFIFOF;

	rule shift1;
		fifo1.enq(r_shift({tpl_1(inFifo.first), tpl_2(inFifo.first), tpl_3(inFifo.first)}, 5));
		inFifo.deq;
	endrule

	rule shift2;
		fifo2.enq(r_shift(fifo1.first, 4));
		fifo1.deq;
	endrule

	rule shift3;
		fifo3.enq(r_shift(fifo2.first, 3));
		fifo2.deq;
	endrule

	rule shift4;
		fifo4.enq(r_shift(fifo3.first, 2));
		fifo3.deq;
	endrule

	rule shift5;
		fifo5.enq(r_shift(fifo4.first, 1));
		fifo4.deq;
	endrule
	
	rule shift6;
		outFifo.enq(r_shift(fifo5.first, 0)[70:7]);
		fifo5.deq;
	endrule

	method Action shift_request(Bit#(64) operand, Bit#(6) shamt, Bit#(1) val);
		inFifo.enq(tuple3(operand, shamt, val));
	endmethod

	method ActionValue#(Bit#(64)) shift_response();
		outFifo.deq;
		return outFifo.first;
	endmethod
endmodule


/* Interface of the three shifter modules
 *
 * They have the same interface.
 * So, we just copy it using typedef declarations.
 */
interface BarrelShifterRightLogicalPipelined;
	method Action shift_request(Bit#(64) operand, Bit#(6) shamt);
	method ActionValue#(Bit#(64)) shift_response();
endinterface

typedef BarrelShifterRightLogicalPipelined BarrelShifterRightArithmeticPipelined;
typedef BarrelShifterRightLogicalPipelined BarrelShifterLeftPipelined;

module mkBarrelShifterLeftPipelined(BarrelShifterLeftPipelined);
	/* TODO: Implement left shifter using the pipelined right shifter. */
	let bsrp <- mkBarrelShifterRightPipelined;

	method Action shift_request(Bit#(64) operand, Bit#(6) shamt);
		bsrp.shift_request(reverseBits(operand), shamt, 0);
	endmethod

	method ActionValue#(Bit#(64)) shift_response();
		let result <- bsrp.shift_response();
		return reverseBits(result);
	endmethod
endmodule

module mkBarrelShifterRightLogicalPipelined(BarrelShifterRightLogicalPipelined);
	/* TODO: Implement right logical shifter using the pipelined right shifter. */
	let bsrp <- mkBarrelShifterRightPipelined;

	method Action shift_request(Bit#(64) operand, Bit#(6) shamt);
		bsrp.shift_request(operand, shamt, 0);
	endmethod

	method ActionValue#(Bit#(64)) shift_response();
		let result <- bsrp.shift_response();
		return result;
	endmethod
endmodule

module mkBarrelShifterRightArithmeticPipelined(BarrelShifterRightArithmeticPipelined);
	/* TODO: Implement right arithmetic shifter using the pipelined right shifter. */
	let bsrp <- mkBarrelShifterRightPipelined;

	method Action shift_request(Bit#(64) operand, Bit#(6) shamt);
		bsrp.shift_request(operand, shamt, operand[63]);
	endmethod

	method ActionValue#(Bit#(64)) shift_response();
		let result <- bsrp.shift_response();
		return result;
	endmethod
endmodule
