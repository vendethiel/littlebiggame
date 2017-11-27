#include "TemporaryObject.hh"

TemporaryObject::TemporaryObject(std::string sprite, int maxTicks, CollisionType collisionType, float x, float y, float vx, float vy)
  : AbstractEntity(sprite),
    _numTicks{0},
    _maxTicks{maxTicks}
{
  _collisionType = collisionType;
  _x = x;
  _y = y;
  _vx = vx;
  _vy = vy;
}

void TemporaryObject::Update()
{
  if (++_numTicks > _maxTicks) {
    Kill();
  } else {
    AbstractEntity::Update();
  }
}
