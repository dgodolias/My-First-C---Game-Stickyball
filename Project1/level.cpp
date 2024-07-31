#pragma once
#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "util.h"
#include "wall.h"
#include "nail.h"
#include <typeinfo>
#include "music.h"
#include "power.h"
#include "sound.h"

namespace gp = graphics;

Nail* last_left;
Nail* next_left;

Nail* last_right;
Nail* next_right;

float minimum_dist = 135.0f;
float maximum_dist = 300.0f;

float distance_from_last_left;
float distance_from_last_right;

graphics::Brush m_brush_score;
Music backgroundMusic("background_music.mp3", 0.1, true);

Wall* wall1;
Wall* wall2;
    
Nail* nail1;
Nail* nail2;
Nail* nail3;
Nail* nail4;
Nail* nail5;
    
Nail* nail6;
Nail* nail7;
Nail* nail8;
Nail* nail9;
Nail* nail10;

Sound collisionSoundEffect("collision_sound.mp3", 0.4, false);
Sound spikesSoundEffect("spikes_sound_effect.mp3", 0.4, false);
Sound greenSoundEffect("green_soundeffect.mp3", 0.4, false);
Sound redSoundEffect("red_soundeffect.mp3", 0.4, false);
Sound powerAppearsSoundEffect("power_appears_soundeffect.mp3", 0.4, false);
Sound nailsFreeze("ice_crackling_sound.mp3", 0.4, false);

Power* power = new Power();
void Level::init()
{
    m_sounds.push_back(&collisionSoundEffect);
    m_sounds.push_back(&spikesSoundEffect);
    m_sounds.push_back(&greenSoundEffect);
    m_sounds.push_back(&redSoundEffect);
    m_sounds.push_back(&powerAppearsSoundEffect);
    m_sounds.push_back(&nailsFreeze);


    wall1 = new Wall("leftwall", "wall_pixelated.png", 0);
    wall2 = new Wall("rightwall", "wall_pixelated.png", GameState::getInstance()->getCanvasWidth());
    m_collidable_objects.push_back(wall1);
    m_collidable_objects.push_back(wall2);

    nail1 = new Nail("leftwall", "left_spikes.png", wall1->getWidth() / 2, true);
    nail2 = new Nail("leftwall", "left_spikes.png", wall1->getWidth() / 2, true);
    nail3 = new Nail("leftwall", "left_spikes.png", wall1->getWidth() / 2, true);
    nail4 = new Nail("leftwall", "left_spikes.png", wall1->getWidth() / 2, true);
    nail5 = new Nail("leftwall", "left_spikes.png", wall1->getWidth() / 2, true);
    m_collidable_objects.push_back(nail1);
    m_collidable_objects.push_back(nail2);
    m_collidable_objects.push_back(nail3);
    m_collidable_objects.push_back(nail4);
    m_collidable_objects.push_back(nail5);

    nail6 = new Nail("rightwall", "right_spikes.png", GameState::getInstance()->getCanvasWidth() - wall1->getWidth() / 2, false);
    nail7 = new Nail("rightwall", "right_spikes.png", GameState::getInstance()->getCanvasWidth() - wall1->getWidth() / 2, false);
    nail8 = new Nail("rightwall", "right_spikes.png", GameState::getInstance()->getCanvasWidth() - wall1->getWidth() / 2, false);
    nail9 = new Nail("rightwall", "right_spikes.png", GameState::getInstance()->getCanvasWidth() - wall1->getWidth() / 2, false);
    nail10 = new Nail("rightwall", "right_spikes.png", GameState::getInstance()->getCanvasWidth() - wall1->getWidth() / 2, false);
    m_collidable_objects.push_back(nail6);
    m_collidable_objects.push_back(nail7);
    m_collidable_objects.push_back(nail8);
    m_collidable_objects.push_back(nail9);
    m_collidable_objects.push_back(nail10);

    m_noncollidable_objects.push_back(power);

    backgroundMusic.init();

    m_brush_box.texture = GameState::getInstance()->getFullAssetPath("background_night.png");

    for (auto p_gob : m_noncollidable_objects) {
        if (p_gob) p_gob->init();
        
    }
    for (auto p_gob : m_collidable_objects) {
        if (p_gob) p_gob->init();
    }
    last_left = nullptr;
    next_left = nullptr;

    last_right= nullptr;
    next_right= nullptr;

    m_brush_score.fill_opacity = 1.0f;
    SETCOLOR(m_brush_score.fill_color, 1.0f, 1.0f, 1.0f);
}
void Level::draw()
{

    graphics::drawText(220.0f, 50.0f, 40.0f, "Score: " + std::to_string(GameState::getInstance()->getPlayer()->points), m_brush_score);
   
    float h = GameState::getInstance()->getCanvasHeight();
    float w = GameState::getInstance()->getCanvasWidth();

    float offset_x = GameState::getInstance()->m_global_offset_x + w / 2.0f;
    float offset_y = GameState::getInstance()->m_global_offset_y + h / 2.0f;

    gp::drawRect(offset_x, offset_y + 1, w, h, m_brush_box);

    if (GameState::getInstance()->getPlayer()->isActive())
        GameState::getInstance()->getPlayer()->draw();

    for (auto p_gob : m_noncollidable_objects)
        if (p_gob) p_gob->draw();
    for (auto p_gob : m_collidable_objects)
        if (p_gob) p_gob->draw();

}
Level::~Level()
{
    for (auto p_gob : m_collidable_objects)
        if (p_gob) delete[] p_gob;
    for (auto p_gob : m_noncollidable_objects)
        if (p_gob) delete[] p_gob;
    
}

