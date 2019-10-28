exception FreeVariable

type exp = X
  | INT of int
  | REAL of float
  | ADD of exp * exp
  | SUB of exp * exp
  | MUL of exp * exp
  | DIV of exp * exp
  | SIGMA of exp * exp * exp
  | INTEGRAL of exp * exp * exp

let rec calculate (e: exp): float =
    let rec fx (func, x: exp * float): float =
        let rec sigma (func, a, b: exp * float * float): float =
          if (a > b) then 0.0
          else fx(func, a) +. sigma(func, a +. 1.0, b) in

        let rec integral (func, a, b: exp * float * float): float =
          if ((b -. a) < 0.1) then 0.0
          else (fx(func, a) *. 0.1) +. integral(func, a +. 0.1, b) in

        match func with
        | X -> x
        | INT i -> float_of_int i
        | REAL f -> f
        | ADD (e1, e2) -> fx(e1, x) +. fx(e2, x)
        | SUB (e1, e2) -> fx(e1, x) -. fx(e2, x)
        | MUL (e1, e2) -> fx(e1, x) *. fx(e2, x)
        | DIV (e1, e2) -> fx(e1, x) /. fx(e2, x)
        | SIGMA (a, b, f) -> let cal_a = float_of_int (int_of_float (fx(a, x))) in
                             let cal_b = float_of_int (int_of_float (fx(b, x))) in
                             sigma(f, cal_a, cal_b)
        | INTEGRAL (a, b, f) -> let cal_a = fx(a, x) in
                                let cal_b = fx(b, x) in
                                if (cal_a > cal_b) then (-1.0) *. integral(f, cal_b, cal_a)
                                else integral(f, cal_a, cal_b) in

    match e with
    | X -> raise(FreeVariable)
    | INT i -> float_of_int i
    | REAL f -> f
    | ADD (e1, e2) -> (calculate e1) +. (calculate e2)
    | SUB (e1, e2) -> (calculate e1) -. (calculate e2)
    | MUL (e1, e2) -> (calculate e1) *. (calculate e2)
    | DIV (e1, e2) -> (calculate e1) /. (calculate e2)
    | SIGMA (a, b, f) -> let cal_a = calculate a in
                         let cal_b = calculate b in
                         fx(SIGMA (REAL cal_a, REAL cal_b, f), 0.0)
    | INTEGRAL (a, b, f) -> let cal_a = calculate a in
                            let cal_b = calculate b in
                            fx(INTEGRAL (REAL cal_a, REAL cal_b, f), 0.0)