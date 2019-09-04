#pragma once

#include "../renderable2d.h"

namespace electro_engine { namespace graphics {

	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> m_Renderables;
		math::mat4 m_TransformationMatrix;
	public:
		Group();
		void submit(Renderer2D* renderer) const override;
	};

} }