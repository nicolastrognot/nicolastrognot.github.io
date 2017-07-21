//
// Parser.hpp for Parser.hpp in /home/nicolas.trognot/rendu/cpp_nanotekspice/inc
//
// Made by Nicolas TROGNOT
// Login   <nicolas.trognot@epitech.net>
//
// Started on  Wed Feb  1 21:41:21 2017 Nicolas TROGNOT
// Last update Thu Feb  2 10:04:23 2017 Nicolas TROGNOT
//

#pragma once
# include <string>
# include <vector>
# include <map>
# include <memory>
# include "IParser.hpp"
# include "components/IComponent.hpp"
# include "components/Components.hpp"
# include "components/Input.hpp"
# include "components/Output.hpp"
# include "components/Clock.hpp"
# include "components/True.hpp"
# include "components/False.hpp"

namespace nts
{
    class Parser : public IParser
    {
    private:
        std::vector<std::string> file;
        std::unique_ptr<Components> components;
        t_ast_node *tree;
        std::map<std::string, IComponent *> circuitComponent;
    public:
        bool openFile(std::string const &pathToFile);
        virtual void feed(std::string const& input);
        virtual void parseTree(t_ast_node& root);
        virtual t_ast_node *createTree();
        t_ast_node  *createNode(t_ast_node *curr, const std::string &, std::string &);
        std::string guessLexeme(const std::string &e);
        std::string guessValue(const std::string &e);
        ASTNodeType guessType(nts::t_ast_node *node, std::string &);
        std::string getFirst(const std::string &, const std::string &);
        std::string getSecond(const std::string &, const std::string &);
        std::string fillNode(nts::t_ast_node *node, std::string const &e,
                      std::string &section);
        bool checkComponentExist(const std::string &);
        Parser();
        virtual ~Parser();
        void setCircuitComponent(std::string const &, IComponent *);
        std::map<std::string, IComponent *> getCircuitComponent() const;
        Components &getComponents() const;
    };
}
