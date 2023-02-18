#include "DBus.hpp"
#include <cinttypes>

void UImGui::DBusUtils::initTypeIDTable(std::array<size_t, 16>& typeIDTable) noexcept
{
    // This is the difference between the \0 and the ( character that dbus uses internally
    constexpr int offset = 40;

    typeIDTable[DBUS_TYPE_BYTE - offset] = typeid(unsigned char).hash_code();
    typeIDTable[DBUS_TYPE_BOOLEAN - offset] = typeid(bool).hash_code();

    typeIDTable[DBUS_TYPE_INT16 - offset] = typeid(int16_t).hash_code();
    typeIDTable[DBUS_TYPE_UINT64 - offset] = typeid(uint16_t).hash_code();

    typeIDTable[DBUS_TYPE_INT32 - offset] = typeid(int32_t).hash_code();
    typeIDTable[DBUS_TYPE_UINT32 - offset] = typeid(uint32_t).hash_code();

    typeIDTable[DBUS_TYPE_INT64 - offset] = typeid(int64_t).hash_code();
    typeIDTable[DBUS_TYPE_UINT64 - offset] = typeid(uint64_t).hash_code();

    typeIDTable[DBUS_TYPE_DOUBLE - offset] = typeid(double).hash_code();

    typeIDTable[DBUS_TYPE_STRING - offset] = typeid(char**).hash_code();

    typeIDTable[DBUS_TYPE_OBJECT_PATH - offset] = typeid(char**).hash_code();
    typeIDTable[DBUS_TYPE_SIGNATURE - offset] = typeid(char**).hash_code();

    typeIDTable[DBUS_TYPE_UNIX_FD - offset] = typeid(int).hash_code();
}
