#pragma once

#include "Shader.h"
#include "FluidGrid.h"

#include <cstdint>

struct Vertex
{
	float x, y;
	float density;
};

class GridRenderer
{
public:
	GridRenderer(FluidGrid* grid, uint32_t screenWidth, uint32_t screenHeight);
	~GridRenderer();

	void RenderGrid();
private:
	uint32_t m_Vao, m_Vbo;
	uint32_t m_ScreenWidth, m_ScreenHeight;
	Shader m_Shader;
	FluidGrid* m_FluidGrid;
};