#ifndef GEOMETRY_BANNER_VIEW_H
#define GEOMETRY_BANNER_VIEW_H

#include "../../shared/xy_banner_view.h"

namespace Geometry {

class BannerView : public Shared::XYBannerView {
public:
    BannerView(Responder * parentResponder, InputEventHandlerDelegate * inputEventHandlerDelegate, TextFieldDelegate * textFieldDelegate);
};

}

#endif