//
// Created by Nicolas on 02/02/17.
//

#include <iostream>
#include "../../inc/LogicGates.hpp"
#include "../../inc/components/C4013.hpp"
#include "../../inc/Errors.hpp"
#include "../../inc/Controller.hpp"

nts::Tristate nts::C4013::Compute(size_t pin_num_this)
{
    if (this->alreadyPassedHere[pin_num_this] >= nts::time_idx) {
        return this->tmp[pin_num_this];
    }
    this->alreadyPassedHere[pin_num_this]++;
    nts::Tristate a = nts::Tristate::UNDEFINED;
    if (pin_num_this == 1) {
        if (this->pins.find(6) == this->pins.end() ||
            this->pins.find(5) == this->pins.end() ||
            this->pins.find(4) == this->pins.end() ||
            this->pins.find(3) == this->pins.end())
            throw (LinksError(std::string("Pin n°").append(std::to_string(pin_num_this)).append(" (Chipset n°4013 : ").append(this->name).append(") is not correctly wired.")));
        a = this->Or->Compute(3);
    }
    else if (pin_num_this == 2) {
        if (this->pins.find(6) == this->pins.end() ||
            this->pins.find(5) == this->pins.end() ||
            this->pins.find(4) == this->pins.end() ||
            this->pins.find(3) == this->pins.end())
            throw (LinksError(std::string("Pin n°").append(std::to_string(pin_num_this)).append(" (Chipset n°4013 : ").append(this->name).append(") is not correctly wired.")));
        a = this->Or->Compute(4);
    }
    else if (pin_num_this == 13) {
        if (this->pins.find(8) == this->pins.end() ||
            this->pins.find(9) == this->pins.end() ||
            this->pins.find(10) == this->pins.end() ||
            this->pins.find(11) == this->pins.end())
            throw (LinksError(std::string("Pin n°").append(std::to_string(pin_num_this)).append(" (Chipset n°4013 : ").append(this->name).append(") is not correctly wired.")));
        a = this->Or_2->Compute(3);
    }
    else if (pin_num_this == 12) {
        if (this->pins.find(8) == this->pins.end() ||
            this->pins.find(9) == this->pins.end() ||
            this->pins.find(10) == this->pins.end() ||
            this->pins.find(11) == this->pins.end())
            throw (LinksError(std::string("Pin n°").append(std::to_string(pin_num_this)).append(" (Chipset n°4013 : ").append(this->name).append(") is not correctly wired.")));
        a = this->Or_2->Compute(4);
    }
    else
        a = this->pins[pin_num_this].second->Compute(this->pins[pin_num_this].first);
    this->tmp[pin_num_this] = a;
    return (this->tmp[pin_num_this]);
}

void nts::C4013::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target)
{
    if (pin_num_this < 1 || pin_num_this == 7 || pin_num_this > 13)
    {
        throw LinksError("Error with 4013 linkage");
    }
    this->pins[pin_num_this] = std::make_pair(pin_num_target, &component);
}

void nts::C4013::Dump(void) const
{

}

nts::C4013::C4013(std::string const &name) : name(name),
                                             Nand(new C4011("Nand")),
                                             Not(new C4069("Not")),
                                             Or(new C4071("Or")),
                                             And(new C4081("And")),
                                             Nand_2(new C4011("Nand_2")),
                                             Not_2(new C4069("Not_2")),
                                             Or_2(new C4071("Or_2")),
                                             And_2(new C4081("And_2"))
{
    for (int i = 1 ; i <= 13 ; i++)
    {
        this->tmp[i] = nts::UNDEFINED;
        this->alreadyPassedHere[i] = 0;
    }
    // 1 et 2
    this->SetLink(1, *this->Or, 3);
    this->Or->SetLink(1, *this, 6);
    this->Or->SetLink(2, *this->And, 3);
    this->And->SetLink(1, *this->Nand, 4);
    this->And->SetLink(2, *this->Not, 4);
    this->Not->SetLink(3, *this->Or, 10);
    this->Or->SetLink(8, *this->Nand, 10);
    this->Or->SetLink(9, *this, 4);
    this->Nand->SetLink(5, *this->Nand, 3);
    this->Nand->SetLink(6, *this->Nand, 10);
    this->Nand->SetLink(8, *this->Nand, 4);
    this->Nand->SetLink(9, *this->Nand, 11);
    this->Nand->SetLink(1, *this, 5);
    this->Nand->SetLink(2, *this, 3);
    this->Nand->SetLink(12, *this, 3);
    this->Nand->SetLink(13, *this->Not, 2);
    this->Not->SetLink(1, *this, 5);
    this->Or->SetLink(5, *this, 4);
    this->Or->SetLink(6, *this->Not, 6);
    this->Not->SetLink(5, *this->Or, 3);

    // 13 et 12
    this->SetLink(13, *this->Or_2, 3);
    this->Or_2->SetLink(1, *this, 8);
    this->Or_2->SetLink(2, *this->And_2, 3);
    this->And_2->SetLink(1, *this->Nand_2, 4);
    this->And_2->SetLink(2, *this->Not_2, 4);
    this->Not_2->SetLink(3, *this->Or_2, 10);
    this->Or_2->SetLink(8, *this->Nand_2, 10);
    this->Or_2->SetLink(9, *this, 10);
    this->Nand_2->SetLink(5, *this->Nand_2, 3);
    this->Nand_2->SetLink(6, *this->Nand_2, 10);
    this->Nand_2->SetLink(8, *this->Nand_2, 4);
    this->Nand_2->SetLink(9, *this->Nand_2, 11);
    this->Nand_2->SetLink(1, *this, 9);
    this->Nand_2->SetLink(2, *this, 11);
    this->Nand_2->SetLink(12, *this, 11);
    this->Nand_2->SetLink(13, *this->Not_2, 2);
    this->Not_2->SetLink(1, *this, 9);
    this->Or_2->SetLink(5, *this, 10);
    this->Or_2->SetLink(6, *this->Not_2, 6);
    this->Not_2->SetLink(5, *this->Or_2, 3);
}
