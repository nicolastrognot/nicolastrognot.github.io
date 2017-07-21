open Link

exception Unknown_Train_Type

type trainType = TGV | Thalys | Eurostar | Unknown

module type TRAIN =
  sig
    type train
    val newTrain		: (trainType * int * Link.link list) -> train
    val getSpeed		: train -> int
    val getType			: train -> trainType
    val getList			: train -> Link.link list
    val trainType_to_string	: train -> string
  end

module Train : TRAIN =
  struct
    type train = (trainType * int * Link.link list)
    let newTrain (t, s, l) = (t, s, l)
    let getSpeed (_, s, _) = s
    let getType (t, _, _) = t
    let getList (_, _, l) = l
    let trainType_to_string t =
      if (getType t == TGV) then "TGV" else
        if (getType t == Thalys) then "Thalys" else
          if (getType t == Eurostar) then "Eurostar" else
	    raise Unknown_Train_Type;
  end
