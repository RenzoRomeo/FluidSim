# Fluid Simulation

This is an implementation of a simple 2D fluid simulation based on Mike Ash's "Fluid Simulation for Dummies" (https://mikeash.com/pyblog/fluid-simulation-for-dummies.html).

## About the simulation

![image](https://user-images.githubusercontent.com/46039237/178845146-f64513c6-b2ad-4c8e-a3d0-4c3049fef08b.png)

You can add fluid with the LMB (Left Mouse Button).

I used:
- OpenGL as the graphics API.
- Glad for the OpenGL bindings.
- GLFW to manage the window and the OpenGL context.

## TODO
- Add ImGUI for user interface.
- Increase and decrease size of brush to add fluid by scrolling.
- Add colors to the simulation.
- Add high and low pressure spots so that the fluid flows.
- Screen resolution, grid size and simulation parameters (viscosity, diffusion rate and time step) should be passed as arguments on execution or selected via UI.
- Screen should be resizable.
- Currently, you can select the grid size and the screen size, so the size (in pixels) of each grid element is implicitly defined. Add a way of defining the screen size and the size of each grid element, so that the size of the grid (the amount of elements) is implicity defined.
