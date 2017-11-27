#include "ResourceManager.hh"

ResourceManager& ResourceManager::GetInstance()
{
  static ResourceManager inst;
  return inst;
}

sf::Sprite* ResourceManager::GetSprite(const std::string &textureFile, bool repeated)
{
  if (!_sprites[textureFile])
  {
    sf::Texture *texture = new sf::Texture();
    _textures[textureFile].reset(texture);
    texture->loadFromFile(textureFile);
    texture->setRepeated(repeated);
    _sprites[textureFile].reset(new sf::Sprite(*texture));
  }
  return _sprites[textureFile].get();
}
