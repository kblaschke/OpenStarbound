#pragma once

#include "StarRenderVertex.hpp"
#include "StarTexture.hpp"

namespace Star {

class RenderTriangle {
public:
    RenderTriangle() = default;
    RenderTriangle(Vec2F posA, Vec2F posB, Vec2F posC, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);
    RenderTriangle(TexturePtr tex, Vec2F posA, Vec2F uvA, Vec2F posB, Vec2F uvB, Vec2F posC, Vec2F uvC, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);

    TexturePtr texture;
    RenderVertex a, b, c;
};


}
