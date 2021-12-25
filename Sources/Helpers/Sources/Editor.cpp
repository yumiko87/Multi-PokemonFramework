#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework {
    static u8 box, slot;

    bool Editor::Setup(void) {
        if (KB<u8>("Box:", true, false, 2, box, 0, 1, (group == Group::XY || group == Group::ORAS ? 31 : 32), KeyboardCallback)) {
            if (KB<u8>("Slot:", true, false, 2, slot, 0, 1, 30, KeyboardCallback)) {
                return true;
            }
        }
        return false;
    }

    void Editor::Initialize(MenuEntry *entry) {
        if (Setup()) {
            Message::Completed();
        }
    }

    bool Editor::IsValid(u32 pointer, PK6 *pkmn) {
        if (!GetPokemon(pointer, pkmn)) {
            MessageBox("Failed to read or decrypt data!", DialogType::DialogOk)();
            return false;
        }
        return true;
    }

    void Editor::Species(MenuEntry *entry) {
        PK6 *pkmn = new PK6;
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));

        SelectAPokemon(entry);
        u16 species = pkmnID;

        if (IsValid(pointer, pkmn)) {
            if (species >= 0) {
                SetSpecies(pkmn, species);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    void Editor::Form(MenuEntry *entry) {
        PK6 *pkmn = new PK6;
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));

        KeyboardPlus keyboard;
        int form, species = ProcessPlus::Read16((group == Group::XY || group == Group::ORAS ? Gen6::Value(0x83D2F98, 0x83F36B4) : Gen7::Value(0x34156A04, 0x33F40D70)));

        if (IsValid(pointer, pkmn)) {
            if (species > 0) {
                if (keyboard.SetKeyboard("Form:", true, Gen6::Forms(species), form) != -1) {
                    SetForm(pkmn, form);

                    if (SetPokemon(pointer, pkmn)) {
                        Message::Completed();
                    }
                }
            }
        }
    }

    void Editor::Shinify(MenuEntry *entry) {
        PK6 *pkmn = new PK6;
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));

        if (IsValid(pointer, pkmn)) {
            if (!IsShiny(pkmn)) {
                MakeShiny(pkmn);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                    return;
                }
            }

            else if (IsShiny(pkmn)) {
                Message::Warning();
            }
        }
    }
}