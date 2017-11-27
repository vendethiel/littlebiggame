#include "Platform.hh"

Platform::Platform(float x, float y, CollisionType ct, std::string sprite)
  : AbstractEntity(sprite)
{
  _collisionType = ct;
  SetPosition(x, y);
}
