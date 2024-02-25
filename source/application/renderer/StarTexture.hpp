#pragma once

#include "StarBiMap.hpp"
#include "StarConfig.hpp"
#include "StarRefPtr.hpp"
#include "StarVector.hpp"

namespace Star {

enum class TextureAddressing {
    Clamp,
    Wrap
};
extern EnumMap<TextureAddressing> const TextureAddressingNames;

enum class TextureFiltering {
    Nearest,
    Linear
};
extern EnumMap<TextureFiltering> const TextureFilteringNames;

class Texture : public RefCounter
{
public:
    virtual ~Texture() = default;

    virtual Vec2U size() const = 0;
    virtual TextureFiltering filtering() const = 0;
    virtual TextureAddressing addressing() const = 0;
};

using TexturePtr = RefPtr<Texture>;

}
