#pragma once

#include "layer.h"
#include "../batchrenderer2d.h"

namespace electro_engine { namespace graphics {

	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader* shader);
		virtual ~TileLayer();
	};

} }