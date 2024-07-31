#include "sound.h"

void Sound::update(float dt)
{
	
}

void Sound::init()
{
	graphics::playSound(asset_dir+asset, volume, loops);
}

void Sound::draw()
{
}
