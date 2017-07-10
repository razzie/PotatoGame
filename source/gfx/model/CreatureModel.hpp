/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "gfx/model/Model.hpp"

namespace gfx
{
namespace model
{
	struct CreatureEntityMaterial : public gfx::core::Material
	{
		CreatureEntityMaterial(resource::ShaderLoader& shader_loader) : Material(shader_loader.get("creature_entity"))
		{
		}
	};

	class CreatureModel : public Model<CreatureEntityMaterial>
	{
	public:
		CreatureModel(uint64_t seed, GL::Color color);
		CreatureModel(scene::Scene& scene, uint32_t id, uint64_t seed, GL::Color color, uint32_t hub_id, uint32_t platform_id);
	};
}
}
