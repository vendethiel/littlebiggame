#ifndef PLATFORM_HH__
#define PLATFORM_HH__

#include "AbstractEntity.hh"

class Platform : public AbstractEntity
{
public:
  Platform(float x, float y, CollisionType = CollisionType::Platform, std::string = "wall.png");
};

#endif
