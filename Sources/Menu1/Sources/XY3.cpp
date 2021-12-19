#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace XY {
    void Speedx2(MenuEntry *entry) {
        static const u32 address[2] = {0x8092DE4, 0x8092F34};
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
        static const u32 address[2] = {Gen6::Auto(0x80B5820, 0x80B5824), Gen6::Auto(0x80B3A1C, 0x80B3A20)};
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
        static const u32 address = 0x8C61CF0;
        
        if (Process::Read32(address, data32) && data32 == 0x6B65C4) {
            Process::Write32(address, 0x6B6A30);
        }
    }
    
    struct Locations {
        int direction;
        const char *name;
        int value;
        float xCoord;
        float yCoord;
    };
    
    Locations locations[27] = {
        {0, "Ambrette Town", 0x2F, 369, 495},
        {0, "Anistar City", 0xD6, 369, 495},
        {0, "Camphrier Town", 0xD, 369, 495},
        {0, "Coumarine City", 0xBE, 369, 495},
        {0, "Couriway Town", 0x28, 369, 495},
        {0, "Cyllage City", 0x9F, 369, 495},
        {0, "Day Care", 0x109, 225, 351},
        {0, "Dendemille Town", 0x21, 369, 495},
        {0, "Friend Safari", 0x163, 153, 315},
        {0, "Geosenge Town", 0x18, 369, 495},
        {0, "Kiloude City", 0xEA, 369, 495},
        {0, "Laverre City", 0xCA, 369, 495},
        {0, "Lumiose City", 0x167, 369, 495},
        {0, "Poké Ball Factory", 0x136, 279, 621},
        {0, "Pokémon Lab", 0x53, 207, 261},
        {0, "Pokémon League", 0xF4, 369, 495},
        {0, "Radiant Chamber", 0x100, 351, 423},
        {0, "Santalune City", 0x36, 369, 495},
        {0, "Santalune Forest", 0x11E, 729, 1359},
        {0, "Sea Spirit's Den", 0x15F, 333, 405},
        {0, "Shalour City", 0xAE, 369, 495},
        {0, "Snowbelle City", 0xE1, 369, 495},
        {0, "Team Flare HQ", 0x155, 711, 891},
        {0, "Terminus Cave", 0x15A, 765, 693},
        {0, "Unknown Dungeon", 0x13F, 351, 567},
        {0, "Vanville Town", 0x2, 369, 495},
        {0, "Video Studio", 0x6B, 315, 585}
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
        static const u32 address[5] = {0x8803BCA, 0x8803C20, 0x8C67192, 0x8C671A0, 0x8C671A8};
        
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
        static const u32 address = 0x8C7A81C;
        static u8 flags[2][3] = {{0xF, 0xF, 0x0}, {0x7, 0xF, 0xF}};
        
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                if (Bit::Read(address + j, data8, i) && data8 != flags[i][j]) {
                    Bit::Edit(address + j, flags[i][j], i);
                }
            }
        }
        
        MessageBox("Operation has been " << Color::LimeGreen << "completed" << Color::White << "!", DialogType::DialogOk, ClearScreen::Both)();
    }
}