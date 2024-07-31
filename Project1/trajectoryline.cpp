#include "trajectoryline.h"
#include "util.h"
#include <iostream>
#include <math.h>

float x_when_y_is_zero;

void TrajectoryLine::createCircles() {

	for (int i = 0; i < 10; i++) {
		//std::cout << "tempvx:" << temp_vx << std::endl;
		circles[i].setPosx(m_pos_x + temp_vx * (i + 1) * .2f);
		//std::cout << "&" << circles[i].getPosx() << std::endl;
		circles[i].setPosy(m_pos_y - createTrajectoryFunc(temp_theta, temp_v, circles[i].getPosx(),
			m_pos_x, m_pos_y, m_player->y_axis_mouse_when_dragging_start, y_current));
	}

}

TrajectoryLine::~TrajectoryLine()
{
	delete m_player;
}

void TrajectoryLine::update(float dt)
{
	

	if (this->isActive()) {
		m_player = GameState::getInstance()->getPlayer();
		m_pos_x = m_player->getPosx();
		m_pos_y = m_player->getPosy();

		graphics::MouseState mouse2;
		graphics::getMouseState(mouse2);


		x_current = mouse2.cur_pos_x;
		y_current = mouse2.cur_pos_y;

		temp_theta = starting_trajectory_angle(m_player->x_axis_mouse_when_dragging_start, m_player->y_axis_mouse_when_dragging_start,
			x_current, y_current);
		temp_v = createVelocity(m_player->x_axis_mouse_when_dragging_start, m_player->y_axis_mouse_when_dragging_start,
			x_current, y_current, m_player -> velocitymultiplier);
		temp_vx = StartingVelocityX(temp_v, temp_theta);

		tempTrajectoryFunction = createTrajectoryFunc;
		createCircles();
	}

}

void TrajectoryLine::init()
{
	m_active = false;
	for (int i = 0; i < 10; i++) {
		circles[i].m_brush_box.texture = GameState::getInstance()->getFullAssetPath("white_circle.png");
		SETCOLOR(circles[i].m_brush_box.fill_color,0.f, .75f, 1.f);
		circles[i].m_brush_box.fill_opacity = 1.0f;
		circles[i].m_brush_box.outline_opacity = 0.0f;
		circles[i].init();
	}

}

void TrajectoryLine::draw()
{
	if (this->isActive()) {
		for (int i = 0; i < 10; i++) {
			graphics::drawRect(circles[i].m_pos_x, circles[i].m_pos_y,
				circles[i].m_width, circles[i].m_height, circles[i].m_brush_box);
			circles[i].draw();
		}
	}
}
		


