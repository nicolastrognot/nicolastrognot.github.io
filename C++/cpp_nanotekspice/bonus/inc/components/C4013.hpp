//
// Created by Nicolas on 02/02/17.
//

#pragma once
# include <vector>
# include <memory>
# include "IComponent.hpp"
# include "Components.hpp"

namespace nts
{
    class C4013 : public IComponent
    {
    private:
        std::map<int, std::pair<int, IComponent *>>pins;
        std::map<int, std::vector<int>>output_pins;
        std::map<int, nts::Tristate>tmp;
        std::map<int, size_t>alreadyPassedHere;
        std::string name;
        std::unique_ptr<nts::IComponent> Nand;
        std::unique_ptr<nts::IComponent> Not;
        std::unique_ptr<nts::IComponent> Or;
        std::unique_ptr<nts::IComponent> And;
        std::unique_ptr<nts::IComponent> Nand_2;
        std::unique_ptr<nts::IComponent> Not_2;
        std::unique_ptr<nts::IComponent> Or_2;
        std::unique_ptr<nts::IComponent> And_2;
    public:
      virtual nts::Tristate Compute(size_t pin_num_this = 1);
      virtual void SetLink(size_t pin_num_this,
			   nts::IComponent &component,
			   size_t pin_num_target);
      virtual void Dump(void) const;
      C4013(std::string const &);
      virtual ~C4013(void) { }
    };
}
