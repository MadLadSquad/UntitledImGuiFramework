#pragma once
#include <C/CTypes.h>
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif
    struct UIMGUI_PUBLIC_API UImGui_TextureData_I
    {
        UImGui_String filename;
        uint32_t id;
        UImGui_FVector2 size;
        int channels;

        // This stores the string location for the internal C storage system
        size_t storageIndex;
    };

    typedef struct UImGui_TextureData_I UImGui_TextureData;
    typedef void(*UImGui_Texture_FreeFunctionT)(void*);

    // The default function for freeing texture data in textures
    UIMGUI_PUBLIC_API void UImGui_Texture_defaultFreeFunc(void* data);

    /**
    * @brief Equivalent to calling the constructor
    * @note Event Safety - Any time
    */
    UIMGUI_PUBLIC_API void UImGui_Texture_init(UImGui_TextureData* texture, UImGui_String file);

    // Loads the image for regular OpenGL/Vulkan usage.
    // Event Safety - Post-begin
    // The C++ API uses the following default arguments:
    // data: nullptr
    // x: 0
    // y: 0
    // bFreeImageData: true
    // freeFunc: UImGui_Texture_defaultFreeFunc
    UIMGUI_PUBLIC_API void UImGui_Texture_load(UImGui_TextureData* texture, void* data, uint32_t x, uint32_t y, uint32_t depth,
                                               bool bFreeImageData, UImGui_Texture_FreeFunctionT defaultFreeFunc);
    // Loads the image for dear imgui OpenGL/Vulkan usage
    // Event Safety - Post-begin
    // The C++ API uses the following default arguments:
    // data: nullptr
    // x: 0
    // y: 0
    // bFreeImageData: true
    // freeFunc: UImGui_Texture_defaultFreeFunc
    UIMGUI_PUBLIC_API void UImGui_Texture_loadImGui(UImGui_TextureData* texture, void* data, uint32_t x, uint32_t y, uint32_t depth,
                                                    bool bFreeImageData, UImGui_Texture_FreeFunctionT defaultFreeFunc);

    // Returns the image buffer
    // Event Safety - Any time
    UIMGUI_PUBLIC_API uint32_t UImGui_Texture_get(UImGui_TextureData* texture);

    // Use the regular OpenGL/Vulkan image
    // Event Safety - All initiated
    UIMGUI_PUBLIC_API void UImGui_Texture_use(UImGui_TextureData* texture);

    // Returns the size of the image
    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Texture_size(UImGui_TextureData* texture);

    // Cleans up the image data
    // Event Safety - All initiated
    UIMGUI_PUBLIC_API void UImGui_Texture_clear(UImGui_TextureData* texture);
#ifdef __cplusplus
};
#endif