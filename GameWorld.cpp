#include <iostream>
#include <algorithm>
#include <functional>
#include "CollisionManager.hh"
#include "GameWorld.hh"
#include "Monster.hh"
#include "PickMonster.hh"
#include "Platform.hh"
#include "WorldStateObs.hh"

GameWorld::GameWorld(Character &character)
    : _character{character}
{
}

void GameWorld::Tick(sf::RenderWindow &window)
{
  // update everything
  std::for_each(_entities.begin(), _entities.end(), std::mem_fn(&AbstractEntity::Update));

  CollisionManager cm(_entities, _character);
  cm.Resolve();

  // clean dead entities
  _entities.erase(
      std::remove_if(_entities.begin(), _entities.end(), std::mem_fn(&AbstractEntity::IsDead)),
      _entities.end() // make sure we don't remove the end
  );

  std::vector<std::unique_ptr<AbstractEntity>> newEntities;
  for (auto &e : _entities)
  {
    auto spawn = e->Spawn();
    if (spawn)
    {
      newEntities.push_back(std::move(spawn));
    }
  }
  _entities.insert(_entities.end(),
                   std::make_move_iterator(newEntities.begin()),
                   std::make_move_iterator(newEntities.end()));

  // draw remaining entities
  int numMobs = 0, numPoles = 0;
  for (auto &e : _entities)
  {
    e->Draw(window);
    if (dynamic_cast<Monster *>(e.get()))
    {
      numMobs++;
    }
    else if (auto p = dynamic_cast<Platform *>(e.get()))
    {
      if (p->GetCollisionType() == CollisionType::Die)
        numPoles++;
    }
  }
  _character.Draw(window);

  NotifyAllClean(new WorldEventMobCount(numMobs));
  NotifyAllClean(new WorldEventPoleCount(numPoles));
  NotifyAllClean(new WorldEventCharacterState(_character.IsAlive()));
}

void GameWorld::AddEntity(AbstractEntity *e)
{
  _entities.emplace_back(e);
}
