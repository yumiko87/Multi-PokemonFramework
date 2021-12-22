#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "stdafx.hpp"

#include "Includes/SM1.hpp"
#include "Includes/SM2.hpp"
#include "Includes/SM3.hpp"
#include "Includes/SM4.hpp"

using namespace CTRPluginFramework;

namespace SM {
    void Menu(PluginMenu &menu) {
        MenuFolder *battle = new MenuFolder("Battle"); {
            *battle += new MenuFolder("Primary", vector<MenuEntry *>({
                // new MenuEntry("God Mode"),
                EntryWithHotkey(new MenuEntry("Access Bag", AccessBag, "Note: hold the hotkey(s) below while pressing on an action when in a battle."), {Key::R, ""}),
                new MenuEntry("Always Critical Hit", AlwaysCriticalHit),
                new MenuEntry("Raise Statuses by 6", RaiseStatusesBy6),
                new MenuEntry("Bypass 1 Mega Restrict.", Bypass1MegaRestrict),
                new MenuEntry("Infinite Z-Moves", InfiniteZMoves),
                EntryWithHotkey(new MenuEntry("Z-Moves Without Crystal", ZMovesWithoutCrystal, "Note: hold the hotkey(s) below while pressing on an action when in a battle."), {Key::L, ""})
            }));

            *battle += new MenuEntry("Always Shiny", AlwaysShiny);
            *battle += new MenuEntry("Guaranteed Catch", GuaranteedCatch);
            *battle += new MenuEntry("Catch Trainer's Pokémon", CatchTrainersPokemon);
            *battle += new MenuEntry("Rematch Trainer", RematchTrainer);
            *battle += new MenuEntry("No Trainer Battle", NoTrainerBattle);

            *battle += new MenuFolder("Other", vector<MenuEntry *>({
                new MenuEntry("View Enemy Stats", ViewEnemyHP),
                EntryWithHotkey(new MenuEntry("No Encounters", NoEncounters, "Note: hold the hotkey(s) below while pressing on an action when in a battle."), {Key::Start, ""}),
                new MenuEntry("Wild Pokémon", nullptr, WildPokemon, "Note: change locations to reset."),
                new MenuEntry("Can Catch Trials", CanCatchTrials),
                new MenuEntry("Rematch Legendaries", RematchLegendaries, RematchLegendariesKB)
            }));
        }

        menu += battle;

        MenuFolder *computer = new MenuFolder("Computer"); {
            *computer += new MenuEntry("Backup", nullptr, PCBackup);

            *computer += new MenuFolder("Modificator", vector<MenuEntry *>({
                EntryWithHotkey(new MenuEntry("Steal Pokémon in Trade", StealPokemonInTrade, "Note: This will overwrite any Pokémon sitting in slot 1 of box 1. If you understand, you may press on the following hotkeys."), {Hotkey(Key::Start, "")})
            }));

            *computer += new MenuEntry("PC Anywhere", PCAnywhere);
            *computer += new MenuEntry("Unlock Every Box", nullptr, UnlockEveryBox);
        }

        menu += computer;

        MenuFolder *movement = new MenuFolder("Movement", vector<MenuEntry *>({
            new MenuEntry("Time of Day", nullptr, TimeOfDay),
            new MenuEntry("Speed Up", Speedx2, "Note: only applies to walk and run speeds."),
            new MenuEntry("Bypass Walls", BypassWalls),
            EntryWithHotkey(new MenuEntry("Camera Zoom Out", CameraZoomOut), {Hotkey(Key::L, "Zoom-Out"), Hotkey(Key::R, "Zoom-In")}),
            new MenuEntry("Register Mounts", nullptr, RegisterMounts)
        }));

        menu += movement;

        MenuFolder *misc = new MenuFolder("Misc"); {
            *misc += new MenuFolder("Pokémon", vector<MenuEntry *>({
                new MenuEntry("Is Renamable", IsRenamable),
                new MenuEntry("Learn Any Teachables", LearnAnyTeachables),
                new MenuEntry("Fast Offspring", FastOffspring),
                new MenuEntry("Instant Egg Hatch", InstantEggHatch),
                new MenuEntry("Quick Friendship", QuickFriendship),
                EntryWithHotkey(new MenuEntry("View Values in Summary", ViewValuesInSummary, "Note: hold one of the following hotkey(s) to view your Individual and Effort Values."), {Hotkey(Key::L, ""), Hotkey(Key::R, "")}),
            }));

            *misc += new MenuEntry("Remove Outlines", NoOutlines);
            *misc += new MenuEntry("Fast Dialogs", FastDialogs);
            *misc += new MenuEntry("No Player Shadow", NoPlayerShadow);
        }

        menu += misc;
    }
}