#ifndef APPS_SAMPLE_VIEW_H
#define APPS_SAMPLE_VIEW_H
#include <complex>

#include <escher.h>

namespace Mandelbrot
{

  const float gradientValues[] = {0.0, 0.10, 0.25, 0.4, 0.55, 0.7, 0.85, 0.95};
  const KDColor gradientColors[] = {
      KDColor::RGB888(10, 2, 20),
      KDColor::RGB888(200, 40, 230),
      KDColor::RGB888(20, 160, 230),
      KDColor::RGB888(60, 230, 80),
      KDColor::RGB888(255, 230, 20),
      KDColor::RGB888(255, 120, 20),
      KDColor::RGB888(255, 40, 60),
      KDColor::RGB888(2, 0, 4),
  };

  class MandelbrotView : public View
  {
  public:
    MandelbrotView();
    void drawRect(KDContext *ctx, KDRect rect) const override;
    void drawMandelbrot(KDContext *ctx, KDRect rect) const;
    void reload();
    int getMandelbrotValue(std::complex<double> c) const;
    KDColor getColor(float t) const;

    void changeTileSize(int m);
    void moveRight();
    void moveUp();
    void moveLeft();
    void moveDown();
    void zoomIn();
    void zoomOut();
    void increaseStep();
    void decreaseStep();

  private:
    BufferTextView m_bufferTextView;
    int tileSize;
    int max_iter;
    int n_zoom;
    double zoom;
    double center_x;
    double center_y;
    float step_size;
  };

}

#endif

/**
 * This is the view, it allows you to show an interface on your calc like rect, string...
 * It follows an MVC pattern -> Model-View-Controller. The view allows you to show some changes on event
 * This file is linked to the C view (sample_view.cpp here). All files are linked -> app files.
 **/