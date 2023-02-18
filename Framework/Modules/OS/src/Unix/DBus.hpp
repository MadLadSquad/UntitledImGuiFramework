#pragma once
#ifdef UIMGUI_OS_MODULE_ENABLED
#include <dbus/dbus.h>
#include <vector>
#include <array>
#include <typeinfo>

namespace UImGui
{

    class DBusUtils
    {
    private:
        static void initTypeIDTable(std::array<size_t, 16>& typeIDTable) noexcept;
    public:
        template<typename ...T>
        static dbus_bool_t dbus_message_append_args(T&&... argv) noexcept
        {
            static std::array<size_t, 16> typeIDTable;
            bool bFirst = true;
            if (bFirst)
            {
                initTypeIDTable(typeIDTable);
                bFirst = false;
            }

            std::vector<size_t> typeids = { typeid(T).hash_code()... };
            return true;
        }

    private:


    };
}

#endif