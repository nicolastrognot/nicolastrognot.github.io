#include <iostream>
#include "inc/Errors.hpp"
#include "inc/Controller.hpp"

size_t nts::time_idx;

int			        main(int argc, char **argv)
{
    try
    {
        nts::time_idx = 1;
        nts::Controller myController(argc, argv);
        myController.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error : " << e.what() << std::endl;
        return (1);
    }
    return (0);
}
