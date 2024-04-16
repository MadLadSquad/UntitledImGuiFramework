#pragma once
#ifdef UIMGUI_OS_MODULE_ENABLED
    #ifdef UIMGUI_UEXEC_SUBMODULE_ENABLED
        #include "../ThirdParty/uexec/uexec.hpp"
        #include "../ThirdParty/uexec/C/cuexec.h"
    #endif

    #ifdef UIMGUI_XDG_BASEDIR_SUBMODULE_ENABLED
        #ifndef _WIN32
            #include "../ThirdParty/UntitledXDGBasedir/UXDGBaseDir.hpp"
            #include "../ThirdParty/UntitledXDGBasedir/CUXDGBaseDir.h"
        #endif
    #endif

    #ifdef UIMGUI_DBUS_SUBMODULE_ENABLED
        #include <OS/ThirdParty/UntitledDBusUtils/DBusUtils.hpp>
    #endif

    #ifdef UIMGUI_OPEN_SUBMODULE_ENABLED
        #include "UntitledOpen/C/CUntitledOpen.h"
        #include "UntitledOpen/UntitledOpen.hpp"
    #endif

    #include "Unix/DBus.hpp"
    #include "Unix/Fontconfig.hpp"
#endif