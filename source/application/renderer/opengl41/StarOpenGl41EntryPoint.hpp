#pragma once

#include "star_renderer_opengl41_export.h"
#include "StarRenderer.hpp"

extern "C" {
STAR_RENDERER_OPENGL41_EXPORT Star::RendererPtr CreateRenderer();
STAR_RENDERER_OPENGL41_EXPORT void DestroyRenderer(Star::RendererPtr& renderer);
}
