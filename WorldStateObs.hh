#ifndef WORLD_STATE_OBS_HH__
#define WORLD_STATE_OBS_HH__

#include "IObserver.hh"

DEFINE_EMPTY_EVENT(Win); /* unused */
DEFINE_EVENT(MobCount, int, count);
DEFINE_EVENT(PoleCount, int, count);
DEFINE_EVENT(CharacterState, bool, alive);

class WorldStateObs : public IObserver
{
public:
  void Notify(IObservable*, WorldEvent* arg = nullptr) override;

public:
  bool IsGameOver() const;
  bool DidPlayerWin() const;

private:
  int _expectPole = 0;
  bool _gameOver = false;
  bool _playerWon = false;
};

#endif
