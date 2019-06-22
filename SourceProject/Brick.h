#pragma once
#include "VisibleObject.h"

class Brick : public VisibleObject
{
public:
	Brick(const Vector3& pos) :
		VisibleObject(State::BrickIdle, pos)
	{
		animations.emplace(State::BrickIdle, Animation(SpriteId::BrickIdle));
	}

	RectF GetBBox() const override
	{
		return VisibleObject::GetBBox().Trim(1.5f, 1, 1.5f, 1);
	}
};
