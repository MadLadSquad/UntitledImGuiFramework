#pragma once
#include <C/CTypes.h>
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct UImGui_TextureData UImGuiTextureData;
    typedef bool(*UImGui_Texture_CustomSaveFunction)(UImGui_TextureData* data, UImGui_String location);

    typedef void UImGui_CTexture;

    /**
     * @brief Stores data for a texture
     * @var filename - file location of the texture
     * @var id - texture ID
     * @var size - Width and height as a 2D Vector
     * @var channels - Number of colour channels
     * @var data - Custom texture data, can be left null if loading from a file
     * @var storageIndex - Internal variable part of the C garbage collection system
     * @var customSaveFunction - Callback for saving the image to a file
     */
    typedef struct UIMGUI_PUBLIC_API UImGui_TextureData
    {
        UImGui_String filename;
        UImGui_FVector2 size;
        int channels;

        void* data;

        // This stores the string location for the internal C storage system
        size_t storageIndex;

        UImGui_Texture_CustomSaveFunction customSaveFunction;
    } UImGui_TextureData;

    /**
     * @brief Enum of standard texture formats. Use UIMGUI_TEXTURE_FORMAT_OTHER when using your own loading function
     */
    typedef enum UIMGUI_PUBLIC_API UImGui_TextureFormat
    {
        UIMGUI_TEXTURE_FORMAT_PNG,
        UIMGUI_TEXTURE_FORMAT_BMP,
        UIMGUI_TEXTURE_FORMAT_TGA,
        UIMGUI_TEXTURE_FORMAT_JPEG,
        UIMGUI_TEXTURE_FORMAT_OTHER
    } UImGui_TextureFormat;

    typedef void(*UImGui_Texture_FreeFunctionT)(void*);

    // The default function for freeing texture data in textures
    UIMGUI_PUBLIC_API void UImGui_Texture_defaultFreeFunc(void* data);

    /**
    * @brief Equivalent to calling the constructor
    * @note Event Safety - Any time
    */
    UIMGUI_PUBLIC_API UImGui_CTexture* UImGui_Texture_init(UImGui_String file);

    // Loads the image for regular OpenGL/Vulkan usage.
    // Event Safety - Post-begin
    // The C++ API uses the following default arguments:
    // data: nullptr
    // x: 0
    // y: 0
    // bFreeImageData: true
    // freeFunc: UImGui_Texture_defaultFreeFunc
    UIMGUI_PUBLIC_API void UImGui_Texture_load(UImGui_CTexture* texture, void* data, uint32_t x, uint32_t y, uint32_t depth,
                                               bool bFreeImageData, UImGui_Texture_FreeFunctionT defaultFreeFunc);

    // Returns the image buffer
    // Event Safety - Any time
    UIMGUI_PUBLIC_API uintptr_t UImGui_Texture_get(UImGui_CTexture* texture);

    // Outputs an image with a given format to a file. Only works if the image buffer is not freed automatically
    // when loading the image.
    // jpegQuality is set to 100 by default in the C++ API. 0 = lowest quality, 100 = highest quality
    // Even Safety - Post-begin
    UIMGUI_PUBLIC_API bool UImGui_Texture_saveToFile(UImGui_CTexture* texture, UImGui_String location,
                                                     UImGui_TextureFormat fmt, uint8_t jpegQuality);

    // Set a function for saving custom image file formats
    // Event Safety - All initiated
    UIMGUI_PUBLIC_API void UImGui_Texture_setCustomSaveFunction(UImGui_CTexture* texture, UImGui_Texture_CustomSaveFunction f);

    // Returns the size of the image
    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Texture_size(UImGui_CTexture* texture);

    // Cleans up the image data
    // Event Safety - All initiated
    UIMGUI_PUBLIC_API void UImGui_Texture_clear(UImGui_CTexture* texture);

    // Frees the Texture handle
    // Event safety - Post-begin
    UIMGUI_PUBLIC_API void UImGui_Texture_release(const UImGui_CTexture* texture);
#ifdef __cplusplus
};
#endif