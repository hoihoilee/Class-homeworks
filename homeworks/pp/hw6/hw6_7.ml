exception TODO

type pgm = cmd
and cmd = ASSIGN of exp
 | SEQUENCE of cmd * cmd
 | REPEAT of cmd
 | CHOICE of cmd * cmd
 | EQ of exp * cmd
 | NEQ of exp * cmd
and exp = NUM of int
 | ADD of exp * exp
 | SUB of exp * exp
 | VAR

type state = int
type stat = PRO of int
 | END of int

let rec cal (e:exp) (st:state): state =
        match e with
        | NUM i -> i
        | ADD (e1, e2) -> (cal e1 st) + (cal e2 st)
        | SUB (e1, e2) -> (cal e1 st) - (cal e2 st)
        | VAR -> st

let rmv (sl:'a list): 'a list =
	let rec rmv2 (s1:'a list) (s2:'a list):'a list =
        	match s1 with
	        | [] -> s2
        	| h::t -> if (List.exists (fun x -> x = h) s2) then (rmv2 t s2)
               		else (rmv2 t (h::s2)) in (rmv2 sl [])

let rec sum_list (sl:'a list list):'a list =
        match sl with
        | [] -> []
        | h::t -> (rmv (List.append (rmv h) (sum_list t)))

let pe (st:stat): bool = match st with | PRO _ -> true | END _ -> false

let rec exe (p:pgm) (st:stat): stat list =
	match st with | END s -> [END s] | PRO s -> (
	match p with
	| ASSIGN e -> let cal_s = (cal e s) in if ((cal_s > 5) || (cal_s < (-5))) then [END s] else [PRO cal_s]
	| SEQUENCE (c1, c2) -> let (p_stl, e_stl) = (List.partition pe (exe c1 st)) in
				if (p_stl = []) then e_stl
				else (rmv (List.append (sum_list (List.map (exe c2) p_stl)) e_stl))
	| REPEAT c -> (match c with | REPEAT _ -> (exe c st) | _ ->
			let rec repeat (p:pgm) (his_stl:stat list) (cur_stl:stat list) : stat list =
				let next_stl = (sum_list (List.map (exe p) cur_stl)) in let (next_pro_stl, _) = (List.partition pe next_stl) in
				if (next_pro_stl = []) then (rmv (List.append next_stl his_stl))
				else if (List.for_all (fun x -> List.mem x his_stl) next_pro_stl) then (rmv (List.append next_stl his_stl))
				else (repeat p (rmv (List.append next_stl his_stl)) next_pro_stl) in
			(repeat c [st] [st]))
	| CHOICE (c1, c2) -> (rmv (List.append (exe c1 st) (exe c2 st)))
	| EQ (e, c) -> if (s = (cal e s)) then (exe c st) else [st]
	| NEQ (e, c) -> if (not (s = (cal e s))) then (exe c st) else [st])

let sort (stl:state list): state list =
        let c (a: state) (b: state): int =
                if (a > b) then 1
                else if (a < b) then (-1)
                else 0
        in (List.sort c stl)

let rec exeval (p:pgm) (st:state): state list =
	let conv (st_:stat): state = match st_ with | PRO a -> a | END a -> a in
	(sort (rmv (List.map conv (exe p (PRO st)))))
