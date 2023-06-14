#pragma once
#include "CDefines.h"

#ifdef __cplusplus
extern "C"
{
#endif
struct UIMGUI_PUBLIC_API UImGui_FVector2_I
{
    float x;
    float y;
};

struct UIMGUI_PUBLIC_API UImGui_FVector_I
{
    float x;
    float y;
    float z;
};

struct UIMGUI_PUBLIC_API UImGui_FVector4_I
{
    float x;
    float y;
    float z;
    float w;
};

typedef const char* UImGui_String;

typedef struct UImGui_FVector2_I UImGui_FVector2;
typedef struct UImGui_FVector_I UImGui_FVector;
typedef struct UImGui_FVector4_I UImGui_FVector4;

#ifdef __cplusplus
};
#endif