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
  const char * title() override;

  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  void viewWillAppear() override;
  TELEMETRY_ID("FigureType");
  int numberOfRows() const override { return 2; }
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
  KDCoordinate cellHeight() override { return k_cellHeight; }
  HighlightCell * reusableCell(int index) override;
  int reusableCellCount() const override { return k_numberOfCells; }
private:
  constexpr static KDCoordinate k_cellHeight = Metric::ParameterCellHeight;
  constexpr static int k_numberOfCells = 2;
  MessageTableCellWithChevron m_cells[k_numberOfCells];
  SelectableTableView m_selectableTableView;
  I18n::Message * m_messages;
  DefinitionTypeController * m_definitionTypeController;
};

}

#endif
