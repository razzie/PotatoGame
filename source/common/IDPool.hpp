/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <raz/bitset.hpp>

namespace common
{
	template<size_t N>
	class IDPool
	{
	public:
		bool get(size_t& id)
		{
			auto it = m_ids.falsebits().begin();
			if (it == m_ids.falsebits().end())
				return false;

			id = *it;
			return true;
		}

		bool reserve(size_t id)
		{
			if (m_ids.isset(id))
				return false;

			m_ids.set(id);
			return true;
		}

		void release(size_t id)
		{
			m_ids.unset(id);
		}

	private:
		raz::Bitset<N> m_ids;
	};
}
