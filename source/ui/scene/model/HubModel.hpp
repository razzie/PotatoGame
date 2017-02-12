/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <raz/memory.hpp>
#include "ui/scene/model/Model.hpp"
#include "ui/core/Mesh.hpp"

namespace ui
{
namespace scene
{
namespace model
{
	class HubModel : public Model
	{
	public:
		struct Platform
		{
			size_t id;
			GL::Vec3 center;
			GL::Vec3 inner1;
			GL::Vec3 inner2;
			GL::Vec3 outer1;
			GL::Vec3 outer2;
		};

		HubModel(scene::Scene& scene);
		virtual void render(scene::Scene& scene);
		const Platform& getPlatform(size_t id);

	private:
		core::Mesh m_mesh;
		std::vector<Platform, raz::Allocator<Platform>> m_platforms;
	};
}
}
}
