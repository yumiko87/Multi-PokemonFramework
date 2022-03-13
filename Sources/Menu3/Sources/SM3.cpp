#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace SM {
    void Speedx2(MenuEntry *entry) {
        static const u32 address = 0x39C394;
        static u32 data[1] = {0x3FC00000};
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

    void BypassWalls(MenuEntry *entry) {
        static const u32 address[2] = {0x39E560, 0x39E694};
        static u32 data[1] = {0xE1A00000};
        static u32 original[2] = {0, 0};

        if (entry->IsActivated()) {
            for (int i = 0; i < 2; i++) {
                if (Process::Read32(address[i], data32) && data32 != data[0]) {
                    Process::Patch(address[i], (void *)&data[0], 4, original);
                }
            }
        }

        if (!entry->IsActivated()) {
            for (int j = 0; j < 2; j++) {
                Process::Patch(address[j], original[j]);
            }
        }
    }

    void RegisterMounts(MenuEntry *entry) {
        static const u32 address = 0x330D7810;

        if (Process::Read32(address, data32) && (data32 & ~0xFFF00000) != 0x3FF80) {
            if (Process::Read32(address, data32)) {
                data32 &= 0xFFF00000;
                data32 += 0x3FF80;
                Process::Write32(address, data32);
            }

            Message::Completed();
            return;
        }

        else {
            Message::Warning();
        }
    }

    void CameraZoomOut(MenuEntry *entry) {
        static const u32 address[3] = {0x597724, 0x8037B18, 0x59773C};
        static u32 patch[7] = {0xED940A1C, 0xED9F1A03, 0xEE300A01, 0xED840A1C, 0xE2840004, 0xE12FFF1E, 0x00000000};
        static u32 original[1] = {0};

        CRO::Toggle(address[1], true);

        if (entry->WasJustActivated()) {
            Process::Patch(address[0], patch, 0x1C);
        }

        if (entry->IsActivated()) {
            if (Process::Read32(address[1], data32) && data32 == 0xE2840004) {
                Process::Patch(address[1], 0xEBFAEB01, original);
            }

            if (entry->Hotkeys[0].IsPressed()) {
                Process::Write32(address[2], 0xC4BB8000);
            }

            if (entry->Hotkeys[1].IsPressed()) {
                Process::Write32(address[2], 0);
            }
        }

        if (!entry->IsActivated()) {
            Process::Patch(address[0], 0, 0x1C);
            Process::Patch(address[1], original, 4);
        }
    }

    void TimeOfDay(MenuEntry *entry) {
        static const u32 address = 0x330D9238;
        u32 time = 0;

        if (!Process::Read32(address, time)) {
            return;
        }

        time /= 3600;

        if (KB<u32>("Time of Day:\n\nChoose an offset between 1-24 hours\n\n" << Color::SkyBlue << "12H" << Color::White << " - Moon" << Color::Orange << " 24H" << Color::White << " - Sun", true, false, 3, time, 0, 1, 24, KeyboardCallback)) {
            Process::Write32(address, time * 3600);
        }
    }
}