#pragma once

#include <string>

class Shader
{
public:
	Shader();
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	void Use();

	void SetUniform1b(const std::string& name, bool value) const;
	void SetUniform1i(const std::string& name, int value) const;
	void SetUniform1f(const std::string& name, float value) const;

	void Free();

	uint32_t GetId() const { return id; }

private:
	uint32_t id;

private:
	void CheckCompileErrors(unsigned int shader, const std::string& type);
};