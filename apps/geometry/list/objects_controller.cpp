#include "objects_controller.h"

namespace Geometry {

ObjectsController::ObjectsController(Responder * responder) :
  NestedMenuController(this)
{
  
}

int ObjectsController::numberOfRows() const {
  return 0;
}

int ObjectsController::reusableCellCount(int type) {
  return 0;
}

int ObjectsController::typeAtLocation(int i, int j) {
  return 0;
}

bool ObjectsController::selectLeaf(int type) {
  return false;
}

HighlightCell * ObjectsController::leafCellAtIndex(int index) {
  return nullptr;
}

HighlightCell * ObjectsController::nodeCellAtIndex(int index) {
  return nullptr;
}

}
