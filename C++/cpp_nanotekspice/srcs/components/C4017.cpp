#include <iostream>
#include "../../inc/LogicGates.hpp"
#include "../../inc/components/C4017.hpp"
#include "../../inc/Errors.hpp"
#include "../../inc/Controller.hpp"

nts::Tristate	nts::C4017::Compute(size_t pin_num_this)
{
  if (this->alreadyPassedHere[pin_num_this] >= nts::time_idx)
    return this->tmp[pin_num_this];
  this->alreadyPassedHere[pin_num_this]++;
  if (pin_num_this == 3)
    this->tmp[pin_num_this] = this->Nor0->Compute(3);
  else if (pin_num_this == 2)
    this->tmp[pin_num_this] = this->Nor0->Compute(4);
  else if (pin_num_this == 4)
    this->tmp[pin_num_this] = this->Nor0->Compute(10);
  else if (pin_num_this == 7)
    this->tmp[pin_num_this] = this->Nor0->Compute(11);
  else if (pin_num_this == 10)
    this->tmp[pin_num_this] = this->Nor1->Compute(3);
  else if (pin_num_this == 1)
    this->tmp[pin_num_this] = this->Nor1->Compute(4);
  else if (pin_num_this == 5)
    this->tmp[pin_num_this] = this->Nor1->Compute(10);
  else if (pin_num_this == 6)
    this->tmp[pin_num_this] = this->Nor1->Compute(11);
  else if (pin_num_this == 9)
    this->tmp[pin_num_this] = this->Nor2->Compute(3);
  else if (pin_num_this == 1)
    this->tmp[pin_num_this] = this->Nor1->Compute(4);
  else
    this->tmp[pin_num_this] = this->pins[pin_num_this].second->Compute(this->pins[pin_num_this].first);
  return this->tmp[pin_num_this];
}

void	nts::C4017::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target)
{
  if (pin_num_this < 1 || pin_num_this == 8 || pin_num_this > 15)
    throw LinksError("Error with 4017 linkage");
  this->pins[pin_num_this] = std::make_pair(pin_num_target, &component);
}

void	nts::C4017::Dump(void) const
{

}

nts::C4017::C4017(std::string const &name) : name(name),
					     FFalse (new False("false")),
					     FF0 (new C4013("FF0")),
					     FF1 (new C4013("FF1")),
					     FF2 (new C4013("FF2")),
					     Nor0 (new C4001("Nor0")),
					     Nor1 (new C4001("Nor1")),
					     Nor2 (new C4001("Nor2")),
					     And (new C4081("And")),
					     Or (new C4071("Or"))
{
  for (int i = i; i <= 15; ++i)
    {
      this->tmp[i] = nts::Tristate::UNDEFINED;
      this->alreadyPassedHere[i] = 0;
    }
  /* First FF */
  this->FF0->SetLink(4, *this, 15);
  this->FF0->SetLink(3, *this, 14);
  this->FF0->SetLink(5, *this->FF2, 2);
  this->FF0->SetLink(6, *this->FFalse, 1);
  this->FF0->SetLink(9, *this->FF0, 1);
  this->Or->SetLink(2, *this->FF0, 1);
  this->Nor0->SetLink(2, *this->FF0, 1);
  this->Nor1->SetLink(8, *this->FF0, 1);
  this->Nor0->SetLink(6, *this->FF0, 2);
  this->Nor1->SetLink(5, *this->FF0, 2);
  /* Second FF */
  this->FF0->SetLink(10, *this, 15);
  this->FF0->SetLink(11, *this, 14);
  // D input already linked
  this->FF0->SetLink(8, *this->FFalse, 1);
  this->And->SetLink(2, *this->FF0, 13);
  this->Nor0->SetLink(5, *this->FF0, 13);
  this->Nor1->SetLink(12, *this->FF0, 13);
  this->Nor0->SetLink(8, *this->FF0, 12);
  this->Nor1->SetLink(9, *this->FF0, 12);
  /* Third FF */
  this->FF1->SetLink(5, *this->And, 3);
  this->FF1->SetLink(3, *this, 14);
  this->FF1->SetLink(4, *this, 15);
  this->FF1->SetLink(6, *this->FFalse, 1);
  this->Or->SetLink(1, *this->FF1, 1);
  this->FF1->SetLink(9, *this->FF1, 1);
  this->Nor2->SetLink(2, *this->FF1, 1);
  this->Nor0->SetLink(9, *this->FF1, 1);
  this->Nor1->SetLink(13, *this->FF1, 2);
  this->Nor0->SetLink(13, *this->FF1, 2);
  /* Fourth FF */
  //D input already linked
  this->FF1->SetLink(8, *this->FFalse, 1);
  this->FF1->SetLink(10, *this, 15);
  this->FF1->SetLink(11, *this, 14);
  this->FF2->SetLink(5, *this->FF1, 13);
  this->Nor2->SetLink(5, *this->FF1, 13);
  this->Nor0->SetLink(12, *this->FF1, 13);
  this->Nor2->SetLink(1, *this->FF1, 12);
  this->Nor1->SetLink(2, *this->FF1, 2);
  /* Fifth FF */
  // D input already linked
  this->FF2->SetLink(6, *this->FFalse, 1);
  this->FF2->SetLink(4, *this, 15);
  this->FF2->SetLink(3, *this, 14);
  this->Nor0->SetLink(1, *this->FF2, 1);
  this->Nor1->SetLink(1, *this->FF2, 1);
  this->SetLink(12, *this->FF2, 2);
  this->Nor2->SetLink(6, *this->FF2, 2);
  this->Nor1->SetLink(6, *this->FF2, 2);
  /* Other link */
  this->And->SetLink(1, *this->Or, 3);
}