void Level::update(float dt)
{
    if (GameState::getInstance()->start_game) {
        for (auto p_gob : m_noncollidable_objects)
            if (p_gob) p_gob->update(dt);

        Nail* nail;
        if (last_left == nullptr) {
            for (auto p_gob : m_collidable_objects) {    
                nail = dynamic_cast<Nail*>(p_gob);
                if (nail != nullptr) {
                    if (nail->isLeft) {
                        p_gob->setActive(true);
                        last_left = nail;
                        distance_from_last_left = generateRandomNumber(minimum_dist, maximum_dist);
                       
                        break;
                    }
                }
            }
        }

        if (next_left == nullptr) {
            for (auto p_gob : m_collidable_objects) {
                nail = dynamic_cast<Nail*>(p_gob);
                if (nail != nullptr && !p_gob->isActive()) {
                    if (nail->isLeft) {
                        next_left = nail;
                        
                        break;
                    }
                }
            }
        }
        if (last_left->getPosy() - last_left->getHeight() >= distance_from_last_left) {

            next_left->GameObject::setActive(true);
            last_left = next_left;
            next_left = nullptr;
            distance_from_last_left = generateRandomNumber(minimum_dist, maximum_dist);
        }
        if (last_right == nullptr) {
            for (auto p_gob : m_collidable_objects) {
                nail = dynamic_cast<Nail*>(p_gob);
                if (nail != nullptr) {
                    if (!nail->isLeft) {
                        p_gob->setActive(true);
                        last_right = nail;
                        distance_from_last_right = generateRandomNumber(minimum_dist, maximum_dist);
                        
                        break;
                    }
                }
            }
        }
        if (next_right == nullptr) {
            for (auto p_gob : m_collidable_objects) {
                nail = dynamic_cast<Nail*>(p_gob);
                if (nail != nullptr && !p_gob->isActive()) {
                    if (!nail->isLeft) {
                        next_right = nail;
                        break;
                    }
                }
            }
        }

        if (last_right->getPosy() - last_right->getHeight() >= distance_from_last_right) {

            next_right->GameObject::setActive(true);
            last_right = next_right;
            next_right = nullptr;
            distance_from_last_right = generateRandomNumber(minimum_dist, maximum_dist);
        }

        for (auto p_gob : m_collidable_objects) {
            nail = dynamic_cast<Nail*>(p_gob);
            if (nail != nullptr && p_gob->isActive() && nail->getPosy() -
                nail->getHeight() / 2 >= GameState::getInstance()->getCanvasHeight()) {
                p_gob->init();
                break;
            }
        }
        
    }
    
    for (auto p_gob : m_collidable_objects) 
        if (p_gob) p_gob->update(dt);

}

