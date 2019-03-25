#pragma once

#include "Category.h"

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>
#include <queue>

class SceneNode;



struct Command
{
	using Action = std::function<void(SceneNode&, sf::Time)> ;


	Action action;
	unsigned int category = ReceiverCategory::None;
};

using CommandQueue = std::queue<Command>;

template <typename GameObject, typename Function>
Command::Action derivedAction(Function fn)
{
	return [fn](SceneNode& node, sf::Time dt)
	{
		// Sprawdza czy mozna bezpiecznie rzutowac
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Dokonuje rzutowania
		fn(static_cast<GameObject&>(node), dt);
	};
}
