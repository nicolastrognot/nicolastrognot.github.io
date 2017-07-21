//
// GUI.cpp for GUI.cpp in /home/nicolas.trognot/rendu/cpp_nanotekspice/bonus/srcs
//
// Made by Nicolas TROGNOT
// Login   <nicolas.trognot@epitech.net>
//
// Started on  Sat Mar  4 15:18:13 2017 Nicolas TROGNOT
// Last update Sun Mar  5 14:15:18 2017 Nicolas TROGNOT
//

#include <iostream>
#include "../inc/Errors.hpp"
#include "../inc/Controller.hpp"
#include "../inc/GUI.hpp"

nts::Gui::Gui(nts::Controller &controller) : window(sf::VideoMode(WIDTH, HEIGHT), "My window"),
					     bg_color(219, 219, 219, 255)
{
  if (this->texture["input_false"].loadFromFile("misc/input_false.png") != true ||
      this->texture["input_true"].loadFromFile("misc/input_true.png") != true ||
      this->texture["clock_false"].loadFromFile("misc/clock_false.png") != true ||
      this->texture["clock_true"].loadFromFile("misc/clock_true.png") != true ||
      this->texture["true"].loadFromFile("misc/true.png") != true ||
      this->texture["false"].loadFromFile("misc/false.png") != true ||
      this->texture["output_false"].loadFromFile("misc/output_false.png") != true ||
      this->texture["output_true"].loadFromFile("misc/output_true.png") != true ||
      this->texture["output_undefined"].loadFromFile("misc/output_undefined.png") != true ||
      this->font.loadFromFile("misc/CaviarDreams_Bold.ttf") != true)
    throw(NtsError("Error while loading the SFML..."));
  this->text.setFont(this->font);
  this->text.setCharacterSize(24);
  this->text.setColor(sf::Color::Red);
  for (auto &e : this->texture)
    this->sprite[e.first] = sf::Sprite(texture[e.first]);
  this->LoadComponents(controller);
  (void)controller;
}

void nts::Gui::Events(nts::Controller &controller)
{
  while (this->window.pollEvent(this->event))
    {
      if (this->event.type == sf::Event::Closed)
	this->window.close();
      if (this->event.type == sf::Event::KeyPressed &&
	  this->event.key.code == sf::Keyboard::Escape)
	this->window.close();
      if (this->event.type == sf::Event::MouseButtonReleased)
	{
	  sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	  for (auto &e : this->btns)
	    {
	      if (e.second.is_input == 1)
		{
		  if (localPosition.x > e.second.sprite.getPosition().x &&
		      localPosition.y > e.second.sprite.getPosition().y &&
		      localPosition.x < e.second.sprite.getPosition().x + e.second.size.x &&
		      localPosition.y < e.second.sprite.getPosition().y + e.second.size.y)
		    {
		      nts::Tristate tmp;
		      sf::Vector2f myPos(this->btns[e.first].sprite.getPosition());
		      tmp = controller.getParser().getCircuitComponent()[e.first]->Compute();
		      if (tmp == nts::Tristate::TRUE)
			{
			  this->btns[e.first].sprite = this->sprite["input_false"];
			  tmp = nts::Tristate::FALSE;
			}
		      else
			{
			  this->btns[e.first].sprite = this->sprite["input_true"];
			  tmp = nts::Tristate::TRUE;
			}
		      this->btns[e.first].sprite.setPosition(myPos);
		      dynamic_cast<nts::Input *>
			(controller.getParser().getCircuitComponent()[e.first])->setState(tmp);
		      controller.simulate("NULL");
		    }
		}
	    }
	}
    }
  (void)controller;
}

