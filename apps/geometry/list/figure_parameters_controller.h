#ifndef GEOMETRY_FIGURE_PARAMETERS_CONTROLLER_H
#define GEOMETRY_FIGURE_PARAMETERS_CONTROLLER_H

#include <escher.h>
#include "apps/i18n.h"
#include "message_table_cell_with_selector.h"
#include "../figures/figure.h"
#include "../../shared/parameter_text_field_delegate.h"
#include "../../shared/input_event_handler_delegate.h"
#include "../../shared/button_with_separator.h"

namespace Geometry {

typedef int (*NumberOfParametersFunction)();
typedef FigureType (*TypeOfParametersAtIndexFunction)(int);

/**
 * \brief Controller returning the parameter choosen by the user to define the figure
 */
class FigureParametersController : public ViewController, public ListViewDataSource, public SelectableTableViewDataSource, public Shared::ParameterTextFieldDelegate, public Shared::InputEventHandlerDelegate {
public:
  FigureParametersController(Responder * parentResponder);
  void setParametersInfoFunctions(NumberOfParametersFunction numberOfParametersFunction, TypeOfParametersAtIndexFunction typeOfParametersAtIndexFunction);
  void returnToMenu();
  /* ViewController */
  const char * title() override { return I18n::translate(I18n::Message::ParametersChoice); }
  // We want to avoid using half of the screen just for titles
  virtual DisplayParameter displayParameter() override { return DisplayParameter::DoNotShowOwnTitle; }
  View * view() override { return &m_selectableTableView; };

  /* Responder */
  void didBecomeFirstResponder() override;
  void viewWillAppear() override;

  /* ListViewDataSource */
  int typeAtLocation(int i, int j) override;
  int reusableCellCount(int type) override; // TO IMPLEMENT
  HighlightCell * reusableCell(int index, int type) override;
  int numberOfRows() const override;
  KDCoordinate rowHeight(int j) override;
  KDCoordinate cumulatedHeightFromIndex(int j) override;
  int indexFromCumulatedHeight(KDCoordinate offsetY) override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;

  /* InputEventHandlerDelegate */
  bool textFieldShouldFinishEditing(TextField * textField, Ion::Events::Event event) override;
  bool textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) override;

private:
  SelectableTableView m_selectableTableView;
  constexpr static int k_textCells = 2;
  constexpr static int k_choiceCells = 3;
  constexpr static int k_buttonMargin = 6;
  int m_lastSelectedRow;
  MessageTableCellWithEditableText m_textCells[k_textCells];
  MessageTableCellWithSelector m_choicesCells[k_choiceCells];
  ButtonWithSeparator m_okButton;
  NumberOfParametersFunction m_numberOfParametersFunction;
  TypeOfParametersAtIndexFunction m_typeOfParametersAtIndexFunction;
};

}

#endif
