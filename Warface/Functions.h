#include "Classes.h"
#include "Menu.h"
#include "Utilities.h"

I3DEngine* p3DEngine;
IGame* pIGame;
ICVar* pIcvar;
SSystemGlobalEnvironment* pSSGE = (SSystemGlobalEnvironment*)(*(DWORD*)(SsystemGlobalEnvironmentAdressRU));
IGameFramework* pFrameWork = IGameFramework::GetGameFramework();

std::string name;
std::string ClassName;
std::string entidade_ativa = "aa";



#pragma region Utilities
float Distance(Vec3 VecA, Vec3 VecB)
{
	return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
		((VecA.z - VecB.z) * (VecA.z - VecB.z)));
}

extern "C" void __fastcall String(int x, int y, DWORD Color, DWORD Style, const char* Format, ...)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	char Buffer[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, Format);
	vsprintf_s(Buffer, Format, va_alist);
	va_end(va_alist);
	pFont->DrawTextA(NULL, Buffer, -1, &rect, Style, Color);

	return;
}

Vec3 GetPlayerPos(IEntity* pEntit)
{
	Vec3 vOffset = Vec3();
	Matrix34 pWorld = pEntit->GetWorldTM();
	vOffset = pWorld.GetTranslation();
	return vOffset;
}

Vec3 GetBonePositionByID(IEntity* pEnt, int BoneID)
{
	char* getBoneName;
	ICharacterInstance* pCharacterInstance = pEnt->GetCharacter(0);
	ISkeletonPose* pSkeletonPose = pCharacterInstance->GetISkeletonPose();
	int sBoneID = BoneID;
	Matrix34 World = pEnt->GetWorldTM();
	Matrix34 SkeletonAbs = Matrix34(pSkeletonPose->GetBoneByID(sBoneID));
	Matrix34 matWorld = World;
	float m03, m13, m23;
	m03 = (World.m00 * SkeletonAbs.m03) + (World.m01 * SkeletonAbs.m13) + (World.m02 * SkeletonAbs.m23) + World.m03;
	matWorld.m03 = m03;
	m13 = (World.m10 * SkeletonAbs.m03) + (World.m11 * SkeletonAbs.m13) + (World.m12 * SkeletonAbs.m23) + World.m13;
	matWorld.m13 = m13;
	m23 = (World.m20 * SkeletonAbs.m03) + (World.m21 * SkeletonAbs.m13) + (World.m22 * SkeletonAbs.m23) + World.m23;
	matWorld.m23 = m23;

	return matWorld.GetTranslation();
}

int GetTeam(IActor* ItActor)
{
	IGameFramework* pFrameWork = IGameFramework::GetGameFramework();
	if (ItActor)
		return pFrameWork->GetIGameRules()->GetTeam(ItActor->getIEntity()->GetID());//ItActor->getEntityId()
}

bool MyTeam(IActor* MePlayer, IActor* LocPlayer)
{
	int mTeam = GetTeam(MePlayer);
	int pTeam = GetTeam(LocPlayer);

	if ((mTeam != pTeam || pTeam == 0))
		return true;
	else
		return false;
}

