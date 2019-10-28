type require = id * (cond list)
and cond =
  Items of gift list
  | Same of id
  | Common of cond * cond
  | Except of cond * gift list
and gift = int
and id = A | B | C | D | E

let rec new_pack (g_pack, want : (id * gift list) list * cond): gift list =
  let rec common_gift (pack, g_list : gift list * gift list): gift list =
    if ((pack = []) || (g_list = [])) then []
    else if (List.hd pack > List.hd g_list) then
      common_gift(pack, List.tl g_list)
    else if (List.hd pack < List.hd g_list) then
      common_gift(List.tl pack, g_list)
    else
      (List.hd pack)::common_gift(List.tl pack, List.tl g_list) in

  let rec except_gift (pack, g_list : gift list * gift list): gift list =
    if ((pack = []) || (g_list = [])) then pack
    else if (List.hd pack > List.hd g_list) then
      except_gift(pack, List.tl g_list)
    else if (List.hd pack < List.hd g_list) then
      (List.hd pack)::except_gift(List.tl pack, g_list)
    else
      except_gift(List.tl pack, List.tl g_list) in

  match want with
  | Items g_list -> List.sort_uniq compare g_list
  | Same him -> let (_, his_pack) = List.hd (List.find_all (fun (a, b) -> a = him) g_pack) in
                his_pack
  | Common (c1, c2) -> common_gift(new_pack(g_pack, c1), new_pack(g_pack, c2))
  | Except (c, g_list) -> except_gift(new_pack(g_pack, c), List.sort_uniq compare g_list)

let his_wants (name, wants, g_pack : id * cond list * (id * gift list) list): (id * gift list) list =
  let rec new_packs (w_list : cond list): gift list =
    match w_list with
    | [] -> []
    | h::t -> List.sort_uniq compare (List.append (new_pack(g_pack, h)) (new_packs t)) in

  let rec give_him (t_g_pack, pack : (id * gift list) list * gift list): (id * gift list) list =
    let (t_name, _) = List.hd t_g_pack in
    if (t_name = name) then (name, pack)::(List.tl t_g_pack)
    else (List.hd t_g_pack)::give_him(List.tl t_g_pack, pack) in

  give_him(g_pack, new_packs wants)

let rec cond_iter (r_list, g_pack : require list * (id * gift list) list): (id * gift list) list =
  match r_list with
  | [] -> g_pack
  | h::t -> let (name, wants) = h in
            cond_iter(t, his_wants(name, wants, g_pack))

let shoppingList (r_list : require list): (id * gift list) list =
  let rec helper (g_pack : (id * gift list) list): (id * gift list) list =
    let new_g_pack = cond_iter(r_list, g_pack) in
    if (g_pack = new_g_pack) then new_g_pack
    else helper new_g_pack in

  let g_pack = [(A, []);(B, []);(C, []);(D, []);(E, [])] in
  helper g_pack