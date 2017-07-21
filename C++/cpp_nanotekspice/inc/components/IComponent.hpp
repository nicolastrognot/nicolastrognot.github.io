//
// Created by Nicolas on 02/02/17.
//

#pragma once
# include <cstddef>

namespace nts
{
    enum Tristate
    {
        UNDEFINED = (-true),
        TRUE = true,
        FALSE = false

    };
    class IComponent
    {
    public:
        virtual nts::Tristate Compute(size_t pin_num_this = 1) = 0;
        virtual void SetLink(size_t pin_num_this,
                             nts::IComponent &component,
                             size_t pin_num_target) = 0;
        virtual void Dump(void) const = 0;
        virtual ~IComponent(void) { }
    };
}