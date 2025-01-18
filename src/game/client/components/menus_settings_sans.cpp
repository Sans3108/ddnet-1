#include <engine/shared/config.h>
#include <engine/shared/linereader.h>
#include <engine/textrender.h>
#include <game/client/gameclient.h>
#include <game/client/ui.h>

#include "binds.h"
#include "menus.h"

void CMenus::RenderSettingsSans(CUIRect MainView)
{
	char aBuf[128 + IO_MAX_PATH_LENGTH];
	CUIRect Label, Button, Left, Right, Game, ClientSettings;
	MainView.HSplitTop(150.0f, &Game, &ClientSettings);

	// game
	{
		// headline
		Game.HSplitTop(30.0f, &Label, &Game);
		Ui()->DoLabel(&Label, "Sans' Client Settings", 20.0f, TEXTALIGN_ML);
		Game.HSplitTop(5.0f, nullptr, &Game);
		Game.VSplitMid(&Left, &Right, 20.0f);

		// Greet in console on startup
		Left.HSplitTop(5.0f, nullptr, &Left);
		Left.HSplitTop(20.0f, &Button, &Left);
		if(DoButton_CheckBox(&g_Config.m_SansGreetOnStart, "Greet in F1 console on startup", g_Config.m_SansGreetOnStart, &Button))
			g_Config.m_SansGreetOnStart ^= 1;

		CUIRect SecondButton;

		Right.HSplitTop(5.0f, nullptr, &Right);
		Right.HSplitTop(20.0f, &SecondButton, &Right);
		if(DoButton_CheckBox(&g_Config.m_ClShowfps, "Toggle FPS counter", g_Config.m_ClShowfps, &SecondButton))
			g_Config.m_ClShowfps ^= 1;
	}
}