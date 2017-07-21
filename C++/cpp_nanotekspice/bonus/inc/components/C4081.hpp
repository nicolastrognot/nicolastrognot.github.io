//
// Created by Nicolas on 02/02/17.
//

#pragma once
# include <vector>
# include "IComponent.hpp"
# include "Components.hpp"

namespace nts
{
    class C4081 : public IComponent
    {
    private:
        std::map<int, std::pair<int, IComponent *>>pins;
        std::map<int, std::vector<int>>output_pins;
        std::map<int, nts::Tristate>tmp;
        std::map<int, size_t>alreadyPassedHere;
        std::string name;
    public:
        virtual nts::Tristate Compute(size_t pin_num_this = 1);
        virtual void SetLink(size_t pin_num_this,
                             nts::IComponent &component,
                             size_t pin_num_target);
        virtual void Dump(void) const;
        C4081(std::string const &);
        virtual ~C4081(void) { }
    };
}