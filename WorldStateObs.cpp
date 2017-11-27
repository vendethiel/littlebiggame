#include "WorldStateObs.hh"
#include "GameWorld.hh"

void WorldStateObs::Notify(IObservable*, WorldEvent* arg)
{
  /*if (WorldEventMobCount* e = dynamic_cast<WorldEventMobCount*>(arg)) {
    
    if (e->count == 0) {
      _gameOver = true;
      _playerWon = true;
    }
  } else */
  if (WorldEventCharacterState* e = dynamic_cast<WorldEventCharacterState*>(arg)) {
    if (!e->alive) {
      _gameOver = true;
      _playerWon = false;
    }
  } else if (auto* e = dynamic_cast<WorldEventPoleCount*>(arg)) {
    if (_expectPole == 0)
      _expectPole = e->count;
    else if (e->count != _expectPole) {
      _gameOver = true;
      _playerWon = true;
    }
  }
}

bool WorldStateObs::IsGameOver() const
{
  return _gameOver;
}

bool WorldStateObs::DidPlayerWin() const
{
  return _playerWon;
}
