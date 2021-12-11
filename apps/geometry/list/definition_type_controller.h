#ifndef GEOMETRY_DEFINITION_TYPE_CONTROLLER_H
#define GEOMETRY_DEFINITION_TYPE_CONTROLLER_H

#include <escher.h>
#include "apps/i18n.h"
#include "../figures/figure_type.h"
#include "figure_parameters_controller.h"

namespace Geometry {
/**
 * \brief DefinitionTypeController is a controller to choose how the figure is defined
 */
class DefinitionTypeController : public ViewController, public SimpleListViewDataSource, public SelectableTableViewDataSource {
public:
  DefinitionTypeController(Responder * parentResponder, FigureParametersController * parametersController);

  /* ViewController */
  View * view() override { return &m_selectableTableView; }
  // We want to avoid using half of the screen just for titles
  virtual DisplayParameter displayParameter() override { return DisplayParameter::DoNotShowOwnTitle; } 
  const char * title() override { return I18n::translate(I18n::Message::DefinitionType); }

  /* Responder */
  bool handleEvent(Ion::Events::Event event) override;

  /* ViewController */
  void didBecomeFirstResponder() override;
  void viewWillAppear() override;
  TELEMETRY_ID("FigureType");

  /* SelectableTableViewDataSource */
  int numberOfRows() const override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
  KDCoordinate cellHeight() override { return k_cellHeight; }
  HighlightCell * reusableCell(int index) override;
  int reusableCellCount() const override { return k_numberOfCells; }

  /* Customs methods */
  void setFigureType(FigureType type);
private:
  constexpr static KDCoordinate k_cellHeight = Metric::ParameterCellHeight;
  constexpr static int k_numberOfCells = 6;
  MessageTableCellWithChevron m_cells[k_numberOfCells];
  SelectableTableView m_selectableTableView;
  I18n::Message * m_messages;
  FigureType m_figureType;
  FigureParametersController * m_parametersController;
};

}

#endif
