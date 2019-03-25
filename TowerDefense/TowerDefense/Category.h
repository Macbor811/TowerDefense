#pragma once


namespace ReceiverCategory
{
	enum Type
	{
		None = 0,
		TowerSlot = 1 << 0,
		Tower = 1 << 1,
		Projectile = 1 << 2,
		Enemy = 1 << 3,
		Any = 1 << 4,
		Player = 1 << 5,
		HUD = 1 << 6,
		Button = 1 << 7
	};
}