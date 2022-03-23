#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"

#include "Backgrounds/TopBackground.c"
#include "Backgrounds/BottomBackground.c"

#include "XY.hpp"
#include "ORAS.hpp"
#include "SM.hpp"
#include "USUM.hpp"

namespace CTRPluginFramework {
    void PatchProcess(FwkSettings &settings) {
        IsCompatible();

        settings.TryLoadSDSounds = false;
        settings.AllowActionReplay = true;
        settings.AllowSearchEngine = true;

        settings.MainTextColor = Color(Color::White);
        settings.WindowTitleColor = Color(Color::White);
        settings.MenuSelectedItemColor = Color(Color::White);
        settings.MenuUnselectedItemColor = Color(Color::Silver);
        settings.BackgroundMainColor = Color(20, 20, 20);
        settings.BackgroundSecondaryColor = Color(20, 20, 20);
        settings.BackgroundBorderColor = Color(Color::White);
        settings.CursorFadeValue = -0.3f;

        settings.Keyboard.Background = Color(20, 20, 20);
        settings.Keyboard.KeyBackground = Color(20, 20, 20);
        settings.Keyboard.KeyBackgroundPressed = settings.Keyboard.KeyBackground.Blend(Color(255, 51, 51), Color::BlendMode::Alpha).Fade(.1f);
        settings.Keyboard.KeyText = Color(Color::White);
        settings.Keyboard.KeyTextPressed = Color(Color::White);
        settings.Keyboard.KeyTextDisabled = Color::DimGrey;
        settings.Keyboard.Cursor = Color(Color::White);
        settings.Keyboard.Input = Color(Color::White);

        settings.CustomKeyboard.BackgroundMain = Color(20, 20, 20);
        settings.CustomKeyboard.BackgroundSecondary = Color(20, 20, 20);
        settings.CustomKeyboard.BackgroundBorder = Color(Color::White);
        settings.CustomKeyboard.KeyBackground = Color(51, 51, 51);
        settings.CustomKeyboard.KeyBackgroundPressed = settings.CustomKeyboard.KeyBackground.Blend(Color(255, 51, 51), Color::BlendMode::Alpha).Fade(.1f);
        settings.CustomKeyboard.KeyText = Color(Color::White);
        settings.CustomKeyboard.KeyTextPressed = Color(Color::White);
        settings.CustomKeyboard.ScrollBarBackground = Color(Color::Silver);
        settings.CustomKeyboard.ScrollBarThumb = Color(255, 51, 51);

        FwkSettings::SetTopScreenBackground((void*) _acTopBackground);
        FwkSettings::SetBottomScreenBackground((void*) _acBottomBackground);
    }

    void BlankMenu(PluginMenu &menu) {

    };

    int main(void) {
        PluginMenu *menu = new PluginMenu("Multi-Pokémon Framework", 22, 3, 23, "A CTRPF plugin for the Nintendo 3DS Pokémon games that supports both the 6th and 7th generations.\n\nFor more details, you may visit the repo at\n" << Color::Orange << REPO);

        menu->ShowWelcomeMessage(false);
        menu->SynchronizeWithFrame(true);
        menu->SetHexEditorState(true);

        if (version == Version::Supported) {
            if (group == Group::XY) {
                XY::Menu(*menu);
            }

            if (group == Group::ORAS) {
                ORAS::Menu(*menu);
            }

            if (group == Group::SM) {
                SM::Menu(*menu);
            }

            if (group == Group::USUM) {
                USUM::Menu(*menu);
            }
        }

        else {
            BlankMenu(*menu);
        }

        menu->Run();
        delete menu;
        return (0);
    }
}