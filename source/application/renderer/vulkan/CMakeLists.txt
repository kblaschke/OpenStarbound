find_package(Vulkan REQUIRED COMPONENTS glslc glslangValidator shaderc_combined)

add_library(star_renderer_vulkan SHARED
        StarSwapChain.cpp
        StarSwapChain.hpp
        StarVulkanRenderer.cpp
        StarVulkanRenderer.hpp
)

set(STAR_RENDERER_VULKAN_LIBS Vulkan::shaderc_combined)

target_include_directories(star_renderer_vulkan
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${STAR_EXTERN_INCLUDES}
        ${STAR_CORE_INCLUDES}
        ${STAR_PLATFORM_INCLUDES}
        ${STAR_APPLICATION_INCLUDES}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(star_renderer_vulkan
        PUBLIC
        ${STAR_RENDERER_VULKAN_LIBS}
)

include(GenerateExportHeader)
generate_export_header(star_renderer_vulkan)
