#include "nail.h"
#include "util.h"
#include "box.h"
#include "gamestate.h"

namespace gp = graphics;

int step_for_score_changing = 10;

void Nail::update(float dt)
{    
    if (GameState::getInstance()->getPlayer()->points % step_for_score_changing != 0 && GameState::getInstance()->getPlayer()->points != 0) {
        changespeed = true;
    }
    if (GameState::getInstance()->getPlayer()->points == 0 && !readyToCollided_value) {
        readyToCollided_value = true;
        changespeed = false;
        velocity = 0.3f;
    }
    if (GameState::getInstance()->getPlayer()->points % step_for_score_changing == 0 && changespeed && velocity!=0) {
        velocity += 0.015f;
        velocity = velocity <= 0.69f ? velocity : 0.69f;
        changespeed = false;
    }

    if (this->GameObject::isActive())
    m_pos_y += velocity;

}

void Nail::init()
{   
    GameObject::setActive(false);
    m_brush_box.fill_opacity = 1.0f;
    m_brush_box.outline_opacity = 0.0f;
    m_brush_box.texture = GameState::getInstance()->getFullAssetPath(asset);

    m_brush_box.outline_opacity = 0.0f;
    m_brush_box_debug.fill_opacity = 0.1f;
    SETCOLOR(m_brush_box_debug.fill_color, 1.0f, 0.2f, 0.1f);
    SETCOLOR(m_brush_box_debug.outline_color, 1.0f, 0.3f, 0.2f);

    m_pos_y = -m_height / 2;
    changespeed = false;
}

void Nail::draw()
{
    graphics::drawRect(m_pos_x, m_pos_y,
        m_width, m_height, m_brush_box);

    if (GameState::getInstance()->m_debbuging) {
        graphics::drawRect(m_pos_x, m_pos_y,
            m_width, m_height, m_brush_box_debug);
    }
}
