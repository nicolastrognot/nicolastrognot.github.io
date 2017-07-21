//
// Created by Nicolas on 03/02/17.
//

#include <iostream>
#include <cstdlib>
#include "../../inc/components/Components.hpp"
#include "../../inc/Errors.hpp"

bool nts::Components::checkComponentExists(std::string const &e)
{
    return (this->Components_map.count(e));
}

nts::Components::Components()
{
  this->Components_map["4001"]   = std::bind(&Components::create4001, this, std::placeholders::_1);
  this->Components_map["4030"]   = std::bind(&Components::create4030, this, std::placeholders::_1);
  this->Components_map["4069"]   = std::bind(&Components::create4069, this, std::placeholders::_1);
  this->Components_map["4081"]   = std::bind(&Components::create4081, this, std::placeholders::_1);
  this->Components_map["4011"]   = std::bind(&Components::create4011, this, std::placeholders::_1);
  this->Components_map["4071"]   = std::bind(&Components::create4071, this, std::placeholders::_1);
  this->Components_map["4013"]   = std::bind(&Components::create4013, this, std::placeholders::_1);
  this->Components_map["4008"]   = std::bind(&Components::create4008, this, std::placeholders::_1);
  this->Components_map["4514"]   = std::bind(&Components::create4514, this, std::placeholders::_1);
  this->Components_map["4040"]   = std::bind(&Components::create4040, this, std::placeholders::_1);
  this->Components_map["input"]   = std::bind(&Components::createInput, this, std::placeholders::_1);
  this->Components_map["clock"]   = std::bind(&Components::createClock, this, std::placeholders::_1);
  this->Components_map["true"]    = std::bind(&Components::createTrue, this, std::placeholders::_1);
  this->Components_map["false"]   = std::bind(&Components::createFalse, this, std::placeholders::_1);
  this->Components_map["output"]  = std::bind(&Components::createOutput, this, std::placeholders::_1);
}

nts::Components::~Components()
{

}

nts::IComponent *nts::Components::createComponent(const std::string &type, const std::string &value)
{
  if (this->Components_map.count(type))
    return (this->Components_map[type](value));
  else
    throw (ComponentError(std::string("Component '").append(type).append("' does not exist.")));
}

nts::IComponent *nts::Components::create4011(const std::string &value) const
{
  return (new C4011(value));
}

nts::IComponent *nts::Components::create4001(const std::string &value) const
{
    return (new C4001(value));
}

nts::IComponent *nts::Components::create4013(const std::string &value) const
{
    return (new C4013(value));
}

nts::IComponent *nts::Components::create4008(const std::string &value) const
{
    return (new C4008(value));
}

nts::IComponent *nts::Components::create4514(const std::string &value) const
{
    return (new C4514(value));
}

nts::IComponent *nts::Components::create4071(const std::string &value) const
{
    return (new C4071(value));
}

nts::IComponent *nts::Components::create4030(const std::string &value) const
{
    return (new C4030(value));
}

nts::IComponent *nts::Components::create4069(const std::string &value) const
{
    return (new C4069(value));
}

nts::IComponent *nts::Components::create4081(const std::string &value) const
{
    return (new C4081(value));
}

nts::IComponent *nts::Components::create4040(const std::string &value) const
{
    return (new C4040(value));
}

nts::IComponent *nts::Components::createInput(const std::string &value) const
{
    return (new Input(value));
}

nts::IComponent *nts::Components::createClock(const std::string &value) const
{
    return (new Clock(value));
}

nts::IComponent *nts::Components::createTrue(const std::string &value) const
{
    return (new True(value));
}

nts::IComponent *nts::Components::createFalse(const std::string &value) const
{
    return (new False(value));
}

nts::IComponent *nts::Components::createOutput(const std::string &value) const
{
    return (new Output(value));
}
