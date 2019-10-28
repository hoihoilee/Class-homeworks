(*
 * SNU 4190.310 Programming Languages 
 * Homework "Exceptions are sugar" Skeleton
 *)

open Xexp

(* TODO : Implement this function *)

let count = ref 0

let new_name () =
  let _ = count := !count + 1 in
  "x_" ^ (string_of_int !count)

let rec cps' exp =
  let k1 = new_name () in
  let k2 = new_name () in
  match exp with
  | Num n -> Fn (k1, Fn (k2, App (Var k1, Num n)))
  | Var x -> Fn (k1, Fn (k2, App (Var k1, Var x)))
  | Fn (x, e) -> Fn (k1, Fn (k2, App (Var k1, Fn (x, cps' e))))
  | App (e1, e2) -> let v1 = new_name() in
                    let v2 = new_name() in
                    Fn (k1, Fn (k2, App (App (cps' e1, 
                    Fn (v1, App (App (cps' e2, 
                    Fn (v2, App (App (App (Var v1, Var v2), Var k1), Var k2))), Var k2))), Var k2)))
  | If (e1, e2, e3) -> let v1 = new_name() in
                       let v2 = new_name() in
                       let v3 = new_name() in
                       Fn (k1, Fn (k2, App (App (cps' e1,
                       Fn (v1, If (Var v1, App (App (cps' e2,
                       Fn (v2, App (Var k1, Var v2))), Var k2), App (App (cps' e3,
                       Fn (v3, App (Var k1, Var v3))), Var k2)))), Var k2)))
  | Equal (e1, e2) -> let v1 = new_name() in
                      let v2 = new_name() in
                      Fn (k1, Fn (k2, App (App (cps' e1,
                      Fn (v1, App (App (cps' e2,
                      Fn (v2, App (Var k1, Equal (Var v1, Var v2)))), Var k2))), Var k2)))
  | Raise e -> Fn (k1, Fn (k2, App (App (cps' e, Var k2), Var k2)))
  | Handle (e1, n, e2) -> let v = new_name() in
                          Fn (k1, Fn (k2, App (App (cps' e1, Var k1),
                          Fn (v, If (Equal (Var v, Num n),
                          App (App (cps' e2, Var k1), Var k2), App (Var k2, Var v))))))

let removeExn : xexp -> xexp = fun e ->
  let x1 = new_name() in
  let x2 = new_name() in
  App (App (cps' e, Fn (x1, Var x1)), Fn (x2, Num 201812))
