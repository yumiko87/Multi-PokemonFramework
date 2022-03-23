#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework {
    u32 pokePointer;

    u32 GetPokePointer(void) {
        if (group == Group::XY) {
            pokePointer = 0x8C861C8;
        }

        if (group == Group::ORAS) {
            pokePointer = 0x8C9E134;
        }

        if (group == Group::SM) {
            pokePointer = 0x330D9838;
        }

        if (group == Group::USUM) {
            pokePointer = 0x33015AB0;
        }

        return pokePointer;
    }

    void Unshuffle(u8 *shuffled, u8 *poke, u32 sv) {
        Process::CopyMemory(poke, shuffled, 232);

        for (short block = 0; block < 4; block++) {
            for (short i = 0; i < 56; i++) {
                *(poke + i + 8 + 56 * block) = *(shuffled + i + 8 + 56 * blockPosition[block][sv]);
            }
        }
    }
}