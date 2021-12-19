#ifndef POINCARE_FIGURE_H
#define POINCARE_FIGURE_H

#include "figure_type.h"

using namespace Poincare;

namespace Geometry {

class FigureNode : public TreeNode {
public:
  virtual size_t size() const override = 0;

  virtual int numberOfChildren() const override { return 0; }

  virtual FigureType type() const = 0;
  virtual FigureDefinitionType definitionType() const = 0;
};

class Figure : public TreeHandle {
public:
  Figure(const FigureNode * node) : TreeHandle(node) {}
};

}

#endif
