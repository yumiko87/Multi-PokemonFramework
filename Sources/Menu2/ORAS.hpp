#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "stdafx.hpp"

#include "Includes/ORAS1.hpp"
#include "Includes/ORAS2.hpp"
#include "Includes/ORAS3.hpp"
#include "Includes/ORAS4.hpp"

using namespace CTRPluginFramework;

namespace ORAS {
    void Menu(PluginMenu &menu) {
        MenuFolder *battle = new MenuFolder("Battle"); {
            *battle += new MenuFolder("Primary", vector<MenuEntry *>({
                EntryWithHotkey(new MenuEntry("Access Bag", AccessBag, "Note: hold the hotkey(s) below while pressing on an action when in a battle."), {Key::R, ""}),
                new MenuEntry("Infinite Mega Evolution", InfiniteMegaEvolution)
            }));

            *battle += new MenuEntry("Always Shiny", AlwaysShiny);
            *battle += new MenuEntry("Guaranteed Catch", GuaranteedCatch);
            *battle += new MenuEntry("Catch Trainer's Pokémon", CatchTrainersPokemon);

            *battle += new MenuFolder("Other", vector<MenuEntry *>({
                new MenuEntry("No Encounters", NoEncounters),
                new MenuEntry("Wild Pokémon", nullptr, WildPokemon, "Note: change locations to reset."),
                new MenuEntry("Rematch Legendaries", RematchLegendaries, RematchLegendariesKB)
            }));
        }

        menu += battle;

        MenuFolder *computer = new MenuFolder("Computer"); {
            *computer += new MenuEntry("Backup", nullptr, PCBackup);
        }

        MenuFolder *editor = new MenuFolder("Editor"); {
            *editor += new MenuEntry(Color::Orange << "Intialize", nullptr, Editor::Initialize),

            *editor += new MenuFolder("Primary", vector<MenuEntry *>({
                new MenuEntry("Species", nullptr, Editor::Species),
                new MenuEntry("Form", nullptr, Editor::Form),
                new MenuEntry("Shinify", nullptr, Editor::Shinify)
            }));
        }

        *computer += editor;

        *computer += new MenuEntry("PC Anywhere", PCAnywhere);
        *computer += new MenuEntry("Unlock Every Box", nullptr, UnlockEveryBox);

        menu += computer;

        MenuFolder *movement = new MenuFolder("Movement", vector<MenuEntry *>({
            new MenuEntry("Speed Up", Speedx2, "Note: only applies to walk and run speeds."),
            new MenuEntry("Bypass Walls", BypassWalls),
            new MenuEntry("Fly Anywhere", FlyAnywhere, "Note: you must click on a Pokémon's summary."),
            EntryWithHotkey(new MenuEntry("Warper", Warper, WarperKB, "Note: hold the hotkey(s) below while moving."), {Key::L, ""}),
            new MenuEntry("Register Locations", nullptr, RegisterLocations)
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
                EntryWithHotkey(new MenuEntry("Steal Pokémon in Trade", StealPokemonInTrade, "Note: This will overwrite any Pokémon sitting in slot 1 of box 1. If you understand, you may press on the following hotkeys."), {Hotkey(Key::Start, "")})
            }));

            *misc += new MenuEntry("Remove Outlines", NoOutlines);
            *misc += new MenuEntry("Fast Dialogs", FastDialogs);
        }

        menu += misc;
    }
}