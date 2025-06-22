#include "TitlebarComponent.hpp"
#include <C/Internal/Keys.h>
#include <Core/Utilities.hpp>
#include <ThirdParty/utfcpp/source/utf8.h>

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <objc/runtime.h>

static NSMenu* buildTitlebarRecursive(const UImGui::TVector<UImGui::TitlebarMenuItem>& items, size_t begin, size_t end, void* ctx) noexcept;

void UImGui::TitlebarBuilder::macOSFinish() noexcept
{
    [NSApp setMainMenu:buildTitlebarRecursive(events, 0, events.size(), data)];
}

@interface FuncBridge : NSObject <NSMenuItemValidation>
{
    std::function<void(NSMenuItem *)> _cb;
    bool *_enabledPtr;
}
- (instancetype)initWithCallback:(std::function<void(NSMenuItem *)>)cb
                         enabled:(bool *)ptr;
- (void)invoke:(NSMenuItem *)sender;
@end

@implementation FuncBridge
- (instancetype)initWithCallback:(std::function<void(NSMenuItem *)>)cb
                         enabled:(bool *)ptr
{
    if ((self = [super init])) { _cb = std::move(cb); _enabledPtr = ptr; }
    return self;
}
- (void)invoke:(NSMenuItem *)sender { if (_cb) _cb(sender); }
- (BOOL)validateMenuItem:(NSMenuItem *)item
{
    return _enabledPtr ? *_enabledPtr : YES;
}
@end

@interface CheckBridge : NSObject <NSMenuItemValidation>
{
    std::function<void(NSMenuItem *)> _cb;
    bool *_flag;
    bool *_enabledPtr;
}
- (instancetype)initWithFlag:(bool*)flag
                     enabled:(bool*)ptr
                    callback:(std::function<void(NSMenuItem*)>)cb;
- (void)toggle:(NSMenuItem*)sender;
@end

@implementation CheckBridge
- (instancetype)initWithFlag:(bool*)flag
                     enabled:(bool*)ptr
                    callback:(std::function<void(NSMenuItem *)>)cb
{
    if ((self = [super init])) { _flag = flag; _enabledPtr = ptr; _cb = std::move(cb); }
    return self;
}
- (void)toggle:(NSMenuItem *)sender
{
    *_flag = !*_flag;
    sender.state = *_flag ? NSControlStateValueOn : NSControlStateValueOff;
    if (_cb) _cb(sender);
}
- (BOOL)validateMenuItem:(NSMenuItem *)item
{
    item.state = *_flag ? NSControlStateValueOn : NSControlStateValueOff;
    return _enabledPtr ? *_enabledPtr : YES;
}
@end

@interface RadioBridge : NSObject <NSMenuItemValidation>
{
    NSInteger              *indexPtr;
    NSInteger               _myValue;
    bool                   *_enabledPtr;
    int                    *normalSize;
}
- (instancetype)initWithIndexPtr:(NSInteger *)ptr
                           value:(NSInteger)value
                         enabled:(bool *)en
                         normalSize:(int*)normal;
- (void)choose:(NSMenuItem *)sender;
@end

@implementation RadioBridge
- (instancetype)initWithIndexPtr:(NSInteger *)ptr value:(NSInteger)v
                         enabled:(bool *)en normalSize:(int*)normal
{
    if ((self = [super init])) { indexPtr = ptr; _myValue = v; _enabledPtr = en; normalSize = normal; }
    return self;
}
- (void)choose:(NSMenuItem *)sender
{
    *indexPtr = _myValue;
    *normalSize = (int)_myValue;
}
- (BOOL)validateMenuItem:(NSMenuItem *)item
{
    if (*indexPtr != *normalSize)
        *indexPtr = *normalSize;
    item.state = (*indexPtr == _myValue) ? NSControlStateValueOn : NSControlStateValueOff;
    return _enabledPtr ? *_enabledPtr : YES;
}
@end

