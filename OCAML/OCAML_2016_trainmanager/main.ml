(* Init *)
open Train
open Link
open Helper
open Trip
open Tmdates
open Printf

exception Quit
exception Unknown_Train_Type
exception Error_During_Trip_Creation
exception Unknown_Command
exception Wrong_number_params_delete_trip
exception Bad_Date_Format
exception List_Invalid_Stations
exception Bad_Town_For_This_Train

(* TGV Init *)
let _TGV = Train.newTrain (TGV, 230,
			   [Link.newLink ("Paris", "Lyon", 427);
			    Link.newLink ("Dijon", "Lyon", 192);
			    Link.newLink ("Paris", "Lille", 225);
			    Link.newLink ("Paris", "Nancy", 327);
			    Link.newLink ("Dijon", "Nancy", 226);
			    Link.newLink ("Brest", "Rennes", 248);
			    Link.newLink ("Rennes", "Le Mans", 163);
			    Link.newLink ("Le Mans", "Nantes", 183);
			    Link.newLink ("Le Mans", "Paris", 201);
			    Link.newLink ("Lyon", "Marseille", 325);
			    Link.newLink ("Paris", "Bordeaux", 568);
			    Link.newLink ("Paris", "Le Havre", 230);
			    Link.newLink ("Nancy", "Strasbourg", 149);
			    Link.newLink ("Paris", "Strasbourg", 449);
			    Link.newLink ("Toulouse", "Bordeaux", 256);
			    Link.newLink ("Marseille", "Montpellier", 176);
			    Link.newLink ("Montpellier", "Toulouse", 248);
			    Link.newLink ("Dijon", "Strasbourg", 309)]
			  );;

(* Thalys Init *)
let _Thalys = Train.newTrain (Thalys, 210,
			      [Link.newLink ("Paris", "Lille", 225);
			       Link.newLink ("Lille", "Brussels", 106);
			       Link.newLink ("Brussels", "Liege", 104);
			       Link.newLink ("Liege", "Cologne", 118);
			       Link.newLink ("Cologne", "Essen", 81);
			       Link.newLink ("Brussels", "Amsterdam", 211)]
			     );;

(* Eurostar Init *)
let _Eurostar = Train.newTrain (Eurostar, 160,
				[Link.newLink ("Paris", "Lille", 225);
				 Link.newLink ("Lille", "London", 269);
				 Link.newLink ("Lille", "Brussels", 106)]
			       );;

let deleteTrip trips str =
  let find_and_delete trips to_delete =
    let rec aux new_list to_delete = function
      | [] -> List.rev new_list
      | value::next -> if (Train.trainType_to_string (Trip.getTrain value))^(string_of_int (Trip.getId value)) = to_delete then
			 aux new_list to_delete next else aux (value::new_list) to_delete next
    in
    aux [] to_delete trips
  in
  let rec check_param idx trips = function
    | [] -> raise Wrong_number_params_delete_trip
    | value::next -> if idx = 1 && next = [] then find_and_delete trips value else
		       check_param (idx + 1) trips next
  in
  check_param 0 trips (Str.split (Str.regexp "[ \t]+") str)
;;

let saveTrips trips =
  let oc =
    open_out "saved.txt"
  in
  let rec aux init = function
    | [] -> close_out oc; init
    | value::next ->	fprintf oc "%s " (Train.trainType_to_string (Trip.getTrain value));
			fprintf oc "%d\n" (Trip.getId value);
			let rec printStations idx trip links date lastStation = function
			  | [] -> ()
			  | value::next -> fprintf oc "%s" value;
					   let rec getDistance first second = function
					     | [] -> raise List_Invalid_Stations
					     | value::next -> if (Link.getFirstStation value = first && Link.getSecondStation value = second) ||
								   (Link.getFirstStation value = second && Link.getSecondStation value = first) then
								Link.getDistance value else getDistance first second next
					   in
					   let print_first trip lastStation value date = function
					     | 0 -> fprintf oc "%s" " (,)"; date
					     | _ -> fprintf oc "%s" " (";
						    Tmdates.printDateChannel oc (Tmdates.addMinutes (date) ((((float_of_int (getDistance lastStation value links)) /. (float_of_int (Train.getSpeed (Trip.getTrain trip))) *. 60.))));
						    fprintf oc "%s" ")";
						    (Tmdates.addMinutes (date) ((((float_of_int (getDistance lastStation value links)) /. (float_of_int (Train.getSpeed (Trip.getTrain trip))) *. 60.))));
					   in
					   let print_second lastStation value date idx = function
					     | [] -> fprintf oc "%s\n" " (,)"; date
					     | _ -> fprintf oc "%s" " (";
						    if idx != 0 then begin Tmdates.printDateChannel oc (Tmdates.addMinutes (date) 10.); fprintf oc "%s\n" ")"; Tmdates.addMinutes (date) 10. end
						    else begin Tmdates.printDateChannel oc date; fprintf oc "%s\n" ")"; date end
					   in
					   printStations (idx + 1) trip links (print_second lastStation value (print_first trip lastStation value date idx) idx next) value next
			in
			printStations 0 value (Train.getList (Trip.getTrain value)) (Trip.getDate value) "" (Trip.getStations value);
			aux init next
  in
  aux trips trips;
;;

