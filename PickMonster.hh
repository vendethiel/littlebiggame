#ifndef PICKMONSTER_HH__
#define PICKMONSTER_HH__

#include "Monster.hh"

class PickMonster : public Monster
{
public:
  PickMonster(float minX, float maxX, float minY, float maxY);

public:
  std::unique_ptr<AbstractEntity> Spawn() const override;

private:
  int _extraTick;
  mutable int _nTick = 0;
};

#endif
