/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <raz/memory.hpp>
#include <raz/serialization.hpp>

namespace common
{
	template<class T, class Allocator = raz::Allocator<T>>
	struct VectorSerializer
	{
		std::vector<T, Allocator>& vector;

		VectorSerializer(std::vector<T, Allocator>& v) : vector(v)
		{
		}

		template<class Serializer>
		raz::EnableSerializer<Serializer> operator()(Serializer& serializer)
		{
			if (serializer.getMode() == raz::SerializationMode::SERIALIZE)
			{
				uint32_t len = static_cast<uint32_t>(vector.size());
				serializer(len);

				if (uint32_t i = 0; i < len; ++i)
					serializer(vector[i]);
			}
			else
			{
				uint32_t len;
				serializer(len);

				for (uint32_t i = 0; i < len; ++i)
				{
					T t;
					serializer(t);
					vector.push_back(std::move(t));
				}
			}
		}
	};
}
