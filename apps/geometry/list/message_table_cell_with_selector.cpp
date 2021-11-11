#include "message_table_cell_with_selector.h"

namespace Geometry {

MessageTableCellWithSelector::MessageTableCellWithSelector(ToolboxMessageTree * root, const KDFont * font) :
  Responder(nullptr),
  MessageTableCell((I18n::Message)0, font),
  m_objectsRoot(root),
  m_selectedMessage(nullptr)
{

}

MessageTableCellWithSelector::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK || event == Ion::Events::EXE) {
    //Container::activeApp()->displayModalViewController(m_toolbox, 0.f, 0.f)
    return true;
  }
  return false;
}

}
