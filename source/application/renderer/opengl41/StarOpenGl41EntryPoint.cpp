#include "StarOpenGl41EntryPoint.hpp"

#include "StarOpenGl41Renderer.hpp"

Star::RendererPtr CreateRenderer() {
  return std::make_shared<Star::OpenGl41Renderer>();
}

void DestroyRenderer(Star::RendererPtr& renderer) {
  renderer.reset();
}