static std::pair<UImGui::FString, NSEventModifierFlags> parseKeybindingHint(const UImGui::TitlebarMenuItem& item) noexcept
{
    if (item.hint.empty())
      return { "", 0 };

    auto& strings = UImGui::Utility::getKeyStrings();
    UImGui::TUnorderedMap<UImGui::FString, NSEventModifierFlags> modifierMap
    {
        { UImGui::Utility::toLower(strings[Keys_LeftControlCmd].second.c_str()),     NSEventModifierFlagCommand    },
        { UImGui::Utility::toLower(strings[Keys_RightControlCmd].second.c_str()),    NSEventModifierFlagCommand    },

        { UImGui::Utility::toLower(strings[Keys_LeftControl].second.c_str()),        NSEventModifierFlagControl    },
        { UImGui::Utility::toLower(strings[Keys_RightControl].second.c_str()),       NSEventModifierFlagControl    },

        { UImGui::Utility::toLower(strings[Keys_LeftAlt].second.c_str()),            NSEventModifierFlagOption     },
        { UImGui::Utility::toLower(strings[Keys_RightAlt].second.c_str()),           NSEventModifierFlagOption     },

        { UImGui::Utility::toLower(strings[Keys_LeftShift].second.c_str()),          NSEventModifierFlagShift      },
        { UImGui::Utility::toLower(strings[Keys_RightShift].second.c_str()),         NSEventModifierFlagShift      },

        { UImGui::Utility::toLower(strings[Keys_CapsLock].second.c_str()),           NSEventModifierFlagCapsLock   }
    };

    UImGui::TUnorderedMap<UImGui::FString, uint16_t> specialKeyMap
    {
        { UImGui::Utility::toLower(strings[Keys_UpArrow    ].second.c_str()),      NSUpArrowFunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_DownArrow  ].second.c_str()),    NSDownArrowFunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_LeftArrow  ].second.c_str()),    NSLeftArrowFunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_RightArrow ].second.c_str()),   NSRightArrowFunctionKey    },

        { UImGui::Utility::toLower(strings[Keys_F1         ].second.c_str()),           NSF1FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F2         ].second.c_str()),           NSF2FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F3         ].second.c_str()),           NSF3FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F4         ].second.c_str()),           NSF4FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F5         ].second.c_str()),           NSF5FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F6         ].second.c_str()),           NSF6FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F7         ].second.c_str()),           NSF7FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F8         ].second.c_str()),           NSF8FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F9         ].second.c_str()),           NSF9FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F10        ].second.c_str()),          NSF10FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F11        ].second.c_str()),          NSF11FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F12        ].second.c_str()),          NSF12FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F13        ].second.c_str()),          NSF13FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F14        ].second.c_str()),          NSF14FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F15        ].second.c_str()),          NSF15FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F16        ].second.c_str()),          NSF16FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F17        ].second.c_str()),          NSF17FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F18        ].second.c_str()),          NSF18FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F19        ].second.c_str()),          NSF19FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F20        ].second.c_str()),          NSF20FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F21        ].second.c_str()),          NSF21FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F22        ].second.c_str()),          NSF22FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F23        ].second.c_str()),          NSF23FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F24        ].second.c_str()),          NSF24FunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_F25        ].second.c_str()),          NSF25FunctionKey    },

        { UImGui::Utility::toLower(strings[Keys_Insert     ].second.c_str()),       NSInsertFunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_Delete     ].second.c_str()),       NSDeleteFunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_Home       ].second.c_str()),         NSHomeFunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_End        ].second.c_str()),          NSEndFunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_PageUp     ].second.c_str()),       NSPageUpFunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_PageDown   ].second.c_str()),     NSPageDownFunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_PrintScreen].second.c_str()),  NSPrintScreenFunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_ScrollLock ].second.c_str()),   NSScrollLockFunctionKey    },
        { UImGui::Utility::toLower(strings[Keys_Pause      ].second.c_str()),        NSPauseFunctionKey    },
    };

    auto split = UImGui::Utility::splitString(item.hint, "+");
    std::pair<UImGui::FString, NSEventModifierFlags> result{ "", 0 };

    for (auto& a : split)
    {
        UImGui::Utility::toLower(a);
        if (modifierMap.contains(a.c_str()))
            result.second |= modifierMap.at(a.c_str());
        else
        {
            if (specialKeyMap.contains(a.c_str()))
                result.first = [[NSString stringWithCharacters:&specialKeyMap.at(a.c_str()) length:1] UTF8String];
            else
            {
                bool bFound = false;
                for (auto& f : strings)
                    if (a == UImGui::Utility::toLower(f.second.c_str()))
                        bFound = true;

                if (bFound)
                    result.first = a;
            }
        }
    }
    UImGui::Utility::toLower(result.first);
    return result;
}

