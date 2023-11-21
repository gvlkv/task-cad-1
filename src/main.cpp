#include "curves.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

static uint32_t rand_32() {
  static uint32_t seed = 429873;
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}

static double rand_between(double from, double to) {
  double d = double(rand_32()) / UINT32_MAX;
  return from + (to - from) * d;
}

int main() {
  // Populate a container of objects created in random manner with random
  // parameters.
  std::vector<std::shared_ptr<Curve>> curves;
  for (int i = 0; i < 10; i++) {
    switch (rand_32() % 3) {
    case 0:
      curves.push_back(std::make_shared<Circle>(rand_between(0, 10)));
      break;
    case 1:
      curves.push_back(
          std::make_shared<Ellipse>(rand_between(0, 10), rand_between(0, 10)));
      break;
    case 2:
      curves.push_back(
          std::make_shared<Helix>(rand_between(0, 10), rand_between(0, 10)));
      break;
    default:
      break;
    }
  }

  // Print coordinates of points and derivatives of all curves in the container
  // at t=PI/4.
  std::for_each(curves.begin(), curves.end(), [](auto c) {
    double at = M_PI_4;
    std::cout << c->tag() << "\tat " << at << " = " << c->at(at) << " "
              << c->derivative_at(at) << std::endl;
  });

  // Populate a second container that would contain only circles from the first
  // container. Make sure the second container shares(i.e.not clones) circles of
  // the first one, e.g.via pointers.
  std::vector<std::shared_ptr<Circle>> circles;
  for (auto c : curves) {
    if (auto cast_c = std::dynamic_pointer_cast<Circle>(c)) {
      circles.push_back(cast_c);
    }
  }

  // Sort the second container in the ascending order of circles’ radii. That
  // is, the first element has the smallest radius, the last - the greatest.
  std::sort(circles.begin(), circles.end(),
            [](auto c1, auto c2) { return c1->radius() < c2->radius(); });
  std::for_each(circles.begin(), circles.end(), [](auto c) {
    std::cout << c->tag() << " radius = " << c->radius() << std::endl;
  });

  // Compute the total sum of radii of all curves in the second container.
  double sum = 0;
#pragma omp parallel for reduction(+ : sum)
  for (size_t i = 0; i < circles.size(); i++)
    sum = sum + circles[i]->radius();
  std::cout << "The sum of radii is " << sum << std::endl;
}
