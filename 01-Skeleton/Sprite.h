#pragma once
#include <d3dx9.h>

// to draw static sprite
class Sprite
{
private:
	const LPDIRECT3DTEXTURE9 pTexture;
	const RECT               portion ;

public:
	Sprite(LPDIRECT3DTEXTURE9 texture, RECT portion); 
	void Draw(const D3DXVECTOR3& pos, bool isFlipX = false, int alpha = 255) const;
};



