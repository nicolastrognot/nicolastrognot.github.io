//
// Errors.hpp for Errors.hpp in /home/nicolas.trognot/rendu/cpp_nanotekspice/inc
//
// Made by Nicolas TROGNOT
// Login   <nicolas.trognot@epitech.net>
//
// Started on  Wed Feb  1 22:18:18 2017 Nicolas TROGNOT
// Last update Wed Feb  1 22:39:22 2017 Nicolas TROGNOT
//

#pragma once
# include <string>

class NtsError : public std::exception
{
private:
	std::string _message;
	std::string _component;
public:
	NtsError(std::string const &message,
			 std::string const &component = "Unknown") : _message(message),
														 _component(component) {}
	~NtsError() throw() {}
	virtual std::string const &getComponent() const { return this->_component; }
	const char *what() const throw() { return _message.c_str(); }
};

class UsageError : public NtsError
{
public:
	UsageError(std::string const &message,
			   std::string const &component =
			   "Unknown") : NtsError(message,
									 component) {}
};

class CircuitFileError : public NtsError
{
public:
	CircuitFileError(std::string const &message,
					 std::string const &component =
					 "Unknown") : NtsError(message,
										   component) {}
};

class ComponentError : public NtsError
{
public:
	ComponentError(std::string const &message,
				   std::string const &component =
				   "Unknown") : NtsError(message,
										 component) {}
};

class PinError : public NtsError
{
public:
	PinError(std::string const &message,
			 std::string const &component =
			 "The given pin does not exist") : NtsError(message,
														component) {}
};

class OutputError : public NtsError
{
public:
	OutputError(std::string const &message,
				std::string const &component =
				"Not every output is linked") : NtsError(message,
														 component) {}
};

class InputError : public NtsError
{
public:
	InputError(std::string const &message,
			   std::string const &component =
			   "Unknown") : NtsError(message,
									 component) {}
};
class ChipsetError : public NtsError
{
public:
	ChipsetError(std::string const &message,
				 std::string const &component =
				 "No chipset section") : NtsError(message,
												  component) {}
};
class LinksError : public NtsError
{
public:
	LinksError(std::string const &message,
			   std::string const &component =
			   "No links section") : NtsError(message,
											  component) {}
};
