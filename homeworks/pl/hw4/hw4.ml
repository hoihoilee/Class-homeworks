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




let idtest (h) = 
    match h with 
    (id, gift) -> 
    match id with 
    | A -> "A" 
    | B -> "B" 
    | C -> "C" 
    | D -> "D" 
    | E -> "E" 

let gifttest (h) = 
    match h with 
    | (id, gift) -> gift 

let rec printlisttest (gift) = 
    match gift with 
    | [] -> "]" 
    | h::t -> (string_of_int h) ^ printlisttest(t) 

let rec printfinaltest (result) = 
    match result with 
    | [] -> () 
    | h::t -> print_string ("(" ^ idtest(h) ^ ",[" ^ printlisttest(gifttest(h)) ^");") 
    
let check1 = [(A, Items[1;2]::[]); (B, []); (C, []); (D, []); (E, [])] 
let check2 = [(A, Items[1;2]::Items[3;4]::[]); (B, []); (C, []); (D, []); (E, [])] 
let check3 = [(A,Items[1;2]::Items[1;4]::[]);(C,Items[3;4]::[]); (B, []); (D, []); (E, [])] 
let check4 = [(A,Items[1;2]::Items[1;4]::[]);(B, Same A::[]);(C,Items[3;4]::[]); (D, []); (E, [])]
let check5 = [(A,Items[1;2]::Items[1;4]::[]);(B, Same C::[]);(C,Items[3;4]::[]); (D, []); (E, [])]
let check6 = [(A,Same B::[]);(B, Same C::[]);(C, Same D::[]);(D, Same E::[]);(E, Same A::[])] 
let check7 = [(A, Items [1;2;3]::[]); (B,Same A::Items [4]::[]); (C, []); (D, []); (E, [Same D])] 

let check8 = [(A, [Items[1;2]]); (B, [Same A]); (C, []); (D, []); (E, [])] 
let check9 = [(A, [Items[1;2]]); (B, [Same C]);(C, [Items[2;3]]); (D, []); (E, [])] 
let check10 = [(A, [Items[1;2]]); (B, [Items[4];Same C]);(C, [Items[2;3]]); (D, []); (E, [])] 
let check11 = [(A, [Items[1;2]]); (B, [Same C;Items[4]]);(C, [Items[2;3]]); (D, []); (E, [])] 
let check12 = [(A, [Items[1;2]; Same C]); (B, [Same A]);(C, [Items[2;3]]); (D, []); (E, [])] 
let check13 = [(A, [Except (Items[1;2;3], [1;2])]); (B, []); (C, []); (D, []); (E, [])] 
let check14 = [(A, [Items[1;2;3]]);(B, [Except (Same A, [1])]); (C, []); (D, []); (E, [])] 
let check15 = [(A, [Common (Items[1;2], Items[2;3])]); (B, []); (C, []); (D, []); (E, [])] 
let check16 = [(A, [Items [5;6]; Common(Items [1;2], Items [2;3])]); (B, []); (C, []); (D, []); (E, [])] 

let check17 = [(A, [Items[1;2;3;4;5]]);(B,[Same D]); (C,[Common (Common (Except (Items [1;2;3;4;5], [3;4]), Same B), Same A)]);(D, [Items [1;3;5;7;9]]); (E, [])] 

