module type LINK =
  sig
    type link
    val newLink			: (string * string * int) -> link
    val getFirstStation		: link -> string
    val getSecondStation	: link -> string
    val getDistance		: link -> int
  end
    
module Link : LINK =
  struct
    type link = (string * string * int)
    let newLink (first, second, distance) = (first, second, distance)
    let getFirstStation (first, _, _) = first
    let getSecondStation (_, second, _) = second
    let getDistance (_, _, distance) = distance
  end
