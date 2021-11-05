#include "figure_type_controller.h"

namespace Geometry {

static I18n::Message sMessages[] = {
  I18n::Message::QuentinGuidee,
  I18n::Message::JeanBaptisteBoric
};

DefinitionTypeController::DefinitionTypeController(Responder * parentResponder) :
  ViewController(parentResponder),
  m_selectableTableView(this)
{
  for (int i = 0; i < k_numberOfCells; i ++) {
    m_cells[i].setMessageFont(KDFont::LargeFont);
  }
  m_messages = sMessages;
}

const char * DefinitionTypeController::title() {
  return I18n::translate(I18n::Message::DefinitionType);
}

void DefinitionTypeController::viewWillAppear() {
  selectRow(0);
}

void DefinitionTypeController::didBecomeFirstResponder() {
  //App::app()->snapshot()->setActivePage(App::Snapshot::Page::Distribution);
  Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

bool DefinitionTypeController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK || event == Ion::Events::EXE || event == Ion::Events::Right) {
    StackViewController * stack = static_cast<StackViewController *>(parentResponder()->parentResponder()->parentResponder());
    stack->pop();
    return true;
  }
  if (event == Ion::Events::Back) {
    StackViewController * stack = static_cast<StackViewController *>(parentResponder()->parentResponder()->parentResponder());
    stack->pop();
    return true;
  }
  return false;
}

HighlightCell * DefinitionTypeController::reusableCell(int index) {
  assert(index >= 0);
  assert(index < k_numberOfCells);
  return &m_cells[index];
}

void DefinitionTypeController::willDisplayCellForIndex(HighlightCell * cell, int index) {
  MessageTableCellWithChevron * myCell = (MessageTableCellWithChevron *)cell;
  myCell->setMessage(m_messages[index]);
}

}
