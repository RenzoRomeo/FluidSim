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
	GridRenderer(FluidGrid* grid, uint32_t grid_size, uint32_t screen_size);
	~GridRenderer();

	void RenderGrid();
private:
	uint32_t m_Vao, m_Vbo;
	uint32_t m_GridSize;
	uint32_t m_ScreenSize;
	Shader m_Shader;
	FluidGrid* m_FluidGrid;
};