type nat = ZERO | SUCC of nat

let rec natadd (n1, n2: nat * nat): nat =
  match n1 with
  | ZERO -> n2
  | SUCC na1 -> SUCC (natadd(na1, n2))

let rec natmul (n1, n2: nat * nat): nat =
  match n1 with
  | ZERO -> ZERO
  | SUCC na1 -> natadd(natmul(na1, n2), n2)
