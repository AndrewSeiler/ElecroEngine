#include <time.h>

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/renderable2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"
#include "src/graphics/staticsprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/math/math.h"
#include "src/utils/timer.h"

#define FPS_FREQUENCY 1.0f
#define TEST_50K_SPRITES 0

int main()
{
	using namespace electro_engine;
	using namespace graphics;
	using namespace math;

	Window window("-Engine Test-", 960, 540);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* s1 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader* s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s1;
	Shader& shader2 = *s2;
	shader.enable();
	shader2.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader2.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	TileLayer layer(&shader);
#if TEST_50K_SPRITES
	for (float y = -9.0f; y < 9.0f; y += 0.1f)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1f)
		{
			layer.add(new Sprite(x, y, 0.09f, 0.09f, math::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}
#else
	Sprite* button = new Sprite(-15.0, 5.0f, 6, 3, math::vec4(1, 1, 1, 1));
	layer.add(button);
	layer.push(math::mat4(button->getPosition()));
	layer.add(new Sprite(0.5f, 0.5f, 5.0f, 2.0f, math::vec4(1, 0, 1, 1)));
	layer.pop(math::mat4(button->getPosition()));
#endif
	TileLayer layer2(&shader2);
	layer2.add(new Sprite(-2, -2, 4, 4, math::vec4(1, 0, 1, 1)));

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
		//shader.setUniform2f("light_pos", vec2(-8, -3));
		//shader2.enable();
		//shader2.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		layer.render();
		layer2.render();

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

	return 0;
}