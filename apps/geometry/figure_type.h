#ifndef GEOMETRY_FIGURE_TYPE_H
#define GEOMETRY_FIGURE_TYPE_H

namespace Geometry {

enum class FigureType {
    None = 0, // Used to trigger assert in debug mode
    Number, // It's not a real figure type but we use it to build figures like points
    Point,
    Circle
};

}

#endif
