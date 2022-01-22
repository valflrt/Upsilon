#include "figure_parameters_controller.h"
#include "../app.h"

namespace Geometry {

FigureParametersController::FigureParametersController(Responder * parentResponder):
  ViewController(parentResponder),
  m_lastSelectedRow(0),
  m_selectableTableView(this),
  m_okButton(&m_selectableTableView, I18n::Message::Ok, Invocation([](void * context, void * sender) {
      FigureParametersController * parameterController = (FigureParametersController *) context;
      parameterController->returnToMenu();
      return true;
    }, this))
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

void FigureParametersController::returnToMenu() {
  StackViewController * stack = static_cast<StackViewController *>(parentResponder());
  stack->pop();
  stack->pop();
  stack->pop();
}

/* ListViewDataSource */
int FigureParametersController::typeAtLocation(int i, int j) {
  if (j == m_numberOfParametersFunction()) {
    return 0; // It's equivalent to "None", so we can use it for button cell
  }
  return (int) m_typeOfParametersAtIndexFunction(j);
}

int FigureParametersController::reusableCellCount(int type) {
  if (type == 0) {
    return 1;
  }
  return type == (int) FigureType::Expression ? k_textCells: k_choiceCells;
}

HighlightCell * FigureParametersController::reusableCell(int index, int type) {
  if (type == 0) {
    return &m_okButton;
  }
  if (type == (int) FigureType::Expression) {
    return &m_textCells[index];
  }
  return &m_choicesCells[index];
}

int FigureParametersController::numberOfRows() const {
  return m_numberOfParametersFunction() + 1;
}
KDCoordinate FigureParametersController::rowHeight(int j) {
  if (j == numberOfRows()-1) {
    return Metric::ParameterCellHeight+k_buttonMargin;
  }
  return Metric::ParameterCellHeight;
}

KDCoordinate FigureParametersController::cumulatedHeightFromIndex(int j) {
  if (j == numberOfRows()) {
    return j*Metric::ParameterCellHeight+k_buttonMargin;
  }
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
  m_selectableTableView.reloadCellAtLocation(0, selectedRow());
  m_selectableTableView.reloadData();
  textField->setText(text);
  if (event == Ion::Events::EXE || event == Ion::Events::OK) {
    m_selectableTableView.selectCellAtLocation(selectedColumn(), selectedRow() + 1);
  } else {
    m_selectableTableView.handleEvent(event);
  }
  return true;
}

}
