module type Queue = 
sig
  type element
  type queue
  exception EMPTY_Q
  val emptyq: queue
  val enq: queue * element -> queue
  val deq: queue -> element * queue
end

module StringSetQ : Queue with type element = string = 
struct 
	type element = string
        type queue = Q of element list * element list
        exception EMPTY_Q

        let emptyq: queue = Q ([], [])

        let enq: queue * element -> queue =
                fun (q, e) ->
		match q with | Q (l, r) -> if (List.mem e (List.append l r)) then Q (l, r) else Q (e::l, r)

        let rec deq: queue -> element * queue =
                fun q ->
                match q with
                | Q ([], []) -> raise EMPTY_Q
                | Q (l, r) -> (match r with | [] -> deq (Q ([], List.rev l)) | h::t -> (h, Q (l, t)))
end

module StringSetQQ : Queue with type element = StringSetQ.queue = 
struct 
        type element = StringSetQ.queue
        type queue = Q of element list * element list
        exception EMPTY_Q

        let emptyq: queue = Q ([], [])

        let enq: queue * element -> queue =
                fun (q, e) ->
		let rec same_q: element * element -> bool =
			fun (el1, el2) -> 
			if ((el1 = StringSetQ.emptyq) && (el2 = StringSetQ.emptyq)) then true
			else if ((el1 = StringSetQ.emptyq) || (el2 = StringSetQ.emptyq)) then false
			else let (e1, q1) = (StringSetQ.deq el1) in let (e2, q2) = (StringSetQ.deq el2) in
			if (e1 = e2) then (same_q (q1, q2)) else false in
                match q with | Q (l, r) -> if (List.exists (fun x -> same_q (x, e)) (List.append l r)) then Q (l, r) else Q (e::l, r)

        let rec deq: queue -> element * queue =
                fun q ->
                match q with
                | Q ([], []) -> raise EMPTY_Q
                | Q (l, r) -> (match r with | [] -> deq (Q ([], List.rev l)) | h::t -> (h, Q (l, t)))
end
