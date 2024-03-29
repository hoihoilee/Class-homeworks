exception TODO

type formula = 
  | TRUE
  | FALSE
  | NOT of formula
  | ANDALSO of formula * formula
  | ORELSE of formula * formula
  | IMPLY of formula * formula
  | LESS of expr * expr
and expr =
  | NUM of int
  | PLUS of expr * expr
  | MINUS of expr * expr

let rec cal (e: expr): int =
	match e with
	| NUM i -> i
	| PLUS (e1, e2) -> (cal e1) + (cal e2)
	| MINUS (e1, e2) -> (cal e1) - (cal e2)

let rec eval (f: formula): bool =
	match f with
	| TRUE -> true
	| FALSE -> false
	| NOT f1 -> let f_ = (eval f1) in if f_ = true then false else true
	| ANDALSO (f1, f2) -> (match ((eval f1), (eval f2)) with
				| (true, true) -> true
				| _ -> false)
	| ORELSE (f1, f2) -> (match ((eval f1), (eval f2)) with
				| (false, false) -> false
				| _ -> true)
	| IMPLY (f1, f2) -> (match ((eval f1), (eval f2)) with
				| (false, _) -> true
				| (true, true) -> true
				| (true, false) -> false)
	| LESS (e1, e2) -> (cal e1) < (cal e2)
