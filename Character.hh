#ifndef CHARACTER_HH__
#define CHARACTER_HH__

#include "AbstractEntity.hh"

class Character : public AbstractEntity
{
public:
  Character();

public:
  void Update() override;
  void Physics();

public:
  sf::View GetView() const;

public:
  void SelectSprite();

private:
  sf::Sprite* _stillSprite;
  sf::Sprite* _jumpSprite;
  sf::Sprite* _leftSprite;
  sf::Sprite* _rightSprite;
};

#endif
