#include "StarRenderTriangle.hpp"

namespace Star {

RenderTriangle::RenderTriangle(Vec2F posA, Vec2F posB, Vec2F posC, Vec4B color, float param1)
  : texture() {
  a = {posA, {0, 0}, color, param1};
  b = {posB, {0, 0}, color, param1};
  c = {posC, {0, 0}, color, param1};
}

RenderTriangle::RenderTriangle(TexturePtr tex, Vec2F posA, Vec2F uvA, Vec2F posB, Vec2F uvB, Vec2F posC, Vec2F uvC,
                               Vec4B color, float param1)
  : texture(std::move(tex)) {
  a = {posA, uvA, color, param1};
  b = {posB, uvB, color, param1};
  c = {posC, uvC, color, param1};
}

}