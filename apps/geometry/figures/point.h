#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H

#include "figure.h"
namespace Geometry {

class PointNode : public FigureNode {
  virtual FigureType type() const override { return FigureType::Point; }
};

class Point : public Figure {
public:
  Point(const PointNode * n) : Figure(n) {}
};

}

#endif
