#ifndef GRAPH_VIEW_CONTROLLER_H
#define GRAPH_VIEW_CONTROLLER_H

#include "../shared/interactive_curve_view_controller.h"

namespace Geometry {

class GraphController : public Shared::InteractiveCurveViewController {
public:
  GraphController(Responder * parentResponder, InputEventHandlerDelegate * inputEventHandlerDelegate, ButtonRowController * header, Shared::InteractiveCurveViewRange * store, Shared::CurveViewCursor * cursor, uint32_t * rangeVersion);

  virtual Shared::InteractiveCurveViewRange * interactiveCurveViewRange() override { return nullptr; } //TOIMPLEMENT
  virtual Shared::CurveView * curveView() override { return nullptr; } //TOIMPLEMENT
  virtual void reloadBannerView() override { } //TOIMPLEMENT
  virtual bool handleEnter() override { return false; } //TOIMPLEMENT
  virtual void initCursorParameters() override { } //TOIMPLEMENT
  virtual bool moveCursorVertically(int direction) override { return false; } //TOIMPLEMENT
  virtual uint32_t rangeVersion() override { return 0; } //TOIMPLEMENT
  virtual bool cursorMatchesModel() override { return false; } //TOIMPLEMENT
  virtual Poincare::Coordinate2D<double> xyValues(int curveIndex, double t, Poincare::Context * context) const override { return Poincare::Coordinate2D<double>(0, 0); } //TOIMPLEMENT
  virtual bool closestCurveIndexIsSuitable(int newIndex, int currentIndex) const override { return false; }
  virtual int selectedCurveIndex() const override { return 0; }
  virtual int numberOfCurves() const override { return 0; }

  /* AlternateEmptyViewDefaultDelegate */
  virtual bool isEmpty() const override { return false; }
  virtual I18n::Message emptyMessage() override { return I18n::Message::NoFigures; }
private:
};

}

#endif