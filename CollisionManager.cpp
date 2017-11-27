#include <iostream>
#include "CollisionManager.hh"
#include "SoundManager.hh"
#include "lbg.hh"

bool CollisionManager::_didJump = false;
bool CollisionManager::_didDoubleJump = false;
bool CollisionManager::_didReleaseSpace = false;

CollisionManager::CollisionManager(std::vector<std::unique_ptr<AbstractEntity>> const& entities, Character* character)
  : _entities{entities},
    _character{character}
{
}

namespace {
  bool goLeft()
  {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
  }

  bool goRight()
  {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
  }

  bool jump()
  {
   return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
  }
}

void CollisionManager::ResetJump()
{
  _didJump = _didDoubleJump = _didReleaseSpace = false;
}

void CollisionManager::Resolve()
{
  /* are we jumping this one frame? */
  bool doJump = false;
  float vx = _character->GetVX();
  float vy = _character->GetVY();
  // TODO move this to CollisionManager::PlayerPhysics()
  if (goLeft() && !goRight()) {
    vx -= 1.f;
  } else if (goRight() && !goLeft()) {
    vx += 1.f;
  } else {
    // stop instantly
    vx = 0.f;
  }
  vx = std::max(vx, -10.0f);
  vx = std::min(vx, 10.0f);

  if (_character->GetY() <= 0.f) {
    // reset Y speed+jump if touching the ground
    vy = 0.f;
    ResetJump();
  }
  if (jump() && !_didJump) {
    // reset state: we're on the ground, let's jump!
    ResetJump();
    doJump = true;
    _didJump = true;
    vy = 10.f;
  }

  if (!jump()) {
    // not jumping anymore!
    _didReleaseSpace = true;
  }
  
  if (jump() && _didJump && !_didDoubleJump && _didReleaseSpace) {
    // only allow double jump on another keypress, UP isn't "sticky"
    // set speed manually, so you can jump full speed even after your _vy went down
    vy += 10.f;
    doJump = true;
    _didDoubleJump = true;
  }

  vy = std::max(vy, -15.f);
  vy = std::min(vy, 15.f);
  
  // Update values
  _character->SetVX(vx);
  _character->SetVY(vy);

  AbstractEntity* currentPlatform = nullptr;
  auto bb = _character->GetBoundingBox();
  for (auto& e : _entities) {
    if (e->GetCollisionType() == CollisionType::Platform
        && bb.intersects(e->GetBoundingBox())) {
      currentPlatform = e.get();
    }
  }

  _character->AbstractEntity::Update();

  auto platformCollider = _character->GetBoundingBox();
  platformCollider.top -= 1;
  for (auto& e : _entities) {
    if (bb.intersects(e->GetBoundingBox())
        || ((e->GetCollisionType() == CollisionType::Platform
            || e->GetCollisionType() == CollisionType::Wall)
          && platformCollider.intersects(e->GetBoundingBox()))
        ) {
      Collide(e.get());
    }
  }


  if (_platform) {
    // we're on top of a platform
    if (!doJump) {
      if (_platform->GetCollisionType() == CollisionType::Platform) {
        _character->SetPosition(_character->GetX(), _platform->GetY() + SPRITE_HEIGHT - 1);
        _character->SetVY(0.f);
        ResetJump();
      } else if (currentPlatform) {
        currentPlatform = currentPlatform ? currentPlatform : _platform;
        std::cout << "current platform||wall" << std::endl;
        if (_character->GetVX() > 0.f) {
          _character->SetPosition(currentPlatform->GetX() - SPRITE_WIDTH, _character->GetY());
        } else {
          _character->SetPosition(currentPlatform->GetX() + SPRITE_WIDTH, _character->GetY());
        }
      } else {
        std::cout << "no current" << std::endl;
        _character->SetVY(-5.f);
      }
    }
  } else if (_wall) {
    if (_character->GetVX() > 0.f) {
      _character->SetPosition(_wall->GetX() - SPRITE_WIDTH, _character->GetY());
    } else {
      _character->SetPosition(_wall->GetX() + SPRITE_WIDTH, _character->GetY());
    }
    _character->SetVY(-5.f);
  } else // we don't collide platform
    if (_character->GetY() > 0.f // character is in the air
      && _character->GetVY() == 0.f) { // character is not falling/jumping
    // fall off platform
    _character->SetVY(-5.f);
  } else if (_character->GetY() > 0.f) {
    // fall
    _character->SetVY(_character->GetVY() - 1.f);
  }

  if (doJump)
    SoundManager::GetInstance().playLittleSound("jump");

  _character->SelectSprite();
}

void CollisionManager::Collide(AbstractEntity* e)
{
  switch (e->GetCollisionType()) {
  case CollisionType::None:
    break;

  case CollisionType::Kill:
    _character->Kill();
    break;

  case CollisionType::Die_Top:
    if (_character->GetY() > e->GetY()) {
      e->Kill();
    } else {
      _character->Kill();
    }
    break;

  case CollisionType::Die:
    e->Kill();
    break;

  case CollisionType::Wall:
    _wall = e;
    break;

  case CollisionType::Platform:
    int diffVY = _character->GetVY() < 0.f ? -_character->GetVY() : 0.f;
    if (_character->GetY() + diffVY > e->GetY() + 8) {
      _platform = e;
    } else {
      float newY = e->GetY();
      if (_character->GetVY() != 0)
        newY -= SPRITE_HEIGHT;
      if (_character->GetVX() < 0) {
        std::cout << "adjust a" << std::endl;
        _character->SetPosition(e->GetX() + SPRITE_WIDTH, newY);
        _character->SetVY(-5.f);
      } else if (_character->GetVX() > 0) {
        std::cout << "adjust b" << std::endl;
        _character->SetPosition(e->GetX() - SPRITE_WIDTH, newY);
        _character->SetVY(-5.f);
      } else {
        /*
        if (false) { 
          std::cout << "adjust c[" << _character->GetVY() << "]" << std::endl;
          _character->SetPosition(e->GetX() - SPRITE_WIDTH, newY);
        }
        */
        _character->SetVY(-5.f);
      }
    }
    break;
  }
}
