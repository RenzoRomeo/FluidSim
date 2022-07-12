#include "GridRenderer.h"

#include <iostream>
#include <vector>

#include <glad/glad.h>

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::cout << "Error [OpenGL]: " << message << '\n';
}

GridRenderer::GridRenderer(FluidGrid* grid, uint32_t grid_size, uint32_t screen_size)
	: m_GridSize(grid_size), m_ScreenSize(screen_size), m_FluidGrid(grid)
{
	if (!gladLoadGL())
	{
		std::cout << "Failed to initialize GLAD.\n";
		exit(1);
	}

	glViewport(0, 0, screen_size, screen_size);
	glDebugMessageCallback(MessageCallback, 0);

	m_Shader = Shader("./Resources/Shaders/vertex.shader", "./Resources/Shaders/fragment.shader");
	m_Shader.Use();

	glCreateVertexArrays(1, &m_Vao);
	glCreateBuffers(1, &m_Vbo);
}

GridRenderer::~GridRenderer()
{
	glDeleteBuffers(1, &m_Vbo);
	glDeleteVertexArrays(1, &m_Vao);
}

void GridRenderer::RenderGrid()
{
	std::vector<Vertex> vertices;
	float quadSize = 2.0f / m_GridSize;

	for (uint32_t y = 0; y < m_GridSize; y++)
	{
		float yPos = -1.0f + y * quadSize;
		for (uint32_t x = 0; x < m_GridSize; x++)
		{
			float xPos = -1.0f + x * quadSize;
			float d = m_FluidGrid->GetDensity(x, y);
			vertices.push_back({ xPos, yPos,  d});
			vertices.push_back({ xPos + quadSize, yPos, d });
			vertices.push_back({ xPos + quadSize, yPos + quadSize, d });
			vertices.push_back({ xPos, yPos, d });
			vertices.push_back({ xPos + quadSize, yPos + quadSize, d });
			vertices.push_back({ xPos , yPos + quadSize, d });
		}
	}

	glBindVertexArray(m_Vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, x));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, y));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 1, GL_FLOAT, GL_TRUE, sizeof(Vertex), (const void*)offsetof(Vertex, density));
	glEnableVertexAttribArray(2);

	m_Shader.Use();

	glBindVertexArray(m_Vao);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());

	m_FluidGrid->Step();
}
