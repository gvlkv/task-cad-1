#include "curves.h"
#include <cmath>

#undef NDEBUG
#include <cassert>

std::ostream &operator<<(std::ostream &stream, Point point) {
  return stream << '(' << point.x << ", " << point.y << ", " << point.z << ')';
}

////////////////////////////////////////

Circle::Circle(double radius) : m_radius(radius) {
  assert(m_radius > 0 && "Radius must be positive");
}
Point Circle::at(double t) const {
  return Point{m_radius * cos(t), m_radius * sin(t), 0};
}
Point Circle::derivative_at(double t) const {
  return Point{-m_radius * sin(t), m_radius * cos(t), 0};
}
const char *Circle::tag() const { return "Circle"; }
double Circle::radius() { return m_radius; }

////////////////////////////////////////

Ellipse::Ellipse(double radius_x, double radius_y)
    : m_radius_x(radius_x), m_radius_y(radius_y) {
  assert(m_radius_x > 0 && m_radius_y > 0 && "Radius must be positive");
}
Point Ellipse::at(double t) const {
  return Point{m_radius_x * cos(t), m_radius_y * sin(t), 0};
}
Point Ellipse::derivative_at(double t) const {
  return Point{-m_radius_x * sin(t), m_radius_y * cos(t), 0};
}
const char *Ellipse::tag() const { return "Ellipse"; }

////////////////////////////////////////

Helix::Helix(double radius, double step) : m_radius(radius), m_step(step) {
  assert(m_radius > 0 && "Radius must be positive");
}
Point Helix::at(double t) const {
  return Point{m_radius * cos(t), m_radius * sin(t), m_step * t / 2.0 / M_PI};
}
Point Helix::derivative_at(double t) const {
  return Point{-m_radius * sin(t), m_radius * cos(t), m_step / 2.0 / M_PI};
}
const char *Helix::tag() const { return "Helix"; }
