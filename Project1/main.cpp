#include "sgg/graphics.h"
#include "gamestate.h"

namespace gp = graphics;

void init()
{
	GameState::getInstance()->init();	
}

void draw()
{
	GameState::getInstance()->draw();
}

void update(float dt)
{
	GameState::getInstance()->update(dt);
}

int main(int argc, char** argv)
{

	gp::createWindow(GameState::getInstance()->getCanvasWidth(),
		GameState::getInstance()->getCanvasHeight(), "Stickball");

	init();

	gp::setDrawFunction(draw);
	gp::setUpdateFunction(update);
	gp::setCanvasSize(GameState::getInstance()->getCanvasWidth(),
	GameState::getInstance()->getCanvasHeight());
	gp::setCanvasScaleMode(gp::CANVAS_SCALE_STRETCH);
	gp::startMessageLoop();
	return 0;
}