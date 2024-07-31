#include "power.h"
#include "random_XY_axis.h"
#include "player.h"
#include "nail.h"
#include <random>
#include "sound.h"

int increaserr = -1;
float size_multiplier = 1;

int time_power_disappeared;
bool readyToCollided_field = true;

std::string properties[] = { "-50%velocitynails","+50%velocitynails","-25%velocityplayer","+25%velocityplayer","-100%velocitynails" };
std::string cur_prop;

Sound* PpowerAppearsSoundEffect;
Sound* PgreenSoundEffect;
Sound* PredSoundEffect;
Sound* PnailsFreeze;

void Power::update(float dt)
{
	if (graphics::getGlobalTime() > spawnTime - dt && graphics::getGlobalTime() < spawnTime + dt && !this->isActive()) {
		this->setActive(true);
		PpowerAppearsSoundEffect->init();

		m_pos_x = generateRandomNumber(80, GameState::getInstance()->getCanvasWidth() - 80);
		m_pos_y = generateRandomNumber(100, GameState::getInstance()->getCanvasHeight() - 100);

		cur_prop = properties[generateRandomNumber(100,199) % 5];
		m_brush_box.texture = GameState::getInstance()->getFullAssetPath(cur_prop + ".png");
	}

	if (this->justcollided && !this->isActive()) {
		
		if (cur_prop == "-50%velocitynails") {
			for (auto p_gob : GameState::getInstance()->getLevel()->m_collidable_objects) {
				Box* ob = dynamic_cast<Box*>(p_gob);
				if (dynamic_cast<Nail*>(ob) != nullptr) {
					initial_nails_velocity = dynamic_cast<Nail*>(ob)->getVelocity();
					dynamic_cast<Nail*>(ob)->setVelocity(dynamic_cast<Nail*>(ob)->getVelocity() * 0.5f);
					//std::cout << dynamic_cast<Nail*>(ob)->getVelocity() << std::endl;
				}
			}

			PgreenSoundEffect->init();
		}
		else if (cur_prop == "+50%velocitynails") {
			for (auto p_gob : GameState::getInstance()->getLevel()->m_collidable_objects) {
				Box* ob = dynamic_cast<Box*>(p_gob);
				if (dynamic_cast<Nail*>(ob) != nullptr) {
					initial_nails_velocity = dynamic_cast<Nail*>(ob)->getVelocity();
					dynamic_cast<Nail*>(ob)->setVelocity(dynamic_cast<Nail*>(ob)->getVelocity() * 1.5f);
					//std::cout << dynamic_cast<Nail*>(ob)->getVelocity() << std::endl;
				}
			}

			PredSoundEffect->init();
		}
		else if (cur_prop == "-25%velocityplayer") {
			initial_player_velocity = GameState::getInstance()->getPlayer()->velocitymultiplier;
			GameState::getInstance()->getPlayer()->velocitymultiplier *= 0.75;

			PredSoundEffect->init();
		}
		else if (cur_prop == "+25%velocityplayer") {
			initial_player_velocity = GameState::getInstance()->getPlayer()->velocitymultiplier;
			GameState::getInstance()->getPlayer()->velocitymultiplier *= 1.25;

			PgreenSoundEffect->init();
		}
		else {
			for (auto p_gob : GameState::getInstance()->getLevel()->m_collidable_objects) {
				Box* ob = dynamic_cast<Box*>(p_gob);
				if (dynamic_cast<Nail*>(ob) != nullptr) {
					initial_nails_velocity = dynamic_cast<Nail*>(ob)->getVelocity();
					dynamic_cast<Nail*>(ob)->setVelocity(0);

					dynamic_cast<Nail*>(ob)->setWidth(592 * ((GameState::getInstance()->getCanvasHeight() + GameState::getInstance()->getCanvasWidth()) / 8248.f));
					dynamic_cast<Nail*>(ob)->setHeight(592 * ((GameState::getInstance()->getCanvasHeight() + GameState::getInstance()->getCanvasWidth()) / 8248.0f));

					if (dynamic_cast<Nail*>(ob)->isLeft) {
						dynamic_cast<Nail*>(ob)->m_brush_box.texture = GameState::getInstance()->getFullAssetPath("left_spikes_iced.png");
						dynamic_cast<Nail*>(ob)->setPosx(dynamic_cast<Nail*>(ob)->getPosx() + 20);
					}
					else {
						dynamic_cast<Nail*>(ob)->m_brush_box.texture = GameState::getInstance()->getFullAssetPath("right_spikes_iced.png");
						dynamic_cast<Nail*>(ob)->setPosx(dynamic_cast<Nail*>(ob)->getPosx() - 20);
					}
				}
			}

			PnailsFreeze->init();
		}		
		

		readyToCollided_field = false;
		time_power_disappeared = graphics::getGlobalTime();
		justcollided = false;
	}



	if ( graphics::getGlobalTime() - spawnTime > 6000) {		// diarkeia power on screen		
		
		this->setActive(false);
		
		spawnTime = generateRandomNumber(graphics::getGlobalTime() + 17000, graphics::getGlobalTime()+ 19000);		//syxnothta emfanishs power
	}
	
	//std::cout << graphics::getGlobalTime() - spawnTime << std::endl;
	if (time_power_disappeared + 10000 < graphics::getGlobalTime() && !readyToCollided_field) {		//diarkeia power pou krataei ston paikth
		if (cur_prop == "-50%velocitynails" || cur_prop == "+50%velocitynails" || cur_prop == "-100%velocitynails") {
			for (auto p_gob : GameState::getInstance()->getLevel()->m_collidable_objects) {
				Box* ob = dynamic_cast<Box*>(p_gob);
				if (dynamic_cast<Nail*>(ob) != nullptr) {
					dynamic_cast<Nail*>(ob)->setVelocity(initial_nails_velocity);

					dynamic_cast<Nail*>(ob)->setWidth(260 * ((GameState::getInstance()->getCanvasHeight() + GameState::getInstance()->getCanvasWidth()) / 8248.f));
					dynamic_cast<Nail*>(ob)->setHeight(592 * ((GameState::getInstance()->getCanvasHeight() + GameState::getInstance()->getCanvasWidth()) / 8248.0f));
					if (cur_prop == properties[4]) {
						
						if (dynamic_cast<Nail*>(ob)->isLeft) {
							dynamic_cast<Nail*>(ob)->m_brush_box.texture = GameState::getInstance()->getFullAssetPath("left_spikes.png");
							dynamic_cast<Nail*>(ob)->setPosx(dynamic_cast<Nail*>(ob)->getPosx() - 20);
						}
						else {
							dynamic_cast<Nail*>(ob)->m_brush_box.texture = GameState::getInstance()->getFullAssetPath("right_spikes.png");
							dynamic_cast<Nail*>(ob)->setPosx(dynamic_cast<Nail*>(ob)->getPosx() + 20);
						}
					}
				}
			}

			initial_nails_velocity = -1;
		}
		else{
			GameState::getInstance()->getPlayer()->velocitymultiplier = initial_player_velocity;

			initial_player_velocity = -1;
		}	

		readyToCollided_field = true;		
	}

	if (size_multiplier <= 0.7f) {
		increaserr = 1;
	}
	else if (size_multiplier >= 1.0) {
		increaserr = -1;
	}

	size_multiplier += increaserr * 0.002f;
	this->setWidth(initial_width * size_multiplier);
	this->setHeight(initial_height * size_multiplier);
}

