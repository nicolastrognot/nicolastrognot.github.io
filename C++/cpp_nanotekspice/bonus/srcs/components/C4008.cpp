#include <iostream>
#include "../../inc/LogicGates.hpp"
#include "../../inc/components/C4008.hpp"
#include "../../inc/Errors.hpp"
#include "../../inc/Controller.hpp"

nts::Tristate	nts::C4008::Compute(size_t pin_num_this)
{
    nts::Tristate a = nts::Tristate::UNDEFINED;

    if (this->alreadyPassedHere[pin_num_this] >= nts::time_idx)
        return this->tmp[pin_num_this];
    this->alreadyPassedHere[pin_num_this]++;
    if (pin_num_this == 10)
        a = this->Xor->Compute(4);
    else if (pin_num_this == 11)
        a = this->Xor->Compute(11);
    else if (pin_num_this == 12)
        a = this->Xor2->Compute(4);
    else if (pin_num_this == 13)
        a = this->Xor2->Compute(10);
    else if (pin_num_this == 14)
        a = this->Or->Compute(11);
    else
        a = this->pins[pin_num_this].second->Compute(this->pins[pin_num_this].first);
    this->tmp[pin_num_this] = a;
    return (a);
}

void	nts::C4008::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target)
{
    if (pin_num_this < 1 || pin_num_this == 8 || pin_num_this > 15)
    {
        throw LinksError("Error with 4008 linkage");
    }
    this->pins[pin_num_this] = std::make_pair(pin_num_target, &component);
}

void	nts::C4008::Dump(void) const
{

}

nts::C4008::C4008(std::string const &name) : name(name),
                                             Xor(new C4030("Xor")),
                                             Xor2(new C4030("Xor2")),
                                             Or(new C4071("Or")),
                                             And(new C4081("And")),
                                             And2(new C4081("And2"))
{
    for (int i = 1; i <= 16; ++i)
    {
        this->tmp[i] = nts::UNDEFINED;
        this->alreadyPassedHere[i] = 0;
    }


    this->SetLink(10, *this->Xor, 4);
    this->Xor->SetLink(5, *this->Xor, 3);
    this->Xor->SetLink(6, *this, 9);

    this->Xor->SetLink(1, *this, 7);
    this->Xor->SetLink(2, *this, 6);

    this->And->SetLink(1, *this, 9);
    this->And->SetLink(2, *this->Xor, 3);

    this->Or->SetLink(1, *this->And, 3);
    this->Or->SetLink(2, *this->And, 4);

    this->And->SetLink(5, *this, 7);
    this->And->SetLink(6, *this, 6);




    this->SetLink(11, *this->Xor, 11);
    this->Xor->SetLink(12, *this->Xor, 10);
    this->Xor->SetLink(13, *this->Or, 3);

    this->Xor->SetLink(8, *this, 5);
    this->Xor->SetLink(9, *this, 4);

    this->And->SetLink(8, *this->Or, 3);
    this->And->SetLink(9, *this->Xor, 10);

    this->Or->SetLink(5, *this->And, 10);
    this->Or->SetLink(6, *this->And, 11);

    this->And->SetLink(13, *this, 5);
    this->And->SetLink(12, *this, 4);



    this->SetLink(12, *this->Xor2, 4);
    this->Xor2->SetLink(5, *this->Xor2, 3);
    this->Xor2->SetLink(6, *this->Or, 4);

    this->Xor2->SetLink(1, *this, 3);
    this->Xor2->SetLink(2, *this, 2);

    this->And2->SetLink(1, *this->Or, 4);
    this->And2->SetLink(2, *this->Xor2, 3);

    this->Or->SetLink(8, *this->And2, 3);
    this->Or->SetLink(9, *this->And2, 4);

    this->And2->SetLink(5, *this, 3);
    this->And2->SetLink(6, *this, 2);



    this->SetLink(13, *this->Xor2, 10);
    this->Xor2->SetLink(8, *this->Xor2, 11);
    this->Xor2->SetLink(9, *this->Or, 10);

    this->Xor2->SetLink(13, *this, 1);
    this->Xor2->SetLink(12, *this, 15);

    this->And2->SetLink(12, *this->Or, 10);
    this->And2->SetLink(13, *this->Xor2, 11);

    this->Or->SetLink(12, *this->And2, 11);
    this->Or->SetLink(13, *this->And2, 10);

    this->And2->SetLink(8, *this, 15);
    this->And2->SetLink(9, *this, 1);

    this->SetLink(14, *this->Or, 11);
}


