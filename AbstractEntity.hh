#ifndef ABSTRACT_ENTITY_HH__
#define ABSTRACT_ENTITY_HH__

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

enum class CollisionType
{
  None, // doesn't collide with anything
  Kill, // kills you anyway
  Die_Top, // dies when you hit its "head"
  Die, // simply dies. Boom.
  Platform, // a platform
  Wall, // a wall
};


struct AbstractEntity
{
protected:
  AbstractEntity(const std::string &);

public:
  virtual void Update();
  virtual void Draw(sf::RenderWindow &);
  virtual std::unique_ptr<AbstractEntity> Spawn() const;

public:
  float GetX() const;
  float GetY() const;
  void SetPosition(float x, float y);

public:
  float GetVX() const;
  float GetVY() const;

  void SetVX(float vx);
  void SetVY(float vy);

  CollisionType GetCollisionType() const;

public:
  sf::IntRect GetBoundingBox() const;

public:
  bool IsAlive() const;
  bool IsDead() const;
  void Kill();

public:
  virtual ~AbstractEntity() = 0;
  
protected:
  float _x, _y;
  float _vx, _vy;
  CollisionType _collisionType;

private:
  bool _alive = true;

protected: /* protected as to handle left/right/jump "animations" */
  sf::Sprite* _sprite;
};

#endif
