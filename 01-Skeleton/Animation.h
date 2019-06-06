#pragma once
#include "enums.h"
#include "Sprite.h"


class Animation
{
private:
	const Sprite& sprite                                  ;
	const float   holdTime                                ;
	      float   holdingTime = 0.0f                      ;
	const UINT    nFrames     = sprite.GetNumberOfFrames();
	      UINT    curFrame    = 0u                        ;
	      bool    doneCycle   = false                     ;

public:
	Animation(SpriteType spriteId, float holdTime = std::numeric_limits<float>::infinity()); // infinity foldTime indicates static animation (only has 1 frame)

	void Update(float dt);
	void Render(const Point& pos, const Vector2& vtScale = { 1.0f, 1.0f }, int alpha = 255) const;

	bool IsDoneCycle(); // for some animation aimed to animate one cycle each call
	Rect GetFrameSize(const Vector2& vtScale = { 1.0f, 1.0f }) const;

};

