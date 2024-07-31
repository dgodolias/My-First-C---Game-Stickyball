#include "gameobject.h"
#include "gamestate.h"

GameObject::GameObject(const std::string& name) :
	m_name(name), m_state(GameState::getInstance()), m_id(m_next_id++)
{

}


void GameObject::update(float dt)
{
}

void GameObject::init()
{
}

void GameObject::draw()
{
}

GameObject::~GameObject() = default;

int GameObject::m_next_id = 1;
