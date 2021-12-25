#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace ORAS {
    void Speedx2(MenuEntry *entry) {
        static const u32 address[2] = {0x80845E8, 0x808475C};
        static u32 data[2][2] = {{0x13A05003, 0x3A05002}, {0x13A05005, 0x3A05003}};
        static u32 original[2][2] = {{0, 0}, {0, 0}};

        if (!Gen6::IsInBattle()) {
            for (int i = 0; i < 2; i++) {
                CRO::Force(address[i]);
            }

            if (entry->IsActivated()) {
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 2; k++) {
                        if (Process::Read32(address[j] + (k * 4), data32) && data32 != data[j][k]) {
                            Process::Patch(address[j], data[j], 8, original[j]);
                        }
                    }
                }
            }

            if (!entry->IsActivated() || !Controller::GetKeysDown()) {
                Recover:
                    for (int l = 0; l < 2; l++) {
                        Process::Patch(address[l], original[l], 8);
                    }
            }
        }

        else {
            goto Recover;
        }
    }

    void BypassWalls(MenuEntry *entry) {
        static const u32 address[2] = {0x80BB414, 0x80B87F8};
        static u32 data[2][1] = {{0xE3A01000}, {0xE3A06000}};
        static u32 original[2][1] = {{0}, {0}};

        if (!Gen6::IsInBattle()) {
            for (int i = 1; i < 2; i++) {
                CRO::Force(address[i]);
            }

            if (entry->IsActivated()) {
                for (int j = 0; j < 2; j++) {
                    if (Process::Read32(address[j], data32) && data32 != data[j][0]) {
                        Process::Patch(address[j], data[j], 4, original[j]);
                    }
                }
            }

            if (!entry->IsActivated() || !Controller::GetKeysDown()) {
                Recover:
                    for (int l = 0; l < 2; l++) {
                        Process::Patch(address[l], original[l], 4);
                    }
            }
        }

        else {
            goto Recover;
        }
    }

    void FlyAnywhere(MenuEntry *entry) {
        static const u32 address = 0x8C69330;

        if (Process::Read32(address, data32) && data32 == 0x7007C0) {
            Process::Write32(address, 0x700C38);
        }
    }

    struct Locations {
        int direction;
        const char *name;
        int value;
        float xCoord;
        float yCoord;
    };

    const Locations locations[36] = {
        {0, "Ancient Tomb", 0x9F, 225, 333},
        {0, "Battle Resort", 0x206, 351, 441},
        {0, "Cave of Origin", 0x70, 333, 621},
        {0, "Day Care", 0x187, 225, 333},
        {0, "Desert Ruins", 0x4D, 225, 333},
        {0, "Dewford Town", 0xE8, 351, 441},
        {0, "Ever Grande City", 0x161, 351, 441},
        {0, "Fabled Cave", 0x20F, 387, 693},
        {0, "Fallarbor Town", 0xF0, 351, 441},
        {0, "Fortree City", 0x12D, 351, 441},
        {0, "Gnarled Den", 0x210, 369, 657},
        {0, "Granite Cave", 0x4E, 531, 639},
        {0, "Island Cave", 0x9E, 225, 333},
        {0, "Lilycove City", 0x135, 351, 441},
        {0, "Littleroot Town", 0xDF, 297, 333},
        {0, "Mauville City", 0x116, 351, 441},
        {0, "Meteor Falls", 0x47, 1035, 639},
        {0, "Mossdeep City", 0x14A, 351, 441},
        {0, "Nameless Cavern", 0x20E, 369, 657},
        {0, "New Mauville", 0x8B, 369, 657},
        {0, "Odale Town", 0xE4, 351, 441},
        {0, "Pacifidlog Town", 0xFD, 351, 441},
        {0, "Petalburg City", 0x103, 351, 441},
        {0, "Petalburg Woods", 0x52, 531, 1161},
        {0, "Pokémon League", 0x16C, 297, 387},
        {0, "Rustboro City", 0x11C, 351, 441},
        {0, "Rusturf Tunnel", 0x4B, 261, 369},
        {0, "Scorched Slab", 0xA7,261, 459},
        {1, "Sea Mauville", 0x92, 369, 45},
        {0, "Sealed Chambers", 0xA3, 801, 1305},
        {0, "Secret Meadow", 0x1DB, 387, 657},
        {0, "Sky Pillar", 0xB0, 639, 981},
        {0, "Slateport City", 0x109, 351, 441},
        {0, "Sootopolis City", 0x155, 351, 441},
        {0, "Verdanturf Town", 0xF6, 351, 441},
        {0, "Victory Road", 0x7B, 387, 855}
    };

    static int locID, place, direction;
    static float coords[2] = {0, 0};

    void WarperKB(MenuEntry *entry) {
        static vector<string> options;

        if (options.empty()) {
            for (const Locations &nickname:locations) {
                options.push_back(nickname.name);
            }
        }

        KeyboardPlus keyboard;

        if (keyboard.SetKeyboard(entry->Name() + ":", true, options, locID) != -1) {
            place = locations[locID].value;
            direction = locations[locID].direction;
            coords[0] = locations[locID].xCoord;
            coords[1] = locations[locID].yCoord;
        }
    }

    void Warper(MenuEntry *entry) {
        static const u32 address[5] = {0x8803BCA, 0x8803C20, 0x8C6E886, 0x8C6E894, 0x8C6E89C};

        if (entry->Hotkeys[0].IsDown()) {
            if (place > 0) {
                if (Process::Read16(address[1], data16) && data16 == 0x5544) {
                    if (Process::Write16(address[0], place)) {
                        if (Process::Write8(address[2], direction)) {
                            for (int i; i < 2; i++) {
                                Process::WriteFloat(address[i + 3], coords[i]);
                            }
                        }
                    }
                }
            }
        }
    }

    void RegisterLocations(MenuEntry *entry) {
        static const u32 address = 0x8C81F24;
        static u8 flags[2][10] = {{0xC, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0x8}, {0xA, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0x3, 0xB, 0x1}};

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 10; j++) {
                if (Bit::Read(address + j, data8, i) && data8 != flags[i][j]) {
                    Bit::Edit(address + j, flags[i][j], i);
                }
            }
        }

        Message::Completed();
    }
}