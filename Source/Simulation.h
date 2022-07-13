#pragma once

#include "Window.h"
#include "GridRenderer.h"
#include "FluidGrid.h"

class Simulation
{
public:
	Simulation(uint32_t gridWidth, uint32_t gridHeight, uint32_t screenWidth, uint32_t screenHeight);

	void Run();
	void UserInput();

private:
	Window m_Window;
	FluidGrid m_FluidGrid;
	GridRenderer m_GridRenderer;
};