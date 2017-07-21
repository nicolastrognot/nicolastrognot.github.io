module type TRAIN =
  sig
    type t
    val length : t -> int
  end

module type TRIP =
  sig
    type t_in
    type t_out
    val trip : t_in -> t_out
    val untrip : t_out -> t_in
  end

module type MAKETRIP = functor (Train : TRAIN) -> TRIP with type t_in = Train.t

module MakeTrip : MAKETRIP = functor (Train : TRAIN) ->
  struct
    type t_in = Train.t
    type t_out = (Train.t * int)
    let trip v = (v, Train.length v)
    let untrip (v, _) = v
  end

module StringTrip = MakeTrip (String)
