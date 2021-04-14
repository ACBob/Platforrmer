#include "render/render.h"

#include "render/opengl/opengl_render.h"

namespace render
{

	RenderDevice *CreateRenderDevice()
	{
		// Eventually, we will parse a config, command-line argument, or global setting, in order to retrieve which RenderDevice should be instantiated.
		// Right now, we only have OpenGL.
		return new OpenGLRenderDevice;
	}

	void DestroyRenderDevice(RenderDevice *renderDevice)
	{
		delete renderDevice;
	}

} // end namespace render
