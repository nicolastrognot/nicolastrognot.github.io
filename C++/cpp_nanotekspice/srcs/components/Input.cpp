//
// Created by Nicolas on 02/02/17.
//

#include <iostream>
#include "../../inc/components/Input.hpp"

void nts::Input::setState(nts::Tristate state)
{
    this->state = state;
}

nts::Tristate nts::Input::Compute(size_t pin_num_this)
{
    (void)pin_num_this;
    return this->state;
}

void nts::Input::SetLink(size_t pin_num_this,
                         nts::IComponent &component,
                         size_t pin_num_target)
{
    (void)pin_num_target;
    (void)pin_num_this;
    (void)component;
}

void nts::Input::Dump(void) const
{
    std::cout << this->name << " (Input), value : " << const_cast<nts::Input *>(this)->Compute() << std::endl;
}

nts::Input::Input(std::string const &name) : name(name)
{
    this->state = nts::UNDEFINED;
}