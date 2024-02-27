add_library(star_renderer STATIC
        StarRenderBuffer.hpp
        StarRenderPoly.cpp
        StarRenderPoly.hpp
        StarRenderQuad.cpp
        StarRenderQuad.hpp
        StarRenderTriangle.cpp
        StarRenderTriangle.hpp
        StarRenderVertex.hpp
        StarRenderer.cpp
        StarRenderer.hpp
        StarTexture.cpp
        StarTexture.hpp
        StarTextureGroup.hpp
)

target_include_directories(star_renderer
        PRIVATE
        ${STAR_EXTERN_INCLUDES}
        ${STAR_CORE_INCLUDES}
        ${STAR_PLATFORM_INCLUDES}
        ${STAR_APPLICATION_INCLUDES}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if (STAR_RENDERER_OPENGL)
    if (STAR_USE_OPENGL_ES)
        add_subdirectory(opengles31)
    else ()
        add_subdirectory(opengl41)
    endif ()
endif ()

if (STAR_RENDERER_VULKAN)
    add_subdirectory(vulkan)
endif ()

if (STAR_RENDERER_METAL)
    add_subdirectory(metal)
endif ()
