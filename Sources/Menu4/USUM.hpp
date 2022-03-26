#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "stdafx.hpp"

#include "Includes/USUM1.hpp"
#include "Includes/USUM2.hpp"
#include "Includes/USUM3.hpp"
#include "Includes/USUM4.hpp"

using namespace CTRPluginFramework;

namespace USUM {
    void Menu(PluginMenu &menu) {
        MenuFolder *battle = new MenuFolder("Battle");
        MenuFolder *primary = new MenuFolder("Primary");
        *primary += new MenuFolder("Active", "Note: must be in a battle to use.", vector<MenuEntry *>({
            new MenuEntry("Condition", nullptr, Condition),
            new MenuEntry("Statistics", Statistics, StatisticsKB),
            new MenuEntry("Invincibility", Invincibility, InvincibilityKB),
            new MenuEntry("Item", nullptr, Item),
            new MenuEntry("Attacks", nullptr, Attacks)
        }));
        *primary += EntryWithHotkey(new MenuEntry("Access Bag", AccessBag, "Note: hold the hotkey(s) below while pressing on an action when in a battle."), {Key::R, ""});
        *primary += new MenuEntry("Always Critical Hit", AlwaysCriticalHit);
        *primary += new MenuEntry("View Enemy Stats", ViewEnemyHP, "Note: tap on the opponent on the bottom screen during a battle."),
        *primary += new MenuEntry("Raise Statuses by 6", RaiseStatusesBy6, "Basically the same as the one in the Statistics cheat, but in ASM.");
        *primary += new MenuEntry("Bypass 1 Mega Restrict.", Bypass1MegaRestrict);
        *primary += new MenuEntry("Infinite Z-Moves", InfiniteZMoves);
        *primary += EntryWithHotkey(new MenuEntry("Z-Moves Without Crystal", ZMovesWithoutCrystal, "Note: activate before battle! When in battle, hold the hotkey(s) below while pressing on an action when in a battle."), {Key::L, ""});
        *battle += primary;
        *battle += new MenuEntry("Always Shiny", AlwaysShiny);
        *battle += new MenuEntry("Guaranteed Catch", GuaranteedCatch);
        *battle += new MenuEntry("Catch Trainer's Pokémon", CatchTrainersPokemon);
        *battle += new MenuEntry("Can Catch Trials", CanCatchTrials);
        *battle += new MenuEntry("Rematch Trainer", RematchTrainer);
        *battle += new MenuEntry("No Trainer Battle", NoTrainerBattle);
        *battle += new MenuFolder("Other", vector<MenuEntry *>({
            new MenuEntry("No Encounters", NoEncounters),
            new MenuEntry("Wild Pokémon", nullptr, WildPokemon, "Note: change locations to reset."),
            new MenuEntry("Rematch Legendaries", RematchLegendaries, RematchLegendariesKB)
        }));
        menu += battle;

        MenuFolder *computer = new MenuFolder("Computer");
        *computer += new MenuEntry("Backup", nullptr, PCBackup);
        MenuFolder *editor = new MenuFolder("Editor");
        *editor += new MenuEntry("Initiate", nullptr, Editor::Initialize, "Note: this is to set up who you would like to modify via the Editor section of the plugin.");
        *editor += new MenuFolder("Primary", vector<MenuEntry *>({
            new MenuEntry("Shiny", nullptr, Editor::Shinify),
            new MenuEntry("Species", nullptr, Editor::Species),
            new MenuEntry("Is Nicknamed", nullptr, Editor::IsNicknamed),
            new MenuEntry("Nickname", nullptr, Editor::Nickname),
            new MenuEntry("Experience", nullptr, Editor::Experience),
            new MenuEntry("Nature", nullptr, Editor::Nature),
            new MenuEntry("Gender", nullptr, Editor::Gender),
            new MenuEntry("Form", nullptr, Editor::Form),
            new MenuEntry("Held Item", nullptr, Editor::HeldItem),
            new MenuEntry("Ability", nullptr, Editor::Ability),
            new MenuEntry("Friendship", nullptr, Editor::Friendship),
            new MenuEntry("Language", nullptr, Editor::Language),
            new MenuEntry("Is Egg", nullptr, Editor::IsEgg),
            new MenuEntry("Pokerus", nullptr, Editor::Pokerus),
            new MenuEntry("Country", nullptr, Editor::Country),
            new MenuEntry("Region"),
            new MenuEntry("3DS Region", nullptr, Editor::ConsoleRegion)
        }));
        *editor += new MenuFolder("Obtained", vector<MenuEntry *>({
            new MenuEntry("Origin Game", nullptr, Editor::OriginGame),
            new MenuEntry("Met Location", nullptr, Editor::MetLocation),
            new MenuEntry("Ball", nullptr, Editor::Ball),
            new MenuEntry("Met Level", nullptr, Editor::MetLevel),
            new MenuEntry("Met Date", nullptr, Editor::MetDate),
            new MenuEntry("Is Fateful Encounter", nullptr, Editor::IsFatefulEncounter),
            new MenuEntry("Egg Met Location", nullptr, Editor::EggMetLoc),
            new MenuEntry("Egg Met Date", nullptr, Editor::EggMetDate)
        }));
        *editor += new MenuFolder("Stats", vector<MenuEntry *>({
            new MenuEntry("IVs", nullptr, Editor::IVs),
            new MenuEntry("EVs", nullptr, Editor::EVs),
            new MenuEntry("Contest", nullptr, Editor::Contest)
        }));
        *editor += new MenuFolder("Attacks", vector<MenuEntry *>({
            new MenuEntry("Cuurent Moves", nullptr, Editor::CurrentMoves),
            new MenuEntry("PP Ups", nullptr, Editor::PPUps),
            new MenuEntry("Relearn Moves", nullptr, Editor::RelearnMoves)
        }));
        *editor += new MenuFolder("Other", vector<MenuEntry *>({
            new MenuEntry("SID", nullptr, Editor::SID),
            new MenuEntry("TID", nullptr, Editor::TID),
            new MenuEntry("OT Name", nullptr, Editor::OTName),
            new MenuEntry("Latest (not OT) Handler", nullptr, Editor::LatestHandler),
            new MenuEntry("Ribbons", nullptr, Editor::Ribbons)
        }));
        *editor += new MenuEntry("Cloning", nullptr, Editor::Cloning);
        *computer += editor;
        *computer += new MenuEntry("PC Anywhere", PCAnywhere);
        *computer += new MenuEntry("Unlock Every Box", nullptr, UnlockEveryBox);
        menu += computer;

        MenuFolder *movement = new MenuFolder("Movement", vector<MenuEntry *>({
            new MenuEntry("Time of Day", nullptr, TimeOfDay),
            new MenuEntry("Speed Up", Speedx2, "Note: only applies to walk and run speeds."),
            new MenuEntry("Bypass Walls", BypassWalls),
            EntryWithHotkey(new MenuEntry("Camera Zoom Out", CameraZoomOut), {Hotkey(Key::L, "Zoom-Out"), Hotkey(Key::R, "Zoom-In")}),
            new MenuEntry("Register Mounts", nullptr, RegisterMounts, "Note: all mounts will be registered and unlocked despite not reaching a certain point of the story.")
        }));
        menu += movement;

        MenuFolder *misc = new MenuFolder("Misc");
        *misc += new MenuFolder("Pokémon", vector<MenuEntry *>({
            new MenuEntry("Is Renamable", IsRenamable, "Note: you will be able to rename any Pokémon despite it not being at your ownership."),
            new MenuEntry("Learn Any Teachables", LearnAnyTeachables, "Note: you will be able to teach your Pokémon any moves."),
            new MenuEntry("Fast Offspring", FastOffspring, "Note: produces Pokémon faster in Day Care."),
            new MenuEntry("Instant Egg Hatch", InstantEggHatch),
            new MenuEntry("Quick Friendship", QuickFriendship),
            EntryWithHotkey(new MenuEntry("View Values in Summary", ViewValuesInSummary, "Note: hold one of the following hotkey(s) to view your Individual and Effort Values."), {Hotkey(Key::L, ""), Hotkey(Key::R, "")}),
            EntryWithHotkey(new MenuEntry("Steal Pokémon in Trade", StealPokemonInTrade, "Note: This will overwrite any Pokémon sitting in slot 1 of box 1. If you understand, you may press on the following hotkeys."), {Hotkey(Key::Start, "")})
        }));
        *misc += new MenuEntry("Remove Outlines", NoOutlines, "Note: removes outlines in the overworld and in battles.");
        *misc += new MenuEntry("Fast Dialogs", FastDialogs, "Note: game dialogs will be sped up.");
        *misc += new MenuEntry("No Player Shadow", NoPlayerShadow);
        menu += misc;
    }
}