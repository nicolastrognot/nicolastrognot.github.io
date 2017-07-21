module type HELPER =
  sig
    val strncmp	: string -> string -> int -> bool
  end

module Helper : HELPER =
  struct
    let strncmp s1 s2 n = match s2 with
      | x -> try
	     if (x = String.sub s1 0 n) then true else false
	   with _ -> false
  end
