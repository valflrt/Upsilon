#ifndef GEOMETRY_OBJECTS_CONTROLLER_H
#define GEOMETRY_OBJECTS_CONTROLLER_H

#include <escher/nested_menu_controller.h>

namespace Geometry {

class ObjectsController : public NestedMenuController {
public:
  ObjectsController(Responder * parentResponder);
  virtual int numberOfRows() const override;
  virtual int reusableCellCount(int type) override;
  virtual int typeAtLocation(int i, int j) override;
  virtual bool selectLeaf(int selectedRow) override;
  virtual HighlightCell * leafCellAtIndex(int index) override;
  virtual HighlightCell * nodeCellAtIndex(int index) override;
};

}

#endif
