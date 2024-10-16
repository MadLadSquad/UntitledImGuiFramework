#include "Global.hpp"
#include <Components/Instance.hpp>
#include <Utilities.hpp>

UImGui::Global::Global() noexcept
{
    Utility::interruptSignalHandler();
}

UImGui::Global::~Global() noexcept
{
#ifdef _WIN32
    if (pBuf != nullptr && hMapFile != nullptr)
    {
        UnmapViewOfFile(pBuf);
        CloseHandle(hMapFile);
    }
    ExitProcess(0);
#endif
}

void UImGui::Global::init() noexcept
{
    window.createWindow();
}

#define WIN32_SHARED_MEMORY_FILE "Global\\UntitledImGuiFrameworkMappingObject"
#define WIN32_SHARED_MEMORY_BUFFER_SIZE 2048

#ifdef _WIN32
static UImGui::Global* windowsGetSharedGlobal(UImGui::Global* parent) noexcept
{
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, WIN32_SHARED_MEMORY_FILE);
    if (hMapFile == nullptr)
    {
        Logger::log("Couldn not open file mapping object. Error: ", ULOG_LOG_TYPE_WARNING, GetLastError());
        return parent;
    }

    pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, WIN32_SHARED_MEMORY_BUFFER_SIZE);
    if (pBuf == nullptr)
    {
        Logger::log("Couldn not map view of  file. Error: ", ULOG_LOG_TYPE_WARNING, GetLastError());
        CloseHandle(hMapFile);
        return parent;
    }
    return reinterpret_cast<UImGui::Global*>(pBuf);
#endif

UImGui::Global& UImGui::Global::get(Global* parent) noexcept
{
#ifdef _WIN32
    static Global* global = parent == nullptr ? getWithCreate() : windowsGetSharedGlobal(parent);
#else
    static Global* global = parent == nullptr ? getWithCreate() : parent;
#endif
    return *global;
}

UImGui::Global* UImGui::Global::getWithCreate() noexcept
{
    static Global global{};
#ifdef _WIN32
    hMapFile = CreateFileMappingA(
                  INVALID_HANDLE_VALUE,             // use paging file
                  NULL,                             // default security
                  PAGE_READWRITE,                   // read/write access
                  0,                                // maximum object size (high-order DWORD)
                  WIN32_SHARED_MEMORY_BUFFER_SIZE,  // maximum object size (low-order DWORD)
                  WIN32_SHARED_MEMORY_FILE);

    if (hMapFile == nullptr)
    {
        Logger::log("Could not create a shared memory segment. Error: ", ULOG_LOG_TYPE_WARNING, GetLastError());
        hMapFile = nullptr;
        return &global;
    }

    pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, WIN32_SHARED_MEMORY_BUFFER_SIZE);
    if (pBuf == nullptr)
    {
        Logger::log("Could not map view of file. Error: ", ULOG_LOG_TYPE_WARNING, GetLastError());
        CloseHandle(hMapFile);

        hMapFile = nullptr;
        pBuf = nullptr;

        return &global;
    }

    CopyMemory((PVOID)pBuf, &global, sizeof(global));
    return reinterpret_cast<Global*>(pBuf);
#endif

    return &global;
}
