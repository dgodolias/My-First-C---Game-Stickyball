#include "wall.h"
#include "util.h"
#include "box.h"


void Wall::update(float dt)
{
}
void Wall::init(){

	m_brush_box.fill_opacity = 1.0f;
	m_brush_box.outline_opacity = 0.0f;
	m_brush_box.texture = GameState::getInstance()->getFullAssetPath(asset);

	m_brush_box.outline_opacity = 0.0f;
	m_brush_box_debug.fill_opacity = 0.1f;
}
void Wall::draw()
{
	graphics::drawRect(m_pos_x, m_pos_y,
		m_width, m_height, m_brush_box);

		if(GameState::getInstance()->m_debbuging){
			graphics::drawRect(m_pos_x, m_pos_y,
				m_width, m_height, m_brush_box_debug);
		}
}