module type LINK =
  sig
    type link
    val newLink			: (string * string * int) -> link
    val getFirstStation		: link -> string
    val getSecondStation	: link -> string
    val getDistance		: link -> int
  end

module Link : LINK