enum Color : D3DCOLOR
{
	Aqua = 0xFF00FFFF,
	Aquamarine = 0xFF7FFFD4,
	WHITE = D3DCOLOR_ARGB(255, 255, 255, 255),
	GREEN = D3DCOLOR_ARGB(255, 000, 255, 000),
	BLACK = D3DCOLOR_ARGB(150, 000, 000, 000),
	PURPLE = D3DCOLOR_ARGB(255, 125, 000, 255),
	GREY = D3DCOLOR_ARGB(255, 128, 128, 128),
	YELLOW = D3DCOLOR_ARGB(255, 255, 255, 000),
	ORANGE = D3DCOLOR_ARGB(255, 255, 165, 000),
	DEEPSKYBLUE = D3DCOLOR_ARGB(255, 30, 144, 255),
	CHOCOLATE2 = D3DCOLOR_ARGB(255, 238, 118, 33),
	GOLD2 = D3DCOLOR_ARGB(255, 238, 201, 0),
	MyColor = D3DCOLOR_ARGB(255, 52, 52, 52),
	MyColor1 = D3DCOLOR_ARGB(255, 25, 25, 25),
	MyColor2 = D3DCOLOR_ARGB(255, 18, 18, 18),
	MyColor6 = D3DCOLOR_ARGB(255, 20, 20, 20),
	MyColor7 = D3DCOLOR_ARGB(220, 29, 29, 29),
	Orange = D3DCOLOR_ARGB(255, 255, 125, 000),
	OrangeWF = D3DCOLOR_ARGB(255, 219, 96, 8),
	Yellow = D3DCOLOR_ARGB(255, 255, 255, 000),
	Grey = D3DCOLOR_ARGB(255, 204, 204, 204),
	Purple = D3DCOLOR_ARGB(255, 125, 000, 255),
	White = D3DCOLOR_ARGB(255, 255, 255, 255),
	White2 = D3DCOLOR_ARGB(100, 255, 255, 255),
	//Red = D3DCOLOR_ARGB(255, 234, 62, 36),
	Green = D3DCOLOR_ARGB(255, 124, 216, 124),
	DARKGREEN = D3DCOLOR_ARGB(255, 34, 138, 15),
	Blue = D3DCOLOR_ARGB(255, 000, 186, 255),
	RED = D3DCOLOR_ARGB(255, 255, 000, 000),
	LIME = D3DCOLOR_ARGB(255, 204, 255, 000),
	Black = D3DCOLOR_ARGB(255, 000, 000, 000),
	BLUE = D3DCOLOR_ARGB(225, 000, 000, 255),
	BLACK_MENU = D3DCOLOR_ARGB(190, 40, 40, 40),
	Black2 = D3DCOLOR_ARGB(10, 26, 26, 26),
	Dark1 = D3DCOLOR_ARGB(255, 10, 10, 10),
	Dark2 = D3DCOLOR_ARGB(255, 26, 26, 26),
	Dark3 = D3DCOLOR_ARGB(255, 30, 30, 30),
	Dark4 = D3DCOLOR_ARGB(255, 40, 40, 40),
	Dark5 = D3DCOLOR_ARGB(255, 50, 50, 50),
	Dark6 = D3DCOLOR_ARGB(255, 62, 62, 62),
	Dark7 = D3DCOLOR_ARGB(255, 70, 70, 70),
	Dark8 = D3DCOLOR_ARGB(255, 80, 80, 80),
	Dark9 = D3DCOLOR_ARGB(255, 90, 90, 90),
	Dark10 = D3DCOLOR_ARGB(255, 100, 100, 100),
	HGREEN = D3DCOLOR_ARGB(255, 000, 255, 000),
	WARNRED = D3DCOLOR_ARGB(255, 207, 10, 10),
	WARNREDDARK = D3DCOLOR_ARGB(255, 130, 1, 1),
	BurlyWood = 0xFFDEB887,
	BlueViolet = 0xFF8A2BE2,
	AliceBlue = 0xFFF0F8FF
};

bool GetDeadPlayer(IActor* Player)
{
	if (Player->IsDead()) return true;
	else return false;
}

bool WorldToScreen(Vec3 vEntPos, Vec3* sPos)
{
	IRenderer::w2s_info info;
	info.Posx = vEntPos.x;
	info.Posy = vEntPos.y;
	info.Posz = vEntPos.z;

	info.Scrnx = &sPos->x;
	info.Scrny = &sPos->y;
	info.Scrnz = &sPos->z;

	pSSGE->pRenderer->ProjectToScreen(&info);

	if (sPos->z < 0.0f || sPos->z > 1.0f) {
		return 0;
	}

	sPos->x *= (Viewport.Width / 100.0f);
	sPos->y *= (Viewport.Height / 100.0f);
	sPos->z *= 1.0f;

	return (sPos->z < 1.0f);
}

