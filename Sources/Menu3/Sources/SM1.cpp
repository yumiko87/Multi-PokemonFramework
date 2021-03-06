#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace SM {
    bool IsOnline = System::IsConnectedToInternet();

    static const u32 party[6][2] =
    {
        {0x30000484, 0x3000746C},
        {0x30000488, 0x30007470},
        {0x3000048C, 0x30007474},
        {0x30000490, 0x30007478},
        {0x30000494, 0x3000747C},
        {0x30000498, 0x30007480}
    };

    static const u32 opponent[6][2] =
    {
        {0x300004B4, 0x3000749C},
        {0x300004B8, 0x300074A0},
        {0x300004BC, 0x300074A4},
        {0x300004C0, 0x300074A8},
        {0x300004C4, 0x300074AC},
        {0x300004C8, 0x300074B0}
    };

    struct Conditions {
        const char *name;
        int choiceNo;
    };

    static const Conditions allCndtions[5] = {
        {"Asleep", 0x30},
        {"Burned", 0x40},
        {"Frozen", 0x38},
        {"Paralyzed", 0x28},
        {"Poisoned", 0x48}
    };

    static int initCndition, getCndition, setCndition;

    void Condition(MenuEntry *entry) {
        static const StringVector init = {"None", "Affected"};
        StringVector options;
        KeyboardPlus keyboard;

        for (const Conditions &nickname : allCndtions) {
            options.push_back(nickname.name);
        }

        if (Gen6::IsInBattle()) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, init, initCndition) != -1) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getCndition) != -1) {
                    setCndition = allCndtions[getCndition].choiceNo;

                    for (int i = 0; i < 1; i++) {
                        for (int j = 0; j < 2; j++) {
                            if (Process::Read32(party[i][j], data32) && data32 != 0) {
                                if (Process::Read32(party[i][j], offset32)) {
                                    for (int i = 0; i < 5; i++)
                                        Process::Write8(offset32 + (0x28 + (i * 4)), 0);

                                    if (initCndition == 1) {
                                        Process::Write8(offset32 + setCndition, 1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    static int statOption, baseIndex, boostsIndex;
    static u16 baseVals[5];
    static u8 boostVals[7];

    void StatisticsKB(MenuEntry *entry) {
        static const StringVector init = {"Base", "Boosts"}, base = {"Attack", "Defense", "Sp. Atk", "Sp. Def", "Speed"}, boosts = {"Attack", "Defense", "Sp. Atk", "Sp. Def", "Speed", "Accuracy", "Evasiveness"};
        u16 vals[2];

        if (Gen6::IsInBattle()) {
            Start:
            KeyboardPlus keyboard;
            keyboard.SetKeyboard(entry->Name() + ":", true, init, statOption);

            if (statOption == 0) {
                Base:
                keyboard.SetKeyboard(entry->Name() + ":", true, base, baseIndex);

                if (baseIndex != -1) {
                    if (KB<u16>(base[baseIndex] + ":", true, false, 3, vals[0], 0, 1, 999, KeyboardCallback))
                        baseVals[baseIndex] = vals[0];

                    else goto Base;
                }

                else goto Start;
            }

            else if (statOption == 1) {
                Boosts:
                keyboard.SetKeyboard(entry->Name() + ":", true, boosts, boostsIndex);

                if (boostsIndex != -1) {
                    if (KB<u16>(boosts[boostsIndex] + ":", true, false, 1, vals[1], 0, 0, 6, KeyboardCallback))
                        boostVals[boostsIndex] = vals[1] + 6;

                    else goto Boosts;
                }

                else goto Start;
            }
        }
    }

    void Statistics(MenuEntry *entry) {
        if (Gen6::IsInBattle()) {
            for (int i = 0; i < 1; i++) {
                for (int j = 0; j < 2; j++) {
                    if (Process::Read32(party[i][j], data32) && data32 != 0) {
                        if (Process::Read32(party[i][j], offset32)) {
                            for (int k = 0; k < 5; k++) {
                                if (baseVals[k] != 0) {
                                    Process::Write16(offset32 + 0x1DA + (k * 2), baseVals[k]);
                                }
                            }

                            for (int l = 0; l < 7; l++) {
                                if (boostVals[l] != 0) {
                                    Process::Write8(offset32 + 0x1EA + (l * 1), boostVals[l]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    static int invincIndex;
    static u16 healthVals;
    static u8 staminaVals;

    void InvincibilityKB(MenuEntry *entry) {
        static const StringVector options = {"Health", "Stamina"};
        u16 val; u8 val2;

        if (Gen6::IsInBattle()) {
            Start:
            KeyboardPlus keyboard;
            keyboard.SetKeyboard(entry->Name() + ":", true, options, invincIndex);

            if (invincIndex == 0) {
                if (KB<u16>("Health:", true, false, 3, val, 0, 1, 999, KeyboardCallback))
                    healthVals = val;

                else goto Start;
            }

            else if (invincIndex == 1) {
                if (KB<u8>("Stamina:", true, false, 2, val2, 0, 1, 99, KeyboardCallback))
                    staminaVals = val2;

                else goto Start;
            }
        }
    }

    void Invincibility(MenuEntry *entry) {
        if (Gen6::IsInBattle()) {
            for (int i = 0; i < 1; i++) {
                for (int j = 0; j < 2; j++) {
                    if (Process::Read32(party[i][j], data32) && data32 != 0) {
                        if (Process::Read32(party[i][j], offset32)) {
                            for (int k = 0; k < 2; k++) {
                                if (healthVals != 0) {
                                    Process::Write16(offset32 + 0x10 - (k * 2), healthVals);
                                }
                            }

                            for (int l = 0; l < 4; l++) {
                                if (staminaVals != 0) {
                                    Process::Write16(offset32 + 0x204 + (l * 0xE), (staminaVals << 8) | staminaVals);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    static u16 item;

    void Item(MenuEntry *entry) {
        if (Gen6::IsInBattle()) {
            FindItemKB(entry);
            item = heldItemID;

            if (item > 0) {
                for (int i = 0; i < 1; i++) {
                    for (int j = 0; j < 2; j++) {
                        if (Process::Read32(party[i][j], data32) && data32 != 0) {
                            if (Process::Read32(party[i][j], offset32)) {
                                Process::Write16(offset32 + 0x12, item);
                            }
                        }
                    }
                }
            }
        }
    }

    static u16 attack;
    static int atkSlot;

    void Attacks(MenuEntry *entry) {
        static const StringVector options = {"Move 1", "Move 2", "Move 3", "Move 4"};
        KeyboardPlus keyboard;

        if (Gen6::IsInBattle()) {
            Start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, atkSlot) != -1) {
                FindMoveKB(entry);
                attack = moveID;

                if (attack > 0) {
                    for (int i = 0; i < 1; i++) {
                        for (int j = 0; j < 2; j++) {
                            if (Process::Read32(party[i][j], data32) && data32 != 0) {
                                if (Process::Read32(party[i][j], offset32)) {
                                    Process::Write16(offset32 + 0x202 + (atkSlot * 0xE), attack);
                                }
                            }
                        }
                    }
                }

                else goto Start;
            }
        }
    }

    void HealthAlwaysFull(MenuEntry *entry) {
        static const u32 address[2] = {0x597800, 0x8097AEC};
        static u32 patch[15] = {0xE1D021B0, 0xE92D407C, 0xE59F2024, 0xE59F3024, 0xE2834018, 0xE4925004, 0xE4936004, 0xE1500005, 0x11500006, 0x03A01000, 0xE1530004, 0x1AFFFFF8, 0xE8BD807C, 0x30000404, 0x300073EC};
        static u32 original[1] = {0};

        if (Gen7::IsInBattle() && !IsOnline) {
            CRO::Toggle(address[1], true);

            if (entry->IsActivated()) {
                for (int i = 0; i < 15; i++) {
                    if (Process::Read32(address[0] + (i * 4), data32) && data32 != patch[i]) {
                        Process::Patch(address[0], patch, 0x3C);
                    }
                }

                if (Process::Read32(address[1], data32) && data32 != 0xEBF96B43) {
                    Process::Patch(address[1], 0xEBF96B43, original);
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
        static const u32 address[2] = {0x597700, 0x808DB1C};
        static u32 patch[11] = {0xE1A04000, 0xE92D4007, 0xE59F0018, 0xE2801018, 0xE4902004, 0xE1560002, 0x03A04000, 0xE1510000, 0x1AFFFFFA, 0xE8BD8007, 0x300073EC};
        static u32 original[1] = {0};

        if (Gen7::IsInBattle() && !IsOnline) {
            CRO::Toggle(address[1], true);

            if (entry->IsActivated()) {
                for (int i = 0; i < 11; i++) {
                    if (Process::Read32(address[0] + (i * 4), data32) && data32 != patch[i]) {
                        Process::Patch(address[0], patch, 0x2C);
                    }
                }

                if (Process::Read32(address[1], data32) && data32 != 0xEBF992F7) {
                    Process::Patch(address[1], 0xEBF992F7, original);
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
        static const u32 address[3] = {0x5979D0, 0x638010, 0x80860D8};
        static u32 patch[12] = {0xE59D0000, 0xE92D401E, 0xE59A1008, 0xE2813004, 0xE281401C, 0xE4932004, 0xE1500002, 0x03A01001, 0x058D1018, 0xE1530004, 0x1AFFFFF9, 0xE8BD801E};
        static u32 original[1] = {0};

        if (Gen7::IsInBattle() && !IsOnline) {
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
                    Process::Patch(address[2], 0xEBF9B23C, original);
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
        static const u32 address[2] = {0x597900, 0x29A168};
        static u32 original[1] = {0};
        static u32 patch[36] = {
            0xE59F2080, 0xE152000E, 0x1A00001D, 0xE92D001F, 0xE59F2074, 0xE59400D0, 0xE2803004, 0xE280401C, 0xE4931004, 0xE3510000, 0x15C121EA, 0x15C121EB,
            0x158121EC, 0x15C121F0, 0xE1530004, 0x1AFFFFF7, 0xE59D002C, 0xE5900A88, 0xE2800A01, 0xE5900808, 0xE590000C, 0xE5900008, 0xE2803004, 0xE280401C,
            0xE4931004, 0xE3510000, 0x15C121EA, 0x15C121EB, 0x158121EC, 0x15C121F0, 0xE1530004, 0x1AFFFFF7, 0xE8BD001F, 0xEAF409F8, 0x006E9680, 0x0C0C0C0C
        };

        if (Gen7::IsInBattle() && !IsOnline) {
            if (entry->IsActivated()) {
                for (int i = 0; i < 36; i++) {
                    if (Process::Read32(address[0] + (i * 4), data32) && data32 != patch[i]) {
                        Process::Patch(address[0], patch, 0x90);
                    }
                }

                if (Process::Read32(address[1], data32) && data32 != 0xEA0BF5E4) {
                    Process::Patch(address[1], 0xEA0BF5E4, original);
                }
            }

            if (!entry->IsActivated()) {
                for (int j = 0; j < 36; j++) {
                    Process::Patch(address[0] + (j * 4), 0);
                }

                Process::Patch(address[1], original, 4);
            }
        }
    }

    void Bypass1MegaRestrict(MenuEntry *entry) {
        static const u32 address = 0x80A2CE4;
        static u32 data[1] = {0xE3A00000};
        static u32 original[1] = {0};

        if (Gen7::IsInBattle() && !IsOnline) {
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
        static const u32 address = 0x80311D4;
        static u32 data[3] = {0xE3A00000, 0xE5C30005, 0xE1500000};
        static u32 original[3] = {0, 0, 0};

        if (Gen7::IsInBattle() && !IsOnline) {
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
        static const u32 address[4] = {0x597800, 0x314300, 0x314370, 0x36DFF4};
        static u32 data[11] = {0xE92D4005, 0xE1A00006, 0xEA000000, 0xE92D4005, 0xE59D2050, 0xE59F100C, 0xE1510002, 0x01D510B4, 0x11A01000, 0xE8BD8005, 0x0078BF60};

        if (entry->WasJustActivated()) {
            Process::Patch(address[0], data, 0x2C);
        }

        if (Gen7::IsInBattle() && !IsOnline) {
            Process::Write32(address[1], 0xEB0A0D3E);
            Process::Write32(address[2], 0xEB0A0D25);

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
        static const u32 address = 0x318AF0;
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
        static const u32 address[2] = {0x59775C, 0x490E68};
        static u32 data[10][1] = {{0xE5D00008}, {0xE92D4003}, {0xE59D0010}, {0xE59F100C}, {0xE1510000}, {0x024000F8}, {0x058D0010}, {0xE8BD8003}, {0x006DA1CC}, {0xEB041A3B}};
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
        static const u32 address = 0x8035AA8;
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
        static const u32 address = 0x49EFC8;
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
        static const u32 address = 0x802EBF0;
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
        static const u32 address = 0x80AE610;
        static u32 data[1] = {0xEAFFFEE7};
        static u32 original[1] = {0};

        if (Gen7::IsInBattle() && !IsOnline) {
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
        static const u32 address = 0x807A5E8;
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
        static u32 address[7] = {0x597BA0, 0x597BC0, 0x399CB4, 0x399CC4, 0x399CF0, 0x399C9C, 0x399D50};
        static u32 data[10] = {0xE92D400E, 0xE59F0014, 0xE3500000, 0x18BD800E, 0xE59F000C, 0xEBF83F51, 0xE2800001, 0xE8BD800E, 0x00000000, 0x00000327};
        static u32 original[1] = {0};

        if (entry->WasJustActivated()) {
            if (Process::Patch(address[0], data, 0x28)) {
                Process::Write32(address[2], 0xEB07F7B9);
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
        FindPkmnKB(entry);
        pokeNo = pkmnID;
        KeyboardPlus keyboard;

        if (pokeNo > 0) {
            if (keyboard.SetKeyboard("Form:", true, Gen7::FindForms(pokeNo), form) != -1) {
                if (KB<u16>("Level:", true, false, 3, level, 0, 1, 100, KeyboardCallback)) {
                    entry->SetGameFunc(InitPokemon);
                }
            }
        }
    }

    void CanCatchTrials(MenuEntry *entry) {
        static const u32 address[2] = {0x8076530, 0x80B8914};
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
        static const StringVector options = {"Tapu Koko", "Tapu Lele", "Tapu Bulu", "Tapu Fini", "Cosmog", AutoGame("Solgaleo", "Lunala"), "Necrozma"};
        KeyboardPlus keyboard;
        keyboard.SetKeyboard(entry->Name() + ":", true, options, legendaryIndex);
    }

    void RematchLegendaries(MenuEntry *entry) {
        if (legendaryIndex == 0) {
            static const u32 address = 0x330D721C;

            if (Bit::Read(address, data8, true) && data8 != 3) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 3, true);
                }
            }
        }

        if (legendaryIndex == 1) {
            static const u32 address = 0x330D721E;

            if (Bit::Read(address, data8, true) && data8 != 1) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 1, true);
                }
            }
        }

        if (legendaryIndex == 2) {
            static const u32 address = 0x330D7220;

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
            static const u32 address = 0x330D76CA;

            if (Bit::Read(address, data8, false) && data8 != 0) {
                if (Bit::Read(address, data8, false)) {
                    Bit::Edit(address, 0, false);
                }
            }
        }

        if (legendaryIndex == 5) {
            static const u32 address = 0x330D76EE;

            if (Bit::Read(address, data8, false) && data8 != 2) {
                if (Bit::Read(address, data8, false)) {
                    Bit::Edit(address, 2, false);
                }
            }
        }

        if (legendaryIndex == 6) {
            static const u32 address = 0x330D783A;

            if (Bit::Read(address, data8, false) && data8 != 1) {
                if (Bit::Read(address, data8, false)) {
                    Bit::Edit(address, 1, false);
                }
            }
        }
    }
}