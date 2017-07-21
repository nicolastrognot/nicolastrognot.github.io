module type TMDATES =
  sig
    type date
    val	newDate		:	Unix.tm -> date
    val	getDate		:	date -> Unix.tm
    val printDate	:	date -> unit
    val printDateChannel:	out_channel -> date -> unit
    val	setDate		:	date -> string -> date
    val setHour		:	date -> string -> date
    val addMinutes	:	date -> float    -> date
  end

module Tmdates : TMDATES
