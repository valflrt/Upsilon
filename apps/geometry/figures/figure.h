#ifndef POINCARE_FIGURE_H
#define POINCARE_FIGURE_H

#include "figure_type.h"

using namespace Poincare;

namespace Geometry {

class FigureNode : public TreeNode {
public:
  FigureNode();
  
  virtual size_t size() const override;

  virtual int numberOfChildren() const override { return 0; }

  virtual FigureType type() const = 0;
  virtual FigureType subtype() const = 0;
};

class Figure : public TreeHandle {
public:
  Figure(const FigureNode * node) : TreeHandle(node) {}
};

class FigureBuilder {
public:
  virtual int numberOfParameters() const = 0;
  virtual FigureType parameterTypeAtIndex() const = 0;
};

}

#endif
