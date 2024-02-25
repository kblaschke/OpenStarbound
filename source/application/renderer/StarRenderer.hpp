#pragma once

#include "StarVariant.hpp"
#include "StarImage.hpp"
#include "StarPoly.hpp"
#include "StarJson.hpp"
#include "StarBiMap.hpp"
#include "StarTextureGroup.hpp"
#include "StarRenderBuffer.hpp"

namespace Star {

STAR_EXCEPTION(RendererException, StarException);

STAR_CLASS(Renderer);

using RenderEffectParameter = Variant<bool, int, float, Vec2F, Vec3F, Vec4F>;

class Renderer {
public:
  virtual ~Renderer() = default;

  virtual String rendererId() const = 0;
  virtual Vec2U screenSize() const = 0;

  virtual void loadConfig(Json const& config) = 0;

  // The actual shaders used by this renderer will be in a default no effects
  // state when constructed, but can be overridden here.  This config will be
  // specific to each type of renderer, so it will be necessary to key the
  // configuration off of the renderId string.  This should not be called every
  // frame, because it will result in a recompile of the underlying shader set.
  virtual void loadEffectConfig(String const& name, Json const& effectConfig, StringMap<String> const& shaders) = 0;

  // The effect config will specify named parameters and textures which can be
  // set here.
  virtual void setEffectParameter(String const& parameterName, RenderEffectParameter const& parameter) = 0;
  virtual void setEffectTexture(String const& textureName, Image const& image) = 0;

  virtual bool switchEffectConfig(String const& name) = 0;

  // Any further rendering will be scissored based on this rect, specified in
  // pixels
  virtual void setScissorRect(Maybe<RectI> const& scissorRect) = 0;

  virtual TexturePtr createTexture(Image const& texture, TextureAddressing addressing, TextureFiltering filtering) = 0;
  virtual void setSizeLimitEnabled(bool enabled) = 0;
  virtual void setMultiTexturingEnabled(bool enabled) = 0;
  virtual TextureGroupPtr createTextureGroup(TextureGroupSize size, TextureFiltering) = 0;
  virtual RenderBufferPtr createRenderBuffer() = 0;

  virtual List<RenderPrimitive>& immediatePrimitives() = 0;
  virtual void render(RenderPrimitive primitive) = 0;
  virtual void renderBuffer(RenderBufferPtr const& renderBuffer, Mat3F const& transformation) = 0;

  virtual void flush() = 0;

  static RenderQuad renderTexturedRect(TexturePtr texture, Vec2F minScreen, float textureScale = 1.0f, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);
  static RenderQuad renderTexturedRect(TexturePtr texture, RectF const& screenCoords, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);
  static RenderQuad renderFlatRect(RectF const& rect, Vec4B color, float param1 = 0.0f);
  static RenderPoly renderFlatPoly(PolyF const& poly, Vec4B color, float param1 = 0.0f);

};

}
