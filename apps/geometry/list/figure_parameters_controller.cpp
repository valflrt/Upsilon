#include "figure_parameters_controller.h"
#include "../app.h"

namespace Geometry {

FigureParametersController::FigureParametersController(Responder * parentResponder): 
  ViewController(parentResponder),
  m_lastSelectedRow(0),
  m_selectableTableView(this)
{
  for (int i = 0; i < k_choiceCells; i++) {    
    m_choicesCells[i].setParentResponder(&m_selectableTableView);
  }
  for (int i = 0; i < k_textCells; i++) {
    m_textCells[i].setParentResponder(&m_selectableTableView);
    m_textCells[i].textField()->setDelegates(this, this);
  }
}


void FigureParametersController::setParametersInfoFunctions(NumberOfParametersFunction numberOfParametersFunction, TypeOfParametersAtIndexFunction typeOfParametersAtIndexFunction) {
  m_numberOfParametersFunction = numberOfParametersFunction;
  m_typeOfParametersAtIndexFunction = typeOfParametersAtIndexFunction;
}

void FigureParametersController::didBecomeFirstResponder() {
  Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

void FigureParametersController::viewWillAppear() {
  selectRow(m_lastSelectedRow);
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
  return (int) m_typeOfParametersAtIndexFunction(i);
}

int FigureParametersController::reusableCellCount(int type) {
  return type == (int) FigureType::Expression ? k_textCells: k_choiceCells;
}

HighlightCell * FigureParametersController::reusableCell(int index, int type) {
  if (type == (int) FigureType::Expression) {
    return &m_textCells[index];
  }
  return &m_choicesCells[index];
}

int FigureParametersController::numberOfRows() const {
  return m_numberOfParametersFunction();
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

bool FigureParametersController::textFieldShouldFinishEditing(TextField * textField, Ion::Events::Event event) {
  return (event == Ion::Events::Down && selectedRow() < numberOfRows()-1)
     || (event == Ion::Events::Up && selectedRow() > 0)
     || TextFieldDelegate::textFieldShouldFinishEditing(textField, event);
}

bool FigureParametersController::textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) {
  return true;
}

}
