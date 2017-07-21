//
// Created by Nicolas on 02/02/17.
//

#include <iostream>
#include "../../inc/components/Output.hpp"
#include "../../inc/Errors.hpp"

nts::Tristate nts::Output::getState() const
{
    return this->state;
}

nts::Tristate nts::Output::Compute(size_t pin_num_this)
{
    if (this->pins.find(pin_num_this) == this->pins.end())
        throw (PinError(std::string("Output '").append(this->name).append("' is not linked to anything.")));
    this->state = this->pins[pin_num_this].second->Compute(this->pins[pin_num_this].first);
    return (this->state);
}

void nts::Output::SetLink(size_t pin_num_this,
                          nts::IComponent &component,
                          size_t pin_num_target)
{
    this->pins[pin_num_this] = std::make_pair(pin_num_target, &component);
}

void nts::Output::Dump(void) const
{
    std::cout << this->name << " (Output), value : " << const_cast<nts::Output *>(this)->state << std::endl;
}

nts::Output::Output(std::string const &name) : name(name)
{
    this->state = nts::UNDEFINED;
}