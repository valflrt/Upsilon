#ifndef POINCARE_FIGURE_H
#define POINCARE_FIGURE_H

using namespace Poincare;

namespace Geometry {

class FigureNode final : public TreeNode {
public:
  FigureNode(const native_uint_t * digits, uint8_t numberOfDigits);
  // TreeNode
  size_t size() const override;
  int numberOfChildren() const override { return 0; }
  virtual FigureType type() const = 0;
};

class Figure final : public TreeHandle {
    
};

}

#endif
