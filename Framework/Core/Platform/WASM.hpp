#pragma once
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
// We need to check whether macOS is used, in order to correctly swap Control & Command on when targeting WASM
namespace UImGui
{
#ifdef __EMSCRIPTEN__
    EM_JS(bool, em_is_on_macOS, (), {
        let platform = navigator.platform.toLowerCase();
        return platform.indexOf("mac") === 0
            || platform.indexOf("ipad") === 0
            || platform.indexOf("ipod") === 0
            || platform.indexOf("iphone") === 0;
    });
#else
    constexpr bool em_is_on_macOS() noexcept
    {
#ifdef __APPLE__
        return true;
#else
        return false;
#endif
    }
#endif
}