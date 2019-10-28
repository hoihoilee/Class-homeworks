exception InvalidArgument

type ae = CONST of int
  | VAR of string
  | POWER of string * int
  | TIMES of ae list
  | SUM of ae list

let rec diff (a, str: ae * string): ae =
    match a with
    | CONST i -> CONST 0
    | VAR s -> if (s = str) then CONST 1
               else CONST 0
    | POWER (s, i) -> if (s = str) then
                        (match i with
                         | 0 -> CONST 0
                         | 1 -> CONST 1
                         | _ -> TIMES[CONST i; POWER(s, i - 1)])
                      else CONST 0
    | TIMES l -> (match l with
                  | [] -> raise(InvalidArgument)
                  | h::[] -> diff(h, str)
                  | h::t -> SUM[TIMES(diff(h, str)::t); TIMES[h; diff((TIMES t), str)]])
    | SUM l -> (match l with
                | [] -> raise(InvalidArgument)
                | h::[] -> diff(h, str)
                | h::t -> SUM[diff(h, str); diff((SUM t), str)])

(*let rec modify (a: ae): ae =
    let rec t_modify (l: ae list): ae list =
        match l with
        | [] -> []
        | h::t -> (modify h)::(t_modify t) in

    let rec scan0 (l: ae list): bool =
        match l with
        | [] -> false
        | h::t -> if (h = CONST 0) then true
                  else scan0 t in

    let rec rmv0 (l: ae list): ae list =
        match l with
        | [] -> []
        | h::t -> if (h = CONST 0) then rmv0 t
                  else h::(rmv0 t) in

    let rec rmv1 (l: ae list): ae list =
        match l with
        | [] -> []
        | h::t -> if (h = CONST 1) then rmv1 t
                  else h::(rmv1 t) in

    let rec uni_times (l: ae list): ae list =
        match l with
        | [] -> []
        | h::t -> (match h with
                   | TIMES l_t -> List.append l_t (uni_times t)
                   | _ -> h::(uni_times t)) in

    let rec uni_sum (l: ae list): ae list =
        match l with
        | [] -> []
        | h::t -> (match h with
                   | SUM l_t -> List.append l_t (uni_sum t)
                   | _ -> h::(uni_sum t)) in

    let rec cal_sum_const (l, con: (ae list) * int): ae list =
        match l with
        | [] -> if (con = 0) then [] else [CONST con]
        | h::t -> (match h with
                   | CONST i -> cal_sum_const(t, con + i)
                   | _ -> h::cal_sum_const(t, con)) in

    let rec cal_sum_var (l, var, cnt: (ae list) * ae * int): ae list =
        match l with
        | [] -> if (cnt = 0) then [] else [TIMES[CONST cnt; var]]
        | h::t -> if (h = var) then cal_sum_var(t, var, cnt + 1)
                  else (match h with
                        | TIMES l_t -> 



    match a with
    | CONST i -> CONST i
    | VAR s -> VAR s
    | POWER (s, i) -> (match i with
                       | 0 -> CONST 1
                       | 1 -> VAR s
                       | _ -> POWER(s, i))
    | TIMES l -> let l_m = rmv1 (t_modify l) in
            (match l_m with
                  | [] -> CONST 1
                  | h::[] -> h
                  | _ -> if (scan0 l_m) then CONST 0
                         else TIMES (uni_times l_m))
    | SUM l -> let l_m = rmv0 (t_modify l) in
            (match l_m with
                  | [] -> CONST 0
                  | h::[] -> h
                  | _ -> SUM (uni_sum l_m))*)