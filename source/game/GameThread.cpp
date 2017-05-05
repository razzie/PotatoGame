/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "Potato.hpp"
#include "game/GameThread.hpp"

game::GameThread::GameThread(Potato& potato, raz::IMemoryPool* memory) :
	m_potato(potato),
	m_memory(memory)
{
}

game::GameThread::~GameThread()
{
}

raz::IMemoryPool* game::GameThread::getMemoryPool()
{
	return m_memory;
}

game::level::Level& game::GameThread::getLevel()
{
	return m_level;
}
