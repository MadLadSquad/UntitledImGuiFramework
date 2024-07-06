#pragma once
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#endif

// We need to check whether macOS is used, in order to correctly swap Control & Command on when targeting WASM
#if __cplusplus || __EMSCRIPTEN__
extern "C"
{
#endif
    bool em_is_on_macOS();
#ifdef __EMSCRIPTEN__
    bool em_supports_wgpu();
#endif
#if __cplusplus || __EMSCRIPTEN__
}
#endif