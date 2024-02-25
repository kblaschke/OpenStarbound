#pragma once

#include "StarList.hpp"
#include "StarRenderVertex.hpp"
#include "StarTexture.hpp"

namespace Star {

class RenderPoly {
public:
    RenderPoly() = default;
    RenderPoly(List<Vec2F> const& verts, Vec4B color, float param1 = 0.0f);

    TexturePtr texture;
    List<RenderVertex> vertexes;
};

}
