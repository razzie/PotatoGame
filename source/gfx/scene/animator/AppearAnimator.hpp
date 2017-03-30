/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

namespace gfx
{
namespace scene
{
namespace model { class Model; }
namespace animator
{
	class AppearAnimator
	{
	public:
		void begin(model::Model* model);
		bool update(model::Model* model, float elapsed);
		void end(model::Model* model);

	private:
		unsigned m_num_faces;
	};
}
}
}
