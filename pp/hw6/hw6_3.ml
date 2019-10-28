exception TODO

type team = Korea | France | Usa | Brazil | Japan | Nigeria | Cameroon
          | Poland | Portugal | Italy | Germany | Norway | Sweden | England
          | Argentina

type tourna = LEAF of team
            | NODE of tourna * tourna

let matching team =
        match team with
        | Korea -> "Korea"
        | France -> "France"
        | Usa -> "Usa"
        | Brazil -> "Brazil"
        | Japan -> "Japan"
        | Nigeria -> "Nigeria"
        | Cameroon -> "Cameroon"
        | Poland -> "Poland"
        | Portugal -> "Portugal"
        | Italy -> "Italy"
        | Germany -> "Germany"
        | Norway -> "Norway"
        | Sweden -> "Sweden"
        | England -> "England"
        | Argentina -> "Argentina"

let rec drop (t: tourna) (d: team): string =
	match t with
	| LEAF team -> if team = d then "" else matching team
	| NODE (t1, t2) -> let d1 = (drop t1 d) in let d2 = (drop t2 d) in
				if (d1 = "") && (d2 = "") then ""
				else if (d1 = "") && (not (d2 = "")) then d2
				else if (not (d1 = "")) && (d2 = "") then d1
				else String.concat "" ["(";d1;" ";d2;")"]
