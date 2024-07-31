#pragma once
#include <math.h>
#include <algorithm>
#include <iostream>
#include <iostream>
struct Rectangle:public GameObject
{

protected:
    float m_pos_x = 0.0f;
    float m_pos_y = 0.0f;
    float m_width = 100.0f;
    float m_height =100.0f;



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

    bool intersect(Rectangle& other)
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
    float intersectDown(Rectangle& other)
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
    float intersectSideways(Rectangle& other)
    {
        std::cout <<"inside:"<< m_pos_x - this->getWidth() / 2 << " " << other.getPosx() + other.getWidth() / 2 <<" "<< (other.getPosx() + other.getWidth() / 2) - (m_pos_x - this->getWidth() / 2) << std::endl;
        if (this->getPosx() < other.getPosx()) return (other.getPosx() - other.getWidth() / 2)- (m_pos_x + this->getWidth() / 2);
        if (this->getPosx() > other.getPosx()) return (other.getPosx() + other.getWidth() / 2) - (m_pos_x - this->getWidth() / 2);
        return 0.0f;

    }

    /** Default ctor
    */
    Rectangle() :GameObject() {  }


    /** Basic Rectangle ctor.
    *   \param x is the x coordinate of the Rectangle center
    *   \param y is the y coordinate of the Rectangle center
    *   \param w is the width of the Rectangle
    *   \param h is the height of the Rectangle
    */
    Rectangle(float x, float y, float w, float h)
        : m_pos_x(x), m_pos_y(y), m_width(w), m_height(h) {}
};