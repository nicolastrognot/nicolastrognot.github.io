open Agenda
open Contact

let tmp = Agenda.addContact [] ("t", "t", 12, "a@a.a", "00 00 00 00 00");;
let tmp2 = Agenda.addContact tmp ("t", "t", 12, "a@a.a", "00 00 00 00 00");;

let test fct l c =
try
        begin
                fct l c;
                print_endline "ko";
        end
with
| _ -> print_endline "ok";;

let test2 fct l i c =
try
        begin
                fct l i c;
                print_endline "ko";
        end
with
| _ -> print_endline "ok";;

test (Agenda.addContact) [] ("", "", 12, "", "");;

test (Agenda.addContact) [] ("t", "t", 12, "a@a.a", "");;
test (Agenda.addContact) [] ("t", "t", 12, "", "00 00 00 00 00");;
test (Agenda.addContact) [] ("t", "t", 144, "a@a.a", "00 00 00 00 00");;
test (Agenda.addContact) [] ("t", "", 10, "a@a.a", "00 00 00 00 00");;

let tmp = Agenda.addContact tmp ("     t  ", "t", 32, "a@a.a", "00 00 00 00 00");;
let tmp = Agenda.addContact tmp ("t  ", "t", 82, "a@a.a", "00 00 00 00 00");;
let tmp = Agenda.addContact tmp ("   t", "t", 110, "a@a.a", "00 00 00 00 00");;
let tmp = Agenda.addContact tmp ("t", "   t", 88, "a@a.a", "00 00 00 00 00");;
let tmp = Agenda.addContact tmp ("t", "   t", 77, "a@a.a", "00 00 00 00 00");;
let tmp = Agenda.addContact tmp ("t", "   t   ", 66, "a@a.a", "00 00 00 00 00");;
let tmp = Agenda.addContact tmp ("t     a", "t", 55, "a@a.a", "00 00 00 00 00");;
let tmp = Agenda.addContact tmp ("t", "t", 0, "a@a.a", "00 00 00 00 00");;
let tmp = Agenda.addContact tmp ("t-a", "t", 42, "a@a.a", "00 00 00 00 00");;
let tmp = Agenda.addContact tmp ("t'a", "t", 34, "a@a.a", "00 00 00 00 00");;
let tmp = Agenda.addContact tmp ("t a", "t", 23, "a@a.a", "00 00 00 00 00");;

test (Agenda.addContact) [] ("t", "t", 2, "a@a.a", "10 00 00 00 00");;
test (Agenda.addContact) [] ("t", "t", 0, "a@a.a", "0 00 00 00 00");;
test (Agenda.addContact) [] ("t", "t", 19, "a@a.a", "0000000000");;

test (Agenda.addContact) [] ("t", "t", 42, "@a.a", "00 00 00 00 00");;
test (Agenda.addContact) [] ("t", "t", 20, "a@.a", "00 00 00 00 00");;
test (Agenda.addContact) [] ("t", "t", 23, "a@a.", "00 00 00 00 00");;

print_endline "------------- removeContact -------------";;
let tmp = Agenda.removeContact tmp 4;;
test Agenda.removeContact [] 10;;
test Agenda.removeContact tmp (-1);;

print_endline "------------- replaceContact -------------";;
let tmp = Agenda.replaceContact tmp 3 ("v", "v", 119, "rt@rt.rt", "00 00 00 00 00");;
test2 (Agenda.replaceContact) [] 0 ("", "", 0, "a@a.a", "00 00 00 00 00");;

print_endline "------------- printContacts -------------";;
Agenda.printContacts tmp Age "";;
Agenda.printContacts tmp Age "12";;

print_endline "------------- getContatId -------------";;
Agenda.getContactId tmp Id "1";;
Agenda.getContactId tmp All "0";;
Agenda.getContactId tmp FirstName "T-A";;
Agenda.getContactId tmp FirstName "A";;
