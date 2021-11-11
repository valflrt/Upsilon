#include "figure_type_controller.h"

namespace Geometry {

static I18n::Message sPointDefinitionsMessages[] = {
  I18n::Message::QuentinGuidee,
  I18n::Message::JeanBaptisteBoric
};

static I18n::Message sCircleDefinitionsMessages[] = {
  I18n::Message::JoachimLeFournis,
  I18n::Message::MaximeFriess
};

DefinitionTypeController::DefinitionTypeController(Responder * parentResponder, FigureParametersController * parametersController) :
  ViewController(parentResponder),
  m_selectableTableView(this),
  m_messages(nullptr),
  m_figureType(FigureType::None),
  m_parametersController(parametersController)
{
  for (int i = 0; i < k_numberOfCells; i ++) {
    m_cells[i].setMessageFont(KDFont::LargeFont);
  }
}

void DefinitionTypeController::viewWillAppear() {
  assert(m_figureType != FigureType::None && m_messages != nullptr);
  m_selectableTableView.reloadVisibleCells(); // We reload the cell of the table view to update their message
  selectRow(0);
}

void DefinitionTypeController::didBecomeFirstResponder() {
  //App::app()->snapshot()->setActivePage(App::Snapshot::Page::Distribution);
  Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

bool DefinitionTypeController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK || event == Ion::Events::EXE || event == Ion::Events::Right) {
    StackViewController * stack = static_cast<StackViewController *>(parentResponder());
    stack->push(m_parametersController);
    return true;
  }
  if (event == Ion::Events::Back) {
    StackViewController * stack = static_cast<StackViewController *>(parentResponder());
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

void DefinitionTypeController::setFigureType(FigureType figureType) {
  m_figureType = figureType;
  switch (m_figureType) {
    case FigureType::Point:
      m_messages = sPointDefinitionsMessages;
      break;
    case FigureType::Circle:
      m_messages = sCircleDefinitionsMessages;
      break;    
    default:
      assert(false);
      break;
  }
}

}
