exception TODO

type metro = STATION of name
	   | AREA of name * metro
	   | CONNECT of metro * metro
 and name = string


let rec checker (m:metro) (l: name list): bool =
	match m with
	| STATION n -> (List.exists (fun x -> (x = n)) l)
	| AREA (n, m1) -> if (List.exists (fun x -> (x = n)) l) then (checker m1 l) else (checker m1 (n::l))
	| CONNECT (m1, m2) -> (checker m1 l) && (checker m2 l)

let rec checkMetro (m:metro): bool = (checker m [])
