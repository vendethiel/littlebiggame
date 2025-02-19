#ifndef SOUND_MANAGER_HH__
#define SOUND_MANAGER_HH__

#include <fstream>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SoundManager
{
public:
  static SoundManager &GetInstance();
  void playLoop();
  void stop();
  void playLittleSound(std::string sound);

private:
  SoundManager() = default;
  static SoundManager m_instance;

private:
  sf::Music _music;
  std::unordered_map<std::string, sf::Music> _sounds;
  std::string _lastSound;
};

#endif
