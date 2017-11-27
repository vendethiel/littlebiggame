#ifndef IOBSERVER_HH__
#define IOBSERVER_HH__

struct IObservable;

struct WorldEvent {
  virtual ~WorldEvent() = 0;
};
#define DEFINE_EVENT(name, arg_type, arg) \
  struct WorldEvent ## name : virtual WorldEvent { \
    WorldEvent ## name(arg_type tmp) : arg(tmp) { } \
    arg_type arg; \
  }

#define DEFINE_EMPTY_EVENT(name) \
  struct WorldEvent ## name : virtual WorldEvent { \
  }


struct IObserver
{
  virtual ~IObserver() = default;
  virtual void Notify(IObservable*, WorldEvent*) {}
};

#endif
