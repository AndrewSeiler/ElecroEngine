#include <time.h>

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"

#include "src/graphics/renderable2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"
#include "src/graphics/staticsprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/graphics/texture.h"

#include "src/math/math.h"

#include "src/utils/timer.h"
#include "src/utils/imageload.h"

#define FPS_FREQUENCY 1.0f

#if 1
int main()
{
	using namespace electro_engine;
	using namespace graphics;
	using namespace math;

	Window window("-Engine Test-", 960, 540);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* s1 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s1;
	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	TileLayer layer(&shader);

	Texture* textures[] =
	{
		new Texture("a.png"),
		new Texture("b.png"),
		new Texture("c.png")
	};

	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			//layer.add(new Sprite(x, y, 0.9f, 0.9f, math::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}


	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);

	shader.setUniform1i("tex", 0);
	shader.setUniformMat4("pr_matrix", mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	Timer timer;
	float time = 0;
	unsigned int frames = 0;

	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getCursorPosition(x, y);
		shader.enable();
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
		
		layer.render();

		window.update();
		frames++;
		float elapsed = timer.elapsed();
		if (elapsed - time > 1000.0f)
		{
			time += 1000.0f;
			printf("FPS: %d\n", frames);
			frames = 0;
		}
	}

	for(Texture* tex : textures)
		delete tex;

	return 0;
}
#endif

#if 0
int main()
{
	const char* filename = "test.png";
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib(0);
	BYTE* bits(0);
	unsigned int width(0), height(0);
	GLuint gl_textID;
	fif = FreeImage_GetFileType(filename, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	if (fif == FIF_UNKNOWN)
		return false;
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	if (!dib)
		return false;
	bits = (BYTE*)FreeImage_GetBits(dib);
	unsigned int bitsPerPixel = FreeImage_GetBPP(dib);
	unsigned int pitch = FreeImage_GetPitch(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	for (int y = 0; y < height; y++)
	{
		BYTE* pixel = (BYTE*)bits;
		for (int x = 0; x < width; x++)
		{
			std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << std::endl;
			pixel += 3;
		}
		bits += pitch;
	}

	FreeImage_Unload(dib);

	return 0;
}
#endif