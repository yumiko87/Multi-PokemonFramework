#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace XY {
    static const u32 party[6][2] =
    {
        {0x81FB284, 0x81FB624},
        {0x81FB288, 0x81FB628},
        {0x81FB28C, 0x81FB62C},
        {0x81FB290, 0x81FB630},
        {0x81FB294, 0x81FB634},
        {0x81FB298, 0x81FB638}
    };

    static const u32 opponent[6][2] =
    {
        {0x81FB2A0, 0x81FB640},
        {0x81FB2A4, 0x81FB644},
        {0x81FB2A8, 0x81FB648},
        {0x81FB2AC, 0x81FB64C},
        {0x81FB2B0, 0x81FB650},
        {0x81FB2B4, 0x81FB654}
    };

    struct Conditions {
        const char *name;
        int choiceNo;
    };

    static const Conditions allCndtions[5] = {
        {"Asleep", 0x24},
        {"Burned", 0x2C},
        {"Frozen", 0x28},
        {"Paralyzed", 0x20},
        {"Poisoned", 0x30}
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
                                        Process::Write8(offset32 + (0x20 + (i * 4)), 0);

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
                                    Process::Write16(offset32 + 0xF6 + (k * 2), baseVals[k]);
                                }
                            }

                            for (int l = 0; l < 7; l++) {
                                if (boostVals[l] != 0) {
                                    Process::Write8(offset32 + 0x104 + (l * 1), boostVals[l]);
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
                                    Process::Write16(offset32 + 0x11E + (l * 0xE), (staminaVals << 8) | staminaVals);
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
                                    Process::Write16(offset32 + 0x11C + (atkSlot * 0xE), attack);
                                }
                            }
                        }
                    }
                }

                else goto Start;
            }
        }
    }

    void AccessBag(MenuEntry *entry) {
        static const u32 pointer = 0x8000158;

        if (Gen6::IsInBattle()) {
            if (entry->Hotkeys[0].IsDown()) {
                if (Process::Read32(pointer, data32) && data32 != 0) {
                    if (Process::Read32(pointer, offset32)) {
                        Process::Write8(offset32 + 0x778, 4);
                    }
                }
            }
        }
    }

    void InfiniteMegaEvolution(MenuEntry *entry) {
        static const u32 address = 0x8C79D86, pointer = 0x8000178;

        if (Bit::Read(address, data8, true) && data8 != 1) {
            if (Bit::Read(address, data8, true)) {
                Bit::Edit(address, 1, true);
            }
        }

        if (Gen6::IsInBattle()) {
            if (Process::Read32(pointer, data32) && data32 != 0){
                if (Process::Read32(pointer, offset32)) {
                    Process::Write8(offset32 + 0xEDD, 1);
                }
            }
        }
    }

    static u16 multiplier;

    void ExpMultiplier(MenuEntry *entry) {
        static const u32 address[2] = {0x53EDA0, 0x175FB0};
        static u32 data[5] = {0xE1D002B2, 0xE92D4002, (0xE3A01000 + multiplier), 0xE0000190, 0xE8BD8002};
        static u32 original[5] = {0, 0, 0, 0, 0};

        if (KB<u16>(entry->Name() + ":", true, false, 3, multiplier, 0, 0, 100, KeyboardCallback)) {
            for (int i = 0; i < 5; i++) {
                if (Process::Read32(address[0] + (i * 4), data32) && data32 != data[i]) {
                    Process::Patch(address[0], data, 20, original);
                }
            }

            Process::Write32(address[1], 0xEB0F237A);
        }

        if (multiplier <= 0) {
            Process::Patch(address[0], original, 20);
            Process::Write32(address[1], 0xE1D002B2);
        }
    }

    void AlwaysShiny(MenuEntry *entry) {
        static const u32 address = 0x14F6A4;
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
        static const u32 address = 0x8073334;
        static u32 data[1] = {0xEA000004};
        static u32 original[1] = {0};

        if (Gen6::IsInBattle()) {
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

    void CatchTrainersPokemon(MenuEntry *entry) {
        static const u32 address = 0x8075474;
        static u32 data[3] = {0xE3A0B000, 0xE5C0B000, 0xEA00000E};
        static u32 original[3] = {0, 0, 0};

        if (Gen6::IsInBattle()) {
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

    void NoEncounters(MenuEntry *entry) {
        static const u32 address = 0x436AC8;
        static u32 data[1] = {0xE12FFF1E};
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

    unsigned int pointerOffset = 0x8CEC564, encDataLength = 0x178, byteJump = 0x10, dexOffset = 0x8CC8D4C;

    bool IsObtained(int value) {
        if ((dexOffset >= 0x8000000) && (dexOffset < 0x8DF0000)) {
            unsigned int obtainedOffset = ProcessPlus::Read32(dexOffset);

            if ((obtainedOffset >= 0x8000000) && (obtainedOffset < 0x8DF0000)) {
                // Check if all is obtained
                for (int i = 0; i < 721; i++) {
                    if ((ProcessPlus::Read8(obtainedOffset + 0xC + (i / 8)) & (1 << (i % 8))) == 0) {
                        break;
                    }

                    if (i == 720) {
                        return false;
                    }
                }

                // Check if value is set
                if ((ProcessPlus::Read8(obtainedOffset + 0xC + ((value - 1) / 8)) & (1 << ((value - 1) % 8))) != 0) {
                    return true;
                }
            }
        }

        return false;
    }

    unsigned short last = 0xFFFF, poke[721];

    void InitPokemon(int pokeID, int form, bool updateRadar) {
        if (pointerOffset != 0) {
            unsigned int zoOffset = ProcessPlus::Read32(pointerOffset);

            // Check for valid pointer
            if ((zoOffset >= 0x8000000) && (zoOffset < 0x8DF0000)) {
                // Check if ZO file contains encounter data
                if (ProcessPlus::Read32(zoOffset + 0x10) != ProcessPlus::Read32(zoOffset + 0x14)) {
                    last = ProcessPlus::Read16(pointerOffset + 4);
                    unsigned int encOffset = zoOffset + ProcessPlus::Read32(zoOffset + 0x10) + byteJump;

                    // Make sure the table for the DexNav is exactly the same as the one used for normal encounters
                    if (group == Group::ORAS && updateRadar) {
                        Process::CopyMemory((void *) (0x16B3DF40 + ProcessPlus::Read32(0x16B3DF40 + 4 + ProcessPlus::Read16(pointerOffset + 4) * 4) + byteJump), (void *) encOffset, 0xF4);
                    }

                    int pokemon = 1;
                    u32 currentEncOffset;

                    for (int i = 0; i < encDataLength; i += 4) {
                        if (ProcessPlus::Read8(encOffset + i + 2) != 1) {
                            currentEncOffset = encOffset + i;
                            pokemon = pokeID;
                            pokemon += 0x800 * form;

                            // Associate the Pokemon ID replaced with the one we use to overwrite it
                            poke[ProcessPlus::Read16(currentEncOffset) - 1] = pokemon;
                            ProcessPlus::Write16(currentEncOffset, pokemon);
                        }
                    }

                    /* Update DexNav because the it is not updated when we go to a location without any possible encounter,
                       so when we return to the previous route the DexNav does not show the good species, a battle is necessary to reload it. */
                    if (updateRadar && group == Group::ORAS) {
                        for (int j = 0; j < encDataLength; j += 4) {
                            // Replace the Pokemon ID according to the one associated with it in the array
                            unsigned int loc = 0x16B3DF40 + ProcessPlus::Read32(0x16B3DF40 + 4 + ProcessPlus::Read16(pointerOffset + 4) * 4) + byteJump + j;

                            if (ProcessPlus::Read16(loc) != 0) {
                                ProcessPlus::Write16(loc, poke[ProcessPlus::Read16(loc) - 1]);
                            }
                        }
                    }

                    return;
                }

                else last = 0xFFFF;
            }
        }
    }

    int pokeID, form;

    void WildPokemon(MenuEntry *entry) {
        FindPkmnKB(entry);
        pokeID = pkmnID;
        KeyboardPlus keyboard;

        if (pokeID > 0) {
            if (keyboard.SetKeyboard("Form:", true, Gen6::FindForms(pokeID), form) != -1) {
                InitPokemon(pokeID, form, AutoGroup(false, true));
            }
        }
    }

    static int legendaryIndex;

    void RematchLegendariesKB(MenuEntry *entry) {
        static const StringVector options = {"Mewtwo", AutoGame("Xerneas", "Yveltal"), "Zygarde"};
        KeyboardPlus keyboard;
        keyboard.SetKeyboard(entry->Name() + ":", true, options, legendaryIndex);
    }

    void RematchLegendaries(MenuEntry *entry) {
        if (legendaryIndex == 0) {
            static const u32 address = 0x8C7A74C;

            if (Bit::Read(address, data8, true) && data8 != 0) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 0, true);
                }
            }
        }

        if (legendaryIndex == 1) {
            static const u32 address[2] = {0x8C7A56C, 0x8C7A73C};

            if (Bit::Read(address[0], data8, true) && data8 != 5) {
                if (Bit::Read(address[0], data8, true)) {
                    Bit::Edit(address[0], 5, true);
                }
            }

            if (Bit::Read(address[1], data8, false) && data8 != 0) {
                if (Bit::Read(address[1], data8, false)) {
                    Bit::Edit(address[1], 0, false);
                }
            }
        }

        if (legendaryIndex == 2) {
            static const u32 address = 0x8C7A736;

            if (Bit::Read(address, data8, false) & & data8 != 0) {
                if (Bit::Read(address, data8, false)) {
                    Bit::Edit(address, 0, false);
                }
            }
        }
    }
}