#pragma once
#include <queue>

class GameEvent
{
public:
	enum class Type
	{
		GameLost,
		GameWon
	};

	Type type;


};


static std::queue<GameEvent> eventQueue;

class GameEventsQueue
{

public:

	friend void pushGameEvent(const GameEvent & event);

	friend bool pollGameEvent(GameEvent & event);
};

