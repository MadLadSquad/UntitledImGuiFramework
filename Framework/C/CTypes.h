#pragma once
#include "CDefines.h"

#ifdef __cplusplus
extern "C"
{
#endif
typedef struct UIMGUI_PUBLIC_API UImGui_FVector2
{
    float x;
    float y;
} UImGui_FVector2;

typedef struct UIMGUI_PUBLIC_API UImGui_FVector
{
    float x;
    float y;
    float z;
} UImGui_FVector;

typedef struct UIMGUI_PUBLIC_API UImGui_FVector4
{
    float x;
    float y;
    float z;
    float w;
} UImGui_FVector4;

typedef const char* UImGui_String;

#ifdef __cplusplus
};
#endif