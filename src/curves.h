#ifndef TASK_CAD_1_CURVES_H_INCLUDED
#define TASK_CAD_1_CURVES_H_INCLUDED

#include <ostream>

struct Point {
  double x;
  double y;
  double z;
  friend std::ostream &operator<<(std::ostream &stream, Point point);
};

class Curve {
public:
  Curve &operator=(const Curve &) = delete;
  Curve() = default;
  Curve(const Curve &) = delete;
  virtual Point at(double t) const = 0;
  virtual Point derivative_at(double t) const = 0;
  virtual const char *tag() const = 0;
  virtual ~Curve() = default;
};

class Circle : public Curve {
  double m_radius;

public:
  Point at(double t) const override;
  Point derivative_at(double t) const override;
  const char *tag() const override;
  double radius();
  explicit Circle(double radius);
};

class Ellipse : public Curve {
  double m_radius_x;
  double m_radius_y;

public:
  Ellipse(double radius_x, double radius_y);
  Point at(double t) const override;
  Point derivative_at(double t) const override;
  const char *tag() const override;
};

class Helix : public Curve {
  double m_radius;
  double m_step;

public:
  Helix(double radius, double step);
  Point at(double t) const override;
  Point derivative_at(double t) const override;
  const char *tag() const override;
};

#endif