bool IsEnemy(IEntity* pLclEnt, IEntity* pEnt)
{
	IGameFramework* pFrameWork = IGameFramework::GetGameFramework();
	IGameRules* pGameRules = pFrameWork->GetIGameRules();

	int pTeam = pGameRules->GetTeam(pEnt->GetID());
	int pLclTeam = pGameRules->GetTeam(pLclEnt->GetID());

	return (pLclTeam != 0) ? (pTeam != pLclTeam) : 1;
}

INT isVisible(Vec3 EnemyPos, Vec3 MyPos)
{
	Vec3 vTemp;
	ray_hit tmpHit;
	vTemp.x = EnemyPos.x - MyPos.x;
	vTemp.y = EnemyPos.y - MyPos.y;
	vTemp.z = EnemyPos.z - MyPos.z;
	return !pSSGE->pPhysicalWorld->RayWorldIntersection(MyPos, vTemp, 779, (10 & 0x0F), &tmpHit, 1);
}

void __fastcall BoneLine(int bone_1, int bone_2, IEntity* pEnt, DWORD color)
{
	Vec3 bone1 = GetBonePositionByID(pEnt, bone_1), bone2 = GetBonePositionByID(pEnt, bone_2);
	Vec3 outbone_1, outbone_2;
	WorldToScreen(bone1, &outbone_1); WorldToScreen(bone2, &outbone_2);
	Line(outbone_1.x, outbone_1.y, outbone_2.x, outbone_2.y, 1, color);
}

void __fastcall Circle(int X, int Y, int radius, int numSides, DWORD Color)
{
	D3DXVECTOR2 Line[128];
	float Step = (float)(D3DX_PI * 2.0 / numSides);
	int Count = 0;
	for (float a = 0; a < D3DX_PI * 2.0; a += Step)//2.0 = 0
	{
		float X1 = radius * cos(a) + X;
		float Y1 = radius * sin(a) + Y;
		float X2 = radius * cos(a + Step) + X;
		float Y2 = radius * sin(a + Step) + Y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}
	pLine->Begin();
	pLine->Draw(Line, Count, Color);
	pLine->End();
}

void __fastcall HeadDraw(int bone_1, int bone_2, IEntity* pEnt, DWORD color)
{
	Vec3 bone1 = GetBonePositionByID(pEnt, bone_1), bone2 = GetBonePositionByID(pEnt, bone_2);
	Vec3 outbone_1, outbone_2;
	WorldToScreen(bone1, &outbone_1); WorldToScreen(bone2, &outbone_2);
	Circle(outbone_2.x, outbone_2.y, 4, 15, color);
}

void __fastcall DrawSkeleton(IEntity* pEnt, DWORD color)
{
	BoneLine(3, 4, pEnt, color);
	BoneLine(3, 5, pEnt, color);
	BoneLine(3, 8, pEnt, color);
	BoneLine(8, 9, pEnt, color);
	BoneLine(9, 13, pEnt, color);
	BoneLine(13, 47, pEnt, color);
	BoneLine(13, 24, pEnt, color);
	BoneLine(47, 68, pEnt, color);
	BoneLine(24, 27, pEnt, color);
	BoneLine(68, 57, pEnt, color);
	BoneLine(27, 34, pEnt, color);
	BoneLine(4, 70, pEnt, color);
	BoneLine(70, 71, pEnt, color);
	BoneLine(5, 77, pEnt, color);
	BoneLine(77, 78, pEnt, color);
	HeadDraw(9, 16, pEnt, color);
	BoneLine(69, 49, pEnt, color);
	BoneLine(49, 52, pEnt, color);
	BoneLine(52, 60, pEnt, color);
	BoneLine(60, 61, pEnt, color);
	BoneLine(49, 53, pEnt, color);
	BoneLine(53, 62, pEnt, color);
	BoneLine(62, 63, pEnt, color);
	BoneLine(49, 54, pEnt, color);
	BoneLine(54, 64, pEnt, color);
	BoneLine(64, 65, pEnt, color);
	BoneLine(49, 55, pEnt, color);
	BoneLine(55, 66, pEnt, color);
	BoneLine(66, 67, pEnt, color);
	BoneLine(49, 51, pEnt, color);
	BoneLine(51, 58, pEnt, color);
	BoneLine(58, 59, pEnt, color);
	BoneLine(47, 15, pEnt, color);
	BoneLine(24, 14, pEnt, color);
	BoneLine(14, 15, pEnt, color);
	BoneLine(24, 25, pEnt, color);
	BoneLine(25, 26, pEnt, color);
	BoneLine(26, 27, pEnt, color);
	BoneLine(1, 3, pEnt, color);
	BoneLine(3, 8, pEnt, color);
	BoneLine(8, 9, pEnt, color);
	BoneLine(9, 10, pEnt, color);
	BoneLine(10, 12, pEnt, color);
	BoneLine(12, 13, pEnt, color);
	BoneLine(5, 1, pEnt, color);
	BoneLine(4, 1, pEnt, color);
	BoneLine(4, 70, pEnt, color);
	BoneLine(70, 71, pEnt, color);
	BoneLine(72, 73, pEnt, color);
	BoneLine(71, 73, pEnt, color);
	BoneLine(72, 75, pEnt, color);
	BoneLine(5, 77, pEnt, color);
	BoneLine(77, 78, pEnt, color);
	BoneLine(78, 80, pEnt, color);
	BoneLine(79, 80, pEnt, color);
	BoneLine(79, 82, pEnt, color);
}

