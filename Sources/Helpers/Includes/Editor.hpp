#ifndef POKEEDITOR_HPP
#define POKEEDITOR_HPP

#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework {
    namespace Editor {
        bool Setup(void);
        void Initialize(MenuEntry *entry);
        bool IsValid(u32 pointer, PK6 *pkmn);
        void Species(MenuEntry *entry);
        void Form(MenuEntry *entry);
        void Shinify(MenuEntry *entry);
    }
}

#endif