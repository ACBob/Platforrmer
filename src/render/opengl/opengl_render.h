#pragma once

#include "render/render.h"

namespace render
{

	class OpenGLRenderDevice : public RenderDevice
	{
		public:

			VertexShader *CreateVertexShader(const char *code) override;

			void DestroyVertexShader(VertexShader *vertexShader) override;

			PixelShader *CreatePixelShader(const char *code) override;

			void DestroyPixelShader(PixelShader *pixelShader) override;

			ShaderPipeline *CreatePipeline(VertexShader *vertexShader, PixelShader *pixelShader) override;

			void DestroyShaderPipeline(ShaderPipeline *pipeline) override;

			void SetPipeline(ShaderPipeline *pipeline) override;

			VertexBuffer *CreateVertexBuffer(long long size, void *data = nullptr) override;

			void DestroyVertexBuffer(VertexBuffer *vertexBuffer) override;

			VertexDescription *CreateVertexDescription(unsigned int numVertexElements, const VertexElement *vertexElements) override;

			void DestroyVertexDescription(VertexDescription *vertexDescription) override;

			VertexArray *CreateVertexArray(unsigned int numVertexBuffers, VertexBuffer **vertexBuffers, VertexDescription **vertexDescriptions) override;

			void DestroyVertexArray(VertexArray *vertexArray) override;

			void SetVertexArray(VertexArray *vertexArray) override;

			void ClearColor(float red, float green, float blue, float alpha) override;

			void DrawTriangles(int offset, int count) override;
	};
}
