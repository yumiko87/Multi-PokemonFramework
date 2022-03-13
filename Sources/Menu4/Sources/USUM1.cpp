#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "stdafx.hpp"

using namespace CTRPluginFramework;

namespace USUM {
    void HealthAlwaysFull(MenuEntry *entry) {
        static const u32 address[2] = {0x5BBBD4, 0x8099DC4};
        static u32 patch[15] = {0xE1D021B0, 0xE92D407C, 0xE59F2024, 0xE59F3024, 0xE2834018, 0xE4925004, 0xE4936004, 0xE1500005, 0x11500006, 0x03A01000, 0xE1530004, 0x1AFFFFF8, 0xE8BD807C, 0x30000404, 0x300073EC};
        static u32 original[1] = {0};

        if (Gen7::IsInBattle()) {
            CRO::Toggle(address[1], true);

            if (entry->IsActivated()) {
                for (int i = 0; i < 15; i++) {
                    if (Process::Read32(address[0] + (i * 4), data32) && data32 != patch[i]) {
                        Process::Patch(address[0], patch, 0x3C);
                    }
                }

                if (Process::Read32(address[1], data32) && data32 != 0xEBF92F82) {
                    Process::Patch(address[1], 0xEBF92F82, original);
                }
            }

            if (!entry->IsActivated()) {
                for (int j = 0; j < 15; j++) {
                    Process::Patch(address[0] + (j * 4), 0);
                }

                Process::Patch(address[1], original, 4);
            }
        }
    }

    void StaminaAlwaysFull(MenuEntry *entry) {
        static const u32 address[2] = {0x5BBC14, 0x808FA28};
        static u32 patch[11] = {0xE1A04000, 0xE92D4007, 0xE59F0018, 0xE2801018, 0xE4902004, 0xE1560002, 0x03A04000, 0xE1510000, 0x1AFFFFFA, 0xE8BD8007, 0x300073EC};
        static u32 original[1] = {0};

        if (Gen7::IsInBattle()) {
            CRO::Toggle(address[1], true);

            if (entry->IsActivated()) {
                for (int i = 0; i < 11; i++) {
                    if (Process::Read32(address[0] + (i * 4), data32) && data32 != patch[i]) {
                        Process::Patch(address[0], patch, 0x2C);
                    }
                }

                if (Process::Read32(address[1], data32) && data32 != 0xEBF95879) {
                    Process::Patch(address[1], 0xEBF95879, original);
                }
            }

            if (!entry->IsActivated()) {
                for (int j = 0; j < 11; j++) {
                    Process::Patch(address[0] + (j * 4), 0);
                }

                Process::Patch(address[1], original, 4);
            }
        }
    }

    void GodMode(MenuEntry *entry) {
        HealthAlwaysFull(entry);
        StaminaAlwaysFull(entry);
    }

    void AccessBag(MenuEntry *entry) {
        static const u32 pointer = 0x302E05B4;

        if (Gen7::IsInBattle()) {
            if (entry->Hotkeys[0].IsDown()) {
                if (Process::Read32(pointer, data32) && data32 != 0) {
                    if (Process::Read32(pointer, offset32)) {
                        Process::Write8(offset32 + 0x760, 3);
                    }
                }
            }
        }
    }

    void AlwaysCriticalHit(MenuEntry *entry) {
        static const u32 address[3] = {0x5BBB90, 0x669018, 0x8087FF0};
        static u32 patch[12] = {0xE59D0000, 0xE92D401E, 0xE59A1008, 0xE2813004, 0xE281401C, 0xE4932004, 0xE1500002, 0x03A01001, 0x058D1018, 0xE1530004, 0x1AFFFFF9, 0xE8BD801E};
        static u32 original[1] = {0};

        if (Gen7::IsInBattle()) {
                CRO::Toggle(address[2], true);

            if (entry->IsActivated()) {
                for (int i = 0; i < 12; i++) {
                    if (Process::Read32(address[0] + (i * 4), data32) && data32 != patch[i]) {
                        Process::Patch(address[0], patch, 0x30);
                    }
                }

                if (Process::Read32(address[2], data32) && data32 == patch[0]) {
                    if (Process::Read32(address[1], data32) && data32 == 0) {
                        Process::Write32(address[1], 0x10);
                    }
                }

                if (Process::Read32(address[1], data32) && data32 != 0) {
                    Process::Read32(address[1], data32);
                    data32 += 0xFFFFFFFF;
                    Process::Write32(address[1], data32);
                }

                if (Process::Read32(address[1], data32) && data32 == 1) {
                    Process::Patch(address[2], 0xEBF976E6, original);
                }
            }

            if (!entry->IsActivated()) {
                for (int j = 0; j < 12; j++) {
                    Process::Patch(address[0] + (j * 4), 0);
                }

                Process::Patch(address[2], original, 4);
            }
        }
    }

