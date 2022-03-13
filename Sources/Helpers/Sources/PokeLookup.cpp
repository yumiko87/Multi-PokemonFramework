#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework
{
    u16 spwnSpecies;
    u8 spawnLv, spwnForm;

    int pkmnID;

    /**
    * @brief Gets the Pokémon that matches the first letters of the input
    * @param output The vector where to put the Pokémon that matches the input
    * @param input The input string entered by the user
    * @return The amount of Pokémon that matches the input.
    */
    int GetPokemonMatches(Pokemon &output, string &input) {
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase) {
            character = tolower(character);
        }

        int index = 0;

        // Parse our possibilities to find the matches
        for (const string &pkmn : allPkmn) {
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
    void OnPokemonInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();

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

        Pokemon matches;
        int count = GetPokemonMatches(matches, input);

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        int choice;
        pkmnID = matches.choiceNo[choice] + 1;

        // If we have only one matches, complete the input
        if (count == 1) {
            // The choiceNo must be within a valid range depending on the game
            if (pkmnID <= (group == Group::XY || group == Group::ORAS ? 721 : 802)) {
                input = matches.name[0];
                return;
            }

            keyboard.SetError("This species is not valid. Please try again.");
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
                if (pkmnID <= (group == Group::XY || group == Group::ORAS ? 721 : 802)) {
                    input = matches.name[choice];
                    return;
                }

                keyboard.SetError("This species is not valid. Please try again.");
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
    void SelectAPokemon(MenuEntry *entry) {
        string output;
        Keyboard keyboard(entry->Name() + ":");
        keyboard.SetMaxLength(11);
        keyboard.OnKeyboardEvent(OnPokemonInputChange);

        if (keyboard.Open(output) >= 0) {
            return;
        }

        pkmnID = -1;
        return;
    }

    int abilityID;

    int lastAbility(void) {
        if (group == Group::XY) {
            return 188;
        }
        return 191;
    }

    /**
    * @brief Gets the ability that matches the first letters of the input
    * @param output The vector where to put the ability that matches the input
    * @param input The input string entered by the user
    * @return The amount of ability that matches the input.
    */
    int GetAbilityMatches(Ability &output, string &input) {
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase) {
            character = tolower(character);
        }

        int index = 0;

        // Parse our possibilities to find the matches
        for (const string &ability : allAbilities) {
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
    void OnAbilityInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();

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

        Ability matches;
        int count = GetAbilityMatches(matches, input);

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        int choice;
        abilityID = matches.choiceNo[choice];

        // If we have only one matches, complete the input
        if (count == 1) {
            // The choiceNo must be within a valid range depending on the game
            if (abilityID <= (group == Group::SM || group == Group::USUM ? 233 : lastAbility())) {
                input = matches.name[0];
                return;
            }

            keyboard.SetError("This ability is not valid. Please try again.");
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            // The choiceNo must be within a valid range depending on the game
            if (abilityID <= (group == Group::SM || group == Group::USUM ? 233 : lastAbility())) {
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
    void SelectAnAbility(MenuEntry *entry) {
        string output;
        Keyboard keyboard(entry->Name() + ":");
        keyboard.SetMaxLength(16);
        keyboard.OnKeyboardEvent(OnAbilityInputChange);

        if (keyboard.Open(output) >= 0) {
            Message::Completed();
            return;
        }

        Message::Interrupted();
        abilityID = -1;
        return;
    }

    int heldItemID;

    int LastHeldItemG6(void) {
        if (group == Group::XY) {
            return 717;
        }
        return 775;
    }

    int LastHeldItemG7(void) {
        if (group == Group::SM) {
            return 920;
        }
        return 959;
    }

    /**
    * @brief Gets the held item that matches the first letters of the input
    * @param output The vector where to put the held item that matches the input
    * @param input The input string entered by the user
    * @return The amount of held item that matches the input.
    */
    int GetHeldItemMatches(HeldItem &output, string &input) {
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase) {
            character = tolower(character);
        }

        int index = 0;

        // Parse our possibilities to find the matches
        for (const string &item : allHeldItems) {
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
    void OnItemInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();

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

        HeldItem matches;
        int count = GetHeldItemMatches(matches, input);

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        int choice;
        heldItemID = matches.choiceNo[choice];

        // If we have only one matches, complete the input
        if (count == 1) {
            // The choiceNo must be within a valid range depending on the game
            if (heldItemID <= (group == Group::SM || group == Group::USUM ? LastHeldItemG7() : LastHeldItemG6())) {
                input = matches.name[0];
                return;
            }

            keyboard.SetError("This item is not valid. Please try again.");
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            // The choiceNo must be within a valid range depending on the game
            if (heldItemID <= (group == Group::SM || group == Group::USUM ? LastHeldItemG7() : LastHeldItemG6())) {
                if (matches.name[choice] == matches.name[choice + 1] || matches.name[choice] == matches.name[choice - 1]) {
                    input = matches.name[choice];
                    return;
                }

                Keyboard populate(matches.name);
                populate.CanAbort(false);
                populate.DisplayTopScreen = false;
                choice = populate.Open();

                if (choice >= 0) {
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
    void SelectAHeldItem(MenuEntry *entry) {
        string output;
        Keyboard keyboard(entry->Name() + ":");
        keyboard.SetMaxLength(18);
        keyboard.OnKeyboardEvent(OnItemInputChange);

        if (keyboard.Open(output) >= 0) {
            Message::Completed();
            return;
        }

        Message::Interrupted();
        heldItemID = -1;
        return;
    }

    int moveID;

    int LastMoveG6(void) {
        if (group == Group::XY) {
            return 617;
        }
        return 621;
    }

    int LastMoveG7(void) {
        if (group == Group::SM) {
            return 719;
        }
        return 742;
    }

    /**
    * @brief Gets the move that matches the first letters of the input
    * @param output The vector where to put the move that matches the input
    * @param input The input string entered by the user
    * @return The amount of move that matches the input.
    */
    int GetMoveMatches(Moves &output, string &input) {
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase) {
            character = tolower(character);
        }

        int index = 0;

        // Parse our possibilities to find the matches
        for (const string &moves : allMoves) {
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
    void OnMovesInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();

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

        Moves matches;
        int count = GetMoveMatches(matches, input);

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        int choice;
        moveID = matches.choiceNo[choice];

        // If we have only one matches, complete the input
        if (count == 1) {
            // The choiceNo must be within a valid range depending on the game
            if (moveID <= (group == Group::SM || group == Group::USUM ? LastMoveG7() : LastMoveG6())) {
                input = matches.name[0];
                return;
            }

            else {
                keyboard.SetError("This move is not valid. Please try again.");
                return;
            }
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            // The choiceNo must be within a valid range depending on the game
            if (moveID <= (group == Group::SM || group == Group::USUM ? LastMoveG7() : LastMoveG6())) {
                if (matches.name[choice] == matches.name[choice + 1] || matches.name[choice] == matches.name[choice - 1]) {
                    input = matches.name[choice];
                    return;
                }

                else {
                    Keyboard populate(matches.name);
                    populate.CanAbort(false);
                    populate.DisplayTopScreen = false;
                    choice = populate.Open();

                    if (choice >= 0) {
                        input = matches.name[choice];
                        return;
                    }
                }
            }

            else {
                keyboard.SetError("This move is not valid. Please try again.");
                return;
            }
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError("Too many results: " + to_string(count) + "\nType more letters to narrow down the results.");
    }

    /**
    * @brief A cheat function that needs the user to select a move before doing something
    * @param entry The entry that called the function
    */
    void SelectAMove(MenuEntry *entry) {
        string output;
        Keyboard keyboard(entry->Name() + ":");
        keyboard.SetMaxLength(27);
        keyboard.OnKeyboardEvent(OnMovesInputChange);

        if (keyboard.Open(output) >= 0) {
            Message::Completed();
            return;
        }

        Message::Interrupted();
        moveID = -1;
        return;
    }
}