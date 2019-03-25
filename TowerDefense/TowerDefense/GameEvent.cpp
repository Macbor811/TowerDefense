#include "GameEvent.h"

void pushGameEvent(const GameEvent & event)
{
	eventQueue.push(event);
}

bool pollGameEvent(GameEvent & event)
{
	if (eventQueue.empty())
		return false;
	else
	{
		event = eventQueue.front();
		eventQueue.pop();
		return true;
	}
}
