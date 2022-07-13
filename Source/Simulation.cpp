#include "Simulation.h"

#include "Input.h"

Simulation::Simulation(uint32_t gridWidth, uint32_t gridHeight, uint32_t screenWidth, uint32_t screenHeight)
	: m_Window(Window(screenWidth, screenHeight, "Fluid Simulation")),
	m_GridRenderer(GridRenderer(&m_FluidGrid, screenWidth, screenHeight)),
	m_FluidGrid(FluidGrid(gridWidth, gridHeight, 0, 0, 0.2))
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
	static uint32_t cellWidth = m_Window.GetWidth() / m_FluidGrid.GetWidth();
	static uint32_t cellHeight = m_Window.GetHeight() / m_FluidGrid.GetHeight();

	if (Input::IsMouseButtonDown(GLFW_MOUSE_BUTTON_1))
	{
		uint32_t xPos = Input::mouse_x / cellWidth;
		uint32_t yPos = (m_Window.GetHeight() - Input::mouse_y) / cellHeight;

		m_FluidGrid.AddDensity(xPos, yPos, 1);

		float vx = Input::x_offset / m_Window.GetWidth();
		float vy = Input::y_offset / m_Window.GetWidth();

		m_FluidGrid.AddVelocity(xPos, yPos, vx, vy);
	}
}
