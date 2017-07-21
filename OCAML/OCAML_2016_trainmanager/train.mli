open Link

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

module Train : TRAIN
