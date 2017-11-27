#ifndef MAP_FACTORY_HH__
#define MAP_FACTORY_HH__
#include <fstream>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include "GameWorld.hh"
class MapFactory
{
public:
  MapFactory();
  GameWorld readMap(std::string map);
private:
  void createElement(std::string element, float x, float y, float mapx, float mapy);
  std::unordered_map<
    std::string,
    std::function<void(GameWorld&, std::istringstream&)>
  > _actions;
};

#endif
