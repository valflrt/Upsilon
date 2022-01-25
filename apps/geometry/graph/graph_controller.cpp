#include "graph_controller.h"

namespace Geometry {

GraphController::GraphController(Responder * parentResponder, InputEventHandlerDelegate * inputEventHandlerDelegate, ButtonRowController * header, Shared::InteractiveCurveViewRange/*TODO -> Store*/ * store, Shared::CurveViewCursor * cursor, uint32_t * rangeVersion) :
  InteractiveCurveViewController(parentResponder, inputEventHandlerDelegate, header, store, nullptr, cursor, rangeVersion)
{
    /* WHEREIWAS: Now i must make the app launch again without crash, by replacing the multiples nullptr that I used... */
}

}
