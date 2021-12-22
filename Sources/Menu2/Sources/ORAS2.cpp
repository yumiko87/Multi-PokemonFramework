#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"
#include <time.h>

using namespace CTRPluginFramework;

namespace ORAS {
    void PCBackup(MenuEntry *entry) {
        static const u32 address = 0x8C9E134;
        vector<string> listOfFiles, listOfFileNames;
        string extension = ".bin";

        Directory directory(bin);
        directory.ListFiles(listOfFiles, extension);
        listOfFileNames = listOfFiles;
        int index = listOfFileNames.size();

        if (index >= 20) {
            if (MessageBox("Maximum backup limit reached! Would you like to erase all backups?", DialogType::DialogYesNo, ClearScreen::Both)()) {
                for (int i = 0; i < index; i++) {
                    File::Remove(bin + listOfFileNames[i]);
                }

                MessageBox("All backups have been erased.", DialogType::DialogOk, ClearScreen::Both)();
            }
            return;
        }

        time_t rawTime;
        struct tm * timeInfo;
        char timeStamp[80];

        time(&rawTime);
        timeInfo = localtime(&rawTime);
        strftime(timeStamp, 80, "[%F_%I-%M-%S]", timeInfo);
        string fileName = timeStamp + extension;

        int choice;
        static const vector<string> options = {"Export", "Import"};
        KeyboardPlus keyboard;
        keyboard.SetKeyboard(entry->Name() + ":", true, options, choice);

        if (choice <= -1) {
            return;
        }

        if (choice == 0) {
            if (!Directory::IsExists(bin)) {
                Directory::Create(bin);
            }

            if (index <= 20) {
                File dumpFile(bin + fileName, File::RWC);
                dumpFile.Dump(address, 215760);
                MessageBox("Operation has been " << Color::LimeGreen << "completed" << Color::White << "!", DialogType::DialogOk, ClearScreen::Both)();
                return;
            }
        }

        if (choice == 1) {
            if (index == 0) {
                MessageBox("You have 0 backup(s) to recover from!", DialogType::DialogOk, ClearScreen::Both)();
                return;
            }

            if (index >= 1) {
                keyboard.Populate(listOfFileNames);
                int fileIndex = keyboard.Open();

                if (fileIndex >= 0) {
                    File injectFile(bin + listOfFileNames[fileIndex]);
                    injectFile.Inject(address, 215760);
                    MessageBox("Operation has been " << Color::LimeGreen << "completed" << Color::White << "!", DialogType::DialogOk, ClearScreen::Both)();
                    return;
                }

                MessageBox("Operation has been " << Color(255, 51, 51) << "interrupted" << Color::White << "!", DialogType::DialogOk, ClearScreen::Both)();
                return;
            }
        }
    }

    // Thanks to H4x0rSpooky for the assistance of this cheat
    void StealPokemonInTrade(MenuEntry *entry) {
        static const u32 address[3] = {0x8523D14, 0x8523D68, 0x8C9E134};

        // Check if the user is in trade or not
        if (Process::Read32(address[0], data32) && data32 == 0x5544) {
            // Must have the user hold down the hotkey
            if (entry->Hotkeys[0].IsDown()) {
                // Reads if the Pokemon data is empty or not, otherwise copy the offered Pokemon
                if (Process::Read32(address[1], data32) && data32 != 0) {
                    Process::CopyMemory((u8 *)address[2], (u8 *)address[1], 232);
                }
            }
        }
    }

    void PCAnywhere(MenuEntry *entry) {
        static const u32 address = Gen6::Auto(0x3D8748, 0x3D8744);
        static u32 data[1] = {0xE3A00004};
        static u32 original[1] = {0};

        if (entry->IsActivated()) {
            if (Process::Read32(address, data32) && data32 != data[0]) {
                Process::Patch(address, data, 4, original);
            }
        }

        if (!entry->IsActivated()) {
            Process::Patch(address, original, 4);
        }
    }

    void UnlockEveryBox(MenuEntry *entry) {
        static const u32 address = 0x8C7232A;

        if (Process::Read8(address, data8) && data8 < 31) {
            Process::Write8(address, 31);
            MessageBox("Operation has been " << Color::LimeGreen << "completed" << Color::White << "!", DialogType::DialogOk, ClearScreen::Both)();
            return;
        }

        MessageBox("Operation has already been " << Color::Orange << "completed" << Color::White << "!", DialogType::DialogOk, ClearScreen::Both)();
    }
}