void Power::init()
{
	for (Sound* sound : GameState::getInstance()->getLevel()->m_sounds) {
		if (sound->getAsset() == "power_appears_soundeffect.mp3") PpowerAppearsSoundEffect = sound;
		if (sound->getAsset() == "green_soundeffect.mp3") PgreenSoundEffect = sound;
		if (sound->getAsset() == "red_soundeffect.mp3") PredSoundEffect = sound;
		if (sound->getAsset() == "ice_crackling_sound.mp3") PnailsFreeze = sound;
	}

	Box::init();

	m_pos_x = generateRandomNumber(50, GameState::getInstance()->getCanvasWidth() - 50);
	m_pos_y = generateRandomNumber(60, GameState::getInstance()->getCanvasHeight() - 60);
	spawnTime = generateRandomNumber(graphics::getGlobalTime() + 17000, graphics::getGlobalTime()+ 19000);


	m_brush_box.fill_opacity = 1.0f;
	m_brush_box.outline_opacity = 0.0f;

	m_brush_box.outline_opacity = 0.0f;


	this->setActive(false);
	readyToCollided_field = true;
}

void Power::draw()
{
	Box::draw();
	if (this->isActive()) {
		graphics::drawRect(m_pos_x, m_pos_y,
			m_width * 1.1f , m_height * 1.1f, m_brush_box);
	}
}