extern "C" void Aim(IActor * MyActor, Vec3 EnemyBone)
{
	Vec3 vDiffer;
	vDiffer = EnemyBone - GetBonePositionByID(MyActor->getIEntity(), 18);//13 is head pvp
	Quat FinalHeadPos = Quat::CreateRotationVDir(vDiffer.normalize());
	MyActor->GetPlayer()->SetViewRotation(FinalHeadPos);
}

extern "C" void SilentAim(IActor * MyActor, Vec3 EnemyHead)
{
	if (!MyActor)
		return;
	MyActor->GetCurrentItem()->SetFiringPos(EnemyHead);
}

extern "C" void Box3D(IEntity * m_IEntity, DWORD Color)
{
	Vec3 Min, Max, vVec1, vVec2, vVec3, vVec4, vVec5, vVec6, vVec7, vVec8;
	AABB bBox;
	m_IEntity->GetWorldBounds(bBox);
	Max = bBox.max;
	Min = bBox.min;
	int width = 2;
	vVec3 = Min;
	vVec3.x = Max.x;
	vVec4 = Min;
	vVec4.y = Max.y;
	vVec5 = Min;
	vVec5.z = Max.z;
	vVec6 = Max;
	vVec6.x = Min.x;
	vVec7 = Max;
	vVec7.y = Min.y;
	vVec8 = Max;
	vVec8.z = Min.z;

	if (!WorldToScreen(Min, &vVec1))
		return;
	if (!WorldToScreen(Max, &vVec2))
		return;
	if (!WorldToScreen(vVec3, &vVec3))
		return;
	if (!WorldToScreen(vVec4, &vVec4))
		return;
	if (!WorldToScreen(vVec5, &vVec5))
		return;
	if (!WorldToScreen(vVec6, &vVec6))
		return;
	if (!WorldToScreen(vVec7, &vVec7))
		return;
	if (!WorldToScreen(vVec8, &vVec8))
		return;
	Line(vVec1.x, vVec1.y, vVec5.x, vVec5.y, width, Color);
	Line(vVec2.x, vVec2.y, vVec8.x, vVec8.y, width, Color);
	Line(vVec3.x, vVec3.y, vVec7.x, vVec7.y, width, Color);
	Line(vVec4.x, vVec4.y, vVec6.x, vVec6.y, width, Color);
	Line(vVec1.x, vVec1.y, vVec3.x, vVec3.y, width, Color);
	Line(vVec1.x, vVec1.y, vVec4.x, vVec4.y, width, Color);
	Line(vVec8.x, vVec8.y, vVec3.x, vVec3.y, width, Color);
	Line(vVec8.x, vVec8.y, vVec4.x, vVec4.y, width, Color);
	Line(vVec2.x, vVec2.y, vVec6.x, vVec6.y, width, Color);
	Line(vVec2.x, vVec2.y, vVec7.x, vVec7.y, width, Color);
	Line(vVec5.x, vVec5.y, vVec6.x, vVec6.y, width, Color);
	Line(vVec5.x, vVec5.y, vVec7.x, vVec7.y, width, Color);
}

