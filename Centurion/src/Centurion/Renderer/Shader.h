#pragma once

#include <string>

namespace Centurion
{
	class Shader
	{
	private:
		uint32_t m_RendererID;
	public:
		Shader(const std::string& vertexSrc, std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	};
}
