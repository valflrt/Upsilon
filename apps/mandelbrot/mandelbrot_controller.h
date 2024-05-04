#ifndef APPS_SAMPLE_CONTROLLER_H
#define APPS_SAMPLE_CONTROLLER_H

#include <escher.h>
#include "mandelbrot_view.h"

namespace Mandelbrot
{

  class MandelbrotController : public ViewController
  {
  public:
    MandelbrotController(Responder *parentResponder);
    MandelbrotView *view() override;
    bool handleEvent(Ion::Events::Event event) override;
    void didBecomeFirstResponder() override;

  private:
    MandelbrotView m_mandelbrotView;
  };

}

#endif

/**
 * This is the controller. It allows you to add some logic when there are events like keys pressed...
 * It follow an MVC pattern -> Model-View-Controller. The controller allows you to show some changes on the view like colors, results...
 * This file is linked to the C controller (sample_controler.cpp here). All files are linked -> app files.
 **/