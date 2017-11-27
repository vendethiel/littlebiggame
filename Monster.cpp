#include <iostream>
#include "Monster.hh"

Monster::Monster(float minX, float maxX, float minY, float maxY, std::string sprite)
  : AbstractEntity(sprite),
    _minX{minX},
    _maxX{maxX},
    _minY{minY},
    _maxY{maxY}
{
  _collisionType = CollisionType::Die_Top;
  _vx = _minX == _maxX ? 0.f : 3.f;
  _vy = _minY == _maxY ? 0.f : 3.f;
  SetPosition(_minX, _minY);
}

void Monster::Update()
{
  AbstractEntity::Update();
  if (_x <= _minX || _x >= _maxX) {
    _vx *= -1;
  }
  if (_y <= _minY || _y >= _maxY) {
    _vy *= -1;
  }
}
