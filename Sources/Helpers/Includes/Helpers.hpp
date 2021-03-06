#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Keyboard.hpp"
#include "HotkeyHelpers.hpp"

#define REPO "https://github.com/Jared0714/Multi-PokemonFramework"

namespace CTRPluginFramework {
    class ProcessPlus {
        public:
            static void Write8(u32 address, u8 value);
            static void Write16(u32 address, u16 value);
            static void Write32(u32 address, u32 value);

            static u8 Read8(u32 address);
            static u16 Read16(u32 address);
            static u32 Read32(u32 address);
    };

    // Thanks to Lukas (RedShyGuy) for these functions
    namespace CRO {
        bool Toggle(u32 address, bool toggle);
        bool Edit(u32 address, u32 value);
        bool Force(u32 address);
    }

    // Thanks to Lukas (RedShyGuy) for these functions
    namespace Bit {
        bool Read(u32 address, u8 &value, bool rightSide);
        bool Edit(u32 address, u8 value, bool rightSide);
    }

    namespace Message {
        void Completed(void);
        void Interrupted(void);
        void Warning(void);
    }

    namespace Gen6 {
        StringVector FindForms(int pokeNo);
        bool IsInBattle(void);
    };

    namespace Gen7 {
        StringVector FindForms(int pokeNo);
        bool IsInBattle(void);
    };

    enum class Game : int {
        None,
        X,
        Y,
        OR,
        AS,
        S,
        M,
        US,
        UM
    };

    enum class Group : int {
        None,
        XY,
        ORAS,
        SM,
        USUM
    };

    enum class Version : int {
        Unsupported,
        Supported
    };

    extern u8 data8, offset8; extern u16 data16, offset16; extern u32 data32, offset32;
    extern Game game; extern Group group; extern Version version;
    extern string bin, path;

    extern bool IsCompatible(void);
    extern bool IsOnWhiteList(void);

    extern int AutoGroup(int data1, int data2);
    extern StringVector AutoGroup(StringVector vect1, StringVector vect2);
    extern u32 AutoGame(u32 address1, u32 address2);
    extern string AutoGame(string name1, string name2);
    extern u32 AutoGen(u32 autoGame1, u32 autoGame2);
    extern StringVector AutoGen(StringVector vect1, StringVector vect2);
}

#include "PokeInfo.hpp"
#include "PokeLookup.hpp"
#include "Editor.hpp"

#endif