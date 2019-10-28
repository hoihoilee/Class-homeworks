let same_list a b =
    (List.for_all (fun x -> List.mem x b) a) && (List.for_all (fun x -> List.mem x a) b)

let _ = if ("c" = "b") then print_endline "y"
