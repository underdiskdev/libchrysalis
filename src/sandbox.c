#include <chrysalis/chrysalis.h>
#include <assert.h>
#include <stdio.h>

int main()
{
	// Initialization, very important!
	chs_init();
	// Simple info display and checks
	assert(chs_version_check() && "libchrysalis headers and implementation do not match");

	CHS_Graphics_API_Info gfx_api_info;
	chs_get_graphics_api_info(&gfx_api_info);

	printf("This libcrysalis implementation supports %s %s to %s %s\n",	gfx_api_info.name, gfx_api_info.oldest_version,
																		gfx_api_info.name, gfx_api_info.latest_version);

	// Configuration
	CHS_Window_Config window_config = {
		.resizable = 1,
		.borderless = 0,
		.high_dpi_support = 1,
		.width = 800,
		.height = 600,
		.title = "libchrysalis",
	};

	CHS_Renderer_Config renderer_config = {
		.use_fallbacks = 1,
		.depth_bits = 24,
		.stencil_bits = 8,
	};

	CHS_Window* window = chs_create_window(&window_config);
	CHS_Renderer* renderer = chs_create_renderer(&renderer_config, window);

	CHS_Color clear_color = { .r = 0.0f, .g = 0.5f, .b = 1.0f, .a = 1.0f };

	chs_renderer_set_clear_color(renderer, clear_color);

	int running = 1;
	while(running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					running = 0;
					break;
			}
		}
		
		chs_renderer_clear(renderer);

		chs_renderer_display(renderer);
	}

	chs_delete_renderer(renderer);
	chs_delete_window(window);

	chs_quit();
	return 0;
}
