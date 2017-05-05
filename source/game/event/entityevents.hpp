/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
#include <vector>
#include <GL/Math/Vec2.hpp>
#include <GL/Util/Color.hpp>
#include <raz/event.hpp>

namespace game
{
namespace event
{
	using namespace raz::literal;

	struct HubPlatform
	{
		uint32_t hub_id;
		uint32_t platform_id;

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(hub_id)(platform_id);
		}
	};

	struct HubParameters
	{
		uint32_t id;
		uint64_t seed;
		uint32_t size;
		GL::Vec2 position;

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(id)(seed)(size)(position.X)(position.Y);
		}
	};

	struct TransportParameters
	{
		uint32_t id;
		HubPlatform position1;
		HubPlatform position2;

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(id)(position1)(position2);
		}
	};

	struct CreatureParameters
	{
		uint32_t id;
		uint64_t seed;
		GL::Color color;
		HubPlatform position;

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(id)(seed)(color.R)(color.G)(color.B)(color.A)(position);
		}
	};

	struct EntityParameters
	{
		uint32_t id;
		HubPlatform position;

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(id)(position);
		}
	};

	struct ValuedEntityParameters
	{
		uint32_t id;
		uint32_t value;
		HubPlatform position;

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(id)(value)(position);
		}
	};

	struct ColoredEntityParameters
	{
		uint32_t id;
		GL::Color color;
		uint32_t diplomacy;
		HubPlatform position;

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(id)(color.R)(color.G)(color.B)(color.A)(diplomacy)(position);
		}
	};

	struct RemoveEntityParameters
	{
		uint32_t id;

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(id);
		}
	};

	struct ChangeColorParameters
	{
		uint32_t id;
		GL::Color color;
		uint32_t diplomacy;

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(id)(color.R)(color.G)(color.B)(color.A)(diplomacy);
		}
	};

	struct MoveCreatureParameters
	{
		uint32_t id;
		HubPlatform position;

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(id)(position);
		}
	};

	typedef raz::Event<"AddHub"_event, HubParameters> AddHubEvent;
	typedef raz::Event<"AddTransport"_event, TransportParameters> AddTransportEvent;
	typedef raz::Event<"AddCharge"_event, EntityParameters> AddChargeEvent;
	typedef raz::Event<"AddResource"_event, ValuedEntityParameters> AddResourceEvent;
	typedef raz::Event<"AddTrace"_event, ColoredEntityParameters> AddTraceEvent;
	typedef raz::Event<"AddSpawn"_event, ColoredEntityParameters> AddSpawnEvent;
	typedef raz::Event<"AddPortal"_event, EntityParameters> AddPortalEvent;
	typedef raz::Event<"AddTrap"_event, ColoredEntityParameters> AddTrapEvent;
	typedef raz::Event<"AddCreature"_event, CreatureParameters> AddCreatureEvent;

	typedef raz::Event<"RemoveCharge"_event, RemoveEntityParameters> RemoveChargeEvent;
	typedef raz::Event<"RemoveResource"_event, RemoveEntityParameters> RemoveResourceEvent;
	typedef raz::Event<"RemoveTrace"_event, RemoveEntityParameters> RemoveTraceEvent;
	typedef raz::Event<"RemoveTrap"_event, RemoveEntityParameters> RemoveTrapEvent;
	typedef raz::Event<"RemoveCreature"_event, RemoveEntityParameters> RemoveCreatureEvent;

	typedef raz::Event<"ChangeHubColor"_event, ChangeColorParameters> ChangeHubColorEvent;
	typedef raz::Event<"ChangeSpawnColor"_event, ChangeColorParameters> ChangeSpawnColorEvent;
	typedef raz::Event<"ChangeCreatureColor"_event, ChangeColorParameters> ChangeCreatureColorEvent;

	typedef raz::Event<"MoveCreature"_event, MoveCreatureParameters> MoveCreatureEvent;
}
}
