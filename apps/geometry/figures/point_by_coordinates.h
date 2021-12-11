#ifndef POINT_BY_COORDINATES_H
#define POINT_BY_COORDINATES_H

#include <poincare/expression.h>
#include "point.h"

namespace Geometry {
    
class PointByCoordinatesNode : public PointNode {
public:
  virtual size_t size() const override { return sizeof(PointByCoordinatesNode); }
  virtual int numberOfChildren() const override { return 2; }
  virtual FigureType type() const override { return FigureType::Point; }
  virtual FigureType subtype() const override { return FigureType::PointByCoordinates; }
#if POINCARE_TREE_LOG
  void logNodeName(std::ostream & stream) const override {
    stream << "PointByCoordinates";
  }
#endif
};

class PointByCoordinates : public Figure {
public:
  PointByCoordinates(const PointByCoordinatesNode * n) : Figure(n) {}
  static PointByCoordinates Builder(Expression x, Expression y) { return TreeHandle::FixedArityBuilder<PointByCoordinates, PointByCoordinatesNode>({x, x}); }

};

class PointByCoordinatesBuilder : public FigureBuilder {
public:
  virtual int numberOfParameters() const override { return 2; }
  virtual FigureType parameterTypeAtIndex() const override { return FigureType::Expression; }
private:
  Expression m_x;
  Expression m_y;
};

#endif
