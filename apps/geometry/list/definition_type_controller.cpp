#include "figure_type_controller.h"
#include "../figures/figures.h"

namespace Geometry {

static constexpr I18n::Message sPointDefinitionsMessages[] = {
  I18n::Message::Coordinates,
  I18n::Message::Middle,
  I18n::Message::VectorProject,
  I18n::Message::OrthogonalProject
};
static const uint8_t sPointDefinitionsMessagesCount = sizeof(sPointDefinitionsMessages) / sizeof(I18n::Message);


static constexpr I18n::Message sLineDefinitionMessages[] = {
  I18n::Message::CartesianEquation,
  I18n::Message::LinearEquation,
  I18n::Message::Points,
  I18n::Message::PointAndVector,
  I18n::Message::Parallele,
  I18n::Message::Perpendicular
};
static const uint8_t sLineDefinitionsMessagesCount = sizeof(sLineDefinitionMessages) / sizeof(I18n::Message);


static constexpr I18n::Message sCircleDefinitionsMessages[] = {
  I18n::Message::PointAndRadius,
  I18n::Message::Diameter,
  I18n::Message::CartesianEquation,
};
static const uint8_t sCircleDefinitionsMessagesCount = sizeof(sCircleDefinitionsMessages) / sizeof(I18n::Message);


static constexpr I18n::Message sVectorDefinitionsMessages[] = {
  I18n::Message::Coordinates,
  I18n::Message::TwoPoints
};
static const uint8_t sVectorDefinitionsMessagesCount = sizeof(sVectorDefinitionsMessages) / sizeof(I18n::Message);


static constexpr I18n::Message sIndicatorDefinitionsMessages[] = {
  I18n::Message::Segment,
  I18n::Message::Angle,
  I18n::Message::Area,
};
static const uint8_t sIndicatorDefinitionsMessagesCount = sizeof(sIndicatorDefinitionsMessages) / sizeof(I18n::Message);


DefinitionTypeController::DefinitionTypeController(Responder * parentResponder, FigureParametersController * parametersController):
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
  m_selectableTableView.reloadData(); // We reload the cell of the table view to update their message
  selectRow(0);
}

void DefinitionTypeController::didBecomeFirstResponder() {
  //App::app()->snapshot()->setActivePage(App::Snapshot::Page::Distribution);
  Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

bool DefinitionTypeController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK || event == Ion::Events::EXE || event == Ion::Events::Right) {
    StackViewController * stack = static_cast<StackViewController *>(parentResponder());
    //m_parametersController->setFigureBuilder(PointByCoordinatesBuilder());
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

int DefinitionTypeController::numberOfRows() const {
  switch (m_figureType) {
    case FigureType::Point:
      return sPointDefinitionsMessagesCount;
      break;
    case FigureType::Line:
      return sLineDefinitionsMessagesCount;
      break;
    case FigureType::Circle:
      return sCircleDefinitionsMessagesCount;
      break;
    case FigureType::Vector:
      return sVectorDefinitionsMessagesCount;
      break;
    case FigureType::Indicator:
      return sIndicatorDefinitionsMessagesCount;
      break;
    default:
      assert(false);
      return 0;
  }
}

void DefinitionTypeController::setFigureType(FigureType figureType) {
  m_figureType = figureType;
  switch (m_figureType) {
    case FigureType::Point:
      m_messages = sPointDefinitionsMessages;
      break;
    case FigureType::Line:
      m_messages = sLineDefinitionMessages;
      break;
    case FigureType::Circle:
      m_messages = sCircleDefinitionsMessages;
      break;
    case FigureType::Vector:
      m_messages = sVectorDefinitionsMessages;
      break;
    case FigureType::Indicator:
      m_messages = sIndicatorDefinitionsMessages;
      break;
    default:
      assert(false);
      break;
  }
}

}
