//
// Created by Nicolas on 18/02/17.
//

#include "../inc/LogicGates.hpp"

nts::Tristate  nts::do_nor(nts::Tristate i1, nts::Tristate i2)
{
    if (i1 == nts::FALSE && i2 == nts::FALSE)
        return (nts::TRUE);
    else if ((i1 == nts::UNDEFINED && i2 != nts::TRUE) ||
             (i2 == nts::UNDEFINED && i1 != nts::TRUE))
        return (nts::UNDEFINED);
    return (nts::FALSE);
}

nts::Tristate  nts::do_xor(nts::Tristate i1, nts::Tristate i2)
{
    if (i1 == nts::UNDEFINED || i2 == nts::UNDEFINED)
        return nts::UNDEFINED;
    return (static_cast<nts::Tristate>(static_cast<int>(i1) ^ static_cast<int>(i2)));
}

nts::Tristate  nts::do_and(nts::Tristate i1, nts::Tristate i2)
{
    if (i1 == nts::FALSE || i2 == nts::FALSE)
        return nts::FALSE;
    if (i1 == nts::TRUE && i2 == nts::TRUE)
        return nts::TRUE;
    return nts::UNDEFINED;
}

nts::Tristate  nts::do_not(nts::Tristate i)
{
    if (i == nts::TRUE)
        return (nts::FALSE);
    if (i == nts::FALSE)
        return (nts::TRUE);
    return (nts::UNDEFINED);
}

nts::Tristate   nts::do_or(nts::Tristate i1, nts::Tristate i2)
{
    if (i1 == nts::Tristate::TRUE || i2 == nts::Tristate::TRUE)
        return nts::Tristate::TRUE;
    if (i1 == nts::Tristate::FALSE && i2 == nts::Tristate::FALSE)
        return nts::Tristate::FALSE;
    return nts::Tristate::UNDEFINED;
}

nts::Tristate   nts::do_nxor(nts::Tristate i1, nts::Tristate i2)
{
    if (i1 == i2 && i1 != nts::Tristate::UNDEFINED)
        return (nts::Tristate::TRUE);
    if (i1 == nts::Tristate::UNDEFINED || i2 == nts::Tristate::UNDEFINED)
        return (nts::Tristate::UNDEFINED);
    return (nts::Tristate::FALSE);
}

nts::Tristate   nts::do_nand(nts::Tristate i1, nts::Tristate i2)
{
    if (i1 == nts::Tristate::TRUE && i2 == nts::Tristate::TRUE)
        return nts::Tristate::FALSE;
    if (i1 == nts::Tristate::FALSE || i2 == nts::Tristate::FALSE)
        return nts::Tristate::TRUE;
    return nts::Tristate::UNDEFINED;
}

nts::Tristate	nts::do_tristate(nts::Tristate i1, nts::Tristate i2)
{
    if (i1 == nts::Tristate::TRUE)
        return (i2);
    return (nts::Tristate::UNDEFINED);
}

nts::Tristate	nts::do_3And(nts::Tristate i1, nts::Tristate i2, nts::Tristate i3)
{
    if (i1 == nts::Tristate::FALSE || i2 == nts::Tristate::FALSE || i3 == nts::Tristate::FALSE)
        return (nts::Tristate::FALSE);
    if (i1 == i2 && i1 == i3 && i1 == nts::Tristate::TRUE)
        return (nts::Tristate::TRUE);
    return (nts::Tristate::UNDEFINED);
}

nts::Tristate	nts::do_3Nand(nts::Tristate i1, nts::Tristate i2, nts::Tristate i3)
{
    if (i1 == nts::Tristate::FALSE || i2 == nts::Tristate::FALSE || i3 == nts::Tristate::FALSE)
        return (nts::Tristate::TRUE);
    if (i1 == i2 && i1 == i3 && i1 == nts::Tristate::TRUE)
        return (nts::Tristate::FALSE);
    return (nts::Tristate::UNDEFINED);
}