#ifndef GEOMETRY_FIGURE_TYPE_CONTROLLER_H
#define GEOMETRY_FIGURE_TYPE_CONTROLLER_H

#include <escher.h>
#include "definition_type_controller.h"

namespace Geometry {
/**
 * \brief FigureTypeController is a controller that is used to select the type of
 * figure to be created.
 */
class FigureTypeController : public ViewController, public SimpleListViewDataSource, public SelectableTableViewDataSource {
public:
  FigureTypeController(Responder * parentResponder, DefinitionTypeController * definitionController);

  /* ViewController */
  View * view() override { return &m_selectableTableView; }
  // We want to avoid using half of the screen just for titles
  virtual DisplayParameter displayParameter() override { return DisplayParameter::DoNotShowOwnTitle; } 
  const char * title() override { return I18n::translate(I18n::Message::FigureType); }

  /* Responder */
  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;

  /* ViewController */
  void viewWillAppear() override;
  TELEMETRY_ID("FigureType");

  /* TableViewDataSource */
  int numberOfRows() const override { return k_numberOfRows; }
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
  KDCoordinate cellHeight() override { return k_cellHeight; }
  HighlightCell * reusableCell(int index) override;
  int reusableCellCount() const override { return k_numberOfCells; }
private:
  constexpr static KDCoordinate k_cellHeight = Metric::ParameterCellHeight;
  constexpr static int k_numberOfCells = 5;
  constexpr static int k_numberOfRows = 5;
  MessageTableCellWithChevron m_cells[k_numberOfCells];
  SelectableTableView m_selectableTableView;
  DefinitionTypeController * m_definitionTypeController;
  I18n::Message * m_messages;
};

}

#endif
