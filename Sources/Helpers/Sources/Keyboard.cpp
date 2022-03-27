#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework {
    int KeyboardPlus::SetKeyboard(const String &name, bool canAbort, bool isHex, const int maxLength, u8 &output, u8 start) {
        Sleep(Milliseconds(100));
        Keyboard keyboard(name);
        keyboard.CanAbort(canAbort);
        keyboard.IsHexadecimal(isHex);
        keyboard.SetMaxLength(maxLength);
        return keyboard.Open((u8 &)output, (u8)start);
    }

    int KeyboardPlus::SetKeyboard(const String &name, bool canAbort, bool isHex, const int maxLength, u16 &output, u16 start) {
        Sleep(Milliseconds(100));
        Keyboard keyboard(name);
        keyboard.CanAbort(canAbort);
        keyboard.IsHexadecimal(isHex);
        keyboard.SetMaxLength(maxLength);
        return keyboard.Open((u16 &)output, (u16)start);
    }

    int KeyboardPlus::SetKeyboard(const String &name, bool canAbort, bool isHex, const int maxLength, u32 &output, u32 start) {
        Sleep(Milliseconds(100));
        Keyboard keyboard(name);
        keyboard.CanAbort(canAbort);
        keyboard.IsHexadecimal(isHex);
        keyboard.SetMaxLength(maxLength);
        return keyboard.Open((u32 &)output, (u32)start);
    }

    int KeyboardPlus::SetKeyboard(const String &name, bool canAbort, const StringVector &options, int &index) {
        Sleep(Milliseconds(100));
        Keyboard keyboard(name);
        keyboard.CanAbort(canAbort);
        keyboard.Populate(options);
        index = keyboard.Open();
        return index;
    }

    u32 min, max;

    bool KeyboardCallback(const void *input, string &error) {
        u16 val = *static_cast<const u16 *>(input);

        if (val >= min && val <= max)
            return (true);

        error = "The value must be between " << to_string(min) << "-" << to_string(max) << ".";
        return (false);
    }
}