static NSMenu* buildTitlebarRecursive(const UImGui::TVector<UImGui::TitlebarMenuItem>& items, size_t begin, size_t end, void* ctx) noexcept
{
    NSMenu* menu = [[NSMenu alloc] initWithTitle:@""];
    int radioBegin = 0;
    for (size_t i = begin; i < end; i++)
    {
        const auto& item = items[i];

        if (item.type == UIMGUI_TITLEBAR_MENU_ITEM_TYPE_MENU_ITEM)
        {
            auto keybinding = parseKeybindingHint(item);

            NSString* title = [NSString stringWithUTF8String:item.label.c_str()];
            NSMenuItem* element = [[NSMenuItem alloc] initWithTitle:title
                                                      action:@selector(invoke:)
                                                      keyEquivalent:[NSString stringWithUTF8String:keybinding.first.c_str()]];
            element.keyEquivalentModifierMask = keybinding.second;

            std::function<void(NSMenuItem*)> fn = [ctx, f = item.f](NSMenuItem*) -> void {
                f(ctx);
            };

            auto *bridge = [[FuncBridge alloc] initWithCallback:fn
                                                        enabled:item.bEnabled];
            element.target = bridge;
            objc_setAssociatedObject(element, bridge, bridge,
                                     OBJC_ASSOCIATION_RETAIN_NONATOMIC);
            [menu addItem:element];
        }
        else if (item.type == UIMGUI_TITLEBAR_MENU_ITEM_TYPE_SEPARATOR)
            [menu addItem:[NSMenuItem separatorItem]];
        else if (item.type == UIMGUI_TITLEBAR_MENU_ITEM_TYPE_CHECKBOX)
        {
            if (item.bSelected == nullptr)
            {
                Logger::log("A checkbox with the following label is null, not rendering: ", ULOG_LOG_TYPE_ERROR, item.label.c_str());
                continue;
            }
            NSMenuItem* element = [[NSMenuItem alloc]
                                        initWithTitle:[NSString stringWithUTF8String:item.label.data()]
                                               action:@selector(toggle:)
                                        keyEquivalent:@""];

            element.state = *item.bSelected ? NSControlStateValueOn : NSControlStateValueOff;
            auto *bridge = [[CheckBridge alloc] initWithFlag:item.bSelected
                                                     enabled:item.bEnabled
                                                    callback:nil];
            element.target = bridge;
            objc_setAssociatedObject(element, bridge, bridge,
                                     OBJC_ASSOCIATION_RETAIN_NONATOMIC);
            [menu addItem:element];
        }
        else if (item.type == UIMGUI_TITLEBAR_MENU_ITEM_TYPE_SUBMENU)
        {
            auto *parent = [[NSMenuItem alloc]
                              initWithTitle:[NSString stringWithUTF8String:item.label.data()]
                                     action:nil
                              keyEquivalent:@""];
            std::size_t childStart = i + 1;
            std::size_t childEnd = i + item.membersLen + 1;
            [parent setSubmenu:buildTitlebarRecursive(items, childStart, childEnd, ctx)];
            [menu addItem:parent];
            i = childEnd;
        }
        else if (item.type == UIMGUI_TITLEBAR_MENU_ITEM_TYPE_END_SUBMENU)
            return menu;
        else if (item.type == UIMGUI_TITLEBAR_MENU_ITEM_TYPE_BEGIN_RADIO)
        {
            if (item.size == nullptr)
            {
                i += item.membersLen + 1;
                Logger::log("A radio button was submitted with a NULL index.\n"
                                    "Make sure to always initialise your radio button with UImGui::RadioBuilder::init()!"
                                    "Not rendering!", ULOG_LOG_TYPE_ERROR);
            }
            else
                radioBegin = CAST(int, i) + 1;
        }
        else if (item.type == UIMGUI_TITLEBAR_MENU_ITEM_TYPE_RADIO_BUTTON)
        {
            NSMenuItem* element = [[NSMenuItem alloc]
                                        initWithTitle:[NSString stringWithUTF8String:item.label.data()]
                                               action:@selector(choose:)
                                        keyEquivalent:@""];

            RadioBridge* bridge = [[RadioBridge alloc]
                                        initWithIndexPtr:(NSInteger*)&item.lsize
                                                   value:i - radioBegin
                                                 enabled:item.bEnabled
                                                normalSize: item.size];
            element.target = bridge;
            objc_setAssociatedObject(element, bridge, bridge,
                                     OBJC_ASSOCIATION_RETAIN_NONATOMIC);

            [menu addItem:element];
        }
        else if (item.type == UIMGUI_TITLEBAR_MENU_ITEM_TYPE_END_RADIO)
            radioBegin = 0;
    }
    return menu;
}
