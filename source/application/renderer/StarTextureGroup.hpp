#pragma once

#include "StarImage.hpp"
#include "StarTexture.hpp"

namespace Star {

STAR_CLASS(TextureGroup);

// Medium is the maximum guaranteed texture group size
// Where a Medium sized texture group is expected to fill a single page Large can be used,
// but is not guaranteed to be supported by all systems.
// Where Large sized textures are not supported, a Medium one is used
enum class TextureGroupSize {
    Small,
    Medium,
    Large
};

// Textures may be created individually, or in a texture group.  Textures in
// a texture group will be faster to render when rendered together, and will
// use less texture memory when many small textures are in a common group.
// Texture groups must all have the same texture parameters, and will always
// use clamped texture addressing.
class TextureGroup
{
public:
    virtual ~TextureGroup() = default;

    virtual TextureFiltering filtering() const = 0;
    virtual TexturePtr create(Image const& texture) = 0;
};

}
