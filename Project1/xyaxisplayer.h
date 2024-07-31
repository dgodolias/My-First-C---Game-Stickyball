#pragma once
#include "sgg/graphics.h"
#include <vector>
#include <iostream>
#include <cmath> using namespace std;
#include "myfunctions.h"


std::vector<float>* get_X_Y_axis(const float& startingTheta, const float& x_start, const float& y_start,
	const float& x_current, const float& y_current, const float& xa,
	const float& ya, const float& xb, const float& yb, const float& startingv) {
	;
	std::vector<float>* vector = new std::vector<float>;
	float vx =StartingVelocityX( startingv, startingTheta);
	float new_x = pos_x(vx, x_start,x_current);
	float new_y = y_start - createTrajectoryFunc(startingTheta,startingv,new_x, x_start, y_start,ya,yb);
	
	*vector = { new_x, new_y };
	return vector;

}
