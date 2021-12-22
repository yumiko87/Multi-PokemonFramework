#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace ORAS
{
    void IsRenamable(MenuEntry *entry) {
        static const u32 address = Gen6::Auto(0x4EA990, 0x4EA998);
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
        static const u32 address = Gen6::Auto(0x4D051C, 0x4D0514);
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
        static const u32 address = Gen6::Auto(0x4658A4, 0x46589C);
        static u32 data[3] = {0xE3A01001, 0xE5C011E8, 0xEA00209B};
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
        static const u32 address = 0x8066EF0;
        static u32 data[1] = {0xEA000007};
        static u32 original[1] = {0};

        CRO::Force(address);

        if (entry->IsActivated()) {
            if (Process::Read32(address, data32) && data32 != data[0]) {
                Process::Patch(address, data, 4, original);
            }
        }

        if (!entry->IsActivated()) {
            Process::Patch(address, original, 4);
        }
    }

    void QuickFriendship(MenuEntry *entry) {
        static const u32 address = 0x8C6F978;

        if (Process::Read16(address, data16) && data16 < 0x7F) {
            Process::Write16(address, 0x7F);
        }
    }

    void ViewValuesInSummary(MenuEntry *entry) {
        static const u32 address[7] = {0x1531AC, 0x15328C, 0x4D2370, 0x4D23BC, 0x4D2534, 0x4D2580, 0x4D2324};
        static u32 original[1] = {0xE92D4070};
        static u32 data[2][7][1] =
        {
            {{0xEA006283}, {0xEA00624B}, {0xEAF2032B}, {0xEAF20325}, {0xEAF202EA}, {0xEAF202E4}, {0xEAF20331}}, 
            {{0xEA006278}, {0xEA006240}, {0xEAF20308}, {0xEAF20300}, {0xEAF202D4}, {0xEAF202CC}, {0xEAF20310}}
        };

        if (entry->Hotkeys[0].IsDown()) {
            for (int i = 0; i < 7; i++) {
                Process::Patch(address[i], data[0][i], 4);
            }
        }

        else if (entry->Hotkeys[1].IsDown()) {
            for (int i = 0; i < 7; i++) {
                Process::Patch(address[i], data[1][i], 4);
            }
        }

        else {
            for (int i = 0; i < 7; i++) {
                Process::Patch(address[i], original, 4);
            }
        }
    }

    // Thanks to H4x0rSpooky for this cheat (original creator)
    void NoOutlines(MenuEntry *entry) {
        static const u32 address = 0x37A140;
        static u32 data[2] = {0, 0};
        static u32 original[2] = {0, 0};

        if (entry->IsActivated()) {
            for (int i = 0; i < 2; i++) {
                if (Process::Read32(address + (i * 4), data32) && data32 != data[i]) {
                    Process::Patch(address, data, 8, original);
                }
            }
        }

        if (!entry->IsActivated()) {
            Process::Patch(address, original, 8);
        }
    }

    void FastDialogs(MenuEntry *entry) {
        static const u32 address[2] = {0x419A34, 0x41A2A4};
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
}