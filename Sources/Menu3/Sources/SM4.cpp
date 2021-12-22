#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace SM {
    void IsRenamable(MenuEntry *entry) {
        static const u32 address = 0x4AA2C0;
        static u32 data[1] = {0xE3A00001};
        static u32 original[1] = {0};

        if (entry->IsActivated()) {
            if (Process::Read32(address, data32) && data32 != data[0]) {
                Process::Patch(address, data, 4, original);
            }
        }

        if (!entry->IsActivated()) {
            Process::Patch(address, original, 4);
        }
    }

    void LearnAnyTeachables(MenuEntry *entry) {
        static const u32 address = 0x490D34;
        static u32 data[1] = {0xE3A00001};
        static u32 original[1] = {0};

        if (entry->IsActivated()) {
            if (Process::Read32(address, data32) && data32 != data[0]) {
                Process::Patch(address, data, 4, original);
            }
        }

        if (!entry->IsActivated()) {
            Process::Patch(address, original, 4);
        }
    }

    void FastOffspring(MenuEntry *entry) {
        static const u32 address = 0x4466A8;
        static u32 data[3] = {0xE3A01001, 0xE5C011E0, 0xEA00684B};
        static u32 original[3] = {0, 0, 0};

        if (entry->IsActivated()) {
            for (int i = 0; i < 3; i++) {
                if (Process::Read32(address + (i * 4), data32) && data32 != data[i]) {
                    Process::Patch(address, data, 12, original);
                }
            }
        }

        if (!entry->IsActivated()) {
            Process::Patch(address, original, 12);
        }
    }

    void InstantEggHatch(MenuEntry *entry) {
        static const u32 address[2] = {0x5977C0, 0x493668};
        static u32 patch[7] = {0xE59D000C, 0xE59F500C, 0xE1500005, 0x03A00000, 0x11A00004, 0xE12FFF1E, 0x006D08C0};
        static u32 original[1] = {0};

        if (entry->WasJustActivated()) {
            for (int i = 0; i < 7; i ++) {
                if (Process::Read32(address[0] + (i * 4), data32) && data32 != patch[i]) {
                    Process::Patch(address[0], patch, 0x1C);
                }
            }

            if (Process::Read32(address[1], data32) && data32 != 0xEB041054) {
                Process::Patch(address[1], 0xEB041054, original);
            }
        } 

        if (!entry->IsActivated()) {
            for (int j = 0; j < 7; j++) {
                Process::Patch(address[0] + (j * 4), 0);
            }

            Process::Patch(address[1], original, 4);
        }
    }

    void QuickFriendship(MenuEntry *entry) {
        static const u32 address = 0x330D67AA;

        if (!Process::Write16(address, 0xFF)) {
            return;
        }
    }

    void ViewValuesInSummary(MenuEntry *entry) {
        static const u32 address[7] = {0x49369C, 0x493A08, 0x4937CC, 0x493818, 0x493A54, 0x493AA0, 0x493780};
        static u32 patch[2][7] = {
            {0xEAFFFCFD, 0xEAFFFC22, 0xEAFFFD15, 0xEAFFFD0F, 0xEAFFFD14, 0xEAFFFD0E, 0xEAFFFD1B},
            {0xEAFFFC9C, 0xEAFFFBC1, 0xEAFFFCF2, 0xEAFFFCEA, 0xEAFFFCE2, 0xEAFFFCDA, 0xEAFFFCFA}
        };

        if (entry->Hotkeys[0].IsDown()) {
            for (int i = 0; i < 7; i++) {
                Process::Patch(address[i], patch[0][i]);
            }
        }

        else if (entry->Hotkeys[1].IsDown()) {
            for (int j = 0; j < 7; j++) {
                Process::Patch(address[j], patch[1][j]);
            }
        }

        else {
            for (int k = 0; k < 7; k++) {
                Process::Patch(address[k], 0xE92D4070);
            }
        }
    }

    void NoOutlines(MenuEntry *entry) {
        static const u32 address = 0x41CFCC;
        static u32 data[1] = {0xE320F000};
        static u32 original[1] = {0};

        if (entry->IsActivated()) {
            if (Process::Read32(address, data32) && data32 != data[0]) {
                Process::Patch(address, data, 4, original);
            }
        }

        if (!entry->IsActivated()) {
            Process::Patch(address, original, 4);
        }
    }

    void FastDialogs(MenuEntry *entry) {
        static const u32 address[2] = {0x3BFBF4, 0x3C0498};
        static u32 data[2][1] = {{0xE3A04003}, {0xE3A05003}};
        static u32 original[2][1] = {{0}, {0}};

        if (entry->IsActivated()) {
            for (int j = 0; j < 2; j++) {
                if (Process::Read32(address[j], data32) && data32 != data[j][0]) {
                    Process::Patch(address[j], data[j], 4, original[j]);
                }
            }
        }

        if (!entry->IsActivated()) {
            for (int l = 0; l < 2; l++) {
                Process::Patch(address[l], original[l], 4);
            }
        }
    }

    void NoPlayerShadow(MenuEntry *entry) {
        static const u32 address = 0x39CA54;
        static u32 data[1] = {0};
        static u32 original[1] = {0};

        if (entry->IsActivated()) {
            if (Process::Read32(address, data32) && data32 != data[0]) {
                Process::Patch(address, data, 4, original);
            }
        }

        if (!entry->IsActivated()) {
            Process::Patch(address, original, 4);
        }
    }
}