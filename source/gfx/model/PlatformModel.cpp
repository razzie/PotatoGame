/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/model/PlatformModel.hpp"
#include "gfx/shape/PlatformShape.hpp"

gfx::model::PlatformModel::PlatformModel(uint64_t seed, float size) :
	Model(0)
{
	gfx::core::MeshBuffer<> meshbuffer;

	gfx::shape::PlatformShape shape;
	shape.seed = seed;
	shape.size = size;
	shape.generate(meshbuffer);

	meshbuffer.recalculateNormals();
	getMesh() = meshbuffer;

	setColor(GL::Color(224, 224, 224));
}
