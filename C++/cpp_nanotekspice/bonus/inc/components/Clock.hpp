//
// Created by Nicolas on 02/02/17.
//

#pragma once
# include <string>
# include "IComponent.hpp"

namespace nts
{
    class Clock : public IComponent
    {
    public:
        nts::Tristate state;
        std::string name;
        size_t alreadyPassedHere;
    public:
        virtual nts::Tristate Compute(size_t pin_num_this = 1);
        virtual void SetLink(size_t pin_num_this,
                             nts::IComponent &component,
                             size_t pin_num_target);
        virtual void Dump(void) const;
        Clock(std::string const &name);
        virtual ~Clock(void) { }
        void setState(nts::Tristate);
    };
}