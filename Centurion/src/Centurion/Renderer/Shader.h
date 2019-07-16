#pragma once

#include <string>

#include <glm/glm.hpp>

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

		void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	};
}
