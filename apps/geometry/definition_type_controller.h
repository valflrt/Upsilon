#ifndef GEOMETRY_DEFINITION_TYPE_CONTROLLER_H
#define GEOMETRY_DEFINITION_TYPE_CONTROLLER_H

#include <escher.h>
#include "apps/i18n.h"

namespace Geometry {
/**
 * \brief DefinitionTypeController is a controller to choose how the figure is defined
 */
class DefinitionTypeController : public ViewController, public SimpleListViewDataSource, public SelectableTableViewDataSource {
public:
  DefinitionTypeController(Responder * parentResponder/*, FigureDefinitionController * definitionController*/);

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
  /*FigureDefinitionController * m_FigureDefinitionController;*/
};

}

#endif
