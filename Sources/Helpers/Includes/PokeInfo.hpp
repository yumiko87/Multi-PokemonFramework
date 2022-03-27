#ifndef POKEINFOHPP
#define POKEINFOHPP

#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework {
    struct PK6 {
        u32 encryptionConstant;
        u16 sanity;
        u16 checksum;

        // Block A
        u16 species;
        u16 heldItem;
        u16 trainerID;
        u16 secretID;
        u32 exp;
        u8  ability;
        u8  abilityNumber;
        u8  trainingBagHits;
        u8  trainingBag;
        u32 pid;
        u8  nature;
        u8  miscData;
        u8  evs[6];
        u8  cntCool;
        u8  cntBeauty;
        u8  cntCute;
        u8  cntSmart;
        u8  cntTough;
        u8  cntSheen;
        u8  markValue;
        u8  pkrus;
        u8  st1;
        u8  st2;
        u8  st3;
        u8  st4;
        u8  ribbons[6];
        u8  unused1[2];
        u8  ribbonCountMemoryContest;
        u8  ribbonCountMemoryBattle;
        u8  superTrainingFlags;
        u8  unused2[5];

        // Block B
        u8  nickname[26];
        u16 move1;
        u16 move2;
        u16 move3;
        u16 move4;
        u8  move1PP;
        u8  move2PP;
        u8  move3PP;
        u8  move4PP;
        u8  move1PPUps;
        u8  move2PPUps;
        u8  move3PPUps;
        u8  move4PPUps;
        u16 relearnMove1;
        u16 relearnMove2;
        u16 relearnMove3;
        u16 relearnMove4;
        u8  secretSuperTrainingUnlockled;
        u8  unused3;
        u32 iv32;

        // Block C
        u8  hiddnTrnerName[26];
        u8  hiddnTrnerGender;
        u8  currentHandler;
        u8  geo1Region;
        u8  geo1Country;
        u8  geo2Region;
        u8  geo2Country;
        u8  geo3Region;
        u8  geo3Country;
        u8  geo4Region;
        u8  geo4Country;
        u8  geo5Region;
        u8  geo5Country;
        u8  unused4[4];
        u8  hiddnTrnerFriendship;
        u8  hiddnTrnerAffection;
        u8  hiddnTrnerIntensity;
        u8  hiddnTrnerMemory;
        u8  hiddnTrnerFeeling;
        u8  unused5;
        u16 hiddnTrnerTextVar;
        u8  unused6[4];
        u8  fullness;
        u8  enjoyment;

        // Block D
        u8  ogTrnerName[26];
        u8  ogTrnerFriendship;
        u8  ogTrnerAffection;
        u8  ogTrnerIntensity;
        u8  ogTrnerMemory;
        u16 ogTrnerTextVar;
        u8  ogTrnerFeeling;
        u8  eggYear;
        u8  eggMonth;
        u8  eggYearDay;
        u8  metYear;
        u8  metMonth;
        u8  metDay;
        u8  unused7;
        u16 eggLocation;
        u16 metLocation;
        u8  ball;
        u8  metLevel;
        u8  fatefulEnc;
        u8  version;
        u8  country;
        u8  region;
        u8  consoleRegion;
        u8  language;
        u8  unused8[4];
    };

    struct PK7 {
        u32 encryptionConstant;
        u16 sanity;
        u16 checksum;

        // Block A
        u16 species;
        u16 heldItem;
        u16 trainerID;
        u16 secretID;
        u32 exp;
        u8  ability;
        u8  abilityNumber;
        u8  markValue;
        u32 pid;
        u8  nature;
        u8  fatefulEncounterGenderForm;
        u8  evs[6];
        u8  cntCool;
        u8  cntBeauty;
        u8  cntCute;
        u8  cntSmart;
        u8  cntTough;
        u8  cntSheen;
        u8  resortEventStatus;
        u8  pkrus;
        u8  st1;
        u8  st2;
        u8  st3;
        u8  st4;
        u8  ribbons[6];
        u8  unused1[2];
        u8  ribbonCountMemoryContest;
        u8  ribbonCountMemoryBattle;
        u8  superTrainingFlags;
        u8  unused2[5];

        // Block B
        u8  nickname[26];
        u16 move1;
        u16 move2;
        u16 move3;
        u16 move4;
        u8  move1PP;
        u8  move2PP;
        u8  move3PP;
        u8  move4PP;
        u8  move1PPUps;
        u8  move2PPUps;
        u8  move3PPUps;
        u8  move4PPUps;
        u16 relearnMove1;
        u16 relearnMove2;
        u16 relearnMove3;
        u16 relearnMove4;
        u8  secretSuperTrainingUnlockled;
        u8  unused3;
        u32 iv32;

        // Block C
        u8  hiddnTrnerName[26];
        u8  hiddnTrnerGender;
        u8  currentHandler;
        u8  geo1Region;
        u8  geo1Country;
        u8  geo2Region;
        u8  geo2Country;
        u8  geo3Region;
        u8  geo3Country;
        u8  geo4Region;
        u8  geo4Country;
        u8  geo5Region;
        u8  geo5Country;
        u8  unused4[4];
        u8  hiddnTrnerFriendship;
        u8  hiddnTrnerAffection;
        u8  hiddnTrnerIntensity;
        u8  hiddnTrnerMemory;
        u8  hiddnTrnerFeeling;
        u8  unused5;
        u16 hiddnTrnerTextVar;
        u8  unused6[4];
        u8  fullness;
        u8  enjoyment;

        // Block D
        u8  ogTrnerName[26];
        u8  ogTrnerFriendship;
        u8  ogTrnerAffection;
        u8  ogTrnerIntensity;
        u8  ogTrnerMemory;
        u16 ogTrnerTextVar;
        u8  ogTrnerFeeling;
        u8  eggYear;
        u8  eggMonth;
        u8  eggYearDay;
        u8  metYear;
        u8  metMonth;
        u8  metDay;
        u8  unused7;
        u16 eggLocation;
        u16 metLocation;
        u8  ball;
        u8  metLevel;
        u8  hyperTrainFlags;
        u8  version;
        u8  country;
        u8  region;
        u8  consoleRegion;
        u8  language;
        u8  unused8[4];
    };

    u32 GetPokePointer(void);

    const u8 blockPosition[4][24] = {
        {0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3},
        {1, 1, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2},
        {2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2, 0, 0, 0, 0, 0, 0, 3, 2, 3, 2, 1, 1},
        {3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0}
    };

    void Unshuffle(u8 *shuffled, u8 *poke, u32 sv);

    template <class PKX>
    void DecryptPokemon(u8 *ekm, PKX *poke) {
        // Encryption key from first 4 bytes of ekm
        u32 pokeVal = *(u32*)ekm;

        // Shuffle Value used to unshuffle the data
        u32 shuffleVal = (((pokeVal >> 0xD) & 0x1F) % 24);

        // Get initial seed from first 4 bytes, same as enc key
        u32 seed = pokeVal;

        // Decrypt data using seed
        for (int i = 8; i < 232; i += 2)  {
            seed = (0x41C64E6D * seed) + 0x00006073;
            ekm[i] ^= (u8)(seed >> 16);
            ekm[i + 1] ^= (u8)(seed >> 24);
        }

        // Unshuffle block data
        Unshuffle(ekm, (u8 *)poke, shuffleVal);
    }

    template <class PKX>
    void EncryptPokemon(PKX *poke, u8 *ekm) {
        // Encryption key from first 4 bytes of ekm
        u32 pokeVal = *(u32*)ekm;

        // Shuffle Value used to reshuffle the data
        u32 shuffleVal = (((pokeVal >> 0xD) & 0x1F) % 24);

        // Get initial seed from first 4 bytes, same as enc key
        u32 seed = pokeVal;

        // Reshuffle block data
        for (int i = 0; i < 11; i++) {
            Unshuffle(ekm, (u8 *)poke, shuffleVal);

            if (!Process::CopyMemory(ekm, poke, 232)) {
                return;
            }
        }

        // Encrypt data using seed
        for (int i = 8; i < 232; i += 2)  {
            seed = (0x41C64E6D * seed) + 0x00006073;
            ekm[i] ^= (u8)(seed >> 16);
            ekm[i + 1] ^= (u8)(seed >> 24);
        }
    }

    template <class PKX>
    u16 Chcksum(PKX *poke) {
        u16 chksum = 0;

        for (u8 i = 4; i < 232 / 2; i++) {
            chksum += *((u16*)(poke) + i);
        }

        return chksum;
    }

    template <class PKX>
    bool IsValid(PKX *poke)  {
        // Ensure sanity check
        if (!poke || poke->sanity) {
            return false;
        }

        // Calculate checksum
        if (Chcksum(poke) != poke->checksum) {
            return false;
        }

        // Ensure species is in a valid range
        return (poke->species >= 1 && poke->species <= (group == Group::XY || group == Group::ORAS ? 721 : 802));
    }

    template <class PKX>
    bool GetPokemon(u32 pokePointer, PKX *poke) {
        if (poke == 0 || pokePointer == 0) {
            return false;
        }

        // Load encrypted game data to ekm
        u8 ekm[232];

        if (!Process::CopyMemory(&ekm, (u8 *)pokePointer, 232)) {
            return false;
        }

        // Decrypt data and store in struct
        DecryptPokemon(ekm, poke);

        // Check validity and return check
        return (IsValid(poke));
    }

    template <class PKX>
    bool SetPokemon(u32 pokePointer, PKX *poke) {
        if (poke == 0 || pokePointer == 0) {
            return false;
        }

        // Fix checksum
        poke->checksum = Chcksum(poke);

        // Load decrypted struct data to ekm
        u8 ekm[232];

        if (!Process::CopyMemory(&ekm, poke, 232)) {
            return false;
        }

        // Encrypt data and store in array
        EncryptPokemon(poke, ekm);

        // Write array data to game
        if (Process::Patch(pokePointer, ekm, 232)) {
            return true;
        }

        MessageBox("Failed to encrypt or write data!", DialogType::DialogOk)();
        return false;
    }

    template <class PKX>
    u8 IsShiny(PKX *poke) {
        return (poke->trainerID ^ poke->secretID ^ (u16)(poke->pid & 0x0000FFFF) ^ (u16)((poke->pid & 0xFFFF0000) >> 16)) < 16;
    }

    template <class PKX>
    void MakeShiny(PKX *poke, bool shinify) {
        u16 sxor = (poke->trainerID ^ poke->secretID ^ (u16)(poke->pid & 0x0000FFFF)) & 0xFFF0;

        if (shinify) {
            poke->pid = (poke->pid & 0x000FFFFF) | (sxor << 16);
        }

        else {
            poke->pid = Utils::Random(1, 0xFFFFFFFF);
        }
    }

    template <class PKX>
    void SetSpecies(PKX *poke, u16 pokeNo) {
        if (pokeNo > 0 && pokeNo <= 721 || pokeNo <= 802 || pokeNo <= 807) {
            poke->species = pokeNo;
        }
    }

    template<class PKX>
    void SetIsNicknamed(PKX *poke, int option) {
        poke->iv32 = ((poke->iv32 & 0x7FFFFFFFu) | (option ? 0x80000000u : 0u));
    }

    template<class PKX>
    void SetNickname(PKX *poke, String name) {
        Process::WriteString((u32)poke->nickname, name, StringFormat::Utf16);
    }

    template<class PKX>
    void SetGender(PKX *poke, int option) {
        poke->miscData = ((poke->miscData & ~0x6) | (option << 1));
    }

    template<class PKX>
    bool SetExp(PKX *poke, u32 amount) {
        if (amount <= 1640000) {
            poke->exp = amount;
            return true;
        }

        return false;
    }

    template <class PKX>
    int SetNature(PKX *poke, int option) {
        return poke->nature = option;
    }

    template<class PKX>
    void SetForm(PKX *poke, int option) {
        poke->miscData = (poke->miscData & 0x7) | (option << 3);
    }

    template<class PKX>
    void SetHeldItem(PKX *poke, int id) {
        poke->heldItem = id;
    }

    template <class PKX>
    void SetAbility(PKX *poke, int option) {
        poke->ability = option;
        // poke->abilityNumber = ((poke->abilityNumber & ~7) | (option & 7));
    }

    template <class PKX>
    void SetFriendship(PKX *poke, int amount) {
        poke->ogTrnerFriendship = amount;
    }

    template<class PKX>
    void SetLanguage(PKX *poke, int languageID) {
        poke->language = languageID;
    }

    template<class PKX>
    void SetIsEgg(PKX *poke, int option) {
        poke->iv32 = (poke->iv32 & ~0x40000000u) | (option ? 0x40000000u : 0u);
    }

    template<class PKX>
    void SetPokerus(PKX *poke, int days, int strain, bool isCured) {
        if (!isCured) {
            poke->pkrus = ((poke->pkrus & ~0xF) | days);
            poke->pkrus = ((poke->pkrus & 0xF) | strain << 4);
            return;
        }

        poke->pkrus = 0;
    }

    template<class PKX>
    void SetCountry(PKX *poke, int countryID) {
        poke->country = countryID;
    }

    template<class PKX>
    void SetRegion(PKX *poke, int regionID) {
        poke->region = regionID;
    }

    template<class PKX>
    void SetConsRegion(PKX *poke, int consoleRegID) {
        poke->consoleRegion = consoleRegID;
    }

    template<class PKX>
    void SetOrigin(PKX *poke, int ver) {
        poke->version = ver;
    }

    template<class PKX>
    void SetMetLocation(PKX *poke, int loc, bool isEgg) {
        if (isEgg) {
            poke->eggLocation = loc;
            return;
        }

        else {
            poke->metLocation = loc;
        }
    }

    template<class PKX>
    void SetBall(PKX *poke, int option) {
        poke->ball = option;
    }

    template<class PKX>
    void SetMetLevel(PKX *poke, int value) {
        poke->metLevel = ((poke->metLevel & 0x80) | value);
    }

    template<class PKX>
    void SetMetDate(PKX *poke, bool setYear, int year, bool setMonth, int month, bool setDay, int day, bool isEgg) {
        if (setYear) {
            if (isEgg) {
                poke->eggYear = year;
                return;
            }

            poke->metYear = year;
        }

        else if (setMonth) {
            if (isEgg) {
                poke->eggMonth = month;
                return;
            }

            poke->metMonth = month;
        }

        else if (setDay) {
            if (isEgg) {
                poke->eggYearDay = day;
                return;
            }

            poke->metDay = day;
        }

        else return;
    }

    template<class PKX>
    void SetIsFatefulEnc(PKX *poke, int option) {
        poke->fatefulEnc = ((poke->fatefulEnc & ~0x1) | (option ? 1 : 0));
    }

    template <class PKX>
    void SetIV(PKX *poke, int index, int value) {
        if (value > 31) {
            return;
        }

        poke->iv32 = (poke->iv32 & ~(0x1F << (5 * index))) | (value << (5 * index));
    }

    template <class PKX>
    void SetEV(PKX *poke, int index, int value) {
        if (value > 252) {
            return;
        }

        static int total;

        for (int i = 0; i < 6; i++) {
            total += poke->evs[i];

            if (total > 510) {
                return;
            }
        }

        poke->evs[index] = value;
    }

    template <class PKX>
    void SetContestStats(PKX *poke, int index, int value) {
        if (value > 255) {
            return;
        }

        switch (index) {
            case 0:
                poke->cntCool = value;
                break;
            case 1:
                poke->cntBeauty = value;
                break;
            case 2:
                poke->cntCute = value;
                break;
            case 3:
                poke->cntSmart = value;
                break;
            case 4:
                poke->cntTough = value;
                break;
            case 5:
                poke->cntSheen = value;
                break;
        }
    }

    template <class PKX>
    void SetMoves(PKX *poke, int index, int id, bool isRelearnable) {
        if (!isRelearnable) {
            switch (index) {
                case 0:
                    poke->move1 = id;
                    break;
                case 1:
                    poke->move2 = id;
                    break;
                case 2:
                    poke->move3 = id;
                    break;
                case 3:
                    poke->move4 = id;
                    break;
            }
            return;
        }

        else {
            switch (index) {
                case 0:
                    poke->relearnMove1 = id;
                    break;
                case 1:
                    poke->relearnMove2 = id;
                    break;
                case 2:
                    poke->relearnMove3 = id;
                    break;
                case 3:
                    poke->relearnMove4 = id;
                    break;
            }
        }
    }

    template <class PKX>
    void SetPPUps(PKX *poke, int index, int value) {
        switch (index) {
            case 0:
                poke->move1PPUps = value;
                break;
            case 1:
                poke->move2PPUps = value;
                break;
            case 2:
                poke->move3PPUps = value;
                break;
            case 3:
                poke->move4PPUps = value;
                break;
        }
    }

    template <class PKX>
    void SetSID(PKX *poke, int value) {
        if (value > 65535) {
            return;
        }

        poke->secretID = value;
    }

    template <class PKX>
    void SetTID(PKX *poke, int value) {
        if (value > 65535) {
            return;
        }

        poke->trainerID = value;
    }

    template <class PKX>
    void SetOTName(PKX *poke, String name) {
        Process::WriteString((u32)poke->ogTrnerName, name, StringFormat::Utf16);
    }

    template <class PKX>
    void SetLatestHandler(PKX *poke, String name) {
        Process::WriteString((u32)poke->hiddnTrnerName, name, StringFormat::Utf16);
    }

    template <class PKX>
    void SetRibbons(PKX *poke, int index, bool obtain, int option) {
        poke->ribbons[index] = ((poke->ribbons[index] & ~(1 << option)) | (obtain ? 1 << option : 0));
    }
}

#endif