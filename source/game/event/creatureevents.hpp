/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
#include <vector>
#include <GL/Util/Color.hpp>
#include <raz/event.hpp>
#include "common/GLhelper.hpp"

namespace game
{
namespace event
{
	using namespace raz::literal;

	struct CreatureCreateParams
	{
		uint32_t creature_id;
		uint32_t hub_id;
		uint32_t platform_id;
		std::vector<size_t, raz::Allocator<size_t>> dimensions;
		GL::Color color;

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(creature_id)(hub_id)(platform_id)(dimensions)(common::GLColorSerializer(color));
		}
	};

	typedef raz::Event<"CreatureCreate"_event, CreatureCreateParams> CreatureCreate;
}
}