void nts::Gui::LoadComponents(nts::Controller &controller)
{
  sf::Vector2f myPos(50, 50);

  for (auto &e : controller.getParser().getCircuitComponent())
    {
      this->btns[e.first].is_input = 0;
      if (dynamic_cast<nts::Input *>(e.second) != nullptr)
	{
	  this->btns[e.first].is_input = 1;
	  nts::Tristate j = e.second->Compute(1);
	  if (j == nts::Tristate::TRUE)
	    {
	      this->btns[e.first].size = this->texture["input_true"].getSize();
	      this->btns[e.first].sprite = this->sprite["input_true"];
	      this->btns[e.first].sprite.setPosition(myPos);
	      myPos.y += MARGIN;
	      if (myPos.y + MARGIN > HEIGHT)
		{
		  myPos.y = 50;
		  myPos.x += MARGIN;
		}
	    }
	  else
	    {
	      this->btns[e.first].size = this->texture["input_false"].getSize();
	      this->btns[e.first].sprite = this->sprite["input_false"];
	      this->btns[e.first].sprite.setPosition(myPos);
	      myPos.y += MARGIN;
	      if (myPos.y + MARGIN > HEIGHT)
		{
		  myPos.y = 50;
		  myPos.x += MARGIN;
		}
	    }
	}
      else if (dynamic_cast<nts::Clock *>(e.second) != nullptr)
	{
	  this->btns[e.first].is_input = 2;
	  nts::Tristate j = e.second->Compute(1);
	  if (j == nts::Tristate::TRUE)
	    {
	      this->btns[e.first].size = this->texture["clock_true"].getSize();
	      this->btns[e.first].sprite = this->sprite["clock_true"];
	      this->btns[e.first].sprite.setPosition(myPos);
	      myPos.y += MARGIN;
	      if (myPos.y + MARGIN > HEIGHT)
		{
		  myPos.y = 50;
		  myPos.x += MARGIN;
		}
	    }
	  else
	    {
	      this->btns[e.first].size = this->texture["clock_false"].getSize();
	      this->btns[e.first].sprite = this->sprite["clock_false"];
	      this->btns[e.first].sprite.setPosition(myPos);
	      myPos.y += MARGIN;
	      if (myPos.y + MARGIN > HEIGHT)
		{
		  myPos.y = 50;
		  myPos.x += MARGIN;
		}
	    }
	}
      else if (dynamic_cast<nts::Output *>(e.second) != nullptr)
	{
	  this->btns[e.first].is_input = 3;
	  nts::Tristate j = e.second->Compute(1);
	  if (j == nts::Tristate::TRUE)
	    {
	      this->btns[e.first].size = this->texture["output_true"].getSize();
	      this->btns[e.first].sprite = this->sprite["output_true"];
	      this->btns[e.first].sprite.setPosition(myPos);
	      myPos.y += MARGIN;
	      if (myPos.y + MARGIN > HEIGHT)
		{
		  myPos.y = 50;
		  myPos.x += MARGIN;
		}
	    }
	  else if (j == nts::Tristate::FALSE)
	    {
	      this->btns[e.first].size = this->texture["output_false"].getSize();
	      this->btns[e.first].sprite = this->sprite["output_false"];
	      this->btns[e.first].sprite.setPosition(myPos);
	      myPos.y += MARGIN;
	      if (myPos.y + MARGIN > HEIGHT)
		{
		  myPos.y = 50;
		  myPos.x += MARGIN;
		}
	    }
	  else
	    {
	      this->btns[e.first].size = this->texture["output_undefined"].getSize();
	      this->btns[e.first].sprite = this->sprite["output_undefined"];
	      this->btns[e.first].sprite.setPosition(myPos);
	      myPos.y += MARGIN;
	      if (myPos.y + MARGIN > HEIGHT)
		{
		  myPos.y = 50;
		  myPos.x += MARGIN;
		}
	    }
	}
    }
}

void nts::Gui::DisplayLabels()
{
  sf::Vector2i localPosition = sf::Mouse::getPosition(window);
  for (auto &e : this->btns)
    {
      if (localPosition.x > e.second.sprite.getPosition().x &&
	  localPosition.y > e.second.sprite.getPosition().y &&
	  localPosition.x < e.second.sprite.getPosition().x + e.second.size.x &&
	  localPosition.y < e.second.sprite.getPosition().y + e.second.size.y)
	{
	  this->text.setString(std::string("(").append(e.first).append(")"));
	  this->text.setPosition(localPosition.x + 10, localPosition.y + 10);
	  this->window.draw(this->text);
	}
    }
}

void nts::Gui::Loop(nts::Controller &controller)
{
  sf::Clock clock;

  while (this->window.isOpen())
    {
      sf::Time elapsed1 = clock.getElapsedTime();
      if (static_cast<int>(elapsed1.asSeconds()) >= 1)
	{
	  controller.simulate("NULL");
	  clock.restart();
	}
      this->window.clear(this->bg_color);
      this->Events(controller);
      this->LoadComponents(controller);
      for (auto &e : this->btns)
	{
	  if (e.second.is_input == 1 ||
	      e.second.is_input == 2 ||
	      e.second.is_input == 3)
	    this->window.draw(e.second.sprite,sf::RenderStates::Default);
	}
      this->DisplayLabels();
      this->window.display();
    }
}

nts::Gui::~Gui()
{

}
