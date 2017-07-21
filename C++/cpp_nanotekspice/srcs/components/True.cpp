//
// Created by Nicolas on 02/02/17.
//

#include <iostream>
#include "../../inc/components/True.hpp"

nts::Tristate nts::True::Compute(size_t pin_num_this)
{
    (void)pin_num_this;
    return TRUE;
}

void nts::True::SetLink(size_t pin_num_this,
                         nts::IComponent &component,
                         size_t pin_num_target)
{
    (void)pin_num_target;
    (void)pin_num_this;
    (void)component;
}

void nts::True::Dump(void) const
{
    std::cout << this->name << " (True)" << std::endl;
}

nts::True::True(std::string const &name) : name(name)
{

}