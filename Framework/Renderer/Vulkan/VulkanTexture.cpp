#include "VulkanTexture.hpp"
#include <Renderer/RendererUtils.hpp>
#include <Interfaces/RendererInterface.hpp>

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

void UImGui::VulkanTexture::init(TextureData& dt, const String location, const bool bFiltered) noexcept
{
    defaultInit(dt, location, bFiltered);
#ifndef __EMSCRIPTEN__
    dt.context = new VulkanTextureData{};
    dt.contextSize = sizeof(VulkanTextureData);
#endif
}

void UImGui::VulkanTexture::load(TextureData& dt, void* data, FVector2 size, uint32_t depth, const bool bFreeImageData, const std::function<void(void*)>& freeFunc) noexcept
{
    beginLoad(dt, &data, size);
#ifndef __EMSCRIPTEN__
    auto* texDt = static_cast<VulkanTextureData*>(dt.context);

    vk::DeviceSize deviceSize = static_cast<vk::DeviceSize>(size.x * size.y) * 4;
    auto* renderer = dynamic_cast<VulkanRenderer*>(RendererUtils::getRenderer());

    auto& windowData = renderer->draw.window;
    auto& device = renderer->device.get();

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
    vk::Result result = device.createImage(&info, nullptr, &texDt->image);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't create Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }

    vk::MemoryRequirements requirements = device.getImageMemoryRequirements(texDt->image);
    const vk::MemoryAllocateInfo allocationInfo
    {
        .sType = vk::StructureType::eMemoryAllocateInfo,
        .allocationSize = requirements.size,
        .memoryTypeIndex = findMemoryType(renderer->device.physicalDevice, requirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal),
    };
    result = device.allocateMemory(&allocationInfo, nullptr, &texDt->imageMemory);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't allocate memory for Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }

    device.bindImageMemory(texDt->image, texDt->imageMemory, 0);

    const vk::ImageViewCreateInfo imageViewCreateInfo
    {
        .sType = vk::StructureType::eImageViewCreateInfo,
        .image = texDt->image,
        .viewType = vk::ImageViewType::e2D,
        .format = vk::Format::eR8G8B8A8Unorm,
        .subresourceRange =
        {
            .aspectMask = vk::ImageAspectFlagBits::eColor,
            .levelCount = 1,
            .layerCount = 1,
        }
    };
    result = device.createImageView(&imageViewCreateInfo, nullptr, &texDt->imageView);
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
    result = device.createSampler(&samplerCreateInfo, nullptr, &texDt->sampler);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't create image sampler for Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }

    texDt->descriptorSet = ImGui_ImplVulkan_AddTexture(texDt->sampler, texDt->imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    const vk::BufferCreateInfo bufferCreateInfo =
    {
        .sType = vk::StructureType::eBufferCreateInfo,
        .size = deviceSize,
        .usage = vk::BufferUsageFlagBits::eTransferSrc,
        .sharingMode = vk::SharingMode::eExclusive,
    };
    result = device.createBuffer(&bufferCreateInfo, nullptr, &texDt->uploadBuffer);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't create upload buffer for Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }

    requirements = device.getBufferMemoryRequirements(texDt->uploadBuffer);
    const vk::MemoryAllocateInfo memoryAllocateInfo
    {
        .sType = vk::StructureType::eMemoryAllocateInfo,
        .allocationSize = requirements.size,
        .memoryTypeIndex = findMemoryType(renderer->device.physicalDevice, requirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible),
    };
    result = device.allocateMemory(&memoryAllocateInfo, nullptr, &texDt->uploadBufferMemory);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't allocate memory for the upload buffer of Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }
    device.bindBufferMemory(texDt->uploadBuffer, texDt->uploadBufferMemory, 0);

    void* map = nullptr;
    result = device.mapMemory(texDt->uploadBufferMemory, 0, deviceSize, static_cast<vk::MemoryMapFlags>(0), &map);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't map memory for the upload buffer of Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }
    memcpy(map, data, deviceSize);

    const vk::MappedMemoryRange range
    {
        .sType = vk::StructureType::eMappedMemoryRange,
        .memory = texDt->uploadBufferMemory,
        .size =  deviceSize
    };
    result = device.flushMappedMemoryRanges(1, &range);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't flush mapped memory for the upload buffer of Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    };
    device.unmapMemory(texDt->uploadBufferMemory);
#endif
    endLoad(dt, data, bFreeImageData, freeFunc);
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
        .image = texDt->image,
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
    commandBuffer.copyBufferToImage(texDt->uploadBuffer, texDt->image, vk::ImageLayout::eTransferDstOptimal, 1, &region);

    const vk::ImageMemoryBarrier useBarrier
    {
        .sType = vk::StructureType::eImageMemoryBarrier,
        .srcAccessMask = vk::AccessFlagBits::eTransferWrite,
        .dstAccessMask = vk::AccessFlagBits::eShaderRead,
        .oldLayout = vk::ImageLayout::eTransferDstOptimal,
        .newLayout = vk::ImageLayout::eShaderReadOnlyOptimal,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image = texDt->image,
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

    result = renderer->device.queue.submit(1, &endInfo, VK_NULL_HANDLE);
    if (result != vk::Result::eSuccess)
    {
        Logger::log("Couldn't submit to the queue for the Vulkan texture at location: ", ULOG_LOG_TYPE_WARNING, dt.filename);
        return;
    }
    renderer->device.queue.waitIdle();
    device.freeCommandBuffers(commandPool, 1, &commandBuffer);
    texDt->bCreated = true;
#endif
}

uintptr_t UImGui::VulkanTexture::get(TextureData& dt) noexcept
{
#ifdef __EMSCRIPTEN__
    return 0;
#else
    return reinterpret_cast<intptr_t>(static_cast<VulkanTextureData*>(dt.context)->descriptorSet);
#endif
}

void UImGui::VulkanTexture::clear(TextureData& dt) noexcept
{
#ifndef __EMSCRIPTEN__
    auto* texDt = static_cast<VulkanTextureData*>(dt.context);
    if (Renderer::data().textureRendererType == UIMGUI_RENDERER_TYPE_VULKAN_WEBGPU && texDt->bCreated)
    {
        auto& device = dynamic_cast<VulkanRenderer*>(RendererUtils::getRenderer())->device.get();

        device.freeMemory(texDt->uploadBufferMemory, nullptr);
        device.destroyBuffer(texDt->uploadBuffer, nullptr);
        device.destroySampler(texDt->sampler, nullptr);
        device.destroyImageView(texDt->imageView, nullptr);
        device.destroyImage(texDt->image, nullptr);
        device.freeMemory(texDt->imageMemory, nullptr);
        ImGui_ImplVulkan_RemoveTexture(texDt->descriptorSet);
        texDt->bCreated = false;

        delete texDt;
    }
#endif
}