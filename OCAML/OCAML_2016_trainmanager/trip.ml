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

module Trip : TRIP =
  struct
    type trip = (int * Train.train * Tmdates.date * (*string **) string list)
    let newTrip		(i, t, d, s) = (i, t, d, s)
    let getId		(i, _, _, _) = i
    let getTrain	(_, t, _, _) = t
    let getDate		(_, _, d, _) = d
    (*let getHour		(_, _, _, h, _) = h*)
    let getStations (_, _, _, s) = s
    let setId		(i, t, d, s) l =
      let rec get_max max = function
	| [] -> max
	| a::b -> if (getId a > max) then get_max (getId a) b else
		    get_max max b
      in let aux (i, t, d, s) = ((get_max 1000 l) + 1, t, d, s)
	 in aux (i, t, d, s)
    let setTrain	(i, t, d, s) tn = (i, tn, d, s)
    let setDate		(i, t, d, s) dn = (i, t, Tmdates.setDate d dn, s)
    let setHour		(i, t, d, s) hn = (i, t, Tmdates.setHour d hn, s)
    let setStations	(i, t, d, s) sn = (i, t, d, sn) 
  end
