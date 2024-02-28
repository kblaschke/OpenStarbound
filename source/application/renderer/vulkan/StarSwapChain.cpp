#include "StarSwapChain.hpp"

#include <iostream>
#include <limits>

namespace Star {

SwapChain::SwapChain(vk::PhysicalDevice physicalDevice,
                     vk::Device logicalDevice,
                     vk::SurfaceKHR nativeSurface)
  : m_physicalDevice(physicalDevice)
  , m_logicalDevice(logicalDevice)
  , m_nativeSurface(nativeSurface)
{
}

SwapChain::~SwapChain()
{
  DeleteOldSwapChain(m_swapChain);
}

void SwapChain::Create(uint32_t graphicsQueueFamilyIndex, uint32_t presentationQueueFamilyIndex)
{
  ChooseExtent();
  ChooseSurfaceFormat();
  ChoosePresentMode();

  LogCapabilities();

  {
    uint32_t imageCount{ std::min(m_surfaceCapabilities.maxImageCount,
                                  m_surfaceCapabilities.minImageCount + 1) };

    vk::SwapchainCreateInfoKHR createInfo{
      vk::SwapchainCreateFlagsKHR(),
      m_nativeSurface,
      imageCount,
      m_imageFormat.format,
      m_imageFormat.colorSpace,
      m_extent,
      1,
      vk::ImageUsageFlagBits::eColorAttachment
    };

    uint32_t const queueFamilyIndices[]{ graphicsQueueFamilyIndex,
                                         presentationQueueFamilyIndex };
    if (graphicsQueueFamilyIndex == presentationQueueFamilyIndex)
    {
      createInfo.imageSharingMode = m_sharingMode = vk::SharingMode::eExclusive;
    }
    else
    {
      createInfo.imageSharingMode = m_sharingMode = vk::SharingMode::eConcurrent;
      createInfo.queueFamilyIndexCount = 2;
      createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }

    createInfo.preTransform = m_surfaceCapabilities.currentTransform;
    createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
    createInfo.presentMode = m_presentMode;
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = m_swapChain;

    try
    {
      m_swapChain = m_logicalDevice.createSwapchainKHR(createInfo);
    }
    catch (const vk::SystemError& ex)
    {
#ifdef VK_ENGINE_DEBUG
      std::cerr << "Failed to create swap chain: " << ex.what() << std::endl;
#endif
      throw std::runtime_error("Failed to create swap chain");
    }

    DeleteOldSwapChain(createInfo.oldSwapchain);
  }

  m_images = m_logicalDevice.getSwapchainImagesKHR(m_swapChain);

  m_frames.clear();
  m_frames.reserve(m_images.size());

  for (const auto& image : m_images)
  {
    vk::ImageViewCreateInfo createInfo{};

    createInfo.image = image;
    createInfo.format = m_imageFormat.format;
    createInfo.viewType = vk::ImageViewType::e2D;
    createInfo.components.r = vk::ComponentSwizzle::eIdentity;
    createInfo.components.g = vk::ComponentSwizzle::eIdentity;
    createInfo.components.b = vk::ComponentSwizzle::eIdentity;
    createInfo.components.a = vk::ComponentSwizzle::eIdentity;
    createInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    m_frames.push_back(m_logicalDevice.createImageView(createInfo));
  }
}

void SwapChain::ChooseSurfaceFormat()
{
  m_surfaceFormats = m_physicalDevice.getSurfaceFormatsKHR(m_nativeSurface);

  if (m_surfaceFormats.empty())
  {
    // ToDo: Throw something better.
    throw std::exception();
  }

  // Prefer standard 32-bit RGBA, otherwise use "best" (AKA first) format.
  m_imageFormat = m_surfaceFormats.at(0);
  for (const auto& format: m_surfaceFormats)
  {
    if (format.format == vk::Format::eB8G8R8A8Unorm && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
    {
      m_imageFormat = format;
    }
  }

#ifdef VK_ENGINE_DEBUG
  std::cout << "Using pixel format " << vk::to_string(m_imageFormat.format) << " in color space "
              << vk::to_string(m_imageFormat.colorSpace) << std::endl;
#endif
}

void SwapChain::ChoosePresentMode()
{
  m_presentModes = m_physicalDevice.getSurfacePresentModesKHR(m_nativeSurface);

  if (m_presentModes.empty())
  {
    // ToDo: Throw something better.
    throw std::exception();
  }

  // Prefer Fifo mode. May later add capability of switching to immediate mode if supported.
  // Might also be good to use eMailbox as best choice.
  m_presentMode = m_presentModes.at(0);
  for (const auto& mode: m_presentModes)
  {
    if (mode == vk::PresentModeKHR::eFifo)
    {
      m_presentMode = mode;
    }
  }

#ifdef VK_ENGINE_DEBUG
  std::cout << "Using presentation mode " << vk::to_string(m_presentMode) << std::endl;
#endif
}

void SwapChain::ChooseExtent()
{
  m_surfaceCapabilities = m_physicalDevice.getSurfaceCapabilitiesKHR(m_nativeSurface);

  if (m_surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
  {
    m_extent = m_surfaceCapabilities.currentExtent;
  }
  else
  {
    m_extent.width = std::min(m_surfaceCapabilities.minImageExtent.width,
                              m_surfaceCapabilities.maxImageExtent.width);
    m_extent.height = std::min(m_surfaceCapabilities.minImageExtent.height,
                               m_surfaceCapabilities.maxImageExtent.height);
  }

#ifdef VK_ENGINE_DEBUG
  std::cout << "Using image extent " << m_extent.width << "x" << m_extent.height << std::endl;
#endif
}


void SwapChain::DeleteOldSwapChain(vk::SwapchainKHR swapChain)
{
  if (m_logicalDevice && swapChain)
  {
    for (const auto& frame: m_frames)
    {
      m_logicalDevice.destroyImageView(frame);
    }

    m_frames.clear();
    m_images.clear();
    m_logicalDevice.destroySwapchainKHR(swapChain);
  }
}

void SwapChain::LogCapabilities() const
{
#ifdef VK_ENGINE_DEBUG
  std::cout << "Swap chain capabilities:" << std::endl;
    std::cout << "    - Min image count: " << m_surfaceCapabilities.minImageCount << std::endl;
    std::cout << "    - Max image count: " << m_surfaceCapabilities.maxImageCount << std::endl;
    std::cout << "    - Current extent: " << m_surfaceCapabilities.currentExtent.width << "x"
              << m_surfaceCapabilities.currentExtent.height << std::endl;
    std::cout << "    - Min image extent: " << m_surfaceCapabilities.minImageExtent.width << "x"
              << m_surfaceCapabilities.minImageExtent.height << std::endl;
    std::cout << "    - Max image extent: " << m_surfaceCapabilities.maxImageExtent.width << "x"
              << m_surfaceCapabilities.maxImageExtent.height << std::endl;
    std::cout << "    - Max image array layers: " << m_surfaceCapabilities.maxImageArrayLayers << std::endl;
    std::cout << "    - Supported transforms: " << std::hex
              << static_cast<uint32_t>(m_surfaceCapabilities.supportedTransforms) << std::dec << std::endl;
    std::cout << "    - Current transform: " << std::hex
              << static_cast<uint32_t>(m_surfaceCapabilities.currentTransform) << std::dec << std::endl;
    std::cout << "    - Supported composite alpha: "
              << static_cast<uint32_t>(m_surfaceCapabilities.supportedCompositeAlpha) << std::endl;
    std::cout << "    - Supported image usage: " << std::hex
              << static_cast<uint32_t>(m_surfaceCapabilities.supportedUsageFlags) << std::dec << std::endl;

    std::cout << "Supported surface formats:" << std::endl;
    for (const auto& format: m_surfaceFormats)
    {
        std::cout << "    - Pixel format " << vk::to_string(format.format) << " in color space "
                  << vk::to_string(format.colorSpace) << std::endl;
    }

    std::cout << "Supported present modes:" << std::endl;
    for (const auto& mode: m_presentModes)
    {
        std::cout << "    - " << vk::to_string(mode) << std::endl;
    }
#endif
}

}
