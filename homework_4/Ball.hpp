#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:

    void setVelocity(const Velocity& velocity);
    void setCollidable(bool isCollidable);
    bool getCollidable() const;
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    
    double m_radius{0};
    Color m_color{};

private:
    Velocity m_velocity{};
    Point m_center{};
    double m_mass{};
    const double m_PI  = 3.141592653589793238463;
    bool m_isCollidable{};
};
