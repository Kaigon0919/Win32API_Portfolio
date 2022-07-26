#include"stdafx.h"
#include"SystemClass.h"
#include"LevelHeaders.h"
#include"ResourceManager.h"

bool SystemClass::UserInit()
{
	// 虐 积己何.
	InputManager::Instance().CreateKey(L"LMouse", VK_LBUTTON);
	InputManager::Instance().CreateKey(L"RMouse", VK_RBUTTON);

#ifdef _DEBUG

	InputManager::Instance().CreateKey(L"SpaceBar", VK_SPACE);
	InputManager::Instance().CreateKey(L"Exit", VK_ESCAPE);

	InputManager::Instance().CreateKey(L"Prev", L'Q');
	InputManager::Instance().CreateKey(L"Next", L'E');
	InputManager::Instance().CreateKey(L"Shift+LMouse", VK_SHIFT, VK_LBUTTON);

	InputManager::Instance().CreateKey(L"LevelPrev", VK_SHIFT, L'Q');
	InputManager::Instance().CreateKey(L"LevelNext", VK_SHIFT, L'E');
#endif
	// Edit 傈侩 虐.
	InputManager::Instance().CreateKey(L"Up", L'W');
	InputManager::Instance().CreateKey(L"Down", L'S');
	InputManager::Instance().CreateKey(L"Left", L'A');
	InputManager::Instance().CreateKey(L"Right", L'D');
	InputManager::Instance().CreateKey(L"MapPrev", VK_SHIFT, L'R');
	InputManager::Instance().CreateKey(L"MapNext", VK_SHIFT, L'F');
	InputManager::Instance().CreateKey(L"TilePrev", L'R');
	InputManager::Instance().CreateKey(L"TileNext", L'F');
	InputManager::Instance().CreateKey(L"BackSpace", VK_BACK);
	InputManager::Instance().CreateKey(L"ChangeMode", L'M');

	InputManager::Instance().CreateKey(L"Save", VK_CONTROL, L'S');
	InputManager::Instance().CreateKey(L"Load", VK_CONTROL, L'O');
	InputManager::Instance().CreateKey(L"Clear", L'C');

	// 府家胶 积己何.
	ResourceManager::Instance().Init();

	// 菩胶 积己.
	ResourceManager::Instance().RootToCreatePath(L"Image");
	ResourceManager::Instance().RootToCreatePath(L"Mouse", L"Image\\Mouse");
	ResourceManager::Instance().RootToCreatePath(L"Map", L"Image\\Map");
	ResourceManager::Instance().RootToCreatePath(L"Character", L"Image\\Character");
	ResourceManager::Instance().RootToCreatePath(L"Title", L"Image\\Title");
	ResourceManager::Instance().RootToCreatePath(L"Monster", L"Image\\Monster");
	ResourceManager::Instance().RootToCreatePath(L"Effect", L"Image\\Effect");
	ResourceManager::Instance().RootToCreatePath(L"Tile", L"Image\\Tile");
	ResourceManager::Instance().RootToCreatePath(L"Sound", L"Sound");
	ResourceManager::Instance().RootToCreatePath(L"MapData", L"Image\\Map\\MapData");
	ResourceManager::Instance().RootToCreatePath(L"UI", L"Image\\UI");
	ResourceManager::Instance().RootToCreatePath(L"Object", L"Image\\Object");
	ResourceManager::Instance().RootToCreatePath(L"Data", L"data");



	//////////////////////////////////////////////////////////////////////////////////
	// bmp 肺靛.

	// title 肺靛.
	ResourceManager::Instance().LoadToPathBmp(L"Title", L"title01.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Title", L"title02.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Title", L"title03.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Title", L"title04.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Title", L"title05.bmp");

	// character 肺靛.
	ResourceManager::Instance().LoadToPathBmp(L"Character", L"Stand.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Character", L"Motion.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Character", L"Shadow.bmp");

	// mouse 肺靛.
	ResourceManager::Instance().LoadToPathBmp(L"Mouse", L"mouse.bmp");

	// map 肺靛.
	ResourceManager::Instance().LoadToPathBmp(L"Map", L"map01.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Map", L"map02.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Map", L"map03.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Map", L"map04.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Map", L"map05.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Map", L"map06.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Map", L"Field.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Map", L"Boss.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Map", L"Dungeon.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Map", L"ItemShop.bmp");
	// map tile Load.
	ResourceManager::Instance().LoadToPathBmp(L"Tile", L"tile01.bmp");

	// Monster Load.
	ResourceManager::Instance().LoadToPathBmp(L"Monster", L"Monster4.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Monster", L"Monster5.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Monster", L"Monster25.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Monster", L"Monster213.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Monster", L"Monster243.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Monster", L"Monster245.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Monster", L"Monster248.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Monster", L"Monster441.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Monster", L"Monster504.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Monster", L"Monster512.bmp");

	//Effect Load.
	ResourceManager::Instance().LoadToPathBmp(L"Effect", L"hitEffect.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Effect", L"DragonArrow1.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Effect", L"FireArrow.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"Effect", L"Skill1.bmp",RGB(0,0,0));

	// Ui Load.
	ResourceManager::Instance().LoadToPathBmp(L"UI", L"DamageFont.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"UI", L"DamageFontMonster.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"UI", L"State.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"UI", L"StateBack.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"UI", L"Hp.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"UI", L"Mp.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"UI", L"Sp.bmp");
	ResourceManager::Instance().LoadToPathBmp(L"UI", L"HpBack.bmp");

	// Object Load.
	ResourceManager::Instance().LoadToPathBmp(L"Object", L"warp1.bmp", RGB(255, 0, 255));
	ResourceManager::Instance().LoadToPathBmp(L"Object", L"warp2.bmp");


	//////////////////////////////////////////////////////////////////////////////////
	// sprite 积己.

	//title sprite 积己.
	ResourceManager::Instance().CreateSprite(L"title01.bmp");
	ResourceManager::Instance().CreateMultiSprite(L"TitleStart", L"title02.bmp", { 2, 1 });
	ResourceManager::Instance().CreateMultiSprite(L"TitleOpenning", L"title03.bmp", { 2, 1 });
	ResourceManager::Instance().CreateMultiSprite(L"TitleCredit", L"title04.bmp", { 2, 1 });
	ResourceManager::Instance().CreateMultiSprite(L"TitleQuit", L"title05.bmp", { 2, 1 });

	// character sprite 积己.
	ResourceManager::Instance().CreateMultiSprite(L"Character", L"Stand.bmp", { 55, 9 });
	ResourceManager::Instance().CreateMultiSprite(L"CharacterMotion", L"Motion.bmp", { 16, 14 });
	ResourceManager::Instance().CreateSprite(L"Shadow.bmp");

	// map sprite 积己.
	ResourceManager::Instance().CreateSprite(L"map01.bmp");
	ResourceManager::Instance().CreateSprite(L"map02.bmp");
	ResourceManager::Instance().CreateSprite(L"map03.bmp");
	ResourceManager::Instance().CreateSprite(L"map04.bmp");
	ResourceManager::Instance().CreateSprite(L"map05.bmp");
	ResourceManager::Instance().CreateSprite(L"map06.bmp");
	ResourceManager::Instance().CreateSprite(L"Field.bmp");
	ResourceManager::Instance().CreateSprite(L"Boss.bmp");
	ResourceManager::Instance().CreateSprite(L"Dungeon.bmp");
	ResourceManager::Instance().CreateSprite(L"ItemShop.bmp");
	// Tile sprite 积己.
	ResourceManager::Instance().CreateMultiSprite(L"Tile01", L"tile01.bmp", { 2, 5 });

	// mouse sprite 积己.
	ResourceManager::Instance().CreateMultiSprite(L"Mouse", L"mouse.bmp", { 2, 31 });

	// Monster sprite 积己.
	ResourceManager::Instance().CreateMultiSprite(L"Monster4", L"Monster4.bmp", { 26, 4 });
	ResourceManager::Instance().CreateMultiSprite(L"Monster5", L"Monster5.bmp", { 26, 4 });
	ResourceManager::Instance().CreateMultiSprite(L"Monster25", L"Monster25.bmp", { 26, 4 });
	ResourceManager::Instance().CreateMultiSprite(L"Monster213", L"Monster213.bmp", { 28, 4 });
	ResourceManager::Instance().CreateMultiSprite(L"Monster243", L"Monster243.bmp", { 24, 4 });
	ResourceManager::Instance().CreateMultiSprite(L"Monster245", L"Monster245.bmp", { 20, 4 });
	ResourceManager::Instance().CreateMultiSprite(L"Monster248", L"Monster248.bmp", { 19, 4 });
	ResourceManager::Instance().CreateMultiSprite(L"Monster441", L"Monster441.bmp", { 23, 4 });
	ResourceManager::Instance().CreateMultiSprite(L"Monster504", L"Monster504.bmp", { 28, 4 });
	ResourceManager::Instance().CreateMultiSprite(L"Monster512", L"Monster512.bmp", { 25, 4 });

	// Effect sprite 积己.
	ResourceManager::Instance().CreateMultiSprite(L"HitEffect", L"hitEffect.bmp", { 4, 1 });
	ResourceManager::Instance().CreateMultiSprite(L"DragonArrow1", L"DragonArrow1.bmp", { 8, 1 });
	ResourceManager::Instance().CreateMultiSprite(L"FireArrow", L"FireArrow.bmp", { 5, 9 });
	ResourceManager::Instance().CreateMultiSprite(L"Skill1", L"Skill1.bmp", { 9, 1 });

	// UI spirte 积己.
	ResourceManager::Instance().CreateMultiSprite(L"DamageUI", L"DamageFont.bmp", { 10, 1 });
	ResourceManager::Instance().CreateMultiSprite(L"DamageUIMonster", L"DamageFontMonster.bmp", { 10, 1 });
	ResourceManager::Instance().CreateSprite(L"State.bmp");
	ResourceManager::Instance().CreateSprite(L"StateBack.bmp");
	ResourceManager::Instance().CreateSprite(L"Hp.bmp");
	ResourceManager::Instance().CreateSprite(L"Mp.bmp");
	ResourceManager::Instance().CreateSprite(L"Sp.bmp");
	ResourceManager::Instance().CreateSprite(L"HpBack.bmp");

	// Ojbect Sprite 积己.
	ResourceManager::Instance().CreateSprite(L"warp1.bmp");
	ResourceManager::Instance().CreateSprite(L"warp2.bmp");

	// Sound
	ResourceManager::Instance().LoadSound(L"Sound", L"Hit.wav");
	ResourceManager::Instance().LoadSound(L"Sound", L"DungeonBGM.mp3");
	ResourceManager::Instance().LoadSound(L"Sound", L"TitleButtonDown.wav");
	ResourceManager::Instance().LoadSound(L"Sound", L"Title.wav");
	ResourceManager::Instance().LoadSound(L"Sound", L"TownBGM.wav");


	// 饭骇 积己何.
	CreateLevel<TitleLevel>(ALLSTATE::TITLE);
	CreateLevel<EditLevel>(ALLSTATE::EDIT);
	CreateLevel<VillageLevel>(ALLSTATE::Village);
	CreateLevel<Stage1Level>(ALLSTATE::Stage1);
	CreateLevel<Stage2Level>(ALLSTATE::Stage2);
	CreateLevel<Stage3Level>(ALLSTATE::Stage3);
#ifdef _DEBUG
	CreateLevel<TestLevel>(ALLSTATE::Test);
	ChangeLevel(ALLSTATE::TITLE);
#else
	ChangeLevel(ALLSTATE::TITLE);
#endif
	ChangeUpdate();

	return true;
}