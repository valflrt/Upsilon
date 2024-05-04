#include "mandelbrot_controller.h"
#include <assert.h>

namespace Mandelbrot
{

  MandelbrotController::MandelbrotController(Responder *parentResponder) : ViewController(parentResponder)
  {
  }

  MandelbrotView *MandelbrotController::view()
  {
    return &m_mandelbrotView;
  }

  void MandelbrotController::didBecomeFirstResponder()
  {
  }

  bool MandelbrotController::handleEvent(Ion::Events::Event event)
  {
    bool update = false;

    if (event == Ion::Events::One)
    {
      view()->changeTileSize(1);
      update = true;
    }
    else if (event == Ion::Events::One)
    {
      view()->changeTileSize(1);
      update = true;
    }
    else if (event == Ion::Events::Two)
    {
      view()->changeTileSize(2);
      update = true;
    }
    else if (event == Ion::Events::Three)
    {
      view()->changeTileSize(3);
      update = true;
    }
    else if (event == Ion::Events::Four)
    {
      view()->changeTileSize(4);
      update = true;
    }
    else if (event == Ion::Events::Five)
    {
      view()->changeTileSize(5);
      update = true;
    }
    else if (event == Ion::Events::Six)
    {
      view()->changeTileSize(6);
      update = true;
    }
    else if (event == Ion::Events::Seven)
    {
      view()->changeTileSize(7);
      update = true;
    }
    else if (event == Ion::Events::Eight)
    {
      view()->changeTileSize(8);
      update = true;
    }
    else if (event == Ion::Events::Nine)
    {
      view()->changeTileSize(9);
      update = true;
    }

    if (event == Ion::Events::Right)
    {
      view()->moveRight();
      update = true;
    }
    else if (event == Ion::Events::Up)
    {
      view()->moveUp();
      update = true;
    }
    else if (event == Ion::Events::Left)
    {
      view()->moveLeft();
      update = true;
    }
    else if (event == Ion::Events::Down)
    {
      view()->moveDown();
      update = true;
    }

    if (event == Ion::Events::Plus)
    {
      view()->zoomIn();
      update = true;
    }
    else if (event == Ion::Events::Minus)
    {
      view()->zoomOut();
      update = true;
    }

    if (event == Ion::Events::Multiplication)
    {
      view()->increaseStep();
    }
    else if (event == Ion::Events::Division)
    {
      view()->decreaseStep();
    }

    if (update)
    {
      view()->reload();
      return true;
    }

    return false;
  }
}

/**
 * This is the controller. It allows you to add some logic when there are events like keys pressed...
 * It follow an MVC pattern -> Model-View-Controller. The controller allows you to show some changes on the view like colors, results...
 * This file is linked to the C controller (sample_controler.h here). All files are linked -> app files.
 **/