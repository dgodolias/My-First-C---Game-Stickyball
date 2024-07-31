
#ifndef COORDINATES_H
#define COORDINATES_H

#define g 9.81

static float createTrajectoryFunc(const float& theta, const float& v, const float& x_new,
	const float& x_start, const float& y_start, const float& ya, const float& yb) {
	double x = x_new - x_start;
	float y;
	y = (tan(theta) * x - (g / (2 * pow(v, 2) *
			pow(cos(theta), 2))) * pow(x, 2));
	
	return y;
}

static float createVelocity(const float& xa, const float& ya, const float& xb, const float& yb, const float& mult) {
	if (ya == yb) {
		if (xa > xb) return mult * pow(pow(xa - xb, 2) + pow(ya - yb, 2), 0.5f) / 2;
		if (xa < xb) return - mult * pow(pow(xa - xb, 2) + pow(ya - yb, 2), 0.5f) / 2;
		if (xa == xb) return 0;
	}
	if (ya > yb) return - mult * pow(pow(xa - xb, 2) + pow(ya - yb, 2), 0.5f) / 2;
	return mult * pow(pow(xa - xb, 2) + pow(ya - yb, 2), 0.5f) / 2;
}

static float starting_trajectory_angle(const float& xa,
	const float& ya, const float& xb, const float& yb) {
	if (xa == xb) return 1.57078f;
	return atan((ya - yb) / (xb - xa));
}


static float StartingVelocityX(const float& v, const float& theta) {

	if (theta < 0) {
		//std::cout << "velocity:" << -v * cos(theta) << std::endl;
		if (-v * cos(theta) == 0) return 0.01f;
		return -v * cos(theta);
	}
	//std::cout << "velocity:" << v * cos(theta) << std::endl;
	if (v * cos(theta) == 0) return 0.01f;
	return v * cos(theta);
}

static float StartingVelocityY(const float& xa, const float& xb, const float& ya, const float& yb, const float& v) {

	return v * sin(starting_trajectory_angle(xa, ya, xb, yb));

}

static float pos_x(const float& vx, const float& x_start, const float& x_current) {
	
	return x_current + vx / (12.f);
}

static float simpleTrajectoryFunc(const float& theta, const float& v, const float& x) {
	return (tan(theta) * x - (g / (2 * pow(v, 2) *
		pow(cos(theta), 2))) * pow(x, 2));
}

#endif