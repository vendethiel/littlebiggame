#ifndef TEMPORARY_OBJECT_HH__
#define TEMPORARY_OBJECT_HH__

#include "AbstractEntity.hh"

class TemporaryObject : public AbstractEntity
{
public:
  TemporaryObject(std::string sprite, int maxTicks, CollisionType collisionType, float x, float y, float vx, float vy);

public:
  void Update() override;

private:
  int _numTicks, _maxTicks;
};

#endif
