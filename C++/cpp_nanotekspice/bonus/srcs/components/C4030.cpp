//
// Created by Nicolas on 02/02/17.
//

#include <iostream>
#include "../../inc/LogicGates.hpp"
#include "../../inc/components/C4030.hpp"
#include "../../inc/Errors.hpp"
#include "../../inc/Controller.hpp"

nts::Tristate nts::C4030::Compute(size_t pin_num_this)
{
    if (this->output_pins.find(pin_num_this) == this->output_pins.end())
        throw (PinError(std::string("Pin n°").append(std::to_string(pin_num_this)).append(" (Chipset n°4030 : ").append(this->name).append(") is not computable.")));
    if (this->pins.find(this->output_pins[pin_num_this][0]) == this->pins.end() ||
        this->pins.find(this->output_pins[pin_num_this][1]) == this->pins.end())
        throw (PinError(std::string("Pin n°").append(std::to_string(pin_num_this)).append(" (Chipset n°4030 : ").append(this->name).append(") is not correctly wired.")));
    if (this->alreadyPassedHere[pin_num_this] >= nts::time_idx)
        return this->tmp[pin_num_this];
    this->alreadyPassedHere[pin_num_this]++;
    nts::Tristate a = this->pins[this->output_pins[pin_num_this][0]].second->Compute(this->pins[this->output_pins[pin_num_this][0]].first);
    nts::Tristate b = this->pins[this->output_pins[pin_num_this][1]].second->Compute(this->pins[this->output_pins[pin_num_this][1]].first);
    this->tmp[pin_num_this] = nts::do_xor(a, b);
    return (this->tmp[pin_num_this]);
}

void nts::C4030::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target)
{
    this->pins[pin_num_this] = std::make_pair(pin_num_target, &component);
}

void nts::C4030::Dump(void) const
{
    std::cout << this->name << " (4030)" << std::endl;
}

nts::C4030::C4030(std::string const &name) : name(name)
{
    this->output_pins[3] = {1, 2};
    this->output_pins[4] = {5, 6};
    this->output_pins[11] = {12, 13};
    this->output_pins[10] = {8, 9};
    for (int i = 1 ; i <= 13 ; i++)
    {
        this->tmp[i] = nts::UNDEFINED;
        this->alreadyPassedHere[i] = 0;
    }
}