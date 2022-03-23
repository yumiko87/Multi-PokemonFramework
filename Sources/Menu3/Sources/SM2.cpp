#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"
#include <time.h>

using namespace CTRPluginFramework;

namespace SM {
    void PCBackup(MenuEntry *entry) {
        static const u32 address = 0x330D9838;
        StringVector listOfFiles, listOfFileNames;
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
        static const StringVector options = {"Export", "Import"};
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
                dumpFile.Dump(address, 222720);
                Message::Completed();
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
                    injectFile.Inject(address, 222720);
                    Message::Completed();
                    return;
                }

                Message::Interrupted();
                return;
            }
        }
    }

    // Thanks to H4x0rSpooky for the assistance of this cheat
    void StealPokemonInTrade(MenuEntry *entry) {
        static const u32 address[3] = {0x32A87098, 0x32A870C8, 0x330D9838};

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
        static const u32 address[4] = {0x597878, 0x37E5E4, 0x374C3C, 0x5978A8};
        static u32 original[3][1] = {{0}, {0}, {0}};
        static u32 patch[37] = {
            0xE92D400E, 0xE59F1074, 0xE5912000, 0xE3A03000, 0xE5813000, 0xE3A03C13, 0xE2833093, 0xE1520003, 0x03A04000, 0x11A04000, 0xE8BD800E, 0xE350000E, 0xEAF77958, 0xE92D400F, 0xE24DD010, 0xE3A00000, 0xE58D0000,
            0xE58D0004, 0xE58D0008, 0xE58D000C, 0xE1A03000, 0xE1A02000, 0xE3A01C13, 0xE2811093, 0xE59F0018, 0xE5801000, 0xE59F0014, 0xE5900000, 0xEBF7D6DC, 0xE3A00002, 0xE28DD010, 0xE8BD800F, 0x00638000, 0x006740BC,
            0xEB0864A3, 0xEB088B18, 0x1AF77958
        };

        if (entry->IsActivated()) {
            for (int i = 0; i < 34; i++) {
                if (Process::Read32(address[0] + (i * 4), data32) && data32 != patch[i]) {
                    Process::Patch(address[0], patch, 0x88);
                }
            }

            for (int j = 1; j < 4; j++) {
                if (Process::Read32(address[j], data32) && data32 != patch[33 + j]) {
                    Process::Patch(address[j], patch[33 + j], original[j - 1]);
                }
            }
        }

        if (!entry->IsActivated()) {
            for (int k = 0; k < 34; k++) {
                Process::Patch(address[0], 0, 0x88);
            }

            for (int l = 1; l < 4; l++) {
                Process::Patch(address[l], original[l - 1], 4);
            }
        }
    }

    void UnlockEveryBox(MenuEntry *entry) {
        static const u32 address = 0x330D982D;

        if (Process::Read8(address, data8) && data8 < 32) {
            Process::Write8(address, 32);
            Message::Completed();
            return;
        }

        Message::Warning();
    }
}