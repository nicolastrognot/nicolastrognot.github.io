//
// Created by Nicolas on 02/02/17.
//

#include <iostream>
#include "../../inc/components/False.hpp"

nts::Tristate nts::False::Compute(size_t pin_num_this)
{
    (void)pin_num_this;
    return FALSE;
}

void nts::False::SetLink(size_t pin_num_this,
                         nts::IComponent &component,
                         size_t pin_num_target)
{
    (void)pin_num_target;
    (void)pin_num_this;
    (void)component;
}

void nts::False::Dump(void) const
{
    std::cout << this->name << " (False)" << std::endl;
}

nts::False::False(std::string const &name) : name(name)
{

}