    void RaiseStatusesBy6(MenuEntry *entry) {
        static const u32 address[2] = {0x5BBD60, 0x29B86C};
        static u32 original[1] = {0};
        static u32 patch[25] = {
            0xE92D401F, 0xE59F0018, 0xE150000E, 0x18BD801F, 0xE59F0010, 0xFA000005, 0xE59F000C, 0xFA000003, 0xE8BD801F, 0x0071C600, 0x30000404, 0x300073EC, 
            0x1C03B53F, 0x68013318, 0xD00B2900, 0x31F531F5, 0x1DE5A406, 0x2AFF7822, 0x700AD000, 0x34013101, 0xD1F742A5, 0x42833004, 0xBD3FD1ED, 0x0C0C0C0C,
            0x000C0C0C,
        };

        if (Gen7::IsInBattle()) {
            if (entry->IsActivated()) {
                for (int i = 0; i < 25; i++) {
                    if (Process::Read32(address[0] + (i * 4), data32) && data32 != patch[i]) {
                        Process::Patch(address[0], patch, 0x64);
                    }
                }

                if (Process::Read32(address[1], data32) && data32 != 0xEA0C813B) {
                    Process::Patch(address[1], 0xEA0C813B, original);
                }
            }

            if (!entry->IsActivated()) {
                for (int j = 0; j < 25; j++) {
                    Process::Patch(address[0] + (j * 4), 0);
                }

                Process::Patch(address[1], original, 4);
            }
        }
    }

