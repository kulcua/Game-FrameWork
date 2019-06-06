#include "pch.h"
#include "GameBase.h"


GameBase::~GameBase()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

void GameBase::Draw(const Point& pos, const LPDIRECT3DTEXTURE9 texture, const Rect& portion, const Vector2& vtScale, int alpha) const
{
	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	if (vtScale != Vector2(1.0f, 1.0f))
	{
		const float bboxWidth   = portion.GetWidth () * std::abs(vtScale.x);
		const float bboxHeight  = portion.GetHeight() * std::abs(vtScale.y);
		Vector2 centerScale = { pos.x + bboxWidth / 2, pos.y + bboxHeight / 2 };
		D3DXMATRIX newMt;
		D3DXMatrixTransformation2D(&newMt, &centerScale, 0.0f, &vtScale, NULL, 0.0f, NULL);
		newMt *= oldMt;
		spriteHandler->SetTransform(&newMt);
	}

	//Draw function: https://docs.microsoft.com/en-us/windows/desktop/direct3d9/id3dxsprite--draw
	spriteHandler->Draw(texture, &portion, NULL, &pos, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	spriteHandler->SetTransform(&oldMt);
}

void GameBase::InitGame()
{
	wnd.InitWindow();
	InitDirectDevice();
	LoadResources();
}

void GameBase::InitDirectDevice()
{
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed         = TRUE;
	d3dpp.SwapEffect       = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount  = 1;
	d3dpp.BackBufferHeight = wnd.GetHeight();
	d3dpp.BackBufferWidth  = wnd.GetWidth();

	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	d3d->CreateDevice(
	     D3DADAPTER_DEFAULT,
	     D3DDEVTYPE_HAL,
	     wnd.GetHWnd(),
	     D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	     &d3dpp,
	     &d3ddv);

	if (d3ddv == nullptr) ThrowMyException("Create DirectX Device failed");

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	D3DXCreateSprite(d3ddv, &spriteHandler);
}

void GameBase::Render()
{
	if (d3ddv->BeginScene())	
	{
		d3ddv->ColorFill(backBuffer, NULL, D3DCOLOR_XRGB(200, 200, 200)); // TODO: When having texture background, color background is needless
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		ComposeFrame(); // actual development render
		spriteHandler->End();
		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void GameBase::Run()
{
	while (wnd.ProcessMessage())
	{
		GameTimer::BeginFrame();
		Update(GameTimer::DeltaTime());
		Render();
	}
}






