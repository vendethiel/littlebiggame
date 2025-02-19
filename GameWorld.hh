#ifndef GAME_WORLD_HH__
#define GAME_WORLD_HH__

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "AbstractEntity.hh"
#include "Character.hh"
#include "IObservable.hh"

class GameWorld : public IObservable
{
public:
  GameWorld(Character &);

public:
  void Tick(sf::RenderWindow &);

public:
  void AddEntity(AbstractEntity *);
  void SetCharacter(Character *);

private:
  std::vector<std::unique_ptr<AbstractEntity>> _entities;
  Character &_character;
};

#endif
