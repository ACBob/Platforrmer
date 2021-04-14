#pragma once

namespace render {
	class VertexShader
	{
		public:
			virtual ~VertexShader() {}
		
		protected:
			VertexShader() {}
	};

	class PixelShader
	{
		public:
			virtual ~PixelShader() {}

		protected:
			PixelShader() {}
	};

	class ShaderPipeline
	{
		public:
			virtual ~ShaderPipeline() {}
		
		protected:
			ShaderPipeline() {}
	};

	// Encapsulates a vertex buffer
	class VertexBuffer
	{
	public:

		// virtual destructor to ensure subclasses have a virtual destructor
		virtual ~VertexBuffer() {}

	protected:

		// protected default constructor to ensure these are never created directly
		VertexBuffer() {}
	};

	// Encapsulates a vertex buffer semantic description
	class VertexDescription
	{
	public:

		// virtual destructor to ensure subclasses have a virtual destructor
		virtual ~VertexDescription() {}

	protected:

		// protected default constructor to ensure these are never created directly
		VertexDescription() {}
	};

	// Encapsulates a collection of vertex buffers and their semantic descriptions
	class VertexArray
	{
	public:

		// virtual destructor to ensure subclasses have a virtual destructor
		virtual ~VertexArray() {}

	protected:

		// protected default constructor to ensure these are never created directly
		VertexArray() {}
	};

	// Describes a vertex element's type
	enum VertexElementType
	{
		VERTEXELEMENTTYPE_BYTE,
		VERTEXELEMENTTYPE_SHORT,
		VERTEXELEMENTTYPE_INT,

		VERTEXELEMENTTYPE_UNSIGNED_BYTE,	
		VERTEXELEMENTTYPE_UNSIGNED_SHORT,
		VERTEXELEMENTTYPE_UNSIGNED_INT,

		VERTEXELEMENTTYPE_BYTE_NORMALIZE,
		VERTEXELEMENTTYPE_SHORT_NORMALIZE,
		VERTEXELEMENTTYPE_INT_NORMALIZE,

		VERTEXELEMENTTYPE_UNSIGNED_BYTE_NORMALIZE,	
		VERTEXELEMENTTYPE_UNSIGNED_SHORT_NORMALIZE,
		VERTEXELEMENTTYPE_UNSIGNED_INT_NORMALIZE,

		VERTEXELEMENTTYPE_HALF_FLOAT,
		VERTEXELEMENTTYPE_FLOAT,
		VERTEXELEMENTTYPE_DOUBLE
	};

	// Describes a vertex element within a vertex buffer
	struct VertexElement
	{
		unsigned int index; // index binding for vertex element
		VertexElementType type; // type of vertex element
		int size; // number of components
		int stride; // number of bytes between each successive element (leave zero for this to be assumed to be size times size of type)
	};

	// TODO: We assume GLSL. Need to abstract shader language!
	class RenderDevice
	{
		public:
			virtual ~RenderDevice() {}

			// Create and return a vertex shader
			virtual VertexShader *CreateVertexShader(const char *code) = 0;

			// Destroys the given vertex shader
			virtual void DestroyVertexShader(VertexShader *shader) = 0;

			// Create and return a pixel shader
			virtual PixelShader *CreatePixelShader(const char *code) = 0;

			// Destroys the given pixel shader
			virtual void DestroyPixelShader(PixelShader *shader) = 0;


			// Create a shader pipeline
			virtual ShaderPipeline *CreatePipeline(VertexShader *vShader, PixelShader *pShader) = 0;

			// Destroy a shader pipeline
			virtual void DestroyShaderPipeline(ShaderPipeline *pipeline) = 0;

			// Use a shader pipeline for drawing
			virtual void SetPipeline(ShaderPipeline *pipeline) = 0;

			// Create a vertex buffer
			virtual VertexBuffer *CreateVertexBuffer(long long size, void *data = nullptr) = 0;

			// Destroy a vertex buffer
			virtual void DestroyVertexBuffer(VertexBuffer *vertexBuffer) = 0;

			// Create a vertex description given an array of VertexElement structures
			virtual VertexDescription *CreateVertexDescription(unsigned int numVertexElements, const VertexElement *vertexElements) = 0;

			// Destroy a vertex description
			virtual void DestroyVertexDescription(VertexDescription *vertexDescription) = 0;

			// Create a vertex array given an array of vertex buffers and associated vertex descriptions; the arrays must be the same size.
			virtual VertexArray *CreateVertexArray(unsigned int numVertexBuffers, VertexBuffer **vertexBuffers, VertexDescription **vertexDescriptions) = 0;

			// Destroy a vertex array
			virtual void DestroyVertexArray(VertexArray *vertexArray) = 0;

			// Set a vertex array as active for subsequent draw commands
			virtual void SetVertexArray(VertexArray *vertexArray) = 0;

			// Clear the default render target's color buffer to the specified RGBA values
			virtual void ClearColor(float red, float green, float blue, float alpha) = 0;

			// Draw a collection of triangles using the currently active shader pipeline and vertex array data
			virtual void DrawTriangles(int offset, int count) = 0;

	};

	// Creates a render device
	RenderDevice *CreateRenderDevice();

	// Destroys a render device
	void DestroyRenderDevice(RenderDevice *renderDevice);
}