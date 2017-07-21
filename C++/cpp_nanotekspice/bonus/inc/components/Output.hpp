//
// Created by Nicolas on 02/02/17.
//

#pragma once
# include <string>
# include <map>
# include "IComponent.hpp"

namespace nts
{
    class Output : public IComponent
    {
    private:
        std::map<int, std::pair<int, IComponent *>>pins;
        nts::Tristate state;
        std::string name;
    public:
        virtual nts::Tristate Compute(size_t pin_num_this = 1);
        virtual void SetLink(size_t pin_num_this,
                             nts::IComponent &component,
                             size_t pin_num_target);
        virtual void Dump(void) const;
        Output(std::string const &name);
        virtual ~Output(void) { }
        nts::Tristate getState() const;
    };
}