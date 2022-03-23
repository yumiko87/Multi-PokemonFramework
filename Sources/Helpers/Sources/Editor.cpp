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
            MessageBox("Failed to read or decrypt data!", DialogType::DialogOk, ClearScreen::Both)();
            return false;
        }

        return true;
    }

    void Editor::Shinify(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

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

    static u16 species;

    void Editor::Species(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            SelectAPokemon(entry);
            species = pkmnID;

            if (species > 0) {
                SetSpecies(pkmn, species);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static int isNick;

    void Editor::IsNicknamed(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"No", "Yes"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, isNick) != -1) {
                SetIsNicknamed(pkmn, isNick);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static String nick;

    void Editor::Nickname(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            if (KB<String>(entry->Name() + ":", true, false, 26, nick, "")) {
                SetNickname(pkmn, nick);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static int genderChoice;

    void Editor::Gender(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"Male", "Female", "Genderless"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, genderChoice) != -1) {
                SetGender(pkmn, genderChoice);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u32 expAmount;

    void Editor::Experience(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            if (KB<u32>(entry->Name() + ":", true, false, 7, expAmount, 0, 1, 1640000, KeyboardCallback)) {
                if (SetExp(pkmn, expAmount)) {
                    if (SetPokemon(pointer, pkmn)) {
                        Message::Completed();
                    }
                }
            }
        }
    }

    static int natureID;

    void Editor::Nature(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, allNatures, natureID) != -1) {
                SetNature(pkmn, natureID);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    void Editor::Form(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        int form, species = ProcessPlus::Read16((group == Group::XY || group == Group::ORAS ? Value(0x83D2F98, 0x83F36B4) : Value(0x34156A04, 0x33F40D70)));
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            if (species > 0) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, Gen6::Forms(species), form) != -1) {
                    SetForm(pkmn, form);

                    if (SetPokemon(pointer, pkmn)) {
                        Message::Completed();
                    }
                }
            }
        }
    }

    static u16 item;

    void Editor::HeldItem(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            SelectAHeldItem(entry);
            item = heldItemID;

            if (item > 0) {
                SetHeldItem(pkmn, item);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u8 abil;

    void Editor::Ability(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            SelectAnAbility(entry);
            abil = abilityID;

            if (abil > 0) {
                SetAbility(pkmn, abil);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u16 friendshipAmount;

    void Editor::Friendship(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            if (KB<u16>(entry->Name() + ":", true, false, 3, friendshipAmount, 0, 0, 255, KeyboardCallback)) {
                SetFriendship(pkmn, friendshipAmount);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static int languageChoice;

    void Editor::Language(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"JPN", "ENG", "FRE", "ITA", "GER", "ESP", "KOR", "CHS", "CHT"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, languageChoice) != -1) {
                SetLanguage(pkmn, languageChoice + 1);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static int eggChoice;

    void Editor::IsEgg(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"No", "Yes"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, eggChoice) != -1) {
                SetIsEgg(pkmn, eggChoice);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u8 pkrsVal[2];
    static int pkrsCureChoice;

    void Editor::Pokerus(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"Cured", "Non-Cured"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            Start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, pkrsCureChoice) != -1) {
                if (pkrsCureChoice == 0) {
                    SetPokerus(pkmn, 0, 0, true);
                }

                else if (pkrsCureChoice == 1) {
                    if (KB<u8>("Days:", true, false, 2, pkrsVal[0], 0, 0, 15, KeyboardCallback)) {
                        if (KB<u8>("Strain:", true, false, 1, pkrsVal[1], 0, 0, 3, KeyboardCallback)) {
                            SetPokerus(pkmn, pkrsVal[0], pkrsVal[1], false);
                        }

                        else goto Start;
                    }

                    else goto Start;
                }

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u8 countryID;

    void Editor::Country(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            if (KB<u8>(entry->Name() + ":", true, false, 3, countryID, 0, 1, 186, KeyboardCallback)) {
                SetCountry(pkmn, countryID);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static int consRegion;

    void Editor::ConsoleRegion(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"Japan", "Americas", "Europe", "China", "Korea", "Taiwan"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, consRegion) != -1) {
                SetConsRegion(pkmn, consRegion + 1);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static int getOrigin, originID;

    void Editor::OriginGame(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        StringVector options;
        KeyboardPlus keyboard;

        for (const Origins &nickname:allOrigins) {
            options.push_back(nickname.name);
        }

        if (IsValid(pointer, pkmn)) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getOrigin) != -1) {
                originID = allOrigins[getOrigin].choiceNo;
                SetOrigin(pkmn, originID);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static int getMetLoc, metLocID, deterVer;

    void Editor::MetLocation(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        StringVector options;
        KeyboardPlus keyboard;

        if (allOrigins[getOrigin].choiceNo == 24 || allOrigins[getOrigin].choiceNo == 25) {
            deterVer = allLocs1[getMetLoc].choiceNo;

            for (const Locations &nickname:allLocs1) {
                options.push_back(nickname.name);
            }
        }

        else if (allOrigins[getOrigin].choiceNo == 26 || allOrigins[getOrigin].choiceNo == 27) {
            deterVer = allLocs2[getMetLoc].choiceNo;

            for (const Locations &nickname:allLocs2) {
                options.push_back(nickname.name);
            }
        }

        else {
            MessageBox("Failed to read or decrypt data!", DialogType::DialogOk, ClearScreen::Both)();
            return;
        }

        if (IsValid(pointer, pkmn)) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getMetLoc) != -1) {
                metLocID = deterVer;
                SetMetLocation(pkmn, metLocID, false);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static int getBall, ballID;

    void Editor::Ball(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        StringVector options;
        KeyboardPlus keyboard;

        for (const Balls &nickname:allBalls) {
            options.push_back(nickname.name);
        }

        if (IsValid(pointer, pkmn)) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getBall) != -1) {
                ballID = allBalls[getBall].choiceNo;
                SetBall(pkmn, ballID);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u16 levelMetAt;

    void Editor::MetLevel(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            if (KB<u16>(entry->Name() + ":", true, false, 3, levelMetAt, 0, 1, 100, KeyboardCallback)) {
                SetMetLevel(pkmn, levelMetAt);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u8 date[3];
    static int dateChoice;

    void Editor::MetDate(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"Year", "Month", "Day"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            Start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, dateChoice) != -1) {
                if (dateChoice == 0) {
                   if (KB<u8>("Year:", true, false, 2, date[0], 0, 0, 99, KeyboardCallback)) {
                       SetMetDate(pkmn, true, date[0], false, 0, false, 0, false);
                   }

                   else goto Start;
                }

                else if (dateChoice == 1) {
                   if (KB<u8>("Month:", true, false, 2, date[1], 0, 1, 12, KeyboardCallback)) {
                       SetMetDate(pkmn, false, 0, true, date[1], false, 0, false);
                   }

                   else goto Start;
                }

                else if (dateChoice == 2) {
                   if (KB<u8>("Day:", true, false, 2, date[2], 0, 1, 31, KeyboardCallback)) {
                       SetMetDate(pkmn, false, 0, false, 0, true, date[2], false);
                   }

                   else goto Start;
                }

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static int encChoice;

    void Editor::IsFatefulEncounter(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"No", "Yes"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, encChoice) != -1) {
                SetIsFatefulEnc(pkmn, encChoice);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static int getEggMetLoc, eggMetLocID, deterEggVer;

    void Editor::EggMetLoc(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        StringVector options;
        KeyboardPlus keyboard;

        if (allOrigins[getOrigin].choiceNo == 24 || allOrigins[getOrigin].choiceNo == 25) {
            deterEggVer = allLocs1[getEggMetLoc].choiceNo;

            for (const Locations &nickname:allLocs1) {
                options.push_back(nickname.name);
            }
        }

        else if (allOrigins[getOrigin].choiceNo == 26 || allOrigins[getOrigin].choiceNo == 27) {
            deterEggVer = allLocs2[getEggMetLoc].choiceNo;

            for (const Locations &nickname:allLocs2) {
                options.push_back(nickname.name);
            }
        }

        else {
            MessageBox("Failed to read or decrypt data!", DialogType::DialogOk, ClearScreen::Both)();
            return;
        }

        if (IsValid(pointer, pkmn)) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getEggMetLoc) != -1) {
                eggMetLocID = deterEggVer;
                SetMetLocation(pkmn, eggMetLocID, true);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u8 eggDate[3];
    static int eggDateChoice;

    void Editor::EggMetDate(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"Year", "Month", "Day"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            Start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, eggDateChoice) != -1) {
                if (eggDateChoice == 0) {
                   if (KB<u8>("Year:", true, false, 2, eggDate[0], 0, 0, 99, KeyboardCallback)) {
                       SetMetDate(pkmn, true, eggDate[0], false, 0, false, 0, true);
                   }

                   else goto Start;
                }

                else if (eggDateChoice == 1) {
                   if (KB<u8>("Month:", true, false, 2, eggDate[1], 0, 1, 12, KeyboardCallback)) {
                       SetMetDate(pkmn, false, 0, true, eggDate[1], false, 0, true);
                   }

                   else goto Start;
                }

                else if (eggDateChoice == 2) {
                   if (KB<u8>("Day:", true, false, 2, eggDate[2], 0, 1, 31, KeyboardCallback)) {
                       SetMetDate(pkmn, false, 0, false, 0, true, eggDate[2], true);
                   }

                   else goto Start;
                }

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u8 ivs[6];
    static int ivChoice;

    void Editor::IVs(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"HP", "Atk", "Def", "SpA", "SpD", "Spe"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            Start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, ivChoice) != -1) {
                if (KB<u8>(options[ivChoice] + ":", true, false, 2, ivs[ivChoice], 0, 0, 31, KeyboardCallback)) {
                    SetIV(pkmn, ivChoice, ivs[ivChoice]);
                }

                else goto Start;

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u16 evAmount[6];
    static int evChoice;

    void Editor::EVs(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"HP", "Atk", "Def", "SpA", "SpD", "Spe"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            Start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, evChoice) != -1) {
                if (KB<u16>(options[evChoice] + ":", true, false, 3, evAmount[evChoice], 0, 0, 252, KeyboardCallback)) {
                    SetEV(pkmn, evChoice, evAmount[evChoice]);
                }

                else goto Start;

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u16 contestStats[6];
    static int contestChoice;

    void Editor::Contest(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"Cool", "Beauty", "Cute", "Smart", "Though", "Sheen"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            Start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, contestChoice) != -1) {
                if (KB<u16>(options[contestChoice] + ":", true, false, 3, contestStats[contestChoice], 0, 0, 255, KeyboardCallback)) {
                    SetContestStats(pkmn, contestChoice, contestStats[contestChoice]);
                }

                else goto Start;

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u16 moves;
    static int moveSlot;

    void Editor::CurrentMoves(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"Move 1", "Move 2", "Move 3", "Move 4"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            Start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, moveSlot) != -1) {
                SelectAMove(entry);
                moves = moveID;

                if (moves > 0) {
                    SetMoves(pkmn, moveSlot, moves, false);
                }

                else goto Start;

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u8 ppUps[6];
    static int ppUpSlot;

    void Editor::PPUps(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"Move 1", "Move 2", "Move 3", "Move 4"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            Start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, ppUpSlot) != -1) {
                if (KB<u8>(options[ppUpSlot] + ":", true, false, 1, ppUps[ppUpSlot], 0, 0, 3, KeyboardCallback)) {
                    SetPPUps(pkmn, ppUpSlot, ppUps[ppUpSlot]);
                }

                else goto Start;

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u16 relearnMoves;
    static int relearnMoveSlot;

    void Editor::RelearnMoves(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"Move 1", "Move 2", "Move 3", "Move 4"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            Start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, relearnMoveSlot) != -1) {
                SelectAMove(entry);
                relearnMoves = moveID;

                if (relearnMoves > 0) {
                    SetMoves(pkmn, relearnMoveSlot, relearnMoves, true);
                }

                else goto Start;

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u16 sidNums;

    void Editor::SID(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            if (KB<u16>(entry->Name() + ":", true, false, 5, sidNums, 0, 1, 65535, KeyboardCallback)) {
                SetSID(pkmn, sidNums);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static u16 tidNums;

    void Editor::TID(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            if (KB<u16>(entry->Name() + ":", true, false, 5, tidNums, 0, 1, 65535, KeyboardCallback)) {
                SetTID(pkmn, tidNums);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static String name;

    void Editor::OTName(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            if (KB<String>(entry->Name() + ":", true, false, 26, name, "")) {
                SetOTName(pkmn, name);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    static String htName;

    void Editor::LatestHandler(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        if (IsValid(pointer, pkmn)) {
            if (KB<String>(entry->Name() + ":", true, false, 26, htName, "")) {
                SetLatestHandler(pkmn, htName);

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }

    int ribb, ribbSection, ribbChoice;

    void Editor::Ribbons(MenuEntry *entry) {
        u32 pointer = (((slot - 1) * 232) + ((box - 1) * 6960 + GetPokePointer()));
        PK6 *pkmn = new PK6;

        static const StringVector options = {"RIB0", "RIB1", "RIB2", "RIB3", "RIB4", "RIB5", "RIB6"}, noYes = {"No", "Yes"};
        KeyboardPlus keyboard;

        if (IsValid(pointer, pkmn)) {
            Start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, ribbSection) != -1) {
                switch (ribbSection) {
                    case 0: {
                        if (keyboard.SetKeyboard(options[ribbSection] + ":", true, rib0Ribbons, ribb) != -1) {
                            if (keyboard.SetKeyboard(rib0Ribbons[ribb] + ":", true, noYes, ribbChoice) != -1) {
                                SetRibbons(pkmn, ribbSection, ribbChoice, ribb);
                            }

                            else goto Start;
                        }

                        else goto Start;
                    }
                    break;

                    case 1: {
                        if (keyboard.SetKeyboard(options[ribbSection] + ":", true, rib1Ribbons, ribb) != -1) {
                            if (keyboard.SetKeyboard(rib1Ribbons[ribb] + ":", true, noYes, ribbChoice) != -1) {
                                SetRibbons(pkmn, ribbSection, ribbChoice, ribb);
                            }

                            else goto Start;
                        }

                        else goto Start;
                    }
                    break;

                    case 2: {
                        if (keyboard.SetKeyboard(options[ribbSection] + ":", true, rib2Ribbons, ribb) != -1) {
                            if (keyboard.SetKeyboard(rib2Ribbons[ribb] + ":", true, noYes, ribbChoice) != -1) {
                                SetRibbons(pkmn, ribbSection, ribbChoice, ribb);
                            }

                            else goto Start;
                        }

                        else goto Start;
                    }
                    break;

                    case 3: {
                        if (keyboard.SetKeyboard(options[ribbSection] + ":", true, rib3Ribbons, ribb) != -1) {
                            if (keyboard.SetKeyboard(rib3Ribbons[ribb] + ":", true, noYes, ribbChoice) != -1) {
                                SetRibbons(pkmn, ribbSection, ribbChoice, ribb);
                            }

                            else goto Start;
                        }

                        else goto Start;
                    }
                    break;

                    case 4: {
                        if (keyboard.SetKeyboard(options[ribbSection] + ":", true, rib4Ribbons, ribb) != -1) {
                            if (keyboard.SetKeyboard(rib4Ribbons[ribb] + ":", true, noYes, ribbChoice) != -1) {
                                SetRibbons(pkmn, ribbSection, ribbChoice, ribb);
                            }

                            else goto Start;
                        }

                        else goto Start;
                    }
                    break;

                    case 5: {
                        if (keyboard.SetKeyboard(options[ribbSection] + ":", true, rib5Ribbons, ribb) != -1) {
                            if (keyboard.SetKeyboard(rib5Ribbons[ribb] + ":", true, noYes, ribbChoice) != -1) {
                                SetRibbons(pkmn, ribbSection, ribbChoice, ribb);
                            }

                            else goto Start;
                        }

                        else goto Start;
                    }
                    break;

                    case 6: {
                        if (keyboard.SetKeyboard(options[ribbSection] + ":", true, rib6Ribbons, ribb) != -1) {
                            if (keyboard.SetKeyboard(rib6Ribbons[ribb] + ":", true, noYes, ribbChoice) != -1) {
                                SetRibbons(pkmn, ribbSection, ribbChoice, ribb);
                            }

                            else goto Start;
                        }

                        else goto Start;
                    }
                    break;

                    default:
                        goto Start;
                        break;
                }

                if (SetPokemon(pointer, pkmn)) {
                    Message::Completed();
                }
            }
        }
    }
}