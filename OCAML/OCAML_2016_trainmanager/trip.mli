open Train
open Tmdates

module type TRIP =
  sig
    type trip
    val newTrip		: (int * Train.train * Tmdates.date * (*string **) string list) -> trip
    val getId		: trip -> int
    val getTrain	: trip -> Train.train
    val getDate		: trip -> Tmdates.date
    (*val getHour		: trip -> string*)
    val getStations	: trip -> string list
    val setId		: trip -> trip list -> trip
    val setTrain	: trip -> Train.train -> trip
    val	setDate		: trip -> string -> trip
    val setHour		: trip -> string -> trip
    val setStations	: trip -> string list -> trip
  end

module Trip : TRIP
