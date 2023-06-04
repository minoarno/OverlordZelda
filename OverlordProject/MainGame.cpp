#include "stdafx.h"
#include "MainGame.h"

/*LAB Content*/
// #define W6
// #define W8
// #define W9
// #define W11

#define ZeldaGame

#pragma region Lab/Milestone Includes
#ifdef W6
#include "Scenes/Week 6/HardwareSkinningScene.h"
#endif

#ifdef W8
#include "Scenes/Week 8/ShadowMappingScene.h"
#endif

#ifdef W9
#include "Scenes/Week 9/ParticleScene.h"
#endif

#ifdef W11
#include "Scenes/Week 11/DeferredRenderingScene.h"
#endif

#ifdef ZeldaGame
#include "Scenes/Game/MainMenu.h"
#include "Scenes/Game/Level1.h"
#include "Scenes/Game/LoseScene.h"
#include "Scenes/Game/WinScene.h"
#include "Scenes/Game/ControlSchemeScene.h"
#endif

#pragma endregion

//Game is preparing
void MainGame::OnGamePreparing(GameContext& gameContext)
{
	//Here you can change some game settings before engine initialize
	//gameContext.windowWidth=... (default is 1280)
	//gameContext.windowHeight=... (default is 720)

	gameContext.windowTitle = L"GP2 - Exam Project (2023) | (2DAE15) Poppe Arno";
}

void MainGame::Initialize()
{
#ifdef W6
	SceneManager::Get()->AddGameScene(new HardwareSkinningScene());
#endif

#ifdef W8
	SceneManager::Get()->AddGameScene(new ShadowMappingScene());
#endif

#ifdef W9
	SceneManager::Get()->AddGameScene(new ParticleScene());
#endif

#ifdef W11
	SceneManager::Get()->AddGameScene(new DeferredRenderingScene());
#endif

#ifdef ZeldaGame
	SceneManager::Get()->AddGameScene(new MainMenu());
	SceneManager::Get()->AddGameScene(new Level1());
	SceneManager::Get()->AddGameScene(new LoseScene());
	SceneManager::Get()->AddGameScene(new WinScene());
	SceneManager::Get()->AddGameScene(new ControlSchemeScene());
#endif
}

LRESULT MainGame::WindowProcedureHook(HWND /*hWnd*/, UINT message, WPARAM wParam, LPARAM lParam)
{

	if(message == WM_KEYUP)
	{
		if ((lParam & 0x80000000) != 0x80000000)
			return -1;

		//[F1] Toggle Scene Info Overlay
		if(wParam == VK_F1)
		{
			const auto pScene = SceneManager::Get()->GetActiveScene();
			pScene->GetSceneSettings().Toggle_ShowInfoOverlay();
		}

		//[F2] Toggle Debug Renderer (Global)
		if (wParam == VK_F2)
		{
			DebugRenderer::ToggleDebugRenderer();
			return 0;
		}

		//[F3] Previous Scene
		if (wParam == VK_F3)
		{
			SceneManager::Get()->PreviousScene();
			return 0;
		}

		//[F4] Next Scene
		if (wParam == VK_F4)
		{
			SceneManager::Get()->NextScene();
			return 0;
		}

		//[F5] If PhysX Framestepping is enables > Next Frame	
		if (wParam == VK_F6)
		{
			const auto pScene = SceneManager::Get()->GetActiveScene();
			pScene->GetPhysxProxy()->NextPhysXFrame();
		}
	}
	

	return -1;
}
