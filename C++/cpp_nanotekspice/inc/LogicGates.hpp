//
// Created by Nicolas on 18/02/17.
//

#pragma once
#include "../inc/components/IComponent.hpp"

namespace		nts
{
  nts::Tristate		do_or(nts::Tristate i1, nts::Tristate i2);
  nts::Tristate		do_nor(nts::Tristate i1, nts::Tristate i2);
  nts::Tristate		do_xor(nts::Tristate i1, nts::Tristate i2);
  nts::Tristate		do_and(nts::Tristate i1, nts::Tristate i2);
  nts::Tristate		do_nxor(nts::Tristate i1, nts::Tristate i2);
  nts::Tristate		do_nand(nts::Tristate i1, nts::Tristate i2);
  nts::Tristate		do_not(nts::Tristate i);
  nts::Tristate		do_tristate(nts::Tristate i1, nts::Tristate i2);
  nts::Tristate		do_3And(nts::Tristate i1, nts::Tristate i2, nts::Tristate i3);
  nts::Tristate		do_3Nand(nts::Tristate i1, nts::Tristate i2, nts::Tristate i3);
}
