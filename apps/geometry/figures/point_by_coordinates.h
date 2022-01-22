#ifndef POINT_BY_COORDINATES_H
#define POINT_BY_COORDINATES_H

#include <poincare/expression.h>
#include "point.h"

namespace Geometry {

class PointByCoordinatesNode : public PointNode {
public:
  virtual size_t size() const override { return sizeof(PointByCoordinatesNode); }
  virtual int numberOfChildren() const override { return 2; }
  virtual FigureDefinitionType definitionType() const override { return FigureDefinitionType::PointByCoordinates; }
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
  static int numberOfParameters() { return 2; }
  static FigureType parameterTypeAtIndex(int i) { return FigureType::Expression; }
};

}

#endif
