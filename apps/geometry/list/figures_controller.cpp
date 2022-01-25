#include "figures_controller.h"
#include "definition_type_controller.h"
#include <apps/i18n.h>

namespace Geometry {

FiguresController::FiguresController(Responder * parentResponder):
  ViewController(parentResponder),
  m_selectableTableView(this, this, this, this),
  m_addFigureCell(),
  m_emptyCell(),
  m_figureTypeController(this, &m_definitionTypeController),
  m_definitionTypeController(&m_figureTypeController, &m_parametersController),
  m_parametersController(&m_definitionTypeController)
{
  m_addFigureCell.setMessage(I18n::Message::AddFigure);
}

bool FiguresController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK || event == Ion::Events::EXE) {
    if (isAddFigureRow(selectedRow())) {
      StackViewController * stack = static_cast<StackViewController *>(parentResponder());
      stack->push(&m_figureTypeController);
      return true;
    }
  }
  if (event == Ion::Events::Up && selectedRow() == 0) {
    m_selectableTableView.deselectTable();
    assert(selectedRow() == -1);
    Container::activeApp()->setFirstResponder(parentResponder()->parentResponder());
    return true;
  }
  return false;
}

void FiguresController::didBecomeFirstResponder() {
  Container::activeApp()->setFirstResponder(&m_selectableTableView);
}


HighlightCell * FiguresController::reusableCell(int index, int type) {
  assert(index >= 0);
  if (type == 2) {
    return &m_emptyCell;
  }
  return &m_addFigureCell;
}

void FiguresController::willDisplayCellAtLocation(HighlightCell * cell, int i, int j) {
  if (i == 0) {
    return;
  }
  EvenOddCell * myCell = (EvenOddCell *)cell;
  myCell->setEven(j%2 == 0);
  myCell->setHighlighted(i == selectedColumn() && j == selectedRow());
  myCell->reloadCell();
}

bool FiguresController::isAddFigureRow(int j) {
  return j == 0;
}

int FiguresController::reusableCellCount(int type) {
  if (type > 1) {
    return 1;
  }
  return 0;
}

int FiguresController::typeAtLocation(int i, int j) {
    if (isAddFigureRow(j)) {
        return i + 2;
    }
    return i;
}

}
