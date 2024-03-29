type heap = EMPTY
  | NODE of rank * value * heap * heap
and rank = int
and value = int

exception EmptyHeap

let rank h =
  match h with
  | EMPTY -> (-1)
  | NODE(r,_,_,_) -> r

let shake(x, lh, rh) =
  if (rank lh) >= (rank rh)
  then NODE(rank rh + 1, x, lh, rh)
  else NODE(rank lh + 1, x, rh, lh)

let rec merge(lh, rh) =
  match (lh, rh) with
  | (EMPTY, EMPTY) -> EMPTY
  | (EMPTY, _) -> rh
  | (_, EMPTY) -> lh
  | (NODE(lr,lv,llh,lrh),NODE(rr,rv,rlh,rrh)) ->
      if (lv > rv) then shake(rv, rlh, merge(rrh, lh))
      else shake(lv, llh, merge(lrh, rh))

let insert(x, h) = merge(h, NODE(0, x, EMPTY, EMPTY))

let findMin h =
  match h with
  | EMPTY -> raise(EmptyHeap)
  | NODE(_,x,_,_) -> x

let deleteMin h =
  match h with
  | EMPTY -> raise(EmptyHeap)
  | NODE(_,x,lh,rh) -> merge(lh, rh)
