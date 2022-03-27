#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework {
    u16 spwnSpecies; u8 spawnLv, spwnForm;
    int pkmnID;

    /**
    * @brief Gets the Pokémon that matches the first letters of the input
    * @param output The vector where to put the Pokémon that matches the input
    * @param input The input string entered by the user
    * @return The amount of Pokémon that matches the input.
    */
    int MatchPkmn(Pokemon &output, string &input) {
        int index = 0;
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const String &pkmn : allPkmn) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator pokeIterator = pkmn.begin();

            // Parse every letter of input while it matches the Pokémon's name
            while (iterator != lowerCase.end() && pokeIterator != pkmn.end() && *iterator == tolower(*pokeIterator)) {
                ++iterator;
                ++pokeIterator;
            }

            // If we're at the end of input then it matches the Pokémon's name
            if (iterator == lowerCase.end()) {
                output.name.push_back(pkmn);
                output.choiceNo.push_back(index);
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    /**
    * @brief This function will be called by the keyboard everytime the input change
    * @param keyboard The keyboard that called the function
    * @param event The event that changed the input
    */
    void PkmnInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        Pokemon matches;
        int count = MatchPkmn(matches, input), choice;
        pkmnID = matches.choiceNo[choice] + 1;

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError("Type a letter to search for a Pokémon.");
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError("Not enough letters to do the search.");
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            // The choiceNo must be within a valid range depending on the game
            if (pkmnID <= AutoGen(721, AutoGroup(802, 807))) {
                input = matches.name[0];
                return;
            }

            keyboard.SetError("This species is not available. Please try again.");
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            Keyboard populate(matches.name);
            populate.CanAbort(false);
            populate.DisplayTopScreen = false;
            choice = populate.Open();

            if (choice >= 0) {
                // The choiceNo must be within a valid range depending on the game
                if (pkmnID <= AutoGen(721, AutoGroup(802, 807))) {
                    input = matches.name[choice];
                    return;
                }

                keyboard.SetError("This species is not available. Please try again.");
                return;
            }
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError("Too many results: " + to_string(count) + "\nType more letters to narrow down the results.");
    }

    /**
    * @brief A cheat function that needs the user to select a Pokémon before doing something
    * @param entry The entry that called the function
    */
    void FindPkmnKB(MenuEntry *entry) {
        String output;

        if (KB<String>(entry->Name() + ":", true, 11, output, "", PkmnInputChange))
            return;

        else pkmnID = 0;
    }

    int abilityID;

    /**
    * @brief Gets the ability that matches the first letters of the input
    * @param output The vector where to put the ability that matches the input
    * @param input The input string entered by the user
    * @return The amount of ability that matches the input.
    */
    int MatchAbility(Ability &output, string &input) {
        int index = 0;
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const String &ability : allAbilities) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator itemIterator = ability.begin();

            // Parse every letter of input while it matches the ability's name
            while (iterator != lowerCase.end() && itemIterator != ability.end() && *iterator == tolower(*itemIterator)) {
                ++iterator;
                ++itemIterator;
            }

            // If we're at the end of input then it matches the ability's name
            if (iterator == lowerCase.end()) {
                output.name.push_back(ability);
                output.choiceNo.push_back(index);
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    /**
    * @brief This function will be called by the keyboard everytime the input change
    * @param keyboard The keyboard that called the function
    * @param event The event that changed the input
    */
    void AbilityInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        Ability matches;
        int count = MatchAbility(matches, input), choice;
        abilityID = matches.choiceNo[choice] + 1;

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError("Type a letter to search for an ability.");
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError("Not enough letters to do the search.");
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            // The choiceNo must be within a valid range depending on the game
            if (abilityID <= AutoGen(AutoGroup(188, 191), 233)) {
                input = matches.name[0];
                return;
            }

            keyboard.SetError("This ability is not valid. Please try again.");
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            // The choiceNo must be within a valid range depending on the game
            if (abilityID <= AutoGen(AutoGroup(188, 191), 233)) {
                Keyboard populate(matches.name);
                populate.CanAbort(false);
                populate.DisplayTopScreen = false;
                choice = populate.Open();

                if (choice >= 0) {
                    input = matches.name[choice];
                    return;
                }
            }

            keyboard.SetError("This ability is not valid. Please try again.");
            return;
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError("Too many results: " + to_string(count) + "\nType more letters to narrow down the results.");
    }

    /**
    * @brief A cheat function that needs the user to select an ability before doing something
    * @param entry The entry that called the function
    */
    void FindAbilityKB(MenuEntry *entry) {
        String output;

        if (KB<String>(entry->Name() + ":", true, 16, output, "", AbilityInputChange))
            return;

        else abilityID = 0;
    }

    int heldItemID;

    /**
    * @brief Gets the held item that matches the first letters of the input
    * @param output The vector where to put the held item that matches the input
    * @param input The input string entered by the user
    * @return The amount of held item that matches the input.
    */
    int MatchHeldItem(HeldItem &output, string &input) {
        int index = 0;
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const String &item : allItems) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator itemIterator = item.begin();

            // Parse every letter of input while it matches the held item's name
            while (iterator != lowerCase.end() && itemIterator != item.end() && *iterator == tolower(*itemIterator)) {
                ++iterator;
                ++itemIterator;
            }

            // If we're at the end of input then it matches the held item's name
            if (iterator == lowerCase.end()) {
                output.name.push_back(item);
                output.choiceNo.push_back(index);
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    /**
    * @brief This function will be called by the keyboard everytime the input change
    * @param keyboard The keyboard that called the function
    * @param event The event that changed the input
    */
    void ItemInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        HeldItem matches;
        int count = MatchHeldItem(matches, input), countInvalid, choice;
        static const vector<int> ignored = {114, 120, 129, 130, 131, 132, 133, 426, 427, 622, 807, 808, 809, 810, 811, 812, 813, 814, 815, 816, 817, 818, 819, 820, 821, 822, 823, 824, 825, 826, 827, 828, 829, 830, 831, 832, 833, 834, 834, 835, 837, 838, 839, 840, 848, 859, 867, 868, 869, 870, 871, 887, 898, 899, 927, 928, 929, 930, 931, 932};

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError("Type a letter to search for an item.");
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError("Not enough letters to do the search.");
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            // The choiceNo must be within a valid range depending on the game
            if (heldItemID <= AutoGen(AutoGroup(717, 775), AutoGroup(920, 959)) - 59) {
                countInvalid = 0;

                for (int i = 0; i < ignored.size(); i++) {
                    if (matches.choiceNo[0] + 1 > ignored[i])
                        countInvalid++;
                }

                heldItemID = matches.choiceNo[0] + 1 + countInvalid;
                input = matches.name[0];
                return;
            }

            keyboard.SetError("This item is not valid. Please try again.");
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            // The choiceNo must be within a valid range depending on the game
            if (heldItemID <= AutoGen(AutoGroup(717, 775), AutoGroup(920, 959)) - 59) {
                Keyboard kb;
                kb.CanAbort(false);
                kb.DisplayTopScreen = false;
                kb.Populate(matches.name);
                choice = kb.Open();

                if (choice >= 0) {
                    countInvalid = 0;

                    for (int i = 0; i < ignored.size(); i++) {
                        if (matches.choiceNo[choice] + 1 > ignored[i])
                            countInvalid++;
                    }

                    heldItemID = matches.choiceNo[choice] + 1 + countInvalid;
                    input = matches.name[choice];
                    return;
                }
            }

            keyboard.SetError("This item is not valid. Please try again.");
            return;
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError("Too many results: " + to_string(count) + "\nType more letters to narrow down the results.");
    }

    /**
    * @brief A cheat function that needs the user to select a held item before doing something
    * @param entry The entry that called the function
    */
    void FindItemKB(MenuEntry *entry) {
        String output;

        if (KB<String>(entry->Name() + ":", true, 18, output, "", ItemInputChange))
            return;

        else heldItemID = 0;
    }

    int moveID;

    /**
    * @brief Gets the move that matches the first letters of the input
    * @param output The vector where to put the move that matches the input
    * @param input The input string entered by the user
    * @return The amount of move that matches the input.
    */
    int MatchMove(Moves &output, string &input) {
        int index = 0;
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const String &moves : allMoves) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator itemIterator = moves.begin();

            // Parse every letter of input while it matches the move's name
            while (iterator != lowerCase.end() && itemIterator != moves.end() && *iterator == tolower(*itemIterator)) {
                ++iterator;
                ++itemIterator;
            }

            // If we're at the end of input then it matches the move's name
            if (iterator == lowerCase.end()) {
                output.name.push_back(moves);
                output.choiceNo.push_back(index);
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    /**
    * @brief This function will be called by the keyboard everytime the input change
    * @param keyboard The keyboard that called the function
    * @param event The event that changed the input
    */
    void MoveInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        Moves matches;
        int count = MatchMove(matches, input), countInvalid, choice;
        static const vector<int> ignored = {622, 623, 624, 625, 626, 627, 628, 629, 630, 631, 632, 633, 634, 635, 636, 637, 638, 639, 640, 641, 642, 643, 644, 645, 646, 647, 648, 649, 650, 651, 652, 653, 654, 655, 656, 657, 658, 695, 696, 697, 698, 699, 700, 701, 702, 703, 719, 723, 724, 725, 726, 727, 728};

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError("Type a letter to search for a move.");
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError("Not enough letters to do the search.");
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            // The choiceNo must be within a valid range depending on the game
            if (moveID <= AutoGen(AutoGroup(617, 621), AutoGroup(719, 742))) {
                countInvalid = 0;

                for (int i = 0; i < ignored.size(); i++) {
                    if (matches.choiceNo[0] + 1 > ignored[i])
                        countInvalid++;
                }

                moveID = matches.choiceNo[0] + 1 + countInvalid;
                input = matches.name[0];
                return;
            }

            keyboard.SetError("This move is not valid. Please try again.");
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            // The choiceNo must be within a valid range depending on the game
            if (moveID <= AutoGen(AutoGroup(617, 621), AutoGroup(719, 728)) - 53) {
                Keyboard kb(matches.name);
                kb.CanAbort(false);
                kb.DisplayTopScreen = false;
                choice = kb.Open();

                if (choice >= 0) {
                    countInvalid = 0;

                    for (int i = 0; i < ignored.size(); i++) {
                        if (matches.choiceNo[choice] + 1 > ignored[i])
                            countInvalid++;
                    }

                    moveID = matches.choiceNo[choice] + 1 + countInvalid;
                    input = matches.name[choice];
                    return;
                }
            }

            keyboard.SetError("This move is not valid. Please try again.");
            return;
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError("Too many results: " + to_string(count) + "\nType more letters to narrow down the results.");
    }

    /**
    * @brief A cheat function that needs the user to select a move before doing something
    * @param entry The entry that called the function
    */
    void FindMoveKB(MenuEntry *entry) {
        String output;

        if (KB<String>(entry->Name() + ":", true, 27, output, "", MoveInputChange))
            return;

        moveID = 0;
    }
}