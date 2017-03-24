/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <bitset>
#include <cstdint>

namespace game
{
namespace level
{
namespace entity
{
	class Entity
	{
	public:
		enum Type
		{
			NONE,
			HUB,
			PLATFORM,
			TRANSPORT,
			CHARGE,
			RESOURCE,
			TRACE,
			SPAWN,
			PORTAL,
			TRAP,
			CREATURE
		};

		struct Data
		{
			Type type = Type::NONE;
			uint32_t id = 0;
			int player_id = 0;

			Data() = default;

			Data(Type t, uint32_t i, int p) :
				type(t), id(i), player_id(p)
			{
			}
		};

		struct Platform
		{
			uint32_t hub_id;
			uint32_t platform_id;
		};

		static constexpr size_t MAX_PLAYERS = 32;

		Entity(Type type, uint32_t id, int player_id = -1);
		Type getType() const;
		uint32_t getID() const;
		int getPlayerID() const;
		Data getData() const;
		bool getVisibility(int player_id) const;
		void setVisibility(int player_id, bool visible);

	private:
		Type m_type;
		uint32_t m_id;
		std::bitset<MAX_PLAYERS> m_visibility;

	protected:
		int m_player_id;
	};
}
}
}
