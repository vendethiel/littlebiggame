#ifndef MUNSTER_HH__
#define MUNSTER_HH__

#include "AbstractEntity.hh"

class Monster : public AbstractEntity
{
public:
  Monster(float minX, float maxX, float minY, float maxY, std::string = "monster.png");

  void Update() override;

private:
  float _minX;
  float _maxX;
  float _minY;
  float _maxY;
};

#endif
