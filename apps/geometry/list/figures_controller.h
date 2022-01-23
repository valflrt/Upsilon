#ifndef FIGURES_CONTROLLER_H
#define FIGURES_CONTROLLER_H

#include <escher.h>
#include "figure_type_controller.h"

namespace Geometry
{
/**
 * \brief FiguresController is a controller to show the list of the figures
 */
class FiguresController : public ViewController, public SelectableTableViewDataSource, public SelectableTableViewDelegate, public TableViewDataSource {
public:
  FiguresController(Responder * parentResponder);

  /* ViewController */
  View * view() override { return &m_selectableTableView; }
  const char * title() override { return I18n::translate(I18n::Message::FiguresTab); }
  virtual DisplayParameter displayParameter() override { return DisplayParameter::DoNotShowOwnTitle; }
  /* Responder */
  bool handleEvent(Ion::Events::Event event) override; // TO IMPLEMENT
  void didBecomeFirstResponder() override;

  /* TableView */
  int numberOfRows() const override { return 1; } // TO IMPLEMENT
  int numberOfColumns() const override { return 2; } // TO IMPLEMENT
  KDCoordinate columnWidth(int i) { return i == 0 ? 50 : 150; } // TO IMPLEMENT
  KDCoordinate rowHeight(int j) { return 50; } // TO IMPLEMENT
  HighlightCell * reusableCell(int index, int type); // TO IMPLEMENT
  void willDisplayCellAtLocation(HighlightCell * cell, int i, int j) override; // TO IMPLEMENT
  int reusableCellCount(int type);
  int typeAtLocation(int i, int j); // TO IMPLEMENT

private:
  /* Customs methods */
  bool isAddFigureRow(int j); // TO IMPLEMENT

  SelectableTableView m_selectableTableView;
  EvenOddMessageTextCell m_addFigureCell;
  EvenOddCell m_emptyCell;
  FigureTypeController m_figureTypeController;
  DefinitionTypeController m_definitionTypeController;
  FigureParametersController m_parametersController;
};

}
#endif