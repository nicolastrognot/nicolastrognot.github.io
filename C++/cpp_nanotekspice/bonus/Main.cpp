#include <SFML/Graphics.hpp>
#include <iostream>
#include "inc/Errors.hpp"
#include "inc/Controller.hpp"
#include "inc/GUI.hpp"

size_t nts::time_idx;

int				main(int argc, char **argv)
{
  try
    {
      nts::time_idx = 1;
      nts::Controller myController(argc, argv);
      nts::Gui myGui(myController);
      myGui.Loop(myController);
    }
  catch (const std::exception &e)
    {
      std::cerr << "Error : " << e.what() << std::endl;
      return (1);
    }
  return (0);
}
