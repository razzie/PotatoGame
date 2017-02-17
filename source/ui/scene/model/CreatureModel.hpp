/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "ui/scene/model/Model.hpp"

namespace ui
{
namespace scene
{
namespace model
{
	class CreatureModel : public Model
	{
	public:
		CreatureModel(scene::Scene& scene);
		virtual void render(scene::Scene& scene);
	};
}
}
}