int iFOV = 360;//M.FOVChoice
bool InFOV(Vec3 EnemyPos, IActor* MyActor)
{
	SMovementState sState;
	MyActor->GetMovementController()->GetMovementState(sState);

	Vec3 vDir = EnemyPos - sState.pos;
	Vec3 AimDir = sState.aimDirection;
	vDir.Normalize();

	float fVal = acos(vDir.Dot(AimDir) / (AimDir.GetLengthSquared() * vDir.GetLengthSquared())) * (180 / D3DX_PI);

	return (fVal <= iFOV);
}

Vec3 FindVisibleBoneFindV(IEntity* TargetEntity, Vec3 PlayerCamera)
{
	Vec3 BestBone = { 0, 0, 0 };

	for (int TestBone = 1; TestBone <= 86; TestBone++)
	{
		Vec3 DummyAim = GetBonePositionByID(TargetEntity, TestBone);

		if (isVisible(DummyAim, PlayerCamera))
		{
			BestBone = DummyAim;
			break;
		}

		else continue;
	}

	return BestBone;
}

extern "C" void Damage(IActor * mActor, INT DamageValue, INT Status)
{
	auto m_pItem = mActor->GetCurrentItem();
	if (m_pItem)
	{
		auto m_pWeapon = m_pItem->GetIWeapon();
		auto m_pExtraOne = m_pWeapon->m_pWeaponSpecific()->m_pWeaponExtraOne();
		auto weaponspec = m_pWeapon->m_pWeaponSpecific();
		if (Status)
		{
			m_pExtraOne->Damage(DamageValue);
		}
		else { m_pExtraOne->Damage(1); }
	}
}

extern "C" void Shutter(IActor * mActor, INT Status)
{
	auto m_pItem = mActor->GetCurrentItem();
	if (m_pItem)
	{
		auto m_pWeapon = m_pItem->GetIWeapon();
		auto m_pExtraOne = m_pWeapon->m_pWeaponSpecific()->m_pWeaponExtraOne();
		auto weaponspec = m_pWeapon->m_pWeaponSpecific();
		if (Status)
		{
			weaponspec->Shutter(0);
		}
		else { weaponspec->Shutter(1); }
	}
}

extern "C" void StartFire(IActor * mActor, INT Status)
{
	auto m_pItem = mActor->GetCurrentItem();
	if (m_pItem)
	{
		auto m_pWeapon = m_pItem->GetIWeapon();
		if (Status)
		{
			if (!mActor->IsDead())
			{
				m_pWeapon->StartFire();
			}
		}
	}
}


