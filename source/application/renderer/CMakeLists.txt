add_library(star_renderer STATIC
            StarRenderBuffer.hpp
            StarRenderQuad.hpp
            StarRenderTriangle.hpp
            StarRenderVertex.hpp
            StarRenderer.cpp
            StarRenderer.hpp
            StarTexture.hpp
            StarTextureGroup.hpp
            StarRenderPoly.hpp
            StarRenderTriangle.cpp
            StarRenderPoly.cpp
            StarTexture.cpp
            StarRenderQuad.cpp
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

if(STAR_RENDERER_OPENGL)
    if(STAR_USE_OPENGL_ES)
        add_subdirectory(opengles31)
    else()
        add_subdirectory(opengl41)
        target_sources(star_renderer
                       PRIVATE
                       $<TARGET_OBJECTS:star_renderer_opengl41>
                       )
        target_link_libraries(star_renderer
                              PUBLIC
                              star_renderer_opengl41
                              )
    endif()
endif()

if(STAR_RENDERER_VULKAN)
    add_subdirectory(vulkan)
endif()

if(STAR_RENDERER_METAL)
    add_subdirectory(metal)
endif()
