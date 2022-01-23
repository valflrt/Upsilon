#ifndef GRAPH_VIEW_CONTROLLER_H
#define GRAPH_VIEW_CONTROLLER_H

#include "../shared/interactive_curve_view_controller.h"
#include "../shared/curve_view_cursor.h"
#include "../shared/cursor_view.h"
#include "../shared/round_cursor_view.h"

namespace Geometry {

class GraphController : public ViewController, public ButtonRowDelegate, public AlternateEmptyViewDefaultDelegate {
public:
  GraphController(Responder * parentResponder):
    ViewController(parentResponder),
    ButtonRowDelegate(nullptr, nullptr) {}
  /* ViewController */
  View * view() override { return nullptr; }
  const char * title() override { return I18n::translate(I18n::Message::GraphTab); }

  /* AlternateEmptyViewDefaultDelegate */
  virtual bool isEmpty() const override { return true; }
  virtual Responder * defaultController() override { return nullptr; }
  virtual I18n::Message emptyMessage() override { return I18n::Message::NoFigures; }
};

}

#endif