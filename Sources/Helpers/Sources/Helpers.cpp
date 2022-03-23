#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "stdafx.hpp"

namespace CTRPluginFramework
{
    void ProcessPlus::Write8(u32 address, u8 value) {
        *(volatile unsigned char *)(address) = value;
    }

    void ProcessPlus::Write16(u32 address, u16 value) {
        *(volatile unsigned short *)(address) = value;
    }

    void ProcessPlus::Write32(u32 address, u32 value) {
        *(volatile unsigned int *)(address) = value;
    }

    u8 ProcessPlus::Read8(u32 address) {
        return *(volatile unsigned char *)(address);
    }

    u16 ProcessPlus::Read16(u32 address) {
        return *(volatile unsigned short *)(address);
    }

    u32 ProcessPlus::Read32(u32 address) {
        return *(volatile unsigned int *)(address);
    }

    bool CRO::Toggle(u32 address, bool toggle) {
        Handle processHandle;
        u32 processID;
        Result res;
        bool out = false;
        MemInfo mInfo;
        PageInfo pInfo;

        svcGetProcessId(&processID, CUR_PROCESS_HANDLE);
        res = svcOpenProcess(&processHandle, processID);

        if (R_SUCCEEDED(res)) {
            res = svcQueryMemory(&mInfo, &pInfo, address);

            if (R_SUCCEEDED(res)) {
                u32 perm = Toggle ? MemPerm(MEMPERM_READ | MEMPERM_EXECUTE | MEMPERM_WRITE) : MemPerm(MEMPERM_READ | MEMPERM_EXECUTE);
                res = svcControlProcessMemory(processHandle, mInfo.base_addr, 0, mInfo.size, MemOp(MEMOP_PROT), perm);

                if (R_SUCCEEDED(res)) {
                    out = true;
                }
            }

            svcCloseHandle(processHandle);
        }

        return out;
    }

    bool CRO::Edit(u32 address, u32 value) {
        if (Toggle(address, true)) {
            *(u32 *)address = value;
            Toggle(address, false);
            return true;
        }

        return false;
    }

    bool CRO::Force(u32 address) {
        Handle processHandle;
        u32 pID;
        Result res;
        bool out = false;
        MemInfo mInfo;
        PageInfo pInfo;

        svcGetProcessId(&pID, CUR_PROCESS_HANDLE);
        res = svcOpenProcess(&processHandle, pID);

        if (R_SUCCEEDED(res)) {
            res = svcQueryMemory(&mInfo, &pInfo, address);

            if (R_SUCCEEDED(res)) {
                if (mInfo.perm < 2) {
                    res = svcControlProcessMemory(processHandle, mInfo.base_addr, 0, mInfo.size, MemOp(MEMOP_PROT), MemPerm(MEMPERM_READ | MEMPERM_EXECUTE | MEMPERM_WRITE));

                    if (R_SUCCEEDED(res)) {
                        out = true;
                    }
                }

                else {
                    out = true;
                }
            }

            svcCloseHandle(processHandle);
        }

        return out;
    }

    bool Bit::Read(u32 address, u8 &value, bool rightSide) {
        // Checks if address is valid or not
        if (!Process::CheckAddress(address)) {
            return false;
        }

        // Right side of the byte
        if (rightSide){
            value = *(u8 *)(address) & 0xF;
            return true;
        }

        // Left side of the byte
        value = (*(u8 *)(address) >> 4) & 0xF;
        return true;
    }

    bool Bit::Edit(u32 address, u8 value, bool rightSide) {
        // Checks if address is valid or not
        if (!Process::CheckAddress(address)) {
            return false;
        }

        // Clears 4-bit first then write 4-bit to the right side of the byte
        if (rightSide) {
            *(u8 *)address &= ~0xF;
            *(u8 *)address |= (value & 0xF);
            return true;
        }

        // Clears 4-bit first then write 4-bit to the left side of the byte
        *(u8 *)address &= ~(0xF << 4);
        *(u8 *)address |= ((value & 0xF) << 4);
        return true;
    }

    u8 data8, offset8;
    u16 data16, offset16;
    u32 data32, offset32;

    string bin, path;

