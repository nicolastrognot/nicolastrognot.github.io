type 'a my_list = Item of ('a * 'a my_list)
		| Empty
;;

let rec length = function
	| Empty -> 0
	| Item(a, b) -> (length b) + 1
;;

let hd = function
	| Empty -> raise (Failure "hd")
	| Item(a, b) -> a
;;

let tl = function
	| Empty -> raise (Failure "tl")
	| Item(a, b) -> b
;;

let rec nth my_list n = match my_list with
	| Empty -> raise (Failure "nth")
	| Item(a, b) -> if (n < 0) then raise (Invalid_argument "List.nth") else
			if (n == 0) then a else nth b (n - 1)
;;

let cons elem my_list = Item(elem, my_list)
;;

let rev my_list =
	let rec revv neww = function
		| Empty -> neww
		| Item(a, b) -> revv (Item(a, neww)) b
	in revv Empty my_list
;;

let append left right =
	let rec appendd left right = match left with
		| Empty -> right
		| Item(a, b) -> appendd b (Item(a, right))
	in appendd (rev left) right
;;

let rev_append left right = append (rev left) right
;;

let rec flatten = function
	| Empty -> Empty
	| Item(left, right) -> append left (flatten right)
;;

let concat = flatten

let rec iter func = function
	| Empty -> ()
	| Item(a, b) -> begin
			func a;
			iter func b;
			end
;;

let map func my_list =
	let rec mapp funcc neww = function
		| Empty -> neww
		| Item(value, next) -> mapp funcc (Item((func value), neww)) next
        in mapp func Empty (rev my_list)
;;

let rec exists func = function
	| Empty -> false
	| Item(a, b) -> if (func a) then true else exists func b
;;

let rec for_all func = function
	| Empty -> true
	| Item(a, b) -> func a &&  for_all func b
;;

let rec mem elem = function
	| Empty -> false
	| Item(a, b) -> if (a = elem) then true else mem elem b
;;

let rec memq elem = function
	| Empty -> false
	| Item(a, b) -> if (a == elem) then true else memq elem b
;;

let filter func my_list =
	let rec filterr func neww = function
		| Empty -> rev neww
		| Item(a, b) -> if (func a) then filterr func (Item(a, neww)) b else filterr func neww b
	in filterr func Empty my_list
;;

let split d =
	let rec splitt nleft nright = function
		| Empty -> (rev nleft, rev nright)
		| Item((a, b), c) -> splitt (Item(a, nleft)) (Item(b, nright)) c
	in splitt Empty Empty d
;;

let combine left right =
	let rec combinee neww left right = match (left, right) with
		| (Empty, Empty) -> neww
		| (Item(a, b), Item(c, d)) -> combinee (Item((a, c), neww)) b d
                | _ -> raise (Invalid_argument "List.combine")
	in combinee Empty (rev left) (rev right)
;;
 
let partition func my_list = 
        let rec partitionn func l1 l2 = function
                | Empty -> (rev l1, rev l2)
                | Item(a, b) -> if (func a) then partitionn func (Item(a, l1)) l2 b else
                                               partitionn func l1 (Item(a, l2)) b
        in partitionn func Empty Empty my_list

let find_all = filter
;;

(* Bonus *)

let rec assoc a = function
        | Empty -> raise (Not_found)
        | Item((b, c), d) -> if (a = b) then c else assoc a d
;;

let rec assq a = function
        | Empty -> raise (Not_found)
        | Item((b, c), d) -> if (a == b) then c else assq a d
;;

let rec mem_assoc a = function
        | Empty -> false
        | Item((b, c), d) -> if (a = b) then true else mem_assoc a d
;;

let rec mem_assq a = function
        | Empty -> false
        | Item((b, c), d) -> if (a == b) then true else mem_assq a d
;;

let remove_assoc a l =
        let rec remove_assocc neww a = function
                | Empty -> neww
                | Item((b, c), d) -> if (a = b) then remove_assocc neww a d
                                else remove_assocc (Item((b, c), neww)) a d
        in remove_assocc Empty a l
;;

let remove_assq a l =
        let rec remove_assqq neww a = function
                | Empty -> neww
                | Item((b, c), d) -> if (a == b) then remove_assqq neww a d
                        else remove_assqq (Item((b, c), neww)) a d
        in remove_assqq Empty a l
;;

let rec find l = function
        | Empty -> raise (Not_found)
        | Item(b, c) -> if (l b) then b else find l c
;;
