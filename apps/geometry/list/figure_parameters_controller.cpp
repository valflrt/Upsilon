#include "figure_parameters_controller.h"
#include "../app.h"

namespace Geometry {
FigureParametersController::FigureParametersController(Responder * parentResponder): 
  ViewController(parentResponder),
  m_selectableTableView(this)
{

}

void FigureParametersController::didBecomeFirstResponder() {
  Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

void FigureParametersController::viewWillAppear() {
  selectRow(0);
}

bool FigureParametersController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK || event == Ion::Events::EXE) {
    StackViewController * stack = static_cast<StackViewController *>(parentResponder());
    stack->pop();
    stack->pop();
    stack->pop();
    return true;
  }
  return false;
}

/* ListViewDataSource */
int FigureParametersController::typeAtLocation(int i, int j) {
  return 0;
}

int FigureParametersController::reusableCellCount(int type) {
  return 2;
}

HighlightCell * FigureParametersController::reusableCell(int index, int type) {
  return &m_choicesCells[index];
}

int FigureParametersController::numberOfRows() const {
  return 2;
}
KDCoordinate FigureParametersController::rowHeight(int j) {
  return Metric::ParameterCellHeight;
}

KDCoordinate FigureParametersController::cumulatedHeightFromIndex(int j) {
  return Metric::ParameterCellHeight*j;
}

int FigureParametersController::indexFromCumulatedHeight(KDCoordinate offsetY) {
  return (offsetY - 1) / Metric::ParameterCellHeight;
}

void FigureParametersController::willDisplayCellForIndex(HighlightCell * cell, int index) {

}

/*bool FigureParametersController::textFieldShouldFinishEditing(TextField * textField, Ion::Events::Event event) {
  return (event == Ion::Events::Up);
  /*return (event == Ion::Events::Down && selectedRow() < numberOfRows()-1)
     || (event == Ion::Events::Up && selectedRow() > 0)
     || TextFieldDelegate::textFieldShouldFinishEditing(textField, event);*//*
}
bool FigureParametersController::textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) {
  return true;
}*/

}
