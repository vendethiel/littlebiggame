#include <functional>
#include <algorithm>
#include "IObservable.hh"

void IObservable::AddObserver(IObserver* o)
{
  _observers.push_back(o);
}

void IObservable::RemoveObserver(IObserver* o)
{
  auto it = std::find(_observers.begin(), _observers.end(), o);
  if (it != _observers.end())
    _observers.erase(it);
}

void IObservable::NotifyAll(WorldEvent* arg)
{
  for (IObserver* o : _observers)
    o->Notify(this, arg);
}
