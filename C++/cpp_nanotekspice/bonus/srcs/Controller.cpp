//
// Created by Nicolas on 07/02/17.
//

#include <csignal>
#include <iostream>
#include "../inc/Errors.hpp"
#include "../inc/Controller.hpp"

static bool loopBool = false;

void loopHandler(int sig)
{
    loopBool = true;
    (void)sig;
}

nts::Parser &nts::Controller::getParser() const
{
    return (*this->parser);
}

void nts::Controller::display(std::string const &s)
{
    for (auto &e : this->parser->getCircuitComponent())
    {
        if (dynamic_cast<nts::Output *>(e.second) != nullptr)
            std::cout << e.first << "=" << dynamic_cast<nts::Output *>(e.second)->getState() << std::endl;
    }
    (void)s;
}

void nts::Controller::input(std::string const &in)
{
    if (in.find("=") != std::string::npos)
    {
        nts::Tristate tmp;
        if (this->parser->getSecond(in, "=") == "1")
            tmp = nts::Tristate::TRUE;
        else if (this->parser->getSecond(in, "=") == "0")
            tmp = nts::Tristate::FALSE;
        else
            tmp = nts::Tristate::UNDEFINED;
        if (dynamic_cast<nts::Input *>(this->parser->getCircuitComponent()[this->parser->getFirst(in, "=")]) != nullptr)
            dynamic_cast<nts::Input *>(this->parser->getCircuitComponent()[this->parser->getFirst(in, "=")])->setState(tmp);
        else
            std::cout << "'" << this->parser->getFirst(in, "=") << "' is not an input" << std::endl;
    }
    else
    {
        std::cout << in << ": Command not found..." << std::endl;
    }
}

void nts::Controller::simulate(std::string const &s)
{
    int i = 0;
    for (auto &e : this->parser->getCircuitComponent())
    {
        if (dynamic_cast<nts::Output *>(e.second) != nullptr) {
            e.second->Compute();
            i++;
        }
    }
    nts::Tristate ret;
    for (auto &e : this->parser->getCircuitComponent())
    {
        if (dynamic_cast<nts::Clock *>(e.second) != nullptr)
        {
            ret = e.second->Compute();
            if (ret == nts::FALSE)
                ret = nts::TRUE;
            else if (ret == nts::TRUE)
                ret = nts::FALSE;
            dynamic_cast<nts::Clock *>(e.second)->setState(ret);
        }
    }
    nts::time_idx += i;
    (void)s;
}

void nts::Controller::loop(std::string const &s)
{
    std::cout << "Currently looping... (Press Ctrl+C to stop the process)" << std::endl;
    loopBool = false;
    signal(SIGINT, loopHandler);
    while (!loopBool)
    {
        this->simulate("NULL");
    }
    signal(SIGINT, SIG_DFL);
    (void)s;
}

void nts::Controller::dump(std::string const &s)
{
    int i = 0;

    for (auto &e : this->parser->getCircuitComponent())
    {
        if (i != 0)
            std::cout << "-----------------------" << std::endl;
        else
            i = 1;
        e.second->Dump();
    }
    (void)s;
}

bool nts::Controller::run()
{
    std::string     in;

    std::cout << "> ";
    while (std::getline(std::cin, in) && in != "exit")
    {
        if (this->Functions_map.find(in) != this->Functions_map.end())
            this->Functions_map[in](in);
        else
        {
            this->input(in);
        }
        std::cout << "> ";
    }
    return (0);
}

nts::Controller::Controller(int argc, char **argv) : parser(new Parser())
{
    if (argc == 1)
        throw (UsageError(std::string("Usage : ").append(argv[0]).append(" file.nts")));
    this->parser->openFile(argv[1]);
    this->Functions_map["display"]  = [this](std::string const &s) { display(s); };
    this->Functions_map["input"]    = [this](std::string const &s) { input(s); };
    this->Functions_map["simulate"] = [this](std::string const &s) { simulate(s); };
    this->Functions_map["loop"]     = [this](std::string const &s) { loop(s); };
    this->Functions_map["dump"]     = [this](std::string const &s) { dump(s); };
    t_ast_node *tree = this->parser->createTree();
    this->parser->parseTree(*tree);
    for (int i = 2; i < argc; i++)
    {
        nts::Tristate tmp;
        if (this->parser->getSecond(argv[i], "=") == "1")
            tmp = nts::Tristate::TRUE;
        else if (this->parser->getSecond(argv[i], "=") == "0")
            tmp = nts::Tristate::FALSE;
        else
            tmp = nts::Tristate::UNDEFINED;
        if (dynamic_cast<nts::Input *>(this->parser->getCircuitComponent()[this->parser->getFirst(argv[i], "=")]) != nullptr)
            dynamic_cast<nts::Input *>(this->parser->getCircuitComponent()[this->parser->getFirst(argv[i], "=")])->setState(tmp);
        else if (dynamic_cast<nts::Clock*>(this->parser->getCircuitComponent()[this->parser->getFirst(argv[i] ,"=")]) != nullptr)
            dynamic_cast<nts::Clock *>(this->parser->getCircuitComponent()[this->parser->getFirst(argv[i], "=")])->setState(tmp);
    }
    this->simulate("NULL");
    this->display("NULL");
}

nts::Controller::~Controller()
{

}
