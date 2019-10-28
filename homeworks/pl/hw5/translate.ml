(*
 * SNU 4190.310 Programming Languages 
 * K-- to SM5 translator skeleton code
 *)

open K
open Sm5
module Translator = struct

  (* TODO : complete this function  *)
  let rec trans : K.program -> Sm5.command = function
    | K.NUM i -> [Sm5.PUSH (Sm5.Val (Sm5.Z i))]
    | K.TRUE -> [Sm5.PUSH (Sm5.Val (Sm5.B true))]
    | K.FALSE -> [Sm5.PUSH (Sm5.Val (Sm5.B false))]
    | K.UNIT -> [Sm5.PUSH (Sm5.Val (Sm5.Unit))]
    | K.VAR x -> [Sm5.PUSH (Sm5.Id x); Sm5.LOAD] 
    | K.ADD (e1, e2) -> trans e1 @ trans e2 @ [Sm5.ADD]
    | K.SUB (e1, e2) -> trans e1 @ trans e2 @ [Sm5.SUB]
    | K.MUL (e1, e2) -> trans e1 @ trans e2 @ [Sm5.MUL]
    | K.DIV (e1, e2) -> trans e1 @ trans e2 @ [Sm5.DIV]
    | K.EQUAL (e1, e2) -> trans e1 @ trans e2 @ [Sm5.EQ]
    | K.LESS (e1, e2) -> trans e1 @ trans e2 @ [Sm5.LESS]
    | K.NOT e -> trans e @ [Sm5.NOT]
    | K.ASSIGN (x, e) -> trans e @ [Sm5.PUSH (Sm5.Id x); Sm5.STORE] @ trans (K.VAR x)
    | K.SEQ (e1, e2) -> trans e1 @ [Sm5.POP] @ trans e2
    | K.IF (e1, e2, e3) -> trans e1 @ [Sm5.JTR (trans e2, trans e3)]
    | K.WHILE (e1, e2) -> let while_f = "@while_f" in
                          let while_x = "@while_x" in
                          trans (K.LETF (while_f, while_x,
                          K.IF (e1, K.SEQ (e2,
                          K.CALLR (while_f, while_x)), K.UNIT),
                          K.CALLV (while_f, K.UNIT)))
    | K.FOR (i, e1, e2, e3) -> let for_i = "@for_i" in
                               let for_e = "@for_e" in
                               trans (K.LETV (for_i, e1,
                                      K.LETV (for_e, e2,
                                      K.WHILE (K.NOT (K.LESS (K.VAR for_e, K.VAR for_i)),
                                      K.SEQ (K.ASSIGN (i, K.VAR for_i),
                                      K.SEQ (K.ASSIGN (for_i, K.ADD (K.VAR for_i, K.NUM 1)),
                                      e3))))))
    | K.LETV (x, e1, e2) ->
      trans e1 @ [Sm5.MALLOC; Sm5.BIND x; Sm5.PUSH (Sm5.Id x); Sm5.STORE] @
      trans e2 @ [Sm5.UNBIND; Sm5.POP]
    | K.LETF (f, x, e1, e2) -> [Sm5.PUSH (Sm5.Fn (x, [Sm5.BIND f] @ trans e1)); Sm5.BIND f] @ trans e2 @ [Sm5.UNBIND; Sm5.POP]
    | K.CALLV (f, e) -> let call_e = "@call_e" in
                        trans (K.LETV (call_e, e, K.CALLR (f, call_e)))
    | K.CALLR (f, x) -> [Sm5.PUSH (Sm5.Id f); Sm5.PUSH (Sm5.Id f); Sm5.PUSH (Sm5.Id x); Sm5.LOAD; Sm5.PUSH (Sm5.Id x); Sm5.CALL]
    | K.READ x -> [Sm5.GET; Sm5.PUSH (Sm5.Id x); Sm5.STORE; Sm5.PUSH (Sm5.Id x); Sm5.LOAD]
    | K.WRITE e -> let write_t = "@write_t" in
                   trans e @ [Sm5.MALLOC; Sm5.BIND write_t; Sm5.PUSH (Sm5.Id write_t); Sm5.STORE;
                   Sm5.PUSH (Sm5.Id write_t); Sm5.LOAD; Sm5.PUT; Sm5.PUSH (Sm5.Id write_t); Sm5.LOAD; Sm5.UNBIND; Sm5.POP]

end