    Game game = Game::None;
    Group group = Group::None;
    Version version = Version::Supported;

    bool IsCompatible(void) {
        u64 titleID = Process::GetTitleID();
        u16 ver = Process::GetVersion();

        switch (titleID) {
            case 0x0004000000055D00: {
                if (ver != 5232) {
                    version = Version::Unsupported;
                }

                game = Game::X;
                group = Group::XY;
            }
            break;

            case 0x0004000000055E00: {
                if (ver != 5216) {
                    version = Version::Unsupported;
                }

                game = Game::Y;
                group = Group::XY;
            }
            break;

            case 0x000400000011C400: {
                if (ver != 7280) {
                    version = Version::Unsupported;
                }

                game = Game::OR;
                group = Group::ORAS;
            }
            break;

            case 0x000400000011C500: {
                if (ver != 7280) {
                    version = Version::Unsupported;
                }

                game = Game::AS;
                group = Group::ORAS;
            }
            break;

            case 0x0004000000164800: {
                if (ver != 2112) {
                    version = Version::Unsupported;
                }

                game = Game::S;
                group = Group::SM;
            }
            break;

            case 0x0004000000175E00: {
                if (ver != 2112) {
                    version = Version::Unsupported;
                }

                game = Game::M;
                group = Group::SM;
            }
            break;

            case 0x00040000001B5000: {
                if (ver != 2080) {
                    version = Version::Unsupported;
                }

                game = Game::US;
                group = Group::USUM;
            }
            break;

            case 0x00040000001B5100: {
                if (ver != 2080) {
                    version = Version::Unsupported;
                }

                game = Game::UM;
                group = Group::USUM;
            }
            break;

            default: {
                abort();
                return false;
            }
        }

        bin = "/luma/plugins/00040000" + Utils::ToHex(titleID) + "/Bin/";
        path = "/luma/plugins/00040000" + Utils::ToHex(titleID);
        return true;
    }

    bool IsOnWhiteList(void) {
        FriendKey frndKey;
        FriendKey *frndKeyPointer = &frndKey;

        u64 frndCode;
        u64 *frndCodePointer = &frndCode;

        frdInit();
        FRD_GetMyFriendKey(frndKeyPointer);
        FRD_PrincipalIdToFriendCode(frndKey.principalId, frndCodePointer);

        StringVector frndCodes;

        if (find(frndCodes.begin(), frndCodes.end(), to_string(*frndCodePointer)) == frndCodes.end()) {
            abort();
            return false;
        }

        else return true;
    }

    int RandMinMax(int low, int high) {
        return low + (rand() % (high - low + 1));
    }

    void Message::Completed(void) {
        MessageBox("Operation has been " << Color::LimeGreen << "completed" << Color::White << "!", DialogType::DialogOk, ClearScreen::Both)();
    }

    void Message::Interrupted(void) {
        MessageBox("Operation has been " << Color(255, 51, 51) << "interrupted" << Color::White << "!", DialogType::DialogOk, ClearScreen::Both)();
    }

    void Message::Warning(void) {
        MessageBox("Operation has already been " << Color::Orange << "completed" << Color::White << "!", DialogType::DialogOk, ClearScreen::Both)();
    }

    int Value(int data1, int data2) {
        if (group == Group::XY || group == Group::SM) {
            return data1;
        }

        return data2;
    }

    StringVector Gen6::Choices(StringVector vect1, StringVector vect2) {
        if (group == Group::XY || group == Group::SM) {
            return vect1;
        }

        return vect2;
    }

    u32 Gen6::Auto(u32 address1, u32 address2) {
        if (game == Game::X || game == Game::OR) {
            return address1;
        }

        return address2;
    }

    string Gen6::Name(string name1, string name2) {
        if (game == Game::X || game == Game::OR) {
            return name1;
        }

        return name1;
    }

