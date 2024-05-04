#include "mandelbrot_view.h"
#include "apps/i18n.h"
#include <cmath>
#include <complex>
// #include <ctime>

namespace Mandelbrot
{

  MandelbrotView::MandelbrotView() : View(),
                                     m_bufferTextView(KDFont::LargeFont, 0.5, 0.5, KDColorBlack),
                                     tileSize(9),
                                     max_iter(200),
                                     n_zoom(0),
                                     zoom(pow(0.6, n_zoom + 3)),
                                     center_x(0.),
                                     center_y(0.),
                                     step_size(20.)
  {
    m_bufferTextView.setText(I18n::translate(I18n::Message::MandelbrotApp));
  }

  void MandelbrotView::drawRect(KDContext *ctx, KDRect rect) const
  {
    drawMandelbrot(ctx, rect);
  }

  void MandelbrotView::reload()
  {
    zoom = pow(0.6, n_zoom + 3); // yes. kalibration.
    markRectAsDirty(bounds());
  }

  void MandelbrotView::drawMandelbrot(KDContext *ctx, KDRect rect) const
  {
    int width = rect.width();
    int height = rect.height();
    int max_x = width / tileSize;
    int max_y = height / tileSize;

    double c_x = (0.1 * tileSize - width / 2) * zoom + center_x;
    double c_y = (0.1 * tileSize - height / 2) * zoom + center_y;

    for (int y = 0; y < max_y + 1; y++)
    {
      if (tileSize <= 3)
        ctx->drawLine(KDPoint(0, y * tileSize), KDPoint(width, y * tileSize), KDColorWhite);
      KDColor line[width * tileSize + 1];
      for (int x = 0; x < max_x + 1; x++)
      {
        std::complex<double> c(x * tileSize * zoom + c_x, y * tileSize * zoom + c_y);
        int v = getMandelbrotValue(c);
        KDColor color = getColor((float)v / (float)max_iter);
        for (int i = 0; i < tileSize && x * tileSize + i < width; i++)
          for (int j = 0; j < tileSize && y * tileSize + j < height; j++)
            line[x * tileSize + j * width + i] = color;
      }
      ctx->fillRectWithPixels(KDRect(0, y * tileSize, width, tileSize), line, nullptr);
    }
  }

  int MandelbrotView::getMandelbrotValue(std::complex<double> c) const
  {
    std::complex<double> z = 0;
    int i = 0;
    while (i < max_iter && abs(z) < 2)
    {
      i += 1;
      z = z * z + c;
    }
    return i;
  }

  KDColor MandelbrotView::getColor(float t) const
  {
    if (t <= gradientValues[0])
      return gradientColors[0];
    if (t >= gradientValues[7])
      return gradientColors[7];
    for (unsigned int i = 0; i < 7; i = i + 1)
    {
      if (gradientValues[i] <= t && t <= gradientValues[i + 1])
      {
        float ratio = (t - gradientValues[i]) / (gradientValues[i + 1] - gradientValues[i]);
        uint8_t r1 = gradientColors[i].red();
        uint8_t g1 = gradientColors[i].green();
        uint8_t b1 = gradientColors[i].blue();
        uint8_t r2 = gradientColors[i + 1].red();
        uint8_t g2 = gradientColors[i + 1].green();
        uint8_t b2 = gradientColors[i + 1].blue();
        uint8_t r = r1 * (1 - ratio) + r2 * ratio;
        uint8_t g = g1 * (1 - ratio) + g2 * ratio;
        uint8_t b = b1 * (1 - ratio) + b2 * ratio;
        return KDColor::RGB888(r, g, b);
      }
    }
    return KDColor::RGB888(0, 255, 0);
  }

  void MandelbrotView::changeTileSize(int m)
  {
    tileSize = m;
  }

  void MandelbrotView::moveRight()
  {
    center_x += step_size * zoom;
  }
  void MandelbrotView::moveUp()
  {
    center_y -= step_size * zoom;
  }
  void MandelbrotView::moveLeft()
  {
    center_x -= step_size * zoom;
  }
  void MandelbrotView::moveDown()
  {
    center_y += step_size * zoom;
  }

  void MandelbrotView::zoomIn()
  {
    n_zoom += 1;
  }
  void MandelbrotView::zoomOut()
  {
    n_zoom -= 1;
  }

  void MandelbrotView::increaseStep()
  {
    step_size += 10;
  }
  void MandelbrotView::decreaseStep()
  {
    if (step_size > 10)
      step_size -= 10;
  }

}

/**
 * This is the view, it allows you to show an interface on your calc like rect, string...
 * It follows an MVC pattern -> Model-View-Controller. The view allows you to show some changes on event
 * This file is linked to the C view (mandelbrot_view.h here). All files are linked -> app files.
 **/
