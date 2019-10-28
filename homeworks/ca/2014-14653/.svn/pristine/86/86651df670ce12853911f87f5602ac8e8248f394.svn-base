import Multiplexer::*;

interface BarrelShifterRight;
  method ActionValue#(Bit#(64)) rightShift(Bit#(64) val, Bit#(6) shiftAmt, Bit#(1) shiftValue);
endinterface

module mkBarrelShifterRight(BarrelShifterRight);
  method ActionValue#(Bit#(64)) rightShift(Bit#(64) val, Bit#(6) shiftAmt, Bit#(1) shiftValue);
    /* TODO: Implement right barrel shifter using six multiplexers. */
    Bit#(64) result = val;
    Bit#(64) tmp;
    Integer div2 = 64;
    for (Integer i = 5; i > -1; i = i - 1)
      begin      
        div2 = div2 / 2;
        for (Integer j = 63; j > -1; j = j - 1)
          begin
            if (j < (64 - div2)) tmp[j] = result[j + div2];
            else tmp[j] = shiftValue;
          end
        result = multiplexer64(shiftAmt[i], result, tmp);
      end
    return result;
  endmethod
endmodule

interface BarrelShifterRightLogical;
  method ActionValue#(Bit#(64)) rightShift(Bit#(64) val, Bit#(6) shiftAmt);
endinterface

module mkBarrelShifterRightLogical(BarrelShifterRightLogical);
  let bsr <- mkBarrelShifterRight;
  method ActionValue#(Bit#(64)) rightShift(Bit#(64) val, Bit#(6) shiftAmt);
    /* TODO: Implement logical right shifter using the right shifter */
    let result <- bsr.rightShift(val, shiftAmt, 0);
    return result;
  endmethod
endmodule

typedef BarrelShifterRightLogical BarrelShifterRightArithmetic;

module mkBarrelShifterRightArithmetic(BarrelShifterRightArithmetic);
  let bsr <- mkBarrelShifterRight;
  method ActionValue#(Bit#(64)) rightShift(Bit#(64) val, Bit#(6) shiftAmt);
    /* TODO: Implement arithmetic right shifter using the right shifter */
    Bit#(1) s_val;
    if (val[63] == 1) s_val = 1;
    else s_val = 0;
    let result <- bsr.rightShift(val, shiftAmt, s_val);
    return result;
  endmethod
endmodule
