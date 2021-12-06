#ifndef ESHER_MESSAGE_TABLE_CELL_WITH_OBJECT_SELECTOR_H_
#define ESHER_MESSAGE_TABLE_CELL_WITH_OBJECT_SELECTOR_H_

#include <escher/message_table_cell_with_buffer.h>
#include <escher/toolbox_message_tree.h>
#include "objects_controller.h"

namespace Geometry {

class MessageTableCellWithSelector : public Responder, public MessageTableCell {
public:
  MessageTableCellWithSelector(ToolboxMessageTree * root = nullptr, const KDFont * font = KDFont::SmallFont);
  ToolboxMessageTree * getSelectedMessage() const { return m_selectedMessage; };
  bool handleEvent(Ion::Events::Event event);
  Responder * responder() override {
    return this;
  }
private:
  ToolboxMessageTree * m_objectsRoot;
  ToolboxMessageTree * m_selectedMessage;
  ObjectsController m_toolbox;
};

}

#endif
