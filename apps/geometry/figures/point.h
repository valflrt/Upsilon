#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H

#include "figure.h"
namespace Geometry {

class PointNode : public FigureNode {
  
};

class Point : public Figure {
public:
  Point(const PointNode * n) : Figure(n) {}
};

}

#endif
