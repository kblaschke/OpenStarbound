#include "StarRenderQuad.hpp"

namespace Star {

RenderQuad::RenderQuad(Vec2F posA, Vec2F posB, Vec2F posC, Vec2F posD, Vec4B color, float param1)
    : texture()
    , a({ posA, { 0, 0 }, color, param1 })
    , b({ posB, { 0, 0 }, color, param1 })
    , c({ posC, { 0, 0 }, color, param1 })
    , d({ posD, { 0, 0 }, color, param1 })
{
}

RenderQuad::RenderQuad(TexturePtr tex, Vec2F minPosition, float textureScale, Vec4B color, float param1)
    : texture(std::move(tex))
{
    Vec2F size = Vec2F(texture->size());
    a = { minPosition, { 0, 0 }, color, param1 };
    b = {{ (minPosition[0] + size[0] * textureScale), minPosition[1] }, { size[0], 0 }, color, param1 };
    c = {{ (minPosition[0] + size[0] * textureScale), (minPosition[1] + size[1] * textureScale) }, size, color,
         param1 };
    d = {{ minPosition[0], (minPosition[1] + size[1] * textureScale) }, { 0, size[1] }, color, param1 };
}

RenderQuad::RenderQuad(TexturePtr tex, RectF const& screenCoords, Vec4B color, float param1)
    : texture(std::move(tex))
{
    Vec2F size = Vec2F(texture->size());
    a = { screenCoords.min(), { 0, 0 }, color, param1 };
    b = {{ screenCoords.xMax(), screenCoords.yMin(), }, { size[0], 0.f }, color, param1 };
    c = { screenCoords.max(), size, color, param1 };
    d = {{ screenCoords.xMin(), screenCoords.yMax(), }, { 0.f, size[1] }, color, param1 };
}

RenderQuad::RenderQuad(TexturePtr tex, Vec2F posA, Vec2F uvA, Vec2F posB, Vec2F uvB, Vec2F posC, Vec2F uvC, Vec2F posD,
                       Vec2F uvD, Vec4B color, float param1)
    : texture(std::move(tex))
    , a({ posA, uvA, color, param1 })
    , b({ posB, uvB, color, param1 })
    , c({ posC, uvC, color, param1 })
    , d({ posD, uvD, color, param1 })
{
}

RenderQuad::RenderQuad(TexturePtr tex, RenderVertex vA, RenderVertex vB, RenderVertex vC, RenderVertex vD)
    : texture(std::move(tex))
    , a(vA)
    , b(vB)
    , c(vC)
    , d(vD)
{
}

RenderQuad::RenderQuad(RectF const& rect, Vec4B color, float param1)
    : a{ rect.min(), {}, color, param1 }
    , b{{ rect.xMax(), rect.yMin() }, {}, color, param1 }
    , c{ rect.max(), {}, color, param1 }
    , d{{ rect.xMin(), rect.yMax() }, {}, color, param1 }
{
};


}