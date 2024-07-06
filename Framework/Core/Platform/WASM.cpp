#include "WASM.hpp"

#ifdef __EMSCRIPTEN__
EM_JS(bool, em_is_on_macOS, (), {
    let platform = navigator.platform.toLowerCase();
    return platform.indexOf("mac") === 0
        || platform.indexOf("ipad") === 0
        || platform.indexOf("ipod") === 0
        || platform.indexOf("iphone") === 0;
});

EM_JS(bool, em_supports_wgpu, (), {
    return navigator.gpu !== undefined && navigator.gpu !== null && bWebGPUEnabled;
});
#else
bool em_is_on_macOS()
{
#ifdef __APPLE__
    return true;
#else
    return false;
#endif
}
#endif