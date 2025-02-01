#include <engine/graphics.h>
#include <engine/textrender.h>

#include <game/generated/protocol.h>

#include <game/client/animstate.h>
#include <game/client/components/touch_controls.h>
#include <game/client/gameclient.h>
#include <game/client/render.h>
#include <game/client/ui.h>
#include <game/client/ui_listbox.h>

#include "menus.h"

void CMenus::RenderInGameSans(CUIRect MainView)
{
	MainView.Draw(ms_ColorTabbarActive, IGraphics::CORNER_B, 10.0f);

	CUIRect Container, Header, Content, HeaderLabelPlayerName, HeaderLabelPlayerClan;

	MainView.Margin(10.0f, &Container);
	Container.Draw(ColorRGBA(.4f, .4f, .4f, 0.25f), IGraphics::CORNER_ALL, 10.0f);
	Container.Margin(10.0f, &Container);

	Container.HSplitTop(46.0f, &Header, &Content);
	Header.Draw(ColorRGBA(.5f, .5f, .5f, 0.25f), IGraphics::CORNER_T, 10.0f);
	Content.Draw(ColorRGBA(.4f, .4f, .4f, 0.25f), IGraphics::CORNER_B, 10.0f);

	Header.VSplitRight(64.0f, &Header, nullptr);
	Header.VSplitMid(&HeaderLabelPlayerName, &HeaderLabelPlayerClan);

	Ui()->DoLabel(&HeaderLabelPlayerName, "Player Name", 18.0f, TEXTALIGN_ML);
	Ui()->DoLabel(&HeaderLabelPlayerClan, "Player Clan", 18.0f, TEXTALIGN_ML);

	int TotalPlayers = 0;
	for(const auto &pInfoByName : m_pClient->m_Snap.m_apInfoByName)
	{
		if(!pInfoByName) continue;
		TotalPlayers++;
	}

	static CListBox s_PlayerList;
	s_PlayerList.DoStart(24.0f, TotalPlayers, 1, 3, -1, &Content);

	static char s_aPlayerIds[MAX_CLIENTS][4] = {{0}};

	for(int i = 0, Count = 0; i < MAX_CLIENTS; ++i)
	{
		if(!m_pClient->m_Snap.m_apInfoByName[i]) continue;
		int Index = m_pClient->m_Snap.m_apInfoByName[i]->m_ClientId;

		CGameClient::CClientData &CurrentClient = m_pClient->m_aClients[Index];
		const CListboxItem Item = s_PlayerList.DoNextItem(&CurrentClient);

		Count++;

		if(!Item.m_Visible) continue;

		CUIRect Row = Item.m_Rect;
		if(Count % 2 == 1) Row.Draw(ColorRGBA(.6f, .6f, .6f, 0.25f), IGraphics::CORNER_NONE, 5.0f);
		Row.VSplitRight(s_PlayerList.ScrollbarWidthMax() - s_PlayerList.ScrollbarWidth(), &Row, nullptr); // Make room for scroll bar

		CUIRect NameLabel, ClanLabel, Tee;

		Row.VSplitRight(64.0f, &Row, &Tee);

		CTeeRenderInfo TeeInfo = CurrentClient.m_RenderInfo;
		TeeInfo.m_Size = Tee.h;

		const CAnimState *pIdleState = CAnimState::GetIdle();
		vec2 OffsetToMid;
		CRenderTools::GetRenderTeeOffsetToRenderedTee(pIdleState, &TeeInfo, OffsetToMid);
		vec2 TeeRenderPos(Tee.x + Tee.h / 2, Tee.y + Tee.h / 2 + OffsetToMid.y);
		RenderTools()->RenderTee(pIdleState, &TeeInfo, EMOTE_NORMAL, vec2(-1.0f, 0.0f), TeeRenderPos);
		Ui()->DoButtonLogic(&s_aPlayerIds[Index][3], 0, &Tee);
		GameClient()->m_Tooltips.DoToolTip(&s_aPlayerIds[Index][3], &Tee, CurrentClient.m_aSkinName);

		Row.VSplitMid(&NameLabel, &ClanLabel);

		Ui()->DoLabel(&NameLabel, CurrentClient.m_aName, 14.0f, TEXTALIGN_ML);
		Ui()->DoLabel(&ClanLabel, CurrentClient.m_aClan, 14.0f, TEXTALIGN_ML);
	}

 	s_PlayerList.DoEnd();
}