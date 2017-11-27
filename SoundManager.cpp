#include "SoundManager.hh"
#include <SFML/Audio.hpp>
#include <iostream>

SoundManager SoundManager::m_instance;

SoundManager::SoundManager()
{
}


SoundManager& SoundManager::GetInstance()
{
	return m_instance;
}

void SoundManager::playLoop()
{
	if (!_music.openFromFile("audio/loop.ogg"))
    	return;
	_music.play();
	_music.setLoop(true);
}

void SoundManager::stop()
{
  _music.stop();
}

void SoundManager::playLittleSound(std::string name)
{
	if (_lastSound != "" && _sounds[_lastSound].getStatus() == sf::Music::Playing)
    return;
  _lastSound = "audio/" + name + ".ogg";
  if (_sounds.find(_lastSound) == _sounds.end()) {
    std::cout << "loaded sound: " << _lastSound << std::endl;
    _sounds[_lastSound].openFromFile(_lastSound);
  }
  _sounds[_lastSound].play();
}

