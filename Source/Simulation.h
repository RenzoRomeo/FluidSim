#pragma once

#include "Window.h"
#include "GridRenderer.h"
#include "FluidGrid.h"

class Simulation
{
public:
	Simulation(uint32_t grid_size, uint32_t screen_size);

	void Run();
	void UserInput();

private:
	Window m_Window;
	FluidGrid m_FluidGrid;
	GridRenderer m_GridRenderer;
};