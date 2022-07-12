#include "Simulation.h"

#include "Input.h"

Simulation::Simulation(uint32_t grid_size, uint32_t screen_size)
	: m_Window(Window(screen_size, screen_size, "Fluid Simulation")),
	m_GridRenderer(GridRenderer(&m_FluidGrid, grid_size, screen_size)),
	m_FluidGrid(FluidGrid(grid_size, 0.1, 0.0, 0.0))
{
	m_Window.SetKeyPressedCallback(Input::KeyCallback);
	m_Window.SetMouseButtonCallback(Input::MouseButtonCallback);
	m_Window.SetMousePosCallback(Input::MouseCallback);
}

void Simulation::Run()
{
	while (!m_Window.ShouldClose())
	{
		m_Window.StartFrame();

		UserInput();

		m_GridRenderer.RenderGrid();

		m_Window.EndFrame();
	}
}

void Simulation::UserInput()
{
	static uint32_t cellSize = m_Window.GetWidth() / m_FluidGrid.GetSize();

	if (Input::IsMouseButtonDown(GLFW_MOUSE_BUTTON_1))
	{
		m_FluidGrid.AddDensity(Input::mouse_x / cellSize, (m_Window.GetHeight() - Input::mouse_y) / cellSize, 0.1);
	}
}
