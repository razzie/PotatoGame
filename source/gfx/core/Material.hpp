/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Math/Vec3.hpp>
#include <GL/Math/Mat4.hpp>
#include <GL/Util/Color.hpp>
#include <GL/GL/Program.hpp>
#include "resource/ShaderLoader.hpp"

namespace gfx
{
namespace core
{
	struct Material
	{
		GL::Program shader;
		GL::Mat4 world_mat;
		GL::Mat4 normal_mat;
		GL::Mat4 camera_mat;
		GL::Color diffuse_color;
		float time;

		Material(GL::Program& shader) : shader(shader)
		{
		}

		void use()
		{
			shader.SetUniform("world_mat", world_mat);
			shader.SetUniform("normal_mat", normal_mat);
			shader.SetUniform("wvp_mat", camera_mat * world_mat);
			shader.SetUniform("diffuse_color", diffuse_color);
			shader.SetUniform("time", time);
		}
	};

	struct EntityMaterial : public Material
	{
		EntityMaterial(resource::ShaderLoader& shader_loader) : Material(shader_loader.get("entity"))
		{
		}
	};
}
}
