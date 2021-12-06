#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H

namespace Geometry {

class PointNode : public FigureNode {
  size_t size() const override { return sizeof(PointNode); }
}

class Point : public Figure

}

#endif
