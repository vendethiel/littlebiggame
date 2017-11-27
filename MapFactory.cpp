#include <iostream>
#include "MapFactory.hh"
#include "GameWorld.hh"
#include "Platform.hh"
#include <sstream>
#include "Monster.hh"
#include "PickMonster.hh"

MapFactory::MapFactory()
{
  _actions = {
    {"monster", [](GameWorld &gw, std::istringstream &stream) {
      float x, y, maxx, maxy;
      /* on sait qu'on doit parser un monstre */
      stream >> x >> y >> maxx >> maxy;
      gw.AddEntity(new Monster(x, y, maxx, maxy));
    }},
    {"platform", [](GameWorld &gw, std::istringstream &stream) {
      std::string type;
      float x, y;

      stream >> type >> x >> y;
      /* on sait qu'on doit parser une plateforme */
      std::string sprite = "wall.png";
      auto ct = CollisionType::Platform;
      if (type == "wall")
        ct = CollisionType::Wall;
      if (type == "pole") {
        ct = CollisionType::Die;
        sprite = "flagpole.png";
      }
      gw.AddEntity(new Platform(x, y, ct, sprite));
    }},
    {"pick", [](GameWorld &gw, std::istringstream &stream) {
      float x, y, maxx, maxy;
      /* on sait qu'on doit parser un monstre */
      stream >> x >> y >> maxx >> maxy;
      gw.AddEntity(new PickMonster(x, y, maxx, maxy));
    }},
  };
 
}

GameWorld  MapFactory::readMap(std::string map)
{
  GameWorld gw;
	std::ifstream file(map);
	std::string line;
	std::string element;
	
  if (file.good() > 0) {
    //Get one line of the file
    while (std::getline(file, line)) {
      //Cut to the space to get one element and is position
      std::istringstream stream(line);

      stream >> element;
      //Add Element to the map
      _actions[element](gw, stream);
    }
  } else {
    std::cout << "The map file does't exist" << std::endl;
  } 
  return gw;
}


