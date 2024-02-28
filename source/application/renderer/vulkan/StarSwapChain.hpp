#pragma once

#include <vulkan/vulkan.hpp>

namespace Star {

class SwapChain
{
public:
  SwapChain(vk::PhysicalDevice physicalDevice,
            vk::Device logicalDevice,
            vk::SurfaceKHR nativeSurface);

  virtual ~SwapChain();

  /**
   * @brief Creates or recreates the swap chain.
   * @note If the logical device has been lost, the whole swap chain class must be recreated!
   * @param graphicsQueueFamilyIndex The index of the graphics queue in use.
   * @param presentationQueueFamilyIndex The index of the presentation queue in use.
   * @throws std::runtime_error Thrown if the swap chain creation failed.
   */
  void Create(uint32_t graphicsQueueFamilyIndex, uint32_t presentationQueueFamilyIndex);

private:
  void ChooseSurfaceFormat();

  void ChoosePresentMode();

  void ChooseExtent();

  void DeleteOldSwapChain(vk::SwapchainKHR swapChain);

  void LogCapabilities() const;

  vk::PhysicalDevice m_physicalDevice; //!< The physical device used by this swap chain.
  vk::Device m_logicalDevice;          //!< The logical device used by this swap chain.
  vk::SurfaceKHR m_nativeSurface;      //!< Native surface this swap chain will run on.

  vk::SurfaceCapabilitiesKHR m_surfaceCapabilities{}; //!< Supported surface capabilities.
  std::vector<vk::SurfaceFormatKHR> m_surfaceFormats; //!< Supported surface formats.
  std::vector<vk::PresentModeKHR> m_presentModes;     //!< Supported presentation modes.

  vk::SharingMode m_sharingMode{ vk::SharingMode::eExclusive };            //!< Image sharing mode, depends on the number of queues used.
  vk::SurfaceFormatKHR m_imageFormat{ vk::Format::eB8G8R8A8Unorm,
                                      vk::ColorSpaceKHR::eSrgbNonlinear }; //!< Image format used by the swap chain.
  vk::PresentModeKHR m_presentMode{ vk::PresentModeKHR::eFifo };           //!< Presentation mode used by the swap chain.
  vk::Extent2D m_extent{};                                                 //!< Extent (AKA image size) for the output.

  vk::SwapchainKHR m_swapChain;        //!< The actual swap chain instance.
  std::vector<vk::Image> m_images;     //!< The swap chain images.
  std::vector<vk::ImageView> m_frames; //!< Image views to access the swap chain images.

};

}
