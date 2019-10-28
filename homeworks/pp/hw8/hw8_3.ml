module type Queue = 
sig
  type element
  type queue
  exception EMPTY_Q
  val emptyq: queue
  val enq: queue * element -> queue
  val deq: queue -> element * queue
end

module type ArgTy = 
sig
  type t
  val is_eq : t -> t -> bool
end

module QueueMake (Arg: ArgTy) 
  : Queue with type element = Arg.t =
struct
        type element = Arg.t
        type queue = Q of element list * element list
        exception EMPTY_Q

        let emptyq: queue = Q ([], [])

        let enq: queue * element -> queue =
                fun (q, e) ->
                match q with | Q (l, r) -> Q (e::l, r)

        let rec deq: queue -> element * queue =
                fun q ->
                match q with
                | Q ([], []) -> raise EMPTY_Q
                | Q (l, r) -> (match r with | [] -> deq (Q ([], List.rev l)) | h::t -> (h, Q (l, t)))
end
