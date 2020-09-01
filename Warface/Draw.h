#pragma once
#include "Includes.h"

#define BRANCO		D3DCOLOR_ARGB(255,255,255,255)
#define PRETO		D3DCOLOR_ARGB(255,0,0,0)
#define VERMELHO    D3DCOLOR_ARGB(255,255,0,0)
#define AGUA		D3DCOLOR_ARGB(255,0,238,238)
#define LIMAT		D3DCOLOR_ARGB(100,0,255,0)
#define VERDE		D3DCOLOR_ARGB(255,0,255,0)
#define LARANJARV	D3DCOLOR_ARGB(140,255,44,0)
#define CHOCOLATE	D3DCOLOR_ARGB(255,160,82,0)
#define AZUL		D3DCOLOR_ARGB(180,0,0,255)
#define GOLD		D3DCOLOR_ARGB(255,244,214,0)
#define Red			D3DCOLOR_ARGB(150, 255, 000, 000)

#define PI 3.14159265//Defining what PI is. PI is a Circle
int CenterX = GetSystemMetrics(0) / 2 - 1;
int CenterY = GetSystemMetrics(1) / 2 - 1;
int ScreenWidth = 0;
int ScreenHeight = 0;
int ScreenCenterX = 0;
int ScreenCenterY = 0;

D3DVIEWPORT9 Viewport;
ID3DXLine* pLine;
LPDIRECT3DTEXTURE9 Vermelho, amarelo, verde, azul;
LPD3DXFONT pFont;

int Esquerda = 25, Topo = 80;
int Altura = 110, largura = 200;
int X = (Esquerda + 6), Y = (Topo + 6);
int total_items = 0;
int index = 0;
bool Gerartexture = true;
bool bShow = true;
bool crossh = false;

struct  items_ {

	bool seleted, on_off;
};

items_ itens[200];
bool glow;
bool precisao;
static bool flashI = false;
static bool accuracyI = false;
static bool minimapI = false;
static bool reculI = false;
static bool shutterI = false;
static bool climbI = false;
static bool slideI = false;
static bool noclaymoreI = false;
static bool sprintI = false;
static bool ammoI = false;
static bool nosoundI = false;
static bool damageI = false;
static bool espexplosiI = false;
static bool espnotificationI = false;
static bool esphealthbarI = false;
static bool espdistanceI = false;
static bool espnameI = false;
static bool espskeletonI = false;
static bool espboxI = false;
static bool glowI = false;
static bool glowhealthbasedI = false;
static bool esplinesI = false;
static bool autoshootI = false;
static bool vectorI = false;
static bool silentI = false;
static bool rotateshieldI = false;
static bool pickupI = false;
static bool wallshotI = false;
static bool mi3j2n321312c = false;
static bool moic897217232 = false;
static int damagecount = 1;


static bool Mnoflash = false;
static bool MvectorAim = false;
static bool Mslide = false;
static bool Mminimap = false;
static bool MGlow = false;
static bool Mprecisao = false;
static bool Mclaymore = false;
static bool mSprint = false;
static bool Mdamage = false;
static bool mShutter = false;
static bool mClimb = false;
static bool mAmmo = false;
static bool mNosound = false;
static bool mSilent = false;
static bool MGlowHB = false;
static bool mRotate = false;
static bool mPickup = false;

void CreatFont(LPDIRECT3DDEVICE9 pD3D9) {

	if (!pFont) {

		D3DXCreateFont(pD3D9, 16, 0, FW_BOLD, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
	}
}
void ResetFont() {

	pFont->OnLostDevice();
	pFont->OnResetDevice();

}

void  Text(int x, int y, const char* text, DWORD color)
{
	RECT rect, rect2;
	SetRect(&rect, x, y, x, y);
	SetRect(&rect2, x - 0.1, y + 0.2, x - 0.1, y + 0.);
	pFont->DrawTextA(NULL, text, -1, &rect2, DT_LEFT | DT_NOCLIP, 0x00000000);
	pFont->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, color);
}

void  DrawBox(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	V[4] = { { x, y + h, 0.0f, 0.0f, Color },{ x, y, 0.0f, 0.01, Color },
	{ x + w, y + h, 0.0f, 0.0f, Color },{ x + w, y, 0.0f, 0.0f, Color } };
	pD3D9->SetTexture(0, NULL);
	pD3D9->SetPixelShader(0);
	pD3D9->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pD3D9->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pD3D9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3D9->SetRenderState(D3DRS_ZENABLE, FALSE);
	pD3D9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pD3D9->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	return;
}



void DrawItem(items_ its, const char* texto, LPDIRECT3DDEVICE9 pDevice) {
	total_items++;
	if (its.seleted)

		DrawBox(Esquerda + 3, Y, largura - 6, 20, CHOCOLATE, pDevice);
	else
		DrawBox(Esquerda + 3, Y, largura - 6, 20, LARANJARV, pDevice);

	if (its.on_off)

		Text(X + 150, Y + 3, " [ON]", VERDE);
	else

		Text(X + 150, Y + 3, "[OFF]", VERMELHO);

	Text(X + 8, Y + 3, texto, GOLD);
	Y += 25;
}



void FillRGB(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice)
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawCircle(int X, int Y, int radius, int numSides, DWORD Color)
{
	D3DXVECTOR2 Line[128];
	float Step = PI * 2.0 / numSides;
	int Count = 0;
	for (float a = 0; a < PI * 2.0; a += Step)
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

void DrawPoint(int x, int y, int w, int h, DWORD color, IDirect3DDevice9* pDevice)
{
	FillRGB((int)x, (int)y, (int)w, (int)h, color, pDevice);
}

void DrawLine(float x, float y, float x2, float y2, float width, DWORD color)
{
	D3DXVECTOR2 vLine[2];
	pLine->SetWidth(width);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();
}

void Line(float x, float y, float x2, float y2, float width, DWORD color)
{
	D3DXVECTOR2 vLine[2];
	pLine->SetWidth(width);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();

	return;
}

void creatline(LPDIRECT3DDEVICE9 pDevice) {

	if (!pLine) {
		D3DXCreateLine(pDevice, &pLine);
		pLine->SetAntialias(true);
		pLine->SetWidth(1.0f);
	}

}

void resetline() {
	pLine->OnLostDevice();
	pLine->OnResetDevice();

}


void crosshair(LPDIRECT3DDEVICE9 pDevice) {

	creatline(pDevice);
	HWND atual = GetActiveWindow();
	RECT rect;
	GetWindowRect(atual, &rect);
	int larg = rect.right - rect.left;
	int alt = rect.bottom - rect.top;
	CenterX = (larg / 2) + 4;
	CenterY = (alt / 2) + 14;
	FillRGB(CenterX - 15, CenterY, 30, 1, VERMELHO, pDevice);//Diagonal line
	FillRGB(CenterX, CenterY - 15, 1, 30, VERMELHO, pDevice);//Vertical line


	resetline();

}

void keyboard() {

	if (GetAsyncKeyState(VK_UP) & 1) {
		if (index > 0) {
			itens[index].seleted = false;
			index--;
		}
		else {
			itens[index].seleted = false;
			index = total_items - 1;

		}

	}


	if (GetAsyncKeyState(VK_DOWN) & 1) {
		if (index < total_items - 1) {
			itens[index].seleted = false;
			index++;
		}
		else {
			itens[index].seleted = false;
			index = 0;

		}
	}

	if (GetAsyncKeyState(VK_DELETE) & 1)
		bShow = (!bShow);


	itens[index].seleted = true;
}