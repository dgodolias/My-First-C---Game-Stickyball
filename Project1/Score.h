#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include <string>
#include "util.h"

class Score : public Box {
    const int customRandMax = 612;
    std::string asset;
    graphics::Brush m_brush_score_text;

public:
    Score() {
        m_pos_y = 50;
        m_pos_x = 350.f;
        m_width = 75.0f;
        m_height = 75.0f;
    }
    void update(float dt) override;
    void init() override;
    void draw() override;
};