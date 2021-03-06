#ifndef HOTKEYHELPERS_HPP
#define HOTKEYHELPERS_HPP

#include <CTRPluginFramework/Menu/MenuEntry.hpp>
#include "stdafx.hpp"

namespace CTRPluginFramework {
    static MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey &hotkey) {
        if (entry != nullptr)
            entry->Hotkeys += hotkey;

        return (entry);
    }

    static MenuEntry *EntryWithHotkey(MenuEntry *entry, const vector<Hotkey> &hotkeys) {
        if (entry != nullptr) {
            for (const Hotkey &hotkey : hotkeys) {
                entry->Hotkeys += hotkey;
            }
        }

        return (entry);
    }
}

#endif