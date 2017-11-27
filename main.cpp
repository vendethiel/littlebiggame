#include <memory>
#include <SFML/Graphics.hpp>
#include "Background.hh"
#include "Character.hh"
#include "GameWorld.hh"
#include "MapFactory.hh"
#include "Monster.hh"
#include "Platform.hh"
#include "SoundManager.hh"
#include "WorldStateObs.hh"
#include "lbg.hh"

sf::Text& getText()
{
  static sf::Text affFps;
  affFps.setFillColor(sf::Color::Red);
  affFps.setCharacterSize(24);
  static sf::Font font;
  font.loadFromFile("font.ttf");
  affFps.setFont(font);
  return affFps;
}

void readEvent(sf::RenderWindow &window)
{
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
  }
}

std::vector<std::pair<float, float>> getClouds()
{
  return {
    {25, 500},
    {255, 450},
    {435, 350},
    {640, 550},
  };
}

int main()
{
  sf::RenderWindow window{sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Little Big Mario"};
  window.setFramerateLimit(30);
  MapFactory mf;
  GameWorld gw = mf.readMap("./map.txt");
  WorldStateObs wso;
  gw.AddObserver(&wso);
  SoundManager::GetInstance().playLoop();
  std::unique_ptr<Character> c = std::make_unique<Character>();
  sf::Clock fpsClock;
  Background bg(SCREEN_WIDTH, SCREEN_HEIGHT, getClouds());
  gw.SetCharacter(c.get());
  sf::Text& txt = getText();
  
  while (window.isOpen()) {
    int fpsNum = 1 / fpsClock.restart().asSeconds();
    txt.setString("FPS : " + std::to_string(fpsNum));
    readEvent(window);

    window.clear();
    window.setView(c->GetView());
    bg.Draw(window);
    txt.setPosition(window.getView().getCenter().x - WINDOW_WIDTH / 2, 0);
    window.draw(txt);
    gw.Tick(window);
    if (wso.IsGameOver()) {
      break;
    }

    window.display();
  }

  SoundManager::GetInstance().stop();
  window.clear();
  window.setView(window.getDefaultView());
  txt.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  txt.setString(wso.DidPlayerWin() ? "YOU WIN!" : "YOU LOSE!");
  window.draw(txt);
  window.display();
  while (window.isOpen()) {
    readEvent(window);
  }
}
