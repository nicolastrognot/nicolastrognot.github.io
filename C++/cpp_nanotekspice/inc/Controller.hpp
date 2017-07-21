//
// Created by Nicolas on 07/02/17.
//

#pragma once
# include <map>
# include <memory>
# include <functional>
# include "Parser.hpp"
# include "components/Components.hpp"

namespace nts
{
    extern size_t time_idx;
    class Controller
    {
    private:
        std::unique_ptr<Parser>          parser;
        std::map<std::string, std::function<void (std::string const &)>> Functions_map;
        void display(std::string const &);
        void input(std::string const &);
        void simulate(std::string const &);
        void loop(std::string const &);
        void dump(std::string const &);
    public:
        bool run();
        Parser &getParser() const;
        Controller(int argc, char **argv);
        ~Controller();
    };
}