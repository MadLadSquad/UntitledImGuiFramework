#pragma once
#include <C/CTypes.h>
#include "CComponentCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum UIMGUI_PUBLIC_API UImGui_TitlebarMenuItemType
    {
        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_MENU_ITEM,
        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_SUBMENU,
        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_END_SUBMENU,

        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_SEPARATOR,
        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_CHECKBOX,

        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_BEGIN_RADIO,
        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_RADIO_BUTTON,
        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_END_RADIO,

        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_APP_MENU_DEFAULT,
        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_WINDOW_MENU_DEFAULT,
        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_HELP_MENU_DEFAULT,
        UIMGUI_TITLEBAR_MENU_ITEM_TYPE_EDIT_MENU_DEFAULT
    } UImGui_TitlebarMenuItemType;

    typedef void UImGui_CTitlebarBuilder;
    typedef void UImGui_CRadioBuilder;
    typedef void(*UImGui_TitlebarBuilderMenuItemFunc)(void*);

    /**
     * @brief Initialises the radio button by setting its selected index reference. Free with UImGui_RadioBuilder_free
     * @param selectedIndex - A pointer to the current selected index
     * @return A pointer to the current radio builder
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API UImGui_CRadioBuilder* UImGui_RadioBuilder_init(int* selectedIndex);

    /**
     * @brief Adds a radio button to the menu bar
     * @param builder - The builder instance, to which the button will be added
     * @param label - The label of the button
     * @param bEnabled - Whether the radio button can be selected
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_RadioBuilder_add(UImGui_CRadioBuilder* builder, UImGui_String label, bool* bEnabled);

    /**
     * @brief Frees the memory for a C radio builder
     * @param builder The builder to be freed
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API void UImGui_RadioBuilder_free(UImGui_CRadioBuilder* builder);


    // Allocates a new C instance of the TitlebarBuilder class
    // Event safety - Any time
    UIMGUI_PUBLIC_API UImGui_CTitlebarBuilder* UImGui_TitlebarBuilder_init();

    /**
     * @brief Enables/disables integrating with the global menu on macOS instead of drawing the menu ourselves using dear imgui
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @param bBuildNativeOnMacOS - Whether to build a native menu on macOS. Doesn't have to be set when not on macOS.
     * Setting this value on macOS changes the behaviour of the finish and render methods.
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_setBuildNativeOnMacOS(UImGui_CTitlebarBuilder* builder, bool bBuildNativeOnMacOS);

    /**
     * @brief Sets the user-defined context variable for the menu that can be consumed by callbacks
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @param data - A void* to your data context for use in menu callback functions
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_setContext(UImGui_CTitlebarBuilder* builder, void* data);

    /**
     * @brief Adds a menu item aka a button to the menu
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @param label - The text label of the menu item
     * @param hint - Hint text, if it's a key binding from the Input interface try converting it to macOS format on macOS
     * @param f - A callback function that is called when pressed. Gets the user-defined void* context pointer
     * @param bEnabled - Whether the menu item is enabled. NULL is interpreted as true. On false values the button is greyed out and cannot be clicked
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_addMenuItem(UImGui_CTitlebarBuilder* builder, UImGui_String label, UImGui_String hint, UImGui_TitlebarBuilderMenuItemFunc f, bool* bEnabled);

    /**
     * @brief Adds a separator to the menu
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_addSeparator(UImGui_CTitlebarBuilder* builder);

    /**
     * @brief Adds a submenu to the menu
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @param label - The text label of the menu item
     * @param submenu - A pointer to another C menu builder instance that will be added as a submenu
     * @param bEnabled - Whether the menu item is enabled. NULL is interpreted as true. On false values the button is greyed out and cannot be clicked
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_addSubmenu(UImGui_CTitlebarBuilder* builder, UImGui_String label, UImGui_CTitlebarBuilder* submenu, bool* bEnabled);

    /**
     * @brief Adds a checkbox element to the menu
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @param label - The text label of the menu item
     * @param bSelected - A pointer to a boolean. The pointer will be mutated by us when the checkbox is pressed
     * @param bEnabled -Whether the menu item is enabled. NULL is interpreted as true. On false values the button is greyed out and cannot be clicked
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_addCheckbox(UImGui_CTitlebarBuilder* builder, UImGui_String label, bool* bSelected, bool* bEnabled);

    /**
     * @brief Adds a group of radio buttons to the menu
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @param submenu - A radio builder to be added to the menu
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_addRadioGroup(UImGui_CTitlebarBuilder* builder, UImGui_CRadioBuilder* submenu);

    /**
     * @brief Add the default items as part of the macOS application menu(The first submenu that always inherits the name of your application.)
     * A submenu of this kind(Most commonly created with an "" label) has to be created beforehand
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @note Only has effect on macOS
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_addAppMenuDefaultItems(UImGui_CTitlebarBuilder* builder);

    /**
     * @brief Adds the default items to the macOS window menu(a submenu with the title "Window" has to be created beforehand)
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @note Only has effect on macOS
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_addWindowMenuDefaultItems(UImGui_CTitlebarBuilder* builder);

    /**
     * @brief Adds the default items for the macOS help menu(a submenu with the title "Help" has to be created beforehand)
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @note Only has effect on macOS
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_addHelpMenuDefaultItems(UImGui_CTitlebarBuilder* builder);

    /**
     * @brief Adds the default items for the macOS edit menu(a submenu with the title "Edit" has to be created beforehand)
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @note Only has effect on macOS
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_addEditMenuDefaultItems(UImGui_CTitlebarBuilder* builder);

    /**
     * @brief Finishes building the menu. When drawing a macOS menu this function submits it to the OS for rendering. When
     * drawing an imgui-native menu it does nothing.
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_finish(UImGui_CTitlebarBuilder* builder);

    /**
     * @brief Renders the menu. Should be called every frame. When drawing a macOS menu it does nothing. When drawing an
     * imgui-native menu it renders the UI for the menu. Should only be called in Titlebar components
     * @param builder - A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @note Event safety - Tick
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_render(UImGui_CTitlebarBuilder* builder);

    /**
     * @brief Clears the menu for rebuilding
     * @param builder A pointer to the C menu builder instance from UImGui_TitlebarBuilder_init
     * @note Event safety - Begin, Post-begin
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_clear(UImGui_CTitlebarBuilder* builder);

    // Frees a C instance of the TitlebarBuilder class
    // Event safety - Any time
    UIMGUI_PUBLIC_API void UImGui_TitlebarBuilder_free(UImGui_CTitlebarBuilder* builder);


    /**
     * @brief Allocates and creates a new titlebar component from the provided callback functions and returns a handle
     * to it
     * @param construct - A function to be called in the constructor(only really useful during reallocation)
     * @param begin - A "begin" event callback function
     * @param tick - A "tick" event callback function
     * @param end - An "end" event callback function
     * @param destruct - A function to be called during the destructor
     * @param data - C data for the component. Check out the definition of UImGui_CComponentData
     * @return A handle to the component
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API UImGui_CComponentHandle* UImGui_TitlebarComponent_makeCTitlebarComponent(UImGui_ComponentRegularFun construct,
                                                                                      UImGui_ComponentRegularFun begin,
                                                                                      UImGui_ComponentTickFun tick,
                                                                                      UImGui_ComponentRegularFun end,
                                                                                      UImGui_ComponentRegularFun destruct,
                                                                                      UImGui_CComponentData data);

    /**
     * @param handle - A C component handle that should be acquired from UImGui_TitlebarComponent_makeCTitlebarComponent
     * @return A pointer to the C data for the component. Check out the definition of UImGui_CComponentData
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API const UImGui_CComponentData_P* UImGui_TitlebarComponent_getCTitlebarComponentData(const UImGui_CComponentHandle* handle);

    /**
     * @brief Gets the name of the component
     * @param handle - A C component handle that should be acquired from UImGui_TitlebarComponent_makeCTitlebarComponent
     * @return A string containing the name of the component
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API UImGui_String UImGui_TitlebarComponent_getCTitlebarComponentName(const UImGui_CComponentHandle* handle);

    /**
     * @brief Frees a C component handle acquired from UImGui_TitlebarComponent_makeCTitlebarComponent
     * @param handle - A C component handle that should be acquired from UImGui_TitlebarComponent_makeCTitlebarComponent
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API void UImGui_TitlebarComponent_destroyCTitlebarComponent(const UImGui_CComponentHandle* handle);
#ifdef __cplusplus
}
#endif