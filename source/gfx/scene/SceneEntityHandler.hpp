/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "game/entity/EntityManager.hpp"

class Potato;

namespace gfx
{
namespace scene
{
	class SceneEntityHandler : public game::entity::EntityHandler
	{
	public:
		SceneEntityHandler(Potato& potato);
		virtual void onEntityAdd(const game::entity::Entity* entity);
		virtual void onEntityRemove(game::entity::Entity::Data entity_data);
		virtual void onEntityPlayerChange(const game::entity::Entity* entity, int old_player, int new_player);
		virtual void onEntityVisibilityChange(const game::entity::Entity* entity, int player, bool new_visibility);
		virtual void onEntityMove(const game::entity::Entity* entity, game::entity::Entity::Platform src_platform, game::entity::Entity::Platform dest_platform);

	private:
		Potato* m_potato;
	};
}
}
