module type Queue = 
sig
  type element
  type queue
  exception EMPTY_Q
  val emptyq: queue
  val enq: queue * element -> queue
  val deq: queue -> element * queue
end

module StringQ : Queue with type element = string = 
struct
	type element = string
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

module StringQQ : Queue with type element = StringQ.queue = 
struct 
	type element = StringQ.queue
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
