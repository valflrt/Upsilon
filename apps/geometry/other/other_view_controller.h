#ifndef OTHER_VIEW_CONTROLLER_H
#define OTHER_VIEW_CONTROLLER_H

namespace Geometry {

class OtherViewController : public ViewController {
public:
  OtherViewController(Responder * parentResponder):
    ViewController(parentResponder) {}
  View * view() override { return nullptr; }
  const char * title() override { return I18n::translate(I18n::Message::OtherTab); }
};

}

#endif