    void Bypass1MegaRestrict(MenuEntry *entry) {
        static const u32 address = 0x80A6150;
        static u32 data[1] = {0xE3A00000};
        static u32 original[1] = {0};

        if (Gen7::IsInBattle()) {
            CRO::Toggle(address, true);

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

    void InfiniteZMoves(MenuEntry *entry) {
        static const u32 address = 0x8031E7C;
        static u32 data[3] = {0xE3A00000, 0xE5C30005, 0xE1500000};
        static u32 original[3] = {0, 0, 0};

        if (Gen7::IsInBattle()) {
            CRO::Toggle(address, true);

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
    }

    void ZMovesWithoutCrystal(MenuEntry *entry) {
        static const u32 address[4] = {0x5BBDE0, 0x31C494, 0x31C504, 0x376EB0};
        static u32 data[23] = {0xE92D407D, 0xE1A00006, 0xEA000000, 0xE92D407D, 0xE1D510B4, 0xE59D201C, 0xE202530F, 0xE3550203, 0x18BD807D, 0xE59F300C, 0xEB000004, 0xE59F3008, 0xEB000002, 0xE8BD807D, 0x30000404, 0x300073EC, 0xE2834018, 0xE4935004, 0xE1550002, 0x01A01000, 0xE1530004, 0x1AFFFFFA, 0xE12FFF1E};

        if (entry->WasJustActivated()) {
            Process::Patch(address[0], data, 0x5C);
        }

        if (Gen7::IsInBattle()) {
            Process::Write32(address[1], 0xEB0A7E51);
            Process::Write32(address[2], 0xEB0A7E38);

            if (entry->Hotkeys[0].IsDown()) {
                Process::Write32(address[3], 0xE3A00001);
            }

            if (!entry->Hotkeys[0].IsDown()) {
                Process::Write32(address[3], 0xE3A00000);
            }
        }

        if (!entry->IsActivated()) {
            Process::Write32(address[1], 0xE1D510B4);
            Process::Write32(address[2], 0xE1D510B4);
            Process::Write32(address[3], 0xE3A00000);
        }
    }

    void AlwaysShiny(MenuEntry *entry) {
        static const u32 address = 0x320CF0;
        static u32 data[1] = {0xEA00001C};
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

    void GuaranteedCatch(MenuEntry *entry) {
        static const u32 address[2] = {0x5BBEA0, 0x4ACD2C};
        static u32 data[10][1] = {{0xE5D00008}, {0xE92D4003}, {0xE59D0010}, {0xE59F100C}, {0xE1510000}, {0x024000F8}, {0x058D0010}, {0xE8BD8003}, {0x0070C62C}, {0xEB043C5B}};
        static u32 original[10][1] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

        if (Gen7::IsInBattle()) {
            if (entry->IsActivated()) {
                for (int i = 0; i < 9; i++) {
                    if (Process::Read32(address[0] + (i * 4), data32) && data32 != data[i][0]) {
                        Process::Patch(address[0] + (i * 4), data[i], 4, original[i]);
                    }
                }

                if (Process::Read32(address[1], data32) && data32 != data[9][0]) {
                    Process::Patch(address[1], data[9], 4, original[9]);
                }
            }

            if (!entry->IsActivated()) {
                for (int i = 0; i < 9; i++) {
                    Process::Patch(address[0] + (i * 4), original[i], 4);
                }

                Process::Patch(address[1], original[9], 4);
            }
        }
    }

    void CatchTrainersPokemon(MenuEntry *entry) {
        static const u32 address = 0x8036F18;
        static u32 data[4] = {0xE3A0B000, 0xE590000C, 0xE5C0B000, 0xEA00000B};
        static u32 original[4] = {0, 0, 0, 0};

        if (Gen7::IsInBattle()) {
            CRO::Toggle(address, true);

            if (entry->IsActivated()) {
                for (int i = 0; i < 4; i++) {
                    if (Process::Read32(address + (i * 4), data32) && data32 != data[i]) {
                        Process::Patch(address, data, 16, original);
                    }
                }
            }

            if (!entry->IsActivated()) {
                Process::Patch(address, original, 16);
            }
        }
    }

    void RematchTrainer(MenuEntry *entry) {
        static const u32 address = 0x4BB03C;
        static u32 data[2] = {0xE3A00000, 0xE12FFF1E};
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

    void NoTrainerBattle(MenuEntry *entry) {
        static const u32 address = 0x8032034;
        static u32 data[1] = {0xE3A00001};
        static u32 original[1] = {0};

        CRO::Toggle(address, true);

        if (entry->IsActivated()) {
            if (Process::Read32(address, data32) && data32 != data[0]) {
                Process::Patch(address, data, 4, original);
            }
        }

        if (!entry->IsActivated()) {
            Process::Patch(address, original, 4);
        }
    }

    void ViewEnemyHP(MenuEntry *entry) {
        static const u32 address = 0x80B2198;
        static u32 data[1] = {0xEAFFFEE7};
        static u32 original[1] = {0};

        if (Gen7::IsInBattle()) {
            CRO::Toggle(address, true);

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

    void NoEncounters(MenuEntry *entry) {
        static const u32 address = 0x807E5B8;
        static u32 data[1] = {0xE3A09000};
        static u32 original[1] = {0};

        CRO::Toggle(address, true);

        if (entry->IsActivated()) {
            if (Process::Read32(address, data32) && data32 != data[0]) {
                Process::Patch(address, data, 4, original);
            }
        }

        if (!entry->IsActivated()) {
            Process::Patch(address, original, 4);
        }
    }

    static int pokeNo, form;
    static u16 level;

    void InitPokemon(MenuEntry *entry) {
        static u32 address[7] = {0x5BBFC0, 0x5BBFE0, Gen7::Auto(0x3A86A0, 0x3A86A4), Gen7::Auto(0x3A86B0, 0x3A86B4), Gen7::Auto(0x3A86DC, 0x3A86E0), Gen7::Auto(0x3A8688, 0x3A868C), Gen7::Auto(0x3A873C, 0x3A8740)};
        static u32 data[10] = {0xE92D400E, 0xE59F0014, 0xE3500000, 0x18BD800E, 0xE59F000C, 0xEBF90532, 0xE2800001, 0xE8BD800E, 0x00000000, 0x00000327};
        static u32 original[1] = {0};

        if (entry->WasJustActivated()) {
            if (Process::Patch(address[0], data, 0x28)) {
                Process::Write32(address[2], Gen7::Auto(0xEB084E46, 0xEB084E45));
                Process::Write32(address[3], 0xE1D400B0);
                Process::Write32(address[4], 0xE1D400B0);

                if (Process::Patch(address[5], (void *) (0xE3A00000), 0x4, original)) {
                    Process::Patch(address[6], (void *) (0xC3A00000), 0x4, original);
                }
            }
        }

        if (entry->IsActivated()) {
            Process::Write32(address[1], pokeNo);
            Process::Write32(address[5], 0xE3A00000 + level);
            Process::Write32(address[6], 0xC3A00000 + form);
        }

        else if (!entry->IsActivated()) {
            for (int i = 2; i < 5; i++) {
                Process::Write32(address[i], 0xE1D500B0);
            }

            if (Process::Patch(address[5], original, 4)) {
                Process::Patch(address[6], original, 4);
            }
        }
    }

    void WildPokemon(MenuEntry *entry) {
        SelectAPokemon(entry);
        pokeNo = pkmnID;
        KeyboardPlus keyboard;

        if (pokeNo > 0) {
            if (keyboard.SetKeyboard("Form:", true, Gen7::Forms(pokeNo), form) != -1) {
                if (KB<u16>("Level:", true, false, 3, level, 0, 1, 100, KeyboardCallback)) {
                    entry->SetGameFunc(InitPokemon);
                }
            }
        }
    }

    void CanCatchTrials(MenuEntry *entry) {
        static const u32 address[2] = {0x8077D10, 0x80BC8AC};
        static u32 data[2] = {0xE3A00001, 0xE3A01000};
        static u32 original[2][1] = {{0}, {0}};

        if (Gen7::IsInBattle()) {
            for (int i = 0; i < 2; i++) {
                CRO::Toggle(address[i], true);
            }

            if (entry->IsActivated()) {
                for (int j = 0; j < 2; j++) {
                    if (Process::Read32(address[j], data32) && data32 != data[j]) {
                        Process::Patch(address[j], data, 4, original[j]);
                    }
                }
            }

            if (!entry->IsActivated()) {
                for (int k = 0; k < 2; k++) {
                    Process::Patch(address[k], original[k], 4);
                }
            }
        }
    }

    static int legendaryIndex;

    void RematchLegendariesKB(MenuEntry *entry) {
        static const vector<string> options = {"Tapu Koko", "Tapu Lele", "Tapu Bulu", "Tapu Fini", "Cosmog", Gen7::Name("Solgaleo", "Lunala"), "Necrozma"};
        KeyboardPlus keyboard;
        keyboard.SetKeyboard(entry->Name() + ":", true, options, legendaryIndex);
    }

    void RematchLegendaries(MenuEntry *entry) {
        if (legendaryIndex == 0) {
            static const u32 address = 0x33013264;

            if (Bit::Read(address, data8, true) && data8 != 3) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 3, true);
                }
            }
        }

        if (legendaryIndex == 1) {
            static const u32 address = 0x33013266;

            if (Bit::Read(address, data8, true) && data8 != 1) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 1, true);
                }
            }
        }

        if (legendaryIndex == 2) {
            static const u32 address = 0x3301322C;

            if (Bit::Read(address, data8, true) && data8 != 1) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 1, true);
                }
            }
        }

        if (legendaryIndex == 3) {
            static const u32 address = 0x330D71E4;

            if (Bit::Read(address, data8, true) && data8 != 3) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 3, true);
                }
            }
        }

        if (legendaryIndex == 4) {
            static const u32 address = 0x33013712;

            if (Bit::Read(address, data8, false) && data8 != 0) {
                if (Bit::Read(address, data8, false)) {
                    Bit::Edit(address, 0, false);
                }
            }
        }

        if (legendaryIndex == 5) {
            static const u32 address = 0x3301379F;

            if (Bit::Read(address, data8, false) && data8 != 2) {
                if (Bit::Read(address, data8, false)) {
                    Bit::Edit(address, 2, false);
                }
            }
        }

        if (legendaryIndex == 6) {
            static const u32 address = 0x33013796;

            if (Bit::Read(address, data8, true) && data8 != 1) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 2, true);
                }
            }
        }
    }
}