let _ = 
if (shoppingList (check1) = [(A,[1;2]);(B,[]);(C,[]);(D,[]);(E,[])])          then print_endline("1") else printfinaltest(shoppingList(check1)); 
if (shoppingList (check2) = [(A,[1;2;3;4]);(B,[]);(C,[]);(D,[]);(E,[])])       then print_endline("2") else printfinaltest(shoppingList(check2)); 
if (shoppingList (check3) = [(A,[1;2;4]);(B,[]);(C,[3;4]);(D,[]);(E,[])])       then print_endline("3") else printfinaltest(shoppingList(check3)); 
if (shoppingList (check4) = [(A,[1;2;4]);(B,[1;2;4]);(C,[3;4]);(D,[]);(E,[])])    then print_endline("4") else printfinaltest(shoppingList(check4)); 
if (shoppingList (check5) = [(A,[1;2;4]);(B,[3;4]);(C,[3;4]);(D,[]);(E,[])])    then print_endline("5") else printfinaltest(shoppingList(check5)); 
if (shoppingList (check6) = [(A,[]);(B,[]);(C,[]);(D,[]);(E,[])])             then print_endline("6") else printfinaltest(shoppingList(check6)); 
if (shoppingList (check7) = [(A,[1;2;3]);(B,[1;2;3;4]);(C,[]);(D,[]);(E,[])])   then print_endline("7") else printfinaltest(shoppingList(check7)); 
if (shoppingList (check8) = [(A,[1;2]);(B,[1;2]);(C,[]);(D,[]);(E,[])])       then print_endline("8") else printfinaltest(shoppingList(check8)); 
if (shoppingList (check9) = [(A,[1;2]);(B,[2;3]);(C,[2;3]);(D,[]);(E,[])])       then print_endline("9") else printfinaltest(shoppingList(check9)); 
if (shoppingList (check10) = [(A,[1;2]);(B,[2;3;4]);(C,[2;3]);(D,[]);(E,[])])    then print_endline("10") else printfinaltest(shoppingList(check10)); 
if (shoppingList (check11) = [(A,[1;2]);(B,[2;3;4]);(C,[2;3]);(D,[]);(E,[])])    then print_endline("11") else printfinaltest(shoppingList(check11)); 
if (shoppingList (check12) = [(A,[1;2;3]);(B,[1;2;3]);(C,[2;3]);(D,[]);(E,[])]) then print_endline("12") else printfinaltest(shoppingList(check12)); 
if (shoppingList (check13) = [(A,[3]);(B,[]);(C,[]);(D,[]);(E,[])])          then print_endline("13") else printfinaltest(shoppingList(check13)); 
if (shoppingList (check14) = [(A,[1;2;3]);(B,[2;3]);(C,[]);(D,[]);(E,[])])       then print_endline("14") else printfinaltest(shoppingList(check14)); 
if (shoppingList (check15) = [(A,[2]);(B,[]);(C,[]);(D,[]);(E,[])])          then print_endline("15") else printfinaltest(shoppingList(check15)); 
if (shoppingList (check16) = [(A,[2;5;6]);(B,[]);(C,[]);(D,[]);(E,[])])       then print_endline("16") else printfinaltest(shoppingList(check16)); 
if (shoppingList (check17) = [(A,[1;2;3;4;5]);(B,[1;3;5;7;9]);(C,[1;5]);(D,[1;3;5;7;9]);(E,[])]) then print_endline("17") else printfinaltest(shoppingList(check17)); 

let emptyL = [(A, []); (B, []); (C, []); (D, []); (E, [])] in 
assert ((shoppingList [ 
            (A, []); (B, []); (C, []); (D, []); (E, []); 
            ]) = emptyL); 
print_endline "b"; 

assert ((shoppingList [ 
            (A, [Same B]); (B, [Same C]); (C, [Same D]); (D, [Same E]); (E, [Same A]); 
            ]) = emptyL); 
print_endline "c"; 

assert ((shoppingList [ 
            (A, [Items [1;2;3]]); (B, [Items [2;3;4]]); 
            (C, [Items [3;4;1]]); (D, [Items [4;1;2]]); 
            (E, [Items [1;2;3;1;2;3]]); 
            ]) = [(A, [1; 2; 3]); (B, [2; 3; 4]); (C, [1; 3; 4]); (D, [1; 2; 4]); (E, [1; 2; 3])]); 
print_endline "d"; 

assert ((shoppingList [ 
            (A, [Items [1;2;3]]); 
            (B, [Same A]); 
            (C, [Same A; Items[1;2]]); 
            (D, [Same A; Items[4]]); 
            (E, [Same D]); 
            ]) = [(A, [1; 2; 3]); (B, [1; 2; 3]); (C, [1; 2; 3]); (D, [1; 2; 3; 4]); (E, [1; 2; 3; 4])]); 
