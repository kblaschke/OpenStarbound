#pragma once

#include "StarRenderTriangle.hpp"
#include "StarRenderQuad.hpp"
#include "StarRenderPoly.hpp"

namespace Star {

STAR_CLASS(RenderBuffer);

using RenderPrimitive = Variant<RenderTriangle, RenderQuad, RenderPoly>;

class RenderBuffer {
public:
    virtual ~RenderBuffer() = default;

    // Transforms the given primitives into a form suitable for the underlying
    // graphics system and stores it for fast replaying.
    virtual void set(List<RenderPrimitive>& primitives) = 0;
};

}