let listTrips trips =
  let rec aux init = function
    | [] -> init
    | value::next ->	print_string (Train.trainType_to_string (Trip.getTrain value));
			print_string " ";
			print_int (Trip.getId value);
			print_endline "";
			let rec printStations idx trip links date lastStation = function
			  | [] -> ()
			  | value::next -> print_string value;
					   let rec getDistance first second = function
					     | [] -> raise List_Invalid_Stations
					     | value::next -> if (Link.getFirstStation value = first && Link.getSecondStation value = second) ||
								   (Link.getFirstStation value = second && Link.getSecondStation value = first) then
								Link.getDistance value else getDistance first second next
					   in
					   let print_first trip lastStation value date = function
					     | 0 -> print_string " (,)"; date
					     | _ -> print_string " (";
						    Tmdates.printDate (Tmdates.addMinutes (date) ((((float_of_int (getDistance lastStation value links)) /. (float_of_int (Train.getSpeed (Trip.getTrain trip))) *. 60.))));
						    print_string ")";
						    (Tmdates.addMinutes (date) ((((float_of_int (getDistance lastStation value links)) /. (float_of_int (Train.getSpeed (Trip.getTrain trip))) *. 60.))));
					   in
					   let print_second lastStation value date idx = function
					     | [] -> print_endline " (,)"; date
					     | _ -> print_string " (";
						    if idx != 0 then begin Tmdates.printDate (Tmdates.addMinutes (date) 10.); print_endline ")"; Tmdates.addMinutes (date) 10. end
						    else begin Tmdates.printDate date; print_endline ")"; date end
					   in
					   printStations (idx + 1) trip links (print_second lastStation value (print_first trip lastStation value date idx) idx next) value next
			in
			printStations 0 value (Train.getList (Trip.getTrain value)) (Trip.getDate value) "" (Trip.getStations value);
			aux init next
  in aux trips trips
;;

let createTrip l s =
  let rec check_town name links = match links with
	| [] -> false
	| x::b -> if (Link.getFirstStation x = name || Link.getSecondStation x = name) then true else
			check_town name b
  in let rec check_towns train = function
	| [] -> true
	| a::b -> if (check_town a (Train.getList train) = true) then check_towns train b else raise Bad_Town_For_This_Train
  in let detect_type = function
    | "TGV" -> _TGV
    | "Thalys" -> _Thalys
    | "Eurostar" -> _Eurostar
    | _ -> raise Unknown_Train_Type
  in let rec aux idx e l = function
       | [] -> if (idx = 5 && check_towns (Trip.getTrain e) (Trip.getStations e) = true) then begin print_string "Trip created: ";
				       print_string (Train.trainType_to_string (Trip.getTrain e));
				       print_string " "; 
				       print_int (Trip.getId e);
				       print_endline "";
				       (List.rev (e::(List.rev l))) end else
		 raise Error_During_Trip_Creation
       | a::b ->	if (idx = 0) then aux (idx + 1) (Trip.setId e l) l b else
			  if (idx = 1) then aux (idx + 1) (Trip.setTrain e (detect_type a)) l b else
			    if (idx = 2) then try aux (idx + 1) (Trip.setDate e a) l b
				with
					| Error_During_Trip_Creation -> raise Error_During_Trip_Creation
					| Bad_Town_For_This_Train -> raise Bad_Town_For_This_Train
					|_ -> raise Bad_Date_Format else
			      if (idx = 3) then try aux (idx + 1) (Trip.setHour e a) l b 
				with
					| Error_During_Trip_Creation -> raise Error_During_Trip_Creation
					| Bad_Town_For_This_Train -> raise Bad_Town_For_This_Train
					|_ -> raise Bad_Date_Format else
						if (idx = 4) then aux (idx + 1) (Trip.setStations e (Str.split (Str.regexp "[,]+") a)) l b else
				  aux (idx + 1) e l b
     in aux 0 (Trip.newTrip (0, (Train.newTrain (Unknown, 0, [])), Tmdates.newDate (Unix.localtime (0.)), []))
	    l (Str.split (Str.regexp "[ \t]+") s)
;;
  
(* App *)
let rec main_loop trips =
  let catch_entry trips = try match (read_line ()) with
    | "quit" -> ignore (saveTrips trips); raise Quit
    | "" -> trips
    | "list" -> listTrips trips
	| x ->	if (Helper.strncmp x "create" 6 = true) then createTrip trips x else
			if (Helper.strncmp x "delete" 6 = true) then deleteTrip trips x else
			raise Unknown_Command
	with
	| Bad_Town_For_This_Train -> print_endline "Bad Town For This Train"; trips
	| Bad_Date_Format -> print_endline "Bad Date Format"; trips
	| Unknown_Train_Type -> print_endline "Unknown Train Type"; trips
	| Unknown_Command -> print_endline "Unknown Command"; trips
	| Error_During_Trip_Creation -> print_endline "Error During Trip Creation"; trips
	| Wrong_number_params_delete_trip -> print_endline "delete command only takes one parameter (Example: delete TGV3847)"; trips
	| List_Invalid_Stations -> print_endline "List invalid stations)"; trips
in
  try main_loop (catch_entry trips) with _ -> ()
;;
  
(* Launch *)
let trips = [];;

main_loop trips;;