print_endline "e"; 

assert ((shoppingList [ 
            (A, [Common (Items [1;2;3], Items [2;1;3])]); 
            (B, [Common (Items [2;1;3], Items [5;6;1;4;2;3])]); 
            (C, [Common (Items [1;2;3], Items [4;5;6])]); 
            (D, [Common (Items [3;2;1], Items [1])]); 
            (E, [Common (Items [1;2;3], Items [])]); 
            ]) = [(A, [1; 2; 3]); (B, [1; 2; 3]); (C, []); (D, [1]); (E, [])]); 
print_endline "f"; 

assert ((shoppingList [ 
            (B, [Common (Items [2;1;3], Items [5;6;1;4;2;3])]); 
            (E, [Common (Items [], Items [])]); 
            (D, [Common (Items [1], Items [1])]); 
            (A, []); (C, []); 
            ]) = [(A, []); (B, [1; 2; 3]); (C, []); (D, [1]); (E, [])]); 
print_endline "g"; 

assert ((shoppingList [ 
            (A, [Except (Items [3;2;1], [3;2;1])]); 
            (B, [Except (Items [2;1;3], [])]); 
            (C, [Except (Items [2;1;3], [1;2;3;4;5;6])]); 
            (D, [Except (Items [], [2;1;3])]); 
            (E, [Except (Items [], [])]); 
            ]) = [(A, []); (B, [1; 2; 3]); (C, []); (D, []); (E, [])]); 
print_endline "h"; 

assert ((shoppingList [ 
            (A, [Common (Common (Same B, Same C), Common (Same D, Same E))]); 
            (B, [Common (Same C, Common (Same D, Except (Same E, [5])))]); 
            (C, [Same D; Items[7;8]]); 
            (D, [Except (Same E, [1;2;3])]); 
            (E, [Items [1;2;3;4;5]]); 
            ]) = [(A, [4]); (B, [4]); (C, [4; 5; 7; 8]); (D, [4; 5]); (E, [1; 2; 3; 4; 5])]); 
print_endline "i"; 

assert ((shoppingList [ 
            (A, [Same B; Same C]); 
            (B, [Except (Same C, [1;2;3]); Same D]); 
            (C, [Items [1;2;3]; Items [3;4;5]; Common (Same A, Items [6;7])]); 
            (D, [Same E]); 
            (E, [Same D; Items[6;8]]); 
            ]) = [(A, [1; 2; 3; 4; 5; 6; 8]); (B, [4; 5; 6; 8]); (C, [1; 2; 3; 4; 5; 6]); (D, [6; 8]); (E, [6; 8])]); 
print_endline "j"; 

assert ((shoppingList [ 
            (A, [Common (Same B, Common (Except (Items [1;2;3;4;5], [1;3;5]), Same C)); Items [2;4;8]]); 
            (B, [Except (Except (Except (Same A, [1]),[1;2]),[3]); Items [3;6;9]]); 
            (C, [Same A; Same B; Same D; Same E]); 
            (D, [Items [10]; Common (Same A, Same D); Items [5]]); 
            (E, [Common (Same C, Common (Same A, Common (Same D, Same B)))]) 
            ]) = [(A, [2; 4; 8]); (B, [3; 4; 6; 8; 9]); (C, [2; 3; 4; 5; 6; 8; 9; 10]); (D, [5; 10]); (E, [])]); 
print_endline "k"; 

assert ((shoppingList [ 
            (A, [Items [1;2;3;1;2;3]; Same D; Items [1;2;3;4]]); 
            (D, [Items [5;5;5;5;5]]); 
            (C, []); 
            (E, [Except (Items [1;2;3;1;2;3], [1;2;3])]); 
            (B, []); 
            ]) = [(A, [1; 2; 3; 4; 5]); (B, []); (C, []); (D, [5]); (E, [])]); 
print_endline "l"; 

print_endline "all passed";