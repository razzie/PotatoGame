/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <raz/timer.hpp>
#include <raz/random.hpp>
#include "game/entity/EntityManager.hpp"

namespace gfx
{
namespace scene
{
	class Scene;

	class Demo : public game::entity::EntityHandler
	{
	public:
		Demo(Scene& scene);
		void update();

		virtual void onEntityAdd(const game::entity::Entity* entity);
		virtual void onEntityRemove(game::entity::Entity::Data entity_data);
		virtual void onEntityPlayerChange(const game::entity::Entity* entity, int old_player, int new_player);
		virtual void onEntityVisibilityChange(const game::entity::Entity* entity, int player, bool new_visibility);
		virtual void onEntityMove(const game::entity::Entity* entity, game::entity::Entity::Platform src_platform, game::entity::Entity::Platform dest_platform);

	private:
		Scene* m_scene;
		raz::Timer m_timer;
		raz::Random m_random;
		game::entity::EntityManager m_entities;
		int m_progress;

		void addRandomEntity(uint32_t hub);
	};
}
}
