#include <random>
#include "PickMonster.hh"
#include "TemporaryObject.hh"

PickMonster::PickMonster(float minX, float maxX, float minY, float maxY)
  : Monster(minX, maxX, minY, maxY, "pick.png")
{
  static std::mt19937 rng(time(0));
  static std::uniform_int_distribution<int> uid(0, 100);
  _extraTick = uid(rng);
}

std::unique_ptr<AbstractEntity> PickMonster::Spawn() const
{
  if (++_nTick >= 100 + _extraTick && _vx != 0.f) {
    _nTick = 0;
    float x = _x;
    float y = _y;
    float vx = _vx * 2.f;
    float vy = _vy ? _vy : -10.f;
    return std::make_unique<TemporaryObject>("chair16.png", 40, CollisionType::Kill, x, y, vx, vy);
  }
  return nullptr;
}
