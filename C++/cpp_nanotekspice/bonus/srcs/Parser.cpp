#include <iostream>
#include <fstream>
#include <regex>
#include "../inc/components/IComponent.hpp"
#include "../inc/Errors.hpp"
#include "../inc/Parser.hpp"

nts::Components &nts::Parser::getComponents() const
{
    return (*this->components);
}

std::map<std::string, nts::IComponent *> nts::Parser::getCircuitComponent() const
{
    return this->circuitComponent;
}

void nts::Parser::setCircuitComponent(std::string const &name, IComponent *component)
{
    this->circuitComponent[name] = component;
}

bool                nts::Parser::openFile(std::string const &pathToFile)
{
    std::ifstream   _file;
    std::string     tmp;
    if (pathToFile.substr(pathToFile.find_last_of(".") + 1) != "nts")
        throw(CircuitFileError("Bad format (must be a nts file)"));
    _file.open(pathToFile.c_str());
    if (_file.fail())
        throw (CircuitFileError("No such file or directory"));
    while (getline(_file, tmp))
        this->feed(tmp);
    _file.close();
    return (0);
}

void                nts::Parser::feed(std::string const& input)
{
    std::string		tmp;

    tmp = std::regex_replace(input, std::regex("\\#([^\n]+)$"), "");
    tmp = std::regex_replace(tmp, std::regex("[\\s]+$"), "");
    tmp = std::regex_replace(tmp, std::regex("^[\\s]+"), "");
    tmp = std::regex_replace(tmp, std::regex("[\\s]+"), " ");
    if (tmp != "")
        this->file.push_back(tmp);
}

bool nts::Parser::checkComponentExist(const std::string &e)
{
    if (this->circuitComponent.find(e) == this->circuitComponent.end())
        return (false);
    return (true);
}
void nts::Parser::parseTree(t_ast_node& root)
{
    t_ast_node *tmp = &root;

    while (tmp != NULL)
    {
        if (tmp->type == nts::ASTNodeType::COMPONENT)
            this->setCircuitComponent(tmp->value, this->getComponents().createComponent(tmp->lexeme, tmp->value));
        if (tmp->type == nts::ASTNodeType::LINK)
        {
            if (this->getFirst(tmp->value, ":") == "" ||
                this->getSecond(tmp->value, ":") == "" ||
                this->getFirst(tmp->lexeme, ":") == "" ||
                this->getSecond(tmp->lexeme, ":") == "")
                throw (LinksError("A component is not correctly linked : check the syntax twice."));
            if (!this->checkComponentExist(this->getFirst(tmp->value, ":")) ||
                !this->checkComponentExist(this->getFirst(tmp->lexeme, ":")))
                throw (LinksError("A component doesn't exists : check the syntax twice"));
            this->getCircuitComponent()[this->getFirst(tmp->value, ":")]->SetLink(atoi(this->getSecond(tmp->value, ":").c_str()),
                                                                                  *(this->getCircuitComponent())[this->getFirst(tmp->lexeme, ":")],
                                                                                  atoi(this->getSecond(tmp->lexeme, ":").c_str()));
            this->getCircuitComponent()[this->getFirst(tmp->lexeme, ":")]->SetLink(atoi(this->getSecond(tmp->lexeme, ":").c_str()),
                                                                                   *(this->getCircuitComponent())[this->getFirst(tmp->value, ":")],
                                                                                   atoi(this->getSecond(tmp->value, ":").c_str()));
        }
        tmp = tmp->children->back();
    }
}

std::string     nts::Parser::getFirst(const std::string &e, const std::string &v)
{
    return (e.substr(0, e.find(v)));
}

std::string     nts::Parser::getSecond(const std::string &e, const std::string &v)
{
    return (e.substr(e.find(v) + 1));
}

std::string     nts::Parser::guessLexeme(const std::string &e)
{
    return this->getFirst(e, " ");
}

std::string     nts::Parser::guessValue(const std::string &e)
{
    return this->getSecond(e, " ");
}

nts::ASTNodeType    nts::Parser::guessType(nts::t_ast_node *node,
                                           std::string &section)
{
    if (node->lexeme == ".chipsets:" ||
        node->lexeme == ".links:")
        return nts::ASTNodeType::SECTION;
    if (section == ".chipsets:")
        return nts::ASTNodeType::COMPONENT;
    if (section == ".links:")
        return (nts::ASTNodeType::LINK);
    return nts::ASTNodeType::DEFAULT;
}

std::string            nts::Parser::fillNode(nts::t_ast_node *node, const std::string &e,
                                             std::string &section)
{
    node->lexeme = this->guessLexeme(e);
    node->value = this->guessValue(e);
    node->type = this->guessType(node, section);
    if (node->type == nts::ASTNodeType::SECTION)
        section = node->lexeme;
    return (section);
}

nts::t_ast_node  *nts::Parser::createNode(nts::t_ast_node *curr, const std::string &e,
                                          std::string &section)
{
    if (curr == NULL)
    {
        curr = new t_ast_node(new std::vector<struct s_ast_node*>);
        section = this->fillNode(curr, e, section);
        curr->children->push_back(NULL);
        return (curr);
    }
    else
    {
        if (curr->children->back() == NULL)
        {
            curr->children->push_back(new t_ast_node(new std::vector<struct s_ast_node*>));
            section = this->fillNode(curr->children->back(), e, section);
            curr->children->back()->children->push_back(NULL);
        }
        else
            this->createNode(curr->children->back(), e, section);
    }
    return (curr);
}

nts::t_ast_node *nts::Parser::createTree()
{
    std::string section("NULL");
    t_ast_node  *ret = NULL;

    for (auto const &e : this->file)
        ret = this->createNode(ret, e, section);
    return (ret);
}

nts::Parser::Parser() : components(new Components()),
                        tree(NULL)
{ }

nts::Parser::~Parser()
{
    for (const auto &key_value : this->circuitComponent)
        delete key_value.second;
    this->circuitComponent.clear();
}