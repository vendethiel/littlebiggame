#include "Background.hh"
#include "lbg.hh"
#include "ResourceManager.hh"

Background::Background(int width, int height, Background::CloudVector clouds)
  : _clouds{std::move(clouds)},
    _floorSprite{ResourceManager::GetInstance().GetSprite("floor.png", true)},
    _grassSprite{ResourceManager::GetInstance().GetSprite("grass0.png", true)},
    _cloudBotLeft{ResourceManager::GetInstance().GetSprite("cloudbotleft.png", true)},
    _cloudBotRight{ResourceManager::GetInstance().GetSprite("cloudbotright.png", true)},
    _cloudTopLeft{ResourceManager::GetInstance().GetSprite("cloudtopleft.png", true)},
    _cloudTopRight{ResourceManager::GetInstance().GetSprite("cloudtopright.png", true)}
{
  _floorSprite->setPosition(0, height);
  _floorSprite->setTextureRect({0, 0, width, SPRITE_HEIGHT});

  _grassSprite->setPosition(0, height + SPRITE_HEIGHT); // 1 below floor
  _grassSprite->setTextureRect({0, 0, width * 2, static_cast<int>(WINDOW_HEIGHT - SCREEN_HEIGHT)});
}

void Background::Draw(sf::RenderWindow &window)
{
  //window.draw(*_skySprite); not used anymore...
  window.clear(sf::Color(139, 200, 255));
  window.draw(*_floorSprite);
  window.draw(*_grassSprite);
  for (auto const& cloudPos : _clouds) {
    int x = std::get<0>(cloudPos);
    int y = std::get<1>(cloudPos);
    _cloudTopLeft->setPosition(x, MAX_Y_SPRITE - y);
    _cloudTopRight->setPosition(x + SPRITE_WIDTH, MAX_Y_SPRITE - y);
    _cloudBotLeft->setPosition(x, MAX_Y_SPRITE - y + SPRITE_HEIGHT);
    _cloudBotRight->setPosition(x + SPRITE_WIDTH, MAX_Y_SPRITE - y + SPRITE_HEIGHT);
    window.draw(*_cloudTopLeft);
    window.draw(*_cloudTopRight);
    window.draw(*_cloudBotLeft);
    window.draw(*_cloudBotRight);
  }
}
