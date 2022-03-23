#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework {
    class KeyboardPlus : public Keyboard {
        public:
            int SetKeyboard(const String &name, bool canAbort, bool isHex, const int maxLength, u8 &output, u8 start);
            int SetKeyboard(const String &name, bool canAbort, bool isHex, const int maxLength, u16 &output, u16 start);
            int SetKeyboard(const String &name, bool canAbort, bool isHex, const int maxLength, u32 &output, u32 start);
            int SetKeyboard(const String &name, bool canAbort, const StringVector &options, int &index);
    };

    using OnCompareCallback = bool (*)(const void *, string &);
    using OnEventsCallback = void(*)(Keyboard &, KeyboardEvent &event);

    extern u32 min, max;
    extern bool KeyboardCallback(const void *input, string &error);

    template<typename T>
    bool KB(const String &name, bool canAbort, bool isHex, const int maxLength, T &output, T Default, const u32 minimum, const u32 maximum, OnCompareCallback callback = nullptr) {
        Sleep(Milliseconds(100));
        Keyboard keyboard(name);
        keyboard.CanAbort(canAbort);
        keyboard.IsHexadecimal(isHex);
        keyboard.SetMaxLength(maxLength);
        min = minimum;
        max = maximum;
        keyboard.SetCompareCallback(callback);
        s8 res = keyboard.Open((T &)output, (T)Default);
        return res == 0;
    };

    template<typename T>
    bool KB(const String &name, bool canAbort, bool isHex, const int maxLength, T &output, T Default, OnCompareCallback callback = nullptr) {
        Sleep(Milliseconds(100));
        Keyboard keyboard(name);
        keyboard.CanAbort(canAbort);
        keyboard.IsHexadecimal(isHex);
        keyboard.SetMaxLength(maxLength);
        keyboard.SetCompareCallback(callback);
        s8 res = keyboard.Open((T &)output, (T)Default);
        return res == 0;
    };

    template<typename T>
    bool KB(const String &name, bool canAbort, const int maxLength, T &output, T Default, OnEventsCallback callback = nullptr) {
        Sleep(Milliseconds(100));
        Keyboard keyboard(name);
        keyboard.CanAbort(canAbort);
        keyboard.SetMaxLength(maxLength);
        keyboard.OnKeyboardEvent(callback);
        s8 res = keyboard.Open((T &)output, (T)Default);
        return res == 0;
    };

    /**
     * \brief Return the arg of an entry. If the arg doesn't exist (nullptr) a new one is created calling the default type constructor
     * \tparam T The type of the arg
     * \param entry The entry to get the arg from
     * \return A pointer to the arg (like reinterpret_cast<T *>(entry->GetArg()))
     */
    template <typename T>
    T *GetArg(MenuEntry *entry) {
        T *arg = reinterpret_cast<T *>(entry->GetArg());

        if (arg == nullptr) {
            arg = new T();
            entry->SetArg(arg);
        }

        return (arg);
    }

    /**
    * \brief Return the arg of an entry. If the arg doesn't exist (nullptr) a new one is created calling the default type constructor
    * \tparam T The type of the arg
    * \param entry The entry to get the arg from
    * \param defaultVal The value to set to a newly created arg
    * \return A pointer to the arg (like reinterpret_cast<T *>(entry->GetArg()))
    */
    template <typename T>
    T *GetArg(MenuEntry *entry, T defaultVal) {
        T *arg = reinterpret_cast<T *>(entry->GetArg());

        if (arg == nullptr) {
            arg = new T(defaultVal);
            entry->SetArg(arg);
        }

        return (arg);
    }
}

#endif