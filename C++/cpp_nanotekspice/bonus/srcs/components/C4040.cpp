#include <iostream>
#include "../../inc/LogicGates.hpp"
#include "../../inc/components/C4040.hpp"
#include "../../inc/Errors.hpp"
#include "../../inc/Controller.hpp"

nts::Tristate	*nts::C4040::getBinary(size_t value)
{
  nts::Tristate	*output = new nts::Tristate[12];
  int		i = 0;
  while (i < 12)
    {
      if (value % 2 == 0)
	output[i] = nts::Tristate::FALSE;
      else
	output[i] = nts::Tristate::TRUE;
      value /= 2;
      ++i;
    }
  return output;
}

nts::Tristate	nts::C4040::Compute(size_t pin_num_this)
{
  nts::Tristate	*binary;
  
  if (this->alreadyPassedHere[pin_num_this] >= nts::time_idx)
    return this->tmp[pin_num_this];
  this->alreadyPassedHere[pin_num_this]++;
  if (this->pins[10].second->Compute(this->pins[10].first) == nts::Tristate::FALSE && flag == true)
    {
      flag = false;
      this->index++;
    }
  if (this->pins[10].second->Compute(this->pins[10].first) == nts::Tristate::TRUE)
    flag = true;
  if (this->pins[11].second->Compute(this->pins[11].first) == nts::Tristate::TRUE)
    this->index = 0;
  binary = getBinary(this->index);
  if (pin_num_this == 1)
    this->tmp[pin_num_this] = binary[11];
  else if (pin_num_this == 2)
    this->tmp[pin_num_this] = binary[5];
  else if (pin_num_this == 3)
    this->tmp[pin_num_this] = binary[4];
  else if (pin_num_this == 4)
    this->tmp[pin_num_this] = binary[6];
  else if (pin_num_this == 5)
    this->tmp[pin_num_this] = binary[3];
  else if (pin_num_this == 6)
    this->tmp[pin_num_this] = binary[2];
  else if (pin_num_this == 7)
    this->tmp[pin_num_this] = binary[1];
  else if (pin_num_this == 9)
    this->tmp[pin_num_this] = binary[0];
  else if (pin_num_this == 12)
    this->tmp[pin_num_this] = binary[8];
  else if (pin_num_this == 13)
    this->tmp[pin_num_this] = binary[7];
  else if (pin_num_this == 14)
    this->tmp[pin_num_this] = binary[9];
  else if (pin_num_this ==15)
    this->tmp[pin_num_this] = binary[10];
  else 
    this->tmp[pin_num_this] = this->pins[pin_num_this].second->Compute(this->pins[pin_num_this].first);
  return this->tmp[pin_num_this];
}

void	nts::C4040::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target)
{
  if (pin_num_this < 1 || pin_num_this == 8 || pin_num_this > 15)
    throw LinksError("Error with 4040 linkage");
  this->pins[pin_num_this] = std::make_pair(pin_num_target, &component);
}

void	nts::C4040::Dump(void) const
{
  
}

nts::C4040::C4040(std::string const &name) : name(name),
					     flag(false),
					     index(0)
{
  for (int i = 1; i <= 15; ++i)
    {
      this->tmp[i] = nts::UNDEFINED;
      this->alreadyPassedHere[i] = 0;
    }
}
