/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "gfx/scene/model/Model.hpp"

namespace gfx
{
namespace scene
{
namespace model
{
	struct PortalEntityMaterial : public gfx::core::Material
	{
		PortalEntityMaterial(resource::ShaderLoader& shader_loader) : Material(shader_loader.get("portal_entity"))
		{
		}
	};

	class PortalModel : public Model<PortalEntityMaterial>
	{
	public:
		PortalModel(Scene& scene, uint32_t id, uint32_t hub_id, uint32_t platform_id);
	};
}
}
}