    StringVector Gen6::Forms(int pokeNo) {
        StringVector options;

        switch (pokeNo)
        {
            case 3:   // Venusaur
            case 9:   // Blastoise
            case 65:  // Alakazam
            case 94:  // Gengar
            case 115: // Kangaskhan
            case 127: // Pinsir
            case 130: // Gyarados
            case 142: // Aerodactyl
            case 181: // Ampharos
            case 208: // Steelix
            case 212: // Scizor
            case 214: // Heracross
            case 229: // Houndoom
            case 248: // Tyranitar
            case 257: // Blaziken
            case 282: // Gardevoir
            case 303: // Mawile
            case 306: // Aggron
            case 308: // Medicham
            case 310: // Manectric
            case 354: // Banette
            case 359: // Absol
            case 380: // Latias
            case 381: // Latios
            case 445: // Garchomp
            case 448: // Lucario
            case 460: // Abomasnow
                options = {"Normal", "Mega"};
                break;

            case 6:   // Charizard
            case 150: // Mewtwo
                options = {"Normal", "Mega X", "Mega Y"};
                break;

            case 15:  // Beedrill
            case 18:  // Pidgeot
            case 80:  // Slowbro
            case 254: // Sceptile
            case 260: // Swampert
            case 302: // Sableye
            case 319: // Sharpedo
            case 323: // Camerupt
            case 334: // Altaria
            case 362: // Glalie
            case 373: // Salamence
            case 376: // Metagross
            case 384: // Rayquaza
            case 428: // Lopunny
            case 475: // Gallade
            case 531: // Audino
            case 719: // Diancie
                options = Gen6::Choices({"Normal"}, {"Normal", "Mega"});
                break;

            case 201: // Unown
                options = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "!", "?"};
                break;

            case 351: // Castform
                options = {"Normal", "Sunny", "Rainy", "Snowy"};
                break;

            case 382: // Kyogre
            case 383: // Groudon
                options = Gen6::Choices({"Normal"}, {"Normal", "Primal"});

            case 386: // Deoxys
                options = {"Normal", "Attack", "Defense", "Speed"};
                break;

            case 412: // Burmy
            case 413: // Wormadam
            case 414: // Mothim
                options = {"Plant", "Sandy", "Trash"};
                break;

            case 422: // Shellos
            case 423: // Gastrodon
                options = {"East", "West"};
                break;

            case 479: // Rotom
                options = {"Normal", "Heat", "Wash", "Frost", "Fan", "Mow"};
                break;

            case 487: // Giratina
                options = {"Altered", "Origin"};
                break;

            case 492: // Shaymin
                options = {"Land", "Sky"};
                break;

            case 493: // Arceus
                options = {"Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark", "Fairy"};
                break;

            case 550: // Basculin
                options = {"Red", "Blue"};
                break;

            case 555: // Darmanitan
                options = {"Standard", "Zen"};
                break;

            case 585: // Deerling
            case 586: // Sawsbuck
                options = {"Spring", "Summer", "Autumn", "Winter"};
                break;

            case 641: // Tornadus
            case 642: // Thundurus
            case 645: // Landorus
                options = {"Incarnate", "Therian"};
                break;

            case 646: // Kyurem
                options = {"Normal", "White", "Black"};
                break;

            case 647: // Keldeo
                options = {"Ordinary", "Resolute"};
                break;

            case 648: // Meloetta
                options = {"Aria", "Pirouette"};
                break;

            case 649: // Genesect
                options = {"Normal", "Douse", "Shock", "Burn", "Chill"};
                break;

            case 664: // Scatterbug
            case 665: // Spewpa
            case 666: // Vivillon
                options = {"Icy Snow", "Polar", "Tundra", "Continental", "Garden", "Elegant", "Meadow", "Modern", "Marine", "Archipelago", "High-Plains", "Sandstorm", "River", "Monsoon", "Savannah", "Sun", "Ocean", "Jungle", "Fancy", "Poke Ball"};
                break;

            case 669: // Flabébé
            case 671: // Florges
                options = {"Red", "Yellow", "Orange", "Blue", "White"};
                break;

            case 670: // Floette
                options = {"Red", "Yellow", "Orange", "Blue", "White", "Eternal"};
                break;

            case 676: // Furfrou
                options = {"Natural", "Heart", "Star", "Diamond", "Deputante", "Matron", "Dandy", "La Reine", "Kabuki", "Pharaoh"};
                break;

            case 681: // Aegislash
                options = {"Shield", "Blade"};
                break;

            case 710: // Pumpkaboo
            case 711: // Gourgeist
                options = {"Average", "Small", "Large", "Super"};
                break;

            case 716: // Xerneas
                options = {"Neutral", "Active"};
                break;

            case 720: // Hoopa
                options = Gen6::Choices({"Confined"}, {"Confined", "Unbound"});
                break;

            default:  // All Others
                options = {"Normal"};
                break;
        }

