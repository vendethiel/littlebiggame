#include "AbstractEntity.hh"
#include "lbg.hh"
#include "ResourceManager.hh"

AbstractEntity::AbstractEntity(const std::string &textureFile)
  : _vx{0},
    _vy{0},
    _collisionType(CollisionType::None),
    _sprite(ResourceManager::GetInstance().GetSprite(textureFile))
{
  SetPosition(0, 0);
}

void AbstractEntity::Draw(sf::RenderWindow &window)
{
  /* XXX refactor, use sf::View */
  float newY = MAX_Y_SPRITE - _y;
  _sprite->setPosition(_x, newY);
  window.draw(*_sprite);
}

std::unique_ptr<AbstractEntity> AbstractEntity::Spawn() const
{
  return nullptr;
}

/* see SetPosition!! */
void AbstractEntity::Update()
{
  SetPosition(_x + _vx, _y + _vy);
}

float AbstractEntity::GetX() const
{
  return _x;
}

float AbstractEntity::GetY() const
{
  return _y;
}

void AbstractEntity::SetPosition(float x, float y)
{
  x = std::min(MAX_X_SPRITE, std::max(0.f, x));
  y = std::min(MAX_Y_SPRITE, std::max(0.f, y));
  _x = x;
  _y = y;
}

float AbstractEntity::GetVX() const
{
  return _vx;
}

float AbstractEntity::GetVY() const
{
  return _vy;
}

void AbstractEntity::SetVX(float vx)
{
  _vx = vx;
}

void AbstractEntity::SetVY(float vy)
{
  _vy = vy;
}

CollisionType AbstractEntity::GetCollisionType() const
{
  return _collisionType;
}

bool AbstractEntity::IsAlive() const
{
  return _alive;
}

bool AbstractEntity::IsDead() const
{
  return !_alive;
}

void AbstractEntity::Kill()
{
  _alive = false;
}

sf::IntRect AbstractEntity::GetBoundingBox() const
{
  sf::IntRect bb;
  bb.left = static_cast<unsigned int>(_x);
  bb.top = static_cast<unsigned int>(_y);
  bb.width = SPRITE_WIDTH;
  bb.height = SPRITE_HEIGHT;
  return bb;
}

AbstractEntity::~AbstractEntity()
{
}
