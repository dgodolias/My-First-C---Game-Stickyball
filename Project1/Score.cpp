#include "Score.h"

void Score::update(float dt)
{
}

void Score::init()
{
	m_brush_box.outline_opacity = 0.0f;
	m_brush_box.fill_opacity = 1.0f;

	SETCOLOR(m_brush_box.fill_color, 1.0f, 0.0f, 0.0f);
	SETCOLOR(m_brush_box_debug.outline_color, 0.3f, 1.0f, 0.2f);
}

void Score::draw()
{
	graphics::drawRect(m_pos_x, m_pos_y,
		m_width, m_height, m_brush_box);
	if (GameState::getInstance()->m_debbuging) {
		graphics::drawRect(m_pos_x, m_pos_y,
			m_width, m_height, m_brush_box_debug);
	}
}
