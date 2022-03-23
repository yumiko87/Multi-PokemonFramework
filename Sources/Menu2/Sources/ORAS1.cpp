#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace ORAS {
    static const u32 party[6][2] =
    {
        {0x81FB58C, 0x81FB92C},
        {0x81FB590, 0x81FB930},
        {0x81FB594, 0x81FB934},
        {0x81FB598, 0x81FB938},
        {0x81FB59C, 0x81FB93C},
        {0x81FB5A0, 0x81FB940},
    };

    static const u32 opponent[6][2] =
    {
        {0x81FB5A8, 0x81FB948},
        {0x81FB5AC, 0x81FB94C},
        {0x81FB5B0, 0x81FB950},
        {0x81FB5B4, 0x81FB954},
        {0x81FB5B8, 0x81FB958},
        {0x81FB5BC, 0x81FB95C},
    };

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

    void AccessBag(MenuEntry *entry) {
        static const u32 pointer = 0x8000158;

        if (Gen6::IsInBattle()) {
            if (entry->Hotkeys[0].IsDown()) {
                if (Process::Read32(pointer, data32) && data32 != 0) {
                    if (Process::Read32(pointer, offset32)) {
                        Process::Write8(offset32 + 0x77C, 4);
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

    void AlwaysShiny(MenuEntry *entry) {
        static const u32 address = 0x14ECA4;
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
        static const u32 address = 0x80737A4;
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
        static const u32 address = 0x8075858;
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
        static const u32 address = Gen6::Auto(0x4640EC, 0x4640E4);
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

    static int legendaryIndex;

    void RematchLegendariesKB(MenuEntry *entry) {
        static const StringVector options = {Gen6::Name("Ho-Oh", "Lugia"), Gen6::Name("Latias", "Latios"), Gen6::Name("Groudon", "Kyogre"), "Rayquaza", "Deoxys", Gen6::Name("Palkia", "Dialga"), "Heatran", "Regigigas", "Giritina", Gen6::Name("Tornadus", "Thunderus"), "Landorus", "Kyruem"};
        KeyboardPlus keyboard;
        keyboard.SetKeyboard(entry->Name() + ":", true, options, legendaryIndex);
    }

    void RematchLegendaries(MenuEntry *entry) {
        if (legendaryIndex == 0) {
            static const u32 address = 0x8C81DF2;

            if (Bit::Read(address, data8, true) && data8 != 0) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 0, true);
                }
            }
        }

        if (legendaryIndex == 1) {
            static const u32 address = 0x8C81E0C;

            if (Bit::Read(address, data8, true) && data8 != 0) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 0, true);
                }
            }
        }

        if (legendaryIndex == 2) {
            static const u32 address = Gen6::Auto(0x8C81E29, 0x8C81E28);

            if (game == Game::OR) {
                if (Bit::Read(address, data8, true) && data8 != 0) {
                    if (Bit::Read(address, data8, true)) {
                        Bit::Edit(address, 0, true);
                    }
                }
            }

            if (game == Game::AS) {
                if (Bit::Read(address, data8, false) && data8 != 0) {
                    if (Bit::Read(address, data8, false)) {
                        Bit::Edit(address, 0, false);
                    }
                }
            }
        }

        if (legendaryIndex == 3) {
            static const u32 address = 0x8C81E41;

            if (Bit::Read(address, data8, false) && data8 != 0xE) {
                if (Bit::Read(address, data8, false)) {
                    Bit::Edit(address, 0xE, false);
                }
            }
        }

        if (legendaryIndex == 4) {
            static const u32 address = 0x8C81E4E;

            if (Bit::Read(address, data8, true) && data8 != 0) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 0, true);
                }
            }
        }

        if (legendaryIndex == 5) {
            static const u32 address = 0x8C81F38;

            if (Bit::Read(address, data8, true) && data8 != 0) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 0, true);
                }
            }
        }

        if (legendaryIndex == 6) {
            static const u32 address = 0x8C81DF8;

            if (Bit::Read(address, data8, true) && data8 != 0) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 0, true);
                }
            }
        }

        if (legendaryIndex == 7) {
            static const u32 address[2] = {0x8C81CC4, 0x8C81DF7};

            if (Bit::Read(address[0], data8, true) && data8 != 1) {
                if (Bit::Read(address[0], data8, true)) {
                    Bit::Edit(address[0], 1, true);
                }
            }

            if (Bit::Read(address[1], data8, false) && data8 != 0) {
                if (Bit::Read(address[1], data8, false)) {
                    Bit::Edit(address[1], 0, false);
                }
            }
        }

        if (legendaryIndex == 8) {
            static const u32 address = 0x8C81F38;

            if (Bit::Read(address, data8, false) && data8 != 0) {
                if (Bit::Read(address, data8, false)) {
                    Bit::Edit(address, 0, false);
                }
            }
        }

        if (legendaryIndex == 9) {
            static const u32 address = 0x8C81F39;

            if (Bit::Read(address, data8, false) && data8 != 0) {
                if (Bit::Read(address, data8, false)) {
                    Bit::Edit(address, 0, false);
                }
            }
        }

        if (legendaryIndex == 10) {
            static const u32 address = 0x8C81F3A;

            if (Bit::Read(address, data8, true) && data8 != 0) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 0, true);
                }
            }
        }

        if (legendaryIndex == 11) {
            static const u32 address = 0x8C81DEF;

            if (Bit::Read(address, data8, true) && data8 != 0) {
                if (Bit::Read(address, data8, true)) {
                    Bit::Edit(address, 0, true);
                }
            }
        }
    }

    unsigned int pointerOffset = 0x8D06468, encDataLength = 0xF4, byteJump = 0xE, dexOffset = 0x8CE0CB8;

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

                else  last = 0xFFFF;
            }
        }
    }

    int pokeID, form;

    void WildPokemon(MenuEntry *entry) {
        SelectAPokemon(entry);
        pokeID = pkmnID;
        KeyboardPlus keyboard;

        if (pokeID > 0) {
            if (keyboard.SetKeyboard("Form:", true, Gen6::Forms(pokeID), form) != -1) {
                InitPokemon(pokeID, form, Value(false, true));
            }
        }
    }
}