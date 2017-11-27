#include "lbg.hh"
#include "Character.hh"
#include "ResourceManager.hh"
#include <iostream>

Character::Character()
  : AbstractEntity("player.png"),
    _stillSprite{_sprite},
    _jumpSprite{ResourceManager::GetInstance().GetSprite("playerjump.png")},
    _leftSprite{ResourceManager::GetInstance().GetSprite("playerleft.png")},
    _rightSprite{ResourceManager::GetInstance().GetSprite("playerright.png")}
{
  _collisionType = CollisionType::None;
}

sf::View Character::GetView() const
{
  float halfView = WINDOW_WIDTH / 2;
  float screenX = std::min(std::max(_x, halfView), SCREEN_WIDTH - halfView);
  return {
    sf::Vector2f{screenX, WINDOW_HEIGHT / 2},
    sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT}
  };
}

void Character::Update()
{
  // delayed to CollisionManager
}

void Character::SelectSprite()
{
  //std::cout << "sprite vy: " << _vy << "; vx: " << _vx << std::endl;
  if (_vy != 0.f) {
    _sprite = _jumpSprite;
  } else if (_vx < 0.f) {
    _sprite = _leftSprite;
  } else if (_vx > 0.f) {
    _sprite = _rightSprite;
  } else {
    _sprite = _stillSprite;
  }
}
