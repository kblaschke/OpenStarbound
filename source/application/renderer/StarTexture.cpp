#include "StarTexture.hpp"

namespace Star {

EnumMap<TextureAddressing> const TextureAddressingNames = {
  {TextureAddressing::Clamp, "Clamp"},
  {TextureAddressing::Wrap, "Wrap"}
};

EnumMap<TextureFiltering> const TextureFilteringNames = {
  {TextureFiltering::Nearest, "Nearest"},
  {TextureFiltering::Linear, "Linear"}
};

}