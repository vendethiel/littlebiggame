#ifndef IOBSERVABLE_HH_
#define IOBSERVABLE_HH_

#include <vector>
#include "IObserver.hh"

struct IObservable
{
  virtual ~IObservable() = default;

  virtual void AddObserver(IObserver*);
  virtual void RemoveObserver(IObserver*);

  void NotifyAll(WorldEvent* arg = nullptr);
  template<typename T>
  void NotifyAllClean(T* arg)
  {
    NotifyAll(arg);
    delete arg;
  }

private:
  std::vector<IObserver*> _observers;
};

#endif
