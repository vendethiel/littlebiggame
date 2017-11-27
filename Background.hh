#ifndef BACKGROUND_HH__
#define BACKGROUND_HH__

#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>

class Background
{
  using CloudVector = std::vector<std::pair<float, float>>;

public:
  Background(int width, int height, CloudVector clouds = {});

public:
  void Draw(sf::RenderWindow &);
  
private:
  CloudVector _clouds;
  sf::Sprite* _floorSprite;
  sf::Sprite* _grassSprite;
  sf::Sprite* _cloudBotLeft;
  sf::Sprite* _cloudBotRight;
  sf::Sprite* _cloudTopLeft;
  sf::Sprite* _cloudTopRight;
};

#endif
