#pragma once
# include <vector>
# include <memory>
# include "IComponent.hpp"
# include "Components.hpp"

namespace	nts
{
  class		C4017 : public IComponent
  {
  private:
    std::map<int, std::pair<int, IComponent *> >	pins;
    std::map<int, std::vector<int> >			output_pins;
    std::map<int, nts::Tristate>			tmp;
    std::map<int, size_t>				alreadyPassedHere;
    std::string						name;
    std::unique_ptr<nts::IComponent>			FFalse;
    std::unique_ptr<nts::IComponent>			FF0;
    std::unique_ptr<nts::IComponent>			FF1;
    std::unique_ptr<nts::IComponent>			FF2;
    std::unique_ptr<nts::IComponent>			Nor0;
    std::unique_ptr<nts::IComponent>			Nor1;
    std::unique_ptr<nts::IComponent>			Nor2;
    std::unique_ptr<nts::IComponent>			And;
    std::unique_ptr<nts::IComponent>			Or;

  public:
    virtual nts::Tristate				Compute(size_t pin_num_this = 1);
    virtual void					SetLink(size_t pin_num_this,
								nts::IComponent &component,
								size_t pin_num_target);
    virtual void					Dump(void) const;
    C4017(std::string const &);
    virtual ~C4017(void) {}
  };
}
