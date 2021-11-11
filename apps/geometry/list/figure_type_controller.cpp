#include "figure_type_controller.h"
#include "apps/i18n.h"

namespace Geometry {

static FigureType sTypes[] = {
  FigureType::Point,
  FigureType::Circle
};

static I18n::Message sMessages[] = {
  I18n::Message::Point,
  I18n::Message::Circle
};

FigureTypeController::FigureTypeController(Responder * parentResponder, DefinitionTypeController * definitionTypeController) :
  ViewController(parentResponder),
  m_selectableTableView(this),
  m_definitionTypeController(definitionTypeController),
  m_messages(sMessages)
{
  for (int i = 0; i < k_numberOfCells; i ++) {
    m_cells[i].setMessageFont(KDFont::LargeFont);
  }
}

void FigureTypeController::viewWillAppear() {
  selectRow(0);
}

void FigureTypeController::didBecomeFirstResponder() {
  //App::app()->snapshot()->setActivePage(App::Snapshot::Page::Distribution);
  Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

bool FigureTypeController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK || event == Ion::Events::EXE || event == Ion::Events::Right) {
    StackViewController * stack = static_cast<StackViewController *>(parentResponder());
    m_definitionTypeController->setFigureType(sTypes[selectedRow()]);
    stack->push(m_definitionTypeController);
    return true;
  }
  if (event == Ion::Events::Back ) {
    StackViewController * stack = static_cast<StackViewController *>(parentResponder());
    stack->pop();
    return true;
  }
  return false;
}

HighlightCell * FigureTypeController::reusableCell(int index) {
  assert(index >= 0);
  assert(index < k_numberOfCells);
  return &m_cells[index];
}

void FigureTypeController::willDisplayCellForIndex(HighlightCell * cell, int index) {
  MessageTableCellWithChevron * myCell = (MessageTableCellWithChevron *)cell;
  myCell->setMessage(m_messages[index]);
}

}
