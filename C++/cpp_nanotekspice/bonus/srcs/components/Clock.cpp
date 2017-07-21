//
// Created by Nicolas on 02/02/17.
//

#include <iostream>
#include "../../inc/components/Clock.hpp"

void nts::Clock::setState(nts::Tristate state)
{
    this->state = state;
}

nts::Tristate nts::Clock::Compute(size_t pin_num_this)
{
    (void)pin_num_this;
    return this->state;
}

void nts::Clock::SetLink(size_t pin_num_this,
                         nts::IComponent &component,
                         size_t pin_num_target)
{
    (void)pin_num_target;
    (void)pin_num_this;
    (void)component;
}

void nts::Clock::Dump(void) const
{
    std::cout << this->name << " (Clock), value : " << this->state << std::endl;
}

nts::Clock::Clock(std::string const &name) : name(name)
{
    this->state = nts::FALSE;
}
