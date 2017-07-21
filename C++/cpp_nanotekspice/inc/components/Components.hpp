//
// Created by Nicolas on 03/02/17.
//

#pragma once
# include <map>
# include <functional>
# include "IComponent.hpp"
# include "C4001.hpp"
# include "C4008.hpp"
# include "C4030.hpp"
# include "C4069.hpp"
# include "C4081.hpp"
# include "C4013.hpp"
# include "C4011.hpp"
# include "C4071.hpp"
# include "C4514.hpp"
# include "C4017.hpp"
# include "C4040.hpp"
# include "Input.hpp"
# include "Clock.hpp"
# include "True.hpp"
# include "False.hpp"
# include "Output.hpp"

namespace nts
{
  class   Components
  {
  private:
    std::map<std::string, std::function<IComponent *(const std::string &)>> Components_map;
    IComponent *create4001(const std::string &value) const;
    IComponent *create4030(const std::string &value) const;
    IComponent *create4069(const std::string &value) const;
    IComponent *create4081(const std::string &value) const;
    IComponent *create4011(const std::string &value) const;
    IComponent *create4071(const std::string &value) const;
    IComponent *create4013(const std::string &value) const;
    IComponent *create4008(const std::string &value) const;
    IComponent *create4514(const std::string &value) const;
    IComponent *create4040(const std::string &value) const;
    IComponent *create4017(const std::string &value) const;
    IComponent *createInput(const std::string &value) const;
    IComponent *createClock(const std::string &value) const;
    IComponent *createTrue(const std::string &value) const;
    IComponent *createFalse(const std::string &value) const;
    IComponent *createOutput(const std::string &value) const;
  public:
    Components();
    ~Components();
    IComponent *createComponent(const std::string &type, const std::string &value);
    bool checkComponentExists(std::string const &);
  };
}
