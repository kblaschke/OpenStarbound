find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_library(star_renderer_opengl41 SHARED
        StarOpenGl41Renderer.cpp
        StarOpenGl41Renderer.hpp
        StarOpenGl41EntryPoint.cpp
        StarOpenGl41EntryPoint.hpp
)

set(STAR_RENDERER_OPENGL41_LIBS GLEW::GLEW OpenGL::GL)

if (TARGET OpenGL::GLX)
    list(APPEND STAR_RENDERER_OPENGL41_LIBS OpenGL::GLX)
endif ()

target_include_directories(star_renderer_opengl41
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${STAR_EXTERN_INCLUDES}
        ${STAR_CORE_INCLUDES}
        ${STAR_PLATFORM_INCLUDES}
        ${STAR_APPLICATION_INCLUDES}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(star_renderer_opengl41
        PUBLIC
        star_renderer
        ${STAR_RENDERER_OPENGL41_LIBS}
)

set_target_properties(star_renderer_opengl41 PROPERTIES
        C_VISIBILITY_PRESET hidden
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN TRUE
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../dist
        PREFIX "" # Prevent "lib" prefixing on UNIX
)

include(GenerateExportHeader)
generate_export_header(star_renderer_opengl41)
