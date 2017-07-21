//
// GUI.hpp for GUI.hpp in /home/nicolas.trognot/rendu/cpp_nanotekspice/bonus/inc
//
// Made by Nicolas TROGNOT
// Login   <nicolas.trognot@epitech.net>
//
// Started on  Sat Mar  4 15:15:32 2017 Nicolas TROGNOT
// Last update Sun Mar  5 14:01:10 2017 Nicolas TROGNOT
//

#pragma once
# include <string>
# include <map>
# include <SFML/Graphics.hpp>
# include "Controller.hpp"
# define WIDTH 800
# define HEIGHT 600
# define MARGIN 100

namespace nts
{
  typedef struct	s_btn
  {
    char		is_input;
    sf::Vector2u	size;
    sf::Vector2f	pos;
    sf::Sprite		sprite;
  }			t_btn;

  class		Gui
  {
  private:
    sf::RenderWindow window;
    sf::Color bg_color;
    sf::Event event;
    sf::Font font;
    sf::Text text;
    std::map<std::string, sf::Texture> texture;
    std::map<std::string, sf::Sprite> sprite;
    std::map<std::string, t_btn> btns;
  public:
    Gui(nts::Controller &controller);
    void LoadComponents(nts::Controller &controller);
    void DisplayLabels();
    void Loop(nts::Controller &controller);
    void Events(nts::Controller &controller);
    ~Gui();
  };
}
