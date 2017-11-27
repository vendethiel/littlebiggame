#ifndef COLLISION_MANAGER_HH__
#define COLLISION_MANAGER_HH__

#include <vector>
#include "AbstractEntity.hh"
#include "Character.hh"

class CollisionManager
{
public:
  CollisionManager(std::vector<std::unique_ptr<AbstractEntity>> const& entities, Character* character);
  void Resolve();

private:
  void ResetJump();

private:
  void Collide(AbstractEntity*);

private:
  AbstractEntity *_platform = nullptr;
  AbstractEntity *_wall = nullptr;
  std::vector<std::unique_ptr<AbstractEntity>> const& _entities;
  Character* _character;
  
private:
  static bool _didJump;
  static bool _didDoubleJump;
  /* XXX _didReleaseSpace can be "folded" into jump()
   * function, given a little state */
  static bool _didReleaseSpace;
};

#endif
