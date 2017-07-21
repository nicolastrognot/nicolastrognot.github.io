#include <iostream>
#include "../../inc/LogicGates.hpp"
#include "../../inc/Errors.hpp"
#include "../../inc/components/C4514.hpp"

extern size_t	time_idx;

nts::Tristate	nts::C4514::Compute(size_t pin_num_this)
{
  unsigned int	output_set;
  int		a, b, c, d;
  
  if (this->pins[23].second->Compute(this->pins[23].first) == nts::Tristate::TRUE)
    return (nts::Tristate::FALSE);
  else if (this->pins[23].second->Compute(this->pins[23].first) == nts::Tristate::FALSE
	   && this->pins[1].second->Compute(this->pins[1].first) == nts::Tristate::TRUE)
    {
      if ((a = this->pins[2].second->Compute(this->pins[2].first)) == nts::Tristate::UNDEFINED ||
	  (b = this->pins[3].second->Compute(this->pins[3].first)) == nts::Tristate::UNDEFINED ||
	  (c = this->pins[21].second->Compute(this->pins[21].first)) == nts::Tristate::UNDEFINED ||
	  (d = this->pins[22].second->Compute(this->pins[22].first)) == nts::Tristate::UNDEFINED)
	return (nts::Tristate::UNDEFINED);
      output_set = a + 2 * b + 4 * c + 8 * d;
      if (output_set == 0 && pin_num_this == 11)
	return (nts::Tristate::TRUE);
      else if (output_set == 1 && pin_num_this == 9)
	return (nts::Tristate::TRUE);
      else if (output_set == 2 && pin_num_this == 10)
	return (nts::Tristate::TRUE);
      else if (output_set == 3 && pin_num_this == 8)
	return (nts::Tristate::TRUE);
      else if (output_set == 4 && pin_num_this == 7)
	return (nts::Tristate::TRUE);
      else if (output_set == 5 && pin_num_this == 6)
	return (nts::Tristate::TRUE);
      else if (output_set == 6 && pin_num_this == 5)
	return (nts::Tristate::TRUE);
      else if (output_set == 7 && pin_num_this == 4)
	return (nts::Tristate::TRUE);
      else if (output_set == 8 && pin_num_this == 18)
	return (nts::Tristate::TRUE);
      else if (output_set == 9 && pin_num_this == 17)
	return (nts::Tristate::TRUE);
      else if (output_set == 10 && pin_num_this == 20)
	return (nts::Tristate::TRUE);
      else if (output_set == 11 && pin_num_this == 19)
	return (nts::Tristate::TRUE);
      else if (output_set == 12 && pin_num_this == 14)
	return (nts::Tristate::TRUE);
      else if (output_set == 13 && pin_num_this == 13)
	return (nts::Tristate::TRUE);
      else if (output_set == 14 && pin_num_this == 16)
	return (nts::Tristate::TRUE);
      else if (output_set == 15 && pin_num_this == 15)
	return (nts::Tristate::TRUE);
      else
	return (nts::Tristate::FALSE);
    }
  else
    return (nts::Tristate::UNDEFINED);
}

void	nts::C4514::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target)
{
  if (pin_num_this < 1 || pin_num_this == 12 || pin_num_this > 23)
    {
      throw LinksError("Error with 4514 linkage");
    }
  this->pins[pin_num_this] = std::make_pair(pin_num_target, &component);
}

void	nts::C4514::Dump(void) const
{
    std::cout << this->name << " (4514)" << std::endl;
}

nts::C4514::C4514(std::string const &name) : name(name)
{
  for (int i = 1; i <= 23; ++i)
    {
      this->tmp[i] = nts::UNDEFINED;
      this->alreadyPassedHere[i] = 0;
    }
}
