#pragma once
class SpriteCommon;
class Sprite
{
public:
	void Initialize(SpriteCommon* spriteCommon=nullptr);
private:
	SpriteCommon* spriteCommon=nullptr;

};

