#pragma once

#include "../utils/imageload.h"
#include <string>
#include <GL/glew.h>

namespace electro_engine { namespace graphics {
	
	class Texture
	{
	private:
		std::string m_FileName;
		GLuint m_TID;
		GLsizei m_Width, m_Height;

		GLuint load();
	public:
		Texture(const std::string& filename);
		~Texture();
		void bind() const;
		void unbind() const;

		inline const unsigned int getWidth() const { return m_Width; }
		inline const unsigned int getHeight() const { return m_Height; }
	};

} }