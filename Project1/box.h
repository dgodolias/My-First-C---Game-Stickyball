#pragma once
#include <math.h>
#include <algorithm>
#include <iostream>
#include "gameobject.h"
#include "gamestate.h"
#include "util.h"

class Box:public GameObject
{
public:
    graphics::Brush m_brush_box_debug;
    graphics::Brush m_brush_box;
  
public:
    float m_pos_x;
    float m_pos_y;
    float m_width ;
    float m_height;



    /** Detects intersection (overlap) between this Rectangle and another Rectangle instance.
    *   \param other is a reference to another Rectangle instance to check for collision with
    *   \return true if the two Rectanglees overlap
    */
public:
    float getWidth() {
        return m_width;
    }

    float getHeight() {
        return m_height;
    }

    float getPosx() {
        return m_pos_x;
    }

    float getPosy() {
        return m_pos_y;
    }

    void setWidth(const float& width) {
        m_width = width;
    }

    void setHeight(const float& height) {
        m_height = height;
    }

    void setPosx(const float& posx) {
        m_pos_x = posx;
    }

    void setPosy(const float& posy) {
        m_pos_y = posy;
    }

    bool intersect(Box& other)
    {
        //std::cout<< fabs(m_pos_x - other.m_pos_x) * 2.0f << " " << (m_width + other.m_width) << " " << fabs(m_pos_y - other.m_pos_y) * 2.0f << " " << (m_height + other.m_height) << " " << std::endl;
        return (fabs(m_pos_x - other.m_pos_x) * 2.0f < (m_width + other.m_width)) &&
            (fabs(m_pos_y - other.m_pos_y) * 2.0f < (m_height + other.m_height));
    }

    /** Detects an intersection when this Rectangle is "above" (smaller y values) a target Rectangle (other)
    *   and reports the adjustment offset so that the two Rectanglees are separated.
    *
    *   \param other is the second (target) Rectangle to test collision on the vertical axis with.
    *   \return the offset this Rectangle needs to move in the y axis, so that it does not collide
    *   anymore with the target Rectangle (other), or 0.0f if no collision is found.
    */
    float intersectDown(Box& other)
    {
        if (fabs(m_pos_x - other.m_pos_x) * 2.0f >= (m_width + other.m_width) || m_pos_y > other.m_pos_y)
            return 0.0f;
        return std::min<float>(0.0f, other.m_pos_y - (other.m_height / 2.0f) - m_pos_y - (m_height / 2.0f));
    }

    /** Detects a horizontal intersection this Rectangle is beside a target Rectangle (other).
    *   and reports the adjustment offset so that the two Rectanglees are separated.
    *
    *   \param other is the second (target) Rectangle to test collision on the horizontal axis with.
    *   \return the offset this Rectangle needs to move in the x axis, so that it does not collide
    *   anymore with the target Rectangle (other), or 0.0f if no collision is found.
    */
    float intersectSideways(Box& other)
    {
        //std::cout <<"inside:"<< m_pos_x - this->getWidth() / 2 << " " << other.getPosx() + other.getWidth() / 2 <<" "<< (other.getPosx() + other.getWidth() / 2) - (m_pos_x - this->getWidth() / 2) << std::endl;
        if (this->getPosx() < other.getPosx()) return (other.getPosx() - other.getWidth() / 2)- (m_pos_x + this->getWidth() / 2) - 0.001f;
        if (this->getPosx() > other.getPosx()) return (other.getPosx() + other.getWidth() / 2) - (m_pos_x - this->getWidth() / 2) + 0.001f;
        return 0.0f;

    }

    /** Default ctor
    */
    Box() :GameObject() { 
        m_pos_x = 0.0f;
        m_pos_y = 0.0f;
        m_width = (GameState::getInstance()->getCanvasWidth() + GameState::getInstance()->getCanvasHeight()) / 20.f;
        m_height = (GameState::getInstance()->getCanvasWidth() + GameState::getInstance()->getCanvasHeight()) / 20.f;
    }

    Box(float mult) :GameObject() {
        m_pos_x = 0.0f;
        m_pos_y = 0.0f;
        m_width = mult * (GameState::getInstance()->getCanvasWidth() + GameState::getInstance()->getCanvasHeight()) / 20.f;
        m_height = mult * (GameState::getInstance()->getCanvasWidth() + GameState::getInstance()->getCanvasHeight()) / 20.f;
    }


    /** Basic Rectangle ctor.
    *   \param x is the x coordinate of the Rectangle center
    *   \param y is the y coordinate of the Rectangle center
    *   \param w is the width of the Rectangle
    *   \param h is the height of the Rectangle
    */
    Box(float x, float y, float w, float h)
        : m_pos_x(x), m_pos_y(y), m_width(w), m_height(h) {}

    void update(float dt) {}
    void init() {

        m_brush_box_debug.fill_opacity = 0.1f;
        SETCOLOR(m_brush_box_debug.fill_color, 0.2f, 1.0f, 0.1f);
        SETCOLOR(m_brush_box_debug.outline_color, 0.3f, 1.0f, 0.2f);

    }
    void draw() {
        if (GameState::getInstance()->m_debbuging) {
            graphics::drawRect(m_pos_x, m_pos_y,
                m_width, m_height, m_brush_box_debug);
        }
    }
};