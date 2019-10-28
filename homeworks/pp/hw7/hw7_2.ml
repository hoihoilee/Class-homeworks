module type SKI = sig
  type liquid =
    | S
    | K
    | I
    | V of string (* varible *)
    | M of liquid * liquid (* mix of two liquids *)
  val react: liquid -> liquid
  val pprint: liquid -> string
end

module SkiLiquid : SKI = struct
  exception ETODO

  type liquid =
    | S
    | K
    | I
    | V of string (* varible *)
    | M of liquid * liquid (* mix of two liquids *)

  let rec react: liquid -> liquid =
    fun l ->
	match l with
	| S -> S
	| K -> K
	| I -> I
	| V s -> V s
	| M (l1, l2) ->
	(match l1 with
	| I -> (react l2)
	| M (K, l3) -> (react l3)
	| M (M (S, l4), l5) -> (react (M (M (l4, l2), M (l5, l2))))
	| _ -> let l1_ = (react l1) in let l2_ = (react l2) in
		if (l1_ = l1) && (l2_ = l2) then M (l1, l2)
		else (react (M (l1_,l2_))))

  let rec pprint: liquid -> string =
    fun l ->
    	match l with
	| S -> "S"
	| K -> "K"
	| I -> "I"
	| V s -> s
	| M (l1, l2) -> String.concat "" ["(";pprint l1;" ";pprint l2;")"]
end
