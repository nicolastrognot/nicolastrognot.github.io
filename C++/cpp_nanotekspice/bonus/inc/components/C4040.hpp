#pragma once
# include <vector>
# include <memory>
# include "IComponent.hpp"
# include "Components.hpp"

namespace	nts
{
  class	C4040 : public IComponent
  {
    std::map<int, std::pair<int, IComponent *> >	pins;
    std::map<int, std::vector<int> >			output_pins;
    std::map<int, nts::Tristate>			tmp;
    std::map<int, size_t>				alreadyPassedHere;
    std::string						name;
    bool						flag;
    size_t						index;

  public:
    virtual nts::Tristate				Compute(size_t pin_num_this = 1);
    virtual void					SetLink(size_t pin_num_this,
								nts::IComponent &component,
								size_t pin_num_target);
    virtual void					Dump(void) const;
    virtual nts::Tristate				*getBinary(size_t value);
    C4040(std::string const &);
    virtual ~C4040(void) {}
  };
}
