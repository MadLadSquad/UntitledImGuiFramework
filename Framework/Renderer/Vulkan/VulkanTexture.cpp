#include "VulkanTexture.hpp"
#include "Interfaces/RendererInterface.hpp"

#ifndef __EMSCRIPTEN__
static uint32_t findMemoryType(const vk::PhysicalDevice& physicalDevice, const uint32_t type_filter, const vk::MemoryPropertyFlags properties)
{
    const auto memoryProperties = physicalDevice.getMemoryProperties();

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
        if ((type_filter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
            return i;

    return 0xFFFFFFFF; // Unable to find memoryType
}
#endif

UImGui::VulkanTexture::VulkanTexture(const String location, const bool bFiltered) noexcept
{
    init(location, bFiltered);
}

void UImGui::VulkanTexture::init(const String location, const bool bFiltered) noexcept
{
    defaultInit(location, bFiltered);
}

void UImGui::VulkanTexture::load(void* data, FVector2 size, uint32_t depth, const bool bFreeImageData, const std::function<void(void*)>& freeFunc) noexcept
{
    beginLoad(&data, size);
#ifndef __EMSCRIPTEN__
    vk::DeviceSize deviceSize = static_cast<vk::DeviceSize>(size.x * size.y) * 4;
    auto& windowData = Renderer::get().vulkan.draw.window;
    auto& device = Renderer::get().vulkan.device.get();

    const vk::ImageCreateInfo info
    {
        .sType = vk::StructureType::eImageCreateInfo,
        .imageType = vk::ImageType::e2D,
        .format = vk::Format::eR8G8B8A8Unorm,
        .extent =
        {
            .width = static_cast<uint32_t>(dt.size.x),
            .height = static_cast<uint32_t>(dt.size.y),
            .depth = 1,
        },
        .mipLevels = 1,
        .arrayLayers = 1,
        .samples = vk::SampleCountFlagBits::e1,
        .tiling = vk::ImageTiling::eOptimal,
        .usage = vk::ImageUsageFlagBits::eSampled | vk::ImageUsageFlagBits::eTransferDst,
        .sharingMode = vk::SharingMode::eExclusive,
        .initialLayout = vk::ImageLayout::eUndefined,
    };
    vk::Result result = device.createImage(&info, nullptr, &image);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't create Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }

    vk::MemoryRequirements requirements = device.getImageMemoryRequirements(image);
    const vk::MemoryAllocateInfo allocationInfo
    {
        .sType = vk::StructureType::eMemoryAllocateInfo,
        .allocationSize = requirements.size,
        .memoryTypeIndex = findMemoryType(Renderer::get().vulkan.device.physicalDevice, requirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal),
    };
    result = device.allocateMemory(&allocationInfo, nullptr, &imageMemory);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't allocate memory for Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }

    device.bindImageMemory(image, imageMemory, 0);

    const vk::ImageViewCreateInfo imageViewCreateInfo
    {
        .sType = vk::StructureType::eImageViewCreateInfo,
        .image = image,
        .viewType = vk::ImageViewType::e2D,
        .format = vk::Format::eR8G8B8A8Unorm,
        .subresourceRange =
        {
            .aspectMask = vk::ImageAspectFlagBits::eColor,
            .levelCount = 1,
            .layerCount = 1,
        }
    };
    result = device.createImageView(&imageViewCreateInfo, nullptr, &imageView);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't create image view for Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }

    const vk::SamplerCreateInfo samplerCreateInfo
    {
        .sType = vk::StructureType::eSamplerCreateInfo,
        .magFilter = dt.bFiltered ? vk::Filter::eLinear : vk::Filter::eNearest,
        .minFilter = dt.bFiltered ? vk::Filter::eLinear : vk::Filter::eNearest,
        .mipmapMode = vk::SamplerMipmapMode::eLinear,
        .addressModeU = vk::SamplerAddressMode::eRepeat,
        .addressModeV = vk::SamplerAddressMode::eRepeat,
        .addressModeW = vk::SamplerAddressMode::eRepeat,
        .maxAnisotropy = 1.0f,
        .minLod = -1000,
        .maxLod = 1000,
    };
    result = device.createSampler(&samplerCreateInfo, nullptr, &sampler);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't create image sampler for Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }

    descriptorSet = ImGui_ImplVulkan_AddTexture(sampler, imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    const vk::BufferCreateInfo bufferCreateInfo =
    {
        .sType = vk::StructureType::eBufferCreateInfo,
        .size = deviceSize,
        .usage = vk::BufferUsageFlagBits::eTransferSrc,
        .sharingMode = vk::SharingMode::eExclusive,
    };
    result = device.createBuffer(&bufferCreateInfo, nullptr, &uploadBuffer);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't create upload buffer for Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }

    requirements = device.getBufferMemoryRequirements(uploadBuffer);
    const vk::MemoryAllocateInfo memoryAllocateInfo
    {
        .sType = vk::StructureType::eMemoryAllocateInfo,
        .allocationSize = requirements.size,
        .memoryTypeIndex = findMemoryType(Renderer::get().vulkan.device.physicalDevice, requirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible),
    };
    result = device.allocateMemory(&memoryAllocateInfo, nullptr, &uploadBufferMemory);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't allocate memory for the upload buffer of Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }
    device.bindBufferMemory(uploadBuffer, uploadBufferMemory, 0);

    void* map = nullptr;
    result = device.mapMemory(uploadBufferMemory, 0, deviceSize, static_cast<vk::MemoryMapFlags>(0), &map);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't map memory for the upload buffer of Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }
    memcpy(map, data, deviceSize);

    const vk::MappedMemoryRange range
    {
        .sType = vk::StructureType::eMappedMemoryRange,
        .memory = uploadBufferMemory,
        .size =  deviceSize
    };
    result = device.flushMappedMemoryRanges(1, &range);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't flush mapped memory for the upload buffer of Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    };
    device.unmapMemory(uploadBufferMemory);
#endif
    endLoad(data, bFreeImageData, freeFunc);
#ifndef __EMSCRIPTEN__

    const vk::CommandPool commandPool = windowData.Frames[windowData.FrameIndex].CommandPool;
    vk::CommandBuffer commandBuffer;

    const vk::CommandBufferAllocateInfo commandBufferAllocateInfo
    {
        .sType = vk::StructureType::eCommandBufferAllocateInfo,
        .commandPool = commandPool,
        .level = vk::CommandBufferLevel::ePrimary,
        .commandBufferCount = 1,
    };
    result = device.allocateCommandBuffers(&commandBufferAllocateInfo, &commandBuffer);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't allocate command for Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    };

    constexpr vk::CommandBufferBeginInfo commandBufferBeginInfo
    {
        .sType = vk::StructureType::eCommandBufferBeginInfo,
        .flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit,
    };
    result = commandBuffer.begin(&commandBufferBeginInfo);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't begin recording the command buffer for Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }

    const vk::ImageMemoryBarrier copyBarrier
    {
        .sType = vk::StructureType::eImageMemoryBarrier,
        .dstAccessMask = vk::AccessFlagBits::eTransferWrite,
        .oldLayout = vk::ImageLayout::eUndefined,
        .newLayout = vk::ImageLayout::eTransferDstOptimal,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image = image,
        .subresourceRange =
        {
            .aspectMask = vk::ImageAspectFlagBits::eColor,
            .levelCount = 1,
            .layerCount = 1,
        }
    };
    commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eHost, vk::PipelineStageFlagBits::eTransfer, static_cast<vk::DependencyFlags>(0), 0, nullptr, 0, nullptr, 1, &copyBarrier);

    const vk::BufferImageCopy region
    {
        .imageSubresource =
        {
            .aspectMask = vk::ImageAspectFlagBits::eColor,
            .layerCount = 1,
        },
        .imageExtent =
        {
            .width = static_cast<uint32_t>(dt.size.x),
            .height = static_cast<uint32_t>(dt.size.y),
            .depth = 1,
        },
    };
    commandBuffer.copyBufferToImage(uploadBuffer, image, vk::ImageLayout::eTransferDstOptimal, 1, &region);

    const vk::ImageMemoryBarrier useBarrier
    {
        .sType = vk::StructureType::eImageMemoryBarrier,
        .srcAccessMask = vk::AccessFlagBits::eTransferWrite,
        .dstAccessMask = vk::AccessFlagBits::eShaderRead,
        .oldLayout = vk::ImageLayout::eTransferDstOptimal,
        .newLayout = vk::ImageLayout::eShaderReadOnlyOptimal,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image = image,
        .subresourceRange =
        {
            .aspectMask = vk::ImageAspectFlagBits::eColor,
            .levelCount = 1,
            .layerCount = 1
        },
    };
    commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eFragmentShader, static_cast<vk::DependencyFlags>(0), 0, nullptr, 0, nullptr, 1, &useBarrier);

    const vk::SubmitInfo endInfo
    {
        .sType = vk::StructureType::eSubmitInfo,
        .commandBufferCount = 1,
        .pCommandBuffers = &commandBuffer,
    };
    commandBuffer.end();

    result = Renderer::get().vulkan.device.queue.submit(1, &endInfo, VK_NULL_HANDLE);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't submit to the queue for the Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }
    Renderer::get().vulkan.device.queue.waitIdle();
    device.freeCommandBuffers(commandPool, 1, &commandBuffer);
    bCreated = true;
#endif
}

uintptr_t UImGui::VulkanTexture::get() noexcept
{
#ifdef __EMSCRIPTEN__
    return 0;
#else
    return reinterpret_cast<intptr_t>(descriptorSet);
#endif
}

void UImGui::VulkanTexture::clear() noexcept
{
#ifndef __EMSCRIPTEN__
    if (Renderer::data().rendererType == UIMGUI_RENDERER_TYPE_VULKAN_WEBGPU && bCreated)
    {
        auto& device = Renderer::get().vulkan.device.get();

        device.freeMemory(uploadBufferMemory, nullptr);
        device.destroyBuffer(uploadBuffer, nullptr);
        device.destroySampler(sampler, nullptr);
        device.destroyImageView(imageView, nullptr);
        device.destroyImage(image, nullptr);
        device.freeMemory(imageMemory, nullptr);
        ImGui_ImplVulkan_RemoveTexture(descriptorSet);
        bCreated = false;
    }
#endif
}

UImGui::VulkanTexture::~VulkanTexture() noexcept
{
    clear();
}
