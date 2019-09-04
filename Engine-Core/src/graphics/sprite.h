#pragma once

#include "renderable2d.h"

namespace electro_engine { namespace graphics {

	class Sprite : public Renderable2D
	{
	private:
	public:
		Sprite(float x, float y, float width, float height, const math::vec4& color);
	};

} }