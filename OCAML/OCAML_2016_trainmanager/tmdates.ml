module type TMDATES =
  sig
    type date
    val	newDate		:	Unix.tm -> date
    val	getDate		:	date -> Unix.tm
    val printDate	:	date -> unit
    val printDateChannel:	out_channel -> date -> unit
    val setDate		:	date -> string -> date
    val setHour		:	date -> string -> date
    val	addMinutes	:	date -> float -> date
  end

module Tmdates : TMDATES =
  struct
    type date = Unix.tm
    let setDate d s	=
      let r = Str.regexp "\\([0-9][0-9]\\)-\\([0-9][0-9]\\)-\\([0-9][0-9][0-9][0-9]\\)" in
      assert (Str.string_match r s 0);
      let aux d s =
	{
	  Unix.tm_sec = d.Unix.tm_sec;
	  Unix.tm_min = d.Unix.tm_min;
	  Unix.tm_hour = d.Unix.tm_hour;
	  Unix.tm_mday = int_of_string (Str.matched_group 1 s);
	  Unix.tm_mon = int_of_string (Str.matched_group 2 s) - 1;
	  Unix.tm_year = int_of_string (Str.matched_group 3 s) - 1900;
	  Unix.tm_wday = d.Unix.tm_wday;
	  Unix.tm_yday = d.Unix.tm_yday;
	  Unix.tm_isdst = d.Unix.tm_isdst
	}
      in aux d s
    let setHour d s	=
      let r = Str.regexp "\\([0-9][0-9]\\):\\([0-9][0-9]\\)" in
      assert (Str.string_match r s 0);
      let aux d s =
	{
	  Unix.tm_sec = d.Unix.tm_sec;
	  Unix.tm_min = int_of_string (Str.matched_group 2 s);
	  Unix.tm_hour = int_of_string (Str.matched_group 1 s);
	  Unix.tm_mday = d.Unix.tm_mday;
	  Unix.tm_mon = d.Unix.tm_mon;
	  Unix.tm_year = d.Unix.tm_year;
	  Unix.tm_wday = d.Unix.tm_wday;
	  Unix.tm_yday = d.Unix.tm_yday;
	  Unix.tm_isdst = d.Unix.tm_isdst
	}
      in aux d s
    let newDate	m	=	m
    let getDate u	=	u
    let printDate d =   Printf.printf "%02d-%02d-%04d,%02d:%02d"
				      d.Unix.tm_mday
				      (d.Unix.tm_mon + 1)
				      (d.Unix.tm_year + 1900)
				      d.Unix.tm_hour
				      d.Unix.tm_min
    let printDateChannel oc d =   Printf.fprintf oc "%02d-%02d-%04d,%02d:%02d"
					  d.Unix.tm_mday
					  (d.Unix.tm_mon + 1)
					  (d.Unix.tm_year + 1900)
					  d.Unix.tm_hour
					  d.Unix.tm_min
    let addMinutes d m = newDate (Unix.localtime ((fst (Unix.mktime d)) +. 60. *. m))
  end
