find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_library(star_renderer_opengl41 OBJECT
            StarRenderer_opengl41.cpp
            StarRenderer_opengl41.hpp
            )

set(STAR_RENDERER_OPENGL41_LIBS GLEW::GLEW OpenGL::GL)

if(TARGET OpenGL::GLX)
    list(APPEND STAR_RENDERER_OPENGL41_LIBS OpenGL::GLX)
endif()

target_include_directories(star_renderer_opengl41
                           PRIVATE
                           ${STAR_EXTERN_INCLUDES}
                           ${STAR_CORE_INCLUDES}
                           ${STAR_PLATFORM_INCLUDES}
                           ${STAR_APPLICATION_INCLUDES}
                           ${CMAKE_CURRENT_SOURCE_DIR}/..
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

target_link_libraries(star_renderer_opengl41
                      PUBLIC
                      ${STAR_RENDERER_OPENGL41_LIBS}
                      )
