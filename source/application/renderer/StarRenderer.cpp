#include "StarRenderer.hpp"

namespace Star {

RenderQuad Renderer::renderTexturedRect(TexturePtr texture,
                                        Vec2F minPosition,
                                        float textureScale,
                                        Vec4B color,
                                        float param1) {
  return {std::move(texture), minPosition, textureScale, color, param1};
}

RenderQuad Renderer::renderTexturedRect(TexturePtr texture, RectF const& screenCoords, Vec4B color, float param1) {
  return {std::move(texture), screenCoords, color, param1};
}

RenderQuad Renderer::renderFlatRect(RectF const& rect, Vec4B color, float param1) {
  return RenderQuad(rect, color, param1);
}

RenderPoly Renderer::renderFlatPoly(PolyF const& poly, Vec4B color, float param1) {
  return {poly.vertexes(), color, param1};
}

}
