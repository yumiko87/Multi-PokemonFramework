#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace XY {
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
    
    static int legendaryIndex;
    
    void RematchLegendariesKB(MenuEntry *entry) {
        static const vector<string> options = {"Mewtwo", Gen6::Name("Xerneas", "Yveltal"), "Zygarde"};
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
                
                else {
                    last = 0xFFFF;
                }
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
                InitPokemon(pokeID, form, Gen6::Value(false, true));
            }
        }
    }
}