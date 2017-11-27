#ifndef RESOURCE_MANAGER__
#define RESOURCE_MANAGER__

#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
  static ResourceManager &GetInstance();

public:
  sf::Sprite* GetSprite(const std::string &textureFile, bool repeated = false);

private:
  ResourceManager() = default;

private:
  std::unordered_map<std::string, std::unique_ptr<sf::Texture>> _textures;
  std::unordered_map<std::string, std::unique_ptr<sf::Sprite>> _sprites;
};

#endif
