#pragma once
#include <string>
#include "gameobject.h"
#include "gamestate.h"
#include "box.h"
#include"player.h"
#include "sgg/graphics.h"
#include <iostream>
#include <random>

class Nail : public Box {
    const int customRandMax = 612;
    std::string asset;

    float velocity = 0.3f;
    bool readyToCollided_value = false;
public:
    bool changespeed = false;
    bool isLeft = true;
    Nail(const std::string& name, const std::string& asset, float x, bool sideofwall) : asset(asset), isLeft(sideofwall) {

        m_width = 260 * ((GameState::getInstance()->getCanvasHeight() + GameState::getInstance()->getCanvasWidth()) / 8248.f);
        m_height = 592 * ((GameState::getInstance()->getCanvasHeight() + GameState::getInstance()->getCanvasWidth()) / 8248.0f);
        if (sideofwall) {
            m_pos_x = x + this->getWidth()/2;
        }
        else {
            m_pos_x = x- this->getWidth() / 2;
        }
        m_pos_y = -m_height / 2;
    }

    Nail() : Box() {}

    float getVelocity() { return velocity; }
    void setVelocity(float x) { velocity = x; }

    float getPosx() {
        return m_pos_x;
    }

    float getPosy() {
        return m_pos_y;
    }
    void update(float dt) override;
    void init() override;
    void draw() override;
};