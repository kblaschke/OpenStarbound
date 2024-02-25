#pragma once

#include "StarVector.hpp"

namespace Star {

// Both screen coordinates and texture coordinates are in pixels from the
// bottom left to top right.
struct RenderVertex {
    Vec2F screenCoordinate;
    Vec2F textureCoordinate;
    Vec4B color;
    float param1;
};

}
