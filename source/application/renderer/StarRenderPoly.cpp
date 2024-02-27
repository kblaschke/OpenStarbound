#include "StarRenderPoly.hpp"

namespace Star {

RenderPoly::RenderPoly(List<Vec2F> const& verts, Vec4B color, float param1) {
  vertexes.reserve(verts.size());
  for (Vec2F const& v : verts)
    vertexes.append({v, {0, 0}, color, param1});
}

}