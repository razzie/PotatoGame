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
	struct TransportEntityMaterial : public gfx::core::Material
	{
		TransportEntityMaterial(resource::ShaderLoader& shader_loader) : Material(shader_loader.get("transport_entity"))
		{
		}

		void use()
		{
			shader.SetUniform("start_pos", start_pos);
			shader.SetUniform("end_pos", end_pos);

			Material::use();
		}

		GL::Vec3 start_pos;
		GL::Vec3 end_pos;
	};

	class TransportModel : public Model<TransportEntityMaterial>
	{
	public:
		TransportModel(gfx::scene::Scene& scene, uint32_t id, uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id);
		void render(MaterialType& material, GL::Context& gl);

	private:
		GL::Vec3 m_start_pos;
		GL::Vec3 m_end_pos;
	};
}
}