void Functions()
{

	IActor* MyPlayer = NULL;
	IActor* EnemyPlayer = NULL;
	IEntitySystem* pEntSys = NULL;
	IEntityIt* pEntIt = NULL;
	IEntity* MyEntity = NULL;
	IEntity* EnemyEntity = NULL;
	IEntityRenderProxy* pEntityRenderProxy = NULL;
	IGameRules* pGameRules = NULL;

	if (!pFrameWork)
		return;

	pGameRules = pFrameWork->GetIGameRules();
	if (!pGameRules)
		return;

	pEntSys = pSSGE->pEntitySystem;
	if (!pEntSys)
		return;

	pEntIt = pEntSys->GetEntityIterator();
	if (!pEntIt)
		return;

	if (!pFrameWork->GetClientActor(&MyPlayer))
		return;

	if (!MyPlayer)
		return;


	p3DEngine = pSSGE->p3DEngine;
	if (!p3DEngine)
		return;

	pIGame = pSSGE->pIGame;
	if (!pIGame)
		return;
	pIcvar = pIGame->GetICvar();
	if (!pIcvar)
		return;
	float OFF = 0;
	pIcvar->ACMemLog(OFF);
	pIcvar->ACMemScan(OFF);
	pIcvar->ACPatternScan(OFF);

	if (GetAsyncKeyState(VK_F10))
	{
		StartFire(MyPlayer, 1);
	}
	if (flashI)
	{
		//remove flashbang
		p3DEngine->SetPostEffectParam("Flashbang_Time", 0);
		p3DEngine->SetPostEffectParam("FlashBang_BlindAmount", 0);
		p3DEngine->SetPostEffectParam("Flashbang_DifractionAmount", 0);
		p3DEngine->SetPostEffectParam("Flashbang_Active", 0);
		//remove flashbang blurring
		p3DEngine->SetPostEffectParam("FilterRadialBlurring_Radius", 0);
		p3DEngine->SetPostEffectParam("FilterRadialBlurring_Amount", 0);
	}
	if (accuracyI)
	{
		pIcvar->SetIPelletsDisp(200);
		pIcvar->CrosshairSpreadTuning(0);
	}
	else
	{
		pIcvar->SetIPelletsDisp(0);
		pIcvar->CrosshairSpreadTuning(77);
	}
	if (minimapI)
	{
		pIcvar->silencer_shoot_spotting(1);
	}
	else
	{
		pIcvar->silencer_shoot_spotting(0);
	}
	if (reculI)
	{
		MyPlayer->GetPlayer()->m_ignoreRecoil = true;
	}
	else
	{
		MyPlayer->GetPlayer()->m_ignoreRecoil = false;
	}
	if (shutterI)
	{
		Shutter(MyPlayer, 3);
	}
	if (climbI)
	{
		MyPlayer->GetPlayer();
		//float aValue = 2.25f;
		MyPlayer->SetExtraClimbHeight(2.25f);
	}
	else
	{
		MyPlayer->GetPlayer();
		MyPlayer->SetExtraClimbHeight(0);
	}
	if (slideI)
	{
		MyPlayer->GetPlayer();
		float bValue = 20;
		MyPlayer->slideDistanceMult(bValue);
	}
	else
	{
		MyPlayer->GetPlayer();
		float bValue = 1;
		MyPlayer->slideDistanceMult(bValue);
	}
	if (noclaymoreI)
	{
		MyPlayer->GetPlayer();
		float eValue = 100;
		MyPlayer->claymore_detector_radius(eValue);
	}
	if (sprintI)
	{
		MyPlayer->GetPlayer();
		float gValue = 0;
		float iValue = 1.2;
		MyPlayer->minStaminaToStartHaste(gValue);
	}
	if (ammoI)
	{
		pIcvar->SetUnlimAmmo(1);
	}
	else
	{
		pIcvar->SetUnlimAmmo(0);
	}
	if (nosoundI)
	{
		pIcvar->i_soundeffects(0);
	}
	else
	{
		pIcvar->i_soundeffects(1);
	}
	if (damageI)
	{
		Damage(MyPlayer, 10, 1);
	}
	else
	{
		Damage(MyPlayer, 10, 0);
	}
	if (pickupI)
	{
		pIcvar->SetPickupDist(100);
	}
	else
	{
		pIcvar->SetPickupDist(2);
	}



	if (Mprecisao) {
		reculI = true;
		accuracyI = true;
	}
	else
	{
		reculI = false;
		accuracyI = false;
	}
	/////////////////////////
	if (Mnoflash) {
		flashI = true;
	}
	else
	{
		flashI = false;
	}
	/////////////////////////
	if (Mclaymore) {
		noclaymoreI = true;
	}
	else
	{
		noclaymoreI = false;
	}
	/////////////////////////
	if (mSprint) {
		sprintI = true;
	}
	else
	{
		sprintI = false;
	}
	/////////////////////////
	if (Mdamage) {
		damageI = true;
	}
	else
	{
		damageI = false;
	}
	/////////////////////////
	if (mShutter) {
		shutterI = true;
	}
	else
	{
		shutterI = false;
	}
	/////////////////////////
	if (mClimb) {
		climbI = true;
	}
	else
	{
		climbI = false;
	}
	/////////////////////////
	if (Mslide) {
		slideI = true;
	}
	else
	{
		slideI = false;
	}
	/////////////////////////
	if (mAmmo) {
		ammoI = true;
	}
	else
	{
		ammoI = false;
	}
	/////////////////////////
	if (mNosound) {
		nosoundI = true;
	}
	else
	{
		nosoundI = false;
	}
	/////////////////////////
	if (MvectorAim) {
		vectorI = true;
	}
	else
	{
		vectorI = false;
	}
	/////////////////////////
	if (mSilent) {
		silentI = true;
	}
	else
	{
		silentI = false;
	}
	/////////////////////////
	if (MGlow) {
		glowI = true;
	}
	else
	{
		glowI = false;
	}
	/////////////////////////
	if (MGlowHB) {
		glowhealthbasedI = true;
	}
	else
	{
		glowhealthbasedI = false;
	}
	/////////////////////////
	if (mRotate) {
		rotateshieldI = true;
	}
	else
	{
		rotateshieldI = false;
	}
	/////////////////////////
	if (mPickup) {
		pickupI = true;
	}
	else
	{
		pickupI = false;
	}

	for (; IEntity * pEnt = pEntIt->Next(); )
	{
		if (!pEnt)
			continue;

		name = pEnt->GetName();

		if ((strstr(name.c_str(), XorString("Turret")) ||
			strstr(name.c_str(), XorString("IronMan")) ||
			strstr(name.c_str(), XorString("Cyborg")) ||
			strstr(name.c_str(), XorString("Black_Wolf")) ||
			strstr(name.c_str(), XorString("Mantis")) ||
			strstr(name.c_str(), XorString("SEDSoldier")) ||
			strstr(name.c_str(), XorString("Drone")) ||
			strstr(name.c_str(), XorString("capsule")) ||
			strstr(name.c_str(), XorString("claymore")) ||
			strstr(name.c_str(), XorString("Mech"))))

			continue;







		if (EnemyPlayer = pFrameWork->GetIActorSystem()->GetActor(pEnt->GetID()))
		{
			if (MyPlayer != EnemyPlayer)
			{

				MyEntity = MyPlayer->getIEntity();
				if (!MyEntity)
					continue;


				EnemyEntity = EnemyPlayer->getIEntity();
				if (!EnemyEntity)
					continue;

				if (EnemyPlayer->IsDead())
					continue;








				Vec3 EnemyPos = GetPlayerPos(pEnt);
				Vec3 Head = GetBonePositionByID(pEnt, 13), Head2;
				Vec3 pHead = GetBonePositionByID(pEnt, 18);
				Vec3 mHead = GetBonePositionByID(MyPlayer->getIEntity(), 18);

				Vec3 Mpos = GetPlayerPos(MyEntity);
				Vec3 EnemyBone{ 0, 0, 0 };
				Vec3 Out;
				EnemyBone = GetBonePositionByID(pEnt, 13);//pvp


				//if (strstr(name.c_str(), XorString("Drone"))) EnemyBone = GetBonePositionByID(pEnt, 12);
				//if (strstr(name.c_str(), XorString("Turret"))) EnemyBone = GetBonePositionByID(pEnt, 1);
				//if (strstr(name.c_str(), XorString("TurretWall"))) EnemyBone = GetBonePositionByID(pEnt, 47);
				//if (strstr(name.c_str(), XorString("TurretCeil"))) EnemyBone = GetBonePositionByID(pEnt, 78);
				//if (strstr(name.c_str(), XorString("TurretFloor_ASR")) || strstr(name.c_str(), XorString("Turret_ASR_Target"))) EnemyBone = GetBonePositionByID(pEnt, 62);
				//if (strstr(name.c_str(), XorString("CQBHeavy"))) EnemyBone = GetBonePositionByID(pEnt, 13);
				//if (strstr(name.c_str(), XorString("SMGHeavy"))) EnemyBone = GetBonePositionByID(pEnt, 13);
				//if (strstr(name.c_str(), XorString("TurretFloor_cqb")) || strstr(name.c_str(), XorString("TurretFloor_CQB")) || strstr(name.c_str(), XorString("TurretHunt_CQB"))) EnemyBone = GetBonePositionByID(pEnt, 58);
				//if (strstr(name.c_str(), XorString("TurretFloor_mg")) || strstr(name.c_str(), XorString("TurretFloor_MG")) || strstr(name.c_str(), XorString("TurretHunt_MG")) || strstr(name.c_str(), XorString("TurretRail_mg")) || strstr(name.c_str(), XorString("Turret_MG"))) EnemyBone = GetBonePositionByID(pEnt, 68);
				//if (strstr(name.c_str(), XorString("HeavyTurretRail"))) EnemyBone = GetBonePositionByID(pEnt, 52);

				//if (strstr(name.c_str(), XorString("Iron"))) EnemyBone = GetBonePositionByID(pEnt, 9);
				//if (strstr(name.c_str(), XorString("SEDAssault"))) EnemyBone = GetBonePositionByID(pEnt, 60);
				//if (strstr(name.c_str(), XorString("SEDSoldier"))) EnemyBone = GetBonePositionByID(pEnt, 58);















				if (glowI)
				{
					if (MyTeam(MyPlayer, EnemyPlayer))
					{

						if (isVisible(EnemyBone, mHead) && glowVisible)
						{
							pEntityRenderProxy = (IEntityRenderProxy*)(pEnt->GetProxy(ENTITY_PROXY_RENDER));
							if (!pEntityRenderProxy)
								continue;
							pEntityRenderProxy->SetRndFlags(eAllMap);
							pEntityRenderProxy->SetHUDSilhouettesParams(GlowColor[0], GlowColor[1], GlowColor[2], 0.0 );
						}
						else
						{
							pEntityRenderProxy = (IEntityRenderProxy*)(pEnt->GetProxy(ENTITY_PROXY_RENDER));
							if (!pEntityRenderProxy)
								continue;
							pEntityRenderProxy->SetRndFlags(eAllMap);
							pEntityRenderProxy->SetHUDSilhouettesParams(GlowColorHide[0], GlowColorHide[1], GlowColorHide[2], 0.0);


						}

					}


				}

				if (skeleton)
				{
					if (MyTeam(MyPlayer, EnemyPlayer))
					{

						DrawSkeleton(pEnt, Color::Green);

					}


				}




				if (MyTeam(MyPlayer, EnemyPlayer) && (!GetDeadPlayer(EnemyPlayer)))
				{
					if ((WorldToScreen(Head, &Head2)) && (WorldToScreen(EnemyPos, &Out) && (!GetDeadPlayer(EnemyPlayer))) && (MyTeam(MyPlayer, EnemyPlayer)))
					{
						float h = abs(Out.y - Head2.y);
						float w = h / 1.25f;
						float ScaledPosX = Head2.x + w / 2 + 5;
						float ScaledPosY = (Head2.y - (w / 2) + w) - 4;
						EnemyBone = GetBonePositionByID(pEnt, 13);//pvp
						float Distancion;
						Distancion = Distance(GetPlayerPos(MyEntity), GetPlayerPos(pEnt));
						if (!Distancion)
							continue;


						if ((InFOV(pHead, MyPlayer)) && isVisible(EnemyBone, mHead))
						{
							if (vectorI)
								if (GetAsyncKeyState(VK_RBUTTON))
								{
									if (!MyPlayer->IsDead())
									{
										Aim(MyPlayer, EnemyBone);
										MyPlayer->GetCurrentItem()->GetIWeapon()->StartFire();
									}
								}
							if (silentI)
								if (!MyPlayer->IsDead())
								{
									SilentAim(MyPlayer, EnemyBone);
								}
						}
						else
						{
							continue;
						}
					}
					else
					{
						continue;
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}
}