        return options;
    }

    bool Gen6::IsInBattle(void) {
        static const u32 pointer = Value(0x81FB170, 0x81FB478);

        if (Process::Read32(pointer, data32) && data32 == 0x40001) {
            return true;
        }

        return false;
    }

    StringVector Gen7::Choices(StringVector vect1, StringVector vect2) {
        if (group == Group::SM || group == Group::USUM) {
            return vect1;
        }

        return vect2;
    }

    u32 Gen7::Auto(u32 address1, u32 address2) {
        if (game == Game::S || game == Game::US) {
            return address1;
        }

        return address2;
    }

    string Gen7::Name(string name1, string name2) {
        if (game == Game::S || game == Game::US) {
            return name1;
        }

        return name2;
    }

    StringVector Gen7::Forms(int pokeNo) {
        StringVector options;

        switch (pokeNo)
        {
            case 3:   // Venusaur
            case 9:   // Blastoise
            case 15:  // Beedrill
            case 18:  // Pidgeot
            case 65:  // Alakazam
            case 80:  // Slowbro
            case 94:  // Gengar
            case 115: // Kangaskhan
            case 127: // Pinsir
            case 130: // Gyarados
            case 142: // Aerodactyl
            case 181: // Ampharos
            case 208: // Steelix
            case 212: // Scizor
            case 214: // Heracross
            case 229: // Houndoom
            case 248: // Tyranitar
            case 254: // Sceptile
            case 257: // Blaziken
            case 260: // Swampert
            case 282: // Gardevoir
            case 302: // Sableye
            case 303: // Mawile
            case 306: // Aggron
            case 308: // Medicham
            case 310: // Manectric
            case 319: // Sharpedo
            case 323: // Camerupt
            case 334: // Altaria
            case 354: // Banette
            case 359: // Absol
            case 362: // Glalie
            case 373: // Salamence
            case 376: // Metagross
            case 380: // Latias
            case 381: // Latios
            case 384: // Rayquaza
            case 428: // Lopunny
            case 445: // Garchomp
            case 448: // Lucario
            case 460: // Abomasnow
            case 475: // Gallade
            case 531: // Audino
            case 719: // Diancie
                options = {"Normal", "Mega"};
                break;

            case 6:   // Charizard
            case 150: // Mewtwo
                options = {"Normal", "Mega X", "Mega Y"};
                break;

            case 19:  // Rattata
            case 26:  // Raichu
            case 27:  // Sandshrew
            case 28:  // Sandslash
            case 37:  // Vulpix
            case 38:  // Ninetails
            case 50:  // Diglett
            case 51:  // Dugtrio
            case 52:  // Meowth
            case 53:  // Persian
            case 74:  // Geodude
            case 75:  // Graveler
            case 76:  // Golem
            case 88:  // Grimer
            case 89:  // Muk
            case 105: // Exeggutor
                options = {"Normal", "Alola"};
                break;

            case 20:  // Raticate
            case 103: // Marowak
                options = {"Normal", "Alola", "Totem"};
                break;

            case 25:  // Pikachu
                options = Gen7::Choices({"Normal"}, {"Normal", "Original Cap", "Hoenn Cap", "Sinnoh Cap", "Unova Cap", "Kalos Cap", "Alola Cap", "Partner Cap"});
                break;

            case 201: // Unown
                options = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "!", "?"};
                break;

            case 351: // Castform
                options = {"Normal", "Sunny", "Rainy", "Snowy"};
                break;

            case 382: // Kyogre
            case 383: // Groudon
                options = {"Normal", "Primal"};
                break;

            case 386: // Deoxys
                options = {"Normal", "Attack", "Defense", "Speed"};
                break;

            case 412: // Burmy
            case 413: // Wormadam
            case 414: // Mothim
                options = {"Plant", "Sandy", "Trash"};
                break;

            case 422: // Shellos
            case 423: // Gastrodon
                options = {"East", "West"};
                break;

            case 479: // Rotom
                options = {"Normal", "Heat", "Wash", "Frost", "Fan", "Mow"};
                break;

            case 487: // Giratina
                options = {"Altered", "Origin"};
                break;

            case 492: // Shaymin
                options = {"Land", "Sky"};
                break;

            case 493: // Arceus
            case 773: // Silvally
                options = {"Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark", "Fairy"};
                break;

            case 550: // Basculin
                options = {"Red", "Blue"};
                break;

            case 555: // Darmanitan
                options = {"Standard", "Zen"};
                break;

            case 585: // Deerling
            case 586: // Sawsbuck
                options = {"Spring", "Summer", "Autumn", "Winter"};
                break;

            case 641: // Tornadus
            case 642: // Thundurus
            case 645: // Landorus
                options = {"Incarnate", "Therian"};
                break;

            case 646: // Kyurem
                options = {"Normal", "White", "Black"};
                break;

            case 647: // Keldeo
                options = {"Ordinary", "Resolute"};
                break;

            case 648: // Meloetta
                options = {"Aria", "Pirouette"};
                break;

            case 649: // Genesect
                options = {"Normal", "Douse", "Shock", "Burn", "Chill"};
                break;

            case 658: // Greninja
                options = {"Normal", "Ash", "Bonded"};
                break;

            case 664: // Scatterbug
            case 665: // Spewpa
            case 666: // Vivillon
                options = {"Icy Snow", "Polar", "Tundra", "Continental", "Garden", "Elegant", "Meadow", "Modern", "Marine", "Archipelago", "High-Plains", "Sandstorm", "River", "Monsoon", "Savannah", "Sun", "Ocean", "Jungle", "Fancy", "Poke Ball"};
                break;

            case 669: // Flabébé
            case 671: // Florges
                options = {"Red", "Yellow", "Orange", "Blue", "White"};
                break;

            case 670: // Floette
                options = {"Red", "Yellow", "Orange", "Blue", "White", "Eternal"};
                break;

            case 676: // Furfrou
                options = {"Natural", "Heart", "Star", "Diamond", "Deputante", "Matron", "Dandy", "La Reine", "Kabuki", "Pharaoh"};
                break;

            case 681: // Aegislash
                options = {"Shield", "Blade"};
                break;

            case 710: // Pumpkaboo
            case 711: // Gourgeist
                options = {"Average", "Small", "Large", "Super"};
                break;

            case 716: // Xerneas
                options = {"Neutral", "Active"};
                break;

            case 718: // Zygarde
                options = {"50%", "10%", "10%-C", "50%-C", "100%-C"};
                break;

            case 720: // Hoopa
                options = {"Confined", "Unbound"};
                break;

            case 735: // Gumshoos
            case 738: // Vikavolt
            case 743: // Ribombee
            case 752: // Araquanid
            case 754: // Lurantis
            case 758: // Salazzle
            case 777: // Togedemaru
            case 784: // Kommo-o
                options = {"Normal", "Totem"};
                break;

            case 741: // Oricorio
                options = {"Red", "Yellow", "Pink", "Blue"};
                break;

            case 745: // Lycanroc
                options = {"Midday", "Midnight", "Dusk"};
                break;

            case 746: // Wishiwashi
                options = {"Normal", "School"};
                break;

            case 774: // Minior
                options = {"Random"};
                break;

            case 778: // Mimikyu
                options = {"Disguised", "Busted", "Totem-Disquised", "Totem-Busted"};
                break;

            case 800: // Necrozma
                options = Gen7::Choices({"Normal"}, {"Normal", "Dawn", "Dusk", "Ultra"});
                break;

            case 801: // Magearna
                options = {"Normal", "Original"};
                break;

            default:  // All Others
                options = {"Normal"};
                break;
        }

        return options;
    }

    bool Gen7::IsInBattle(void) {
        static u32 pointer[2] = {0x30000158, 0x30000180};

        if (Process::Read32(pointer[0], data32) && data32 == 0x40001 && Process::Read8(pointer[1], data8) && data8 == 3) {
            return true;
        }

        return false;
    }
}