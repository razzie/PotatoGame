/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <future>
#include <raz/memory.hpp>
#include "game/level/Level.hpp"

class Potato;

namespace game
{
	class GameThread
	{
	public:
		GameThread(Potato& potato, raz::IMemoryPool* memory = nullptr);
		~GameThread();
		raz::IMemoryPool* getMemoryPool();
		game::level::Level& getLevel();
		int run(std::future<void> exit_token);

	private:
		Potato& m_potato;
		raz::IMemoryPool* m_memory;
		level::Level m_level;
	};
}
