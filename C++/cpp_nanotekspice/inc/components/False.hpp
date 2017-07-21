//
// Created by Nicolas on 02/02/17.
//

#pragma once
# include <string>
# include "IComponent.hpp"

namespace nts
{
    class False : public IComponent
    {
    private:
        std::string name;
    public:
        virtual nts::Tristate Compute(size_t pin_num_this = 1);
        virtual void SetLink(size_t pin_num_this,
                             nts::IComponent &component,
                             size_t pin_num_target);
        virtual void Dump(void) const;
        False(std::string const &name);
        virtual ~False(void) { }
    };
}