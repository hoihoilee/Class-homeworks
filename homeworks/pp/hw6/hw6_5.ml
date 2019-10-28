exception TODO

type ae =
  | CONST of int
  | VAR of string
  | POWER of string * int
  | TIMES of ae list
  | SUM of ae list

let rec diff (e: ae) (x: string): ae =
	match e with
	| CONST i -> CONST 0
	| VAR s -> if s = x then CONST 1 else CONST 0
	| POWER (s, i) -> if (not (s = x)) then CONST 0
			else (match i with
				| 0 -> CONST 0
				| 1 -> CONST 1
				| _ -> TIMES [CONST i;POWER (s, (i-1))])
	| TIMES l -> (match l with
			| [] -> CONST 0
			| h::t -> SUM [(TIMES ((diff h x)::t));(TIMES [h;(diff (TIMES t) x)])])
	| SUM l -> (match l with
			| [] -> CONST 0
			| h::t -> SUM [(diff h x);(diff (SUM t) x)])
