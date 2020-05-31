#include <chrysalis.h>

#include <GL/glew.h>
#include <OpenGL/gl.h>

/**
 * @brief Renderer Data unique for OpenGL
 */
typedef struct
CHS_Renderer_Data {
	/**
	 * @brief OpenGL context
	 */
	SDL_GLContext gl_context;
}	CHS_Renderer_Data;

CHS_Renderer* chs_create_renderer(CHS_Renderer_Config* config, CHS_Window* window)
{	
	CHS_Renderer* ret = (CHS_Renderer*)malloc(sizeof(CHS_Renderer));
	ret->data = malloc(sizeof(CHS_Renderer_Data));

	//todo: fallbacks
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, config->depth_bits);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, config->stencil_bits);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	ret->window = window;

	//ret->window->window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

	((CHS_Renderer_Data*)ret->data)->gl_context = SDL_GL_CreateContext(window->window);

	if (((CHS_Renderer_Data*)ret->data)->gl_context == NULL)
	{
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		chs_die("Could not create OpenGL context\n");
	}

	glewExperimental = GL_TRUE; 
	GLenum glewError = glewInit();
	if(glewError != GLEW_OK)
	{
		fprintf(stderr, "Error initializing GLEW! %s\n", glewGetErrorString(glewError));
	}

	return ret;
}

void chs_delete_renderer(CHS_Renderer* renderer)
{
	SDL_GL_DeleteContext(((CHS_Renderer_Data*)renderer->data)->gl_context);
	free(renderer->data);
	free(renderer);
}

void chs_renderer_display(CHS_Renderer* renderer)
{
	SDL_GL_SwapWindow(renderer->window->window);
}

int chs_get_version_major()
{
	return 1;
}
  
 int chs_get_version_minor()
 {
	 return 0;
 }
  
 int chs_get_version_patch()
 {
	 return 0;
 }
  
 void chs_get_graphics_api_info(CHS_Graphics_API_Info* info)
 {
	 info->name = "OpenGL";
	 info->latest_version = "4.6";
	 info->oldest_version = "3.3";
 }

 Uint32 chs_get_additional_sdl_window_flags()
 {
	 return SDL_WINDOW_OPENGL; // Mandatory on SDL Window creation for OpenGL context creation later on
 }

void chs_renderer_set_clear_color(CHS_Renderer* renderer, CHS_Color color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void chs_renderer_clear(CHS_Renderer* renderer)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void chs_before_window_creation(CHS_Window_Config* config)
{
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
}

void chs_init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
        chs_die("Unable to initialize SDL");
}

void chs_quit()
{
	SDL_Quit();
}