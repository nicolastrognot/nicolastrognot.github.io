module type HELPER =
	sig
		val strncmp	: string -> string -> int -> bool
	end

module Helper : HELPER
