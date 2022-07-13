#include <GLFW/glfw3.h>

#include "Simulation.h"

int main()
{
	Simulation sim(50, 50, 900, 600);
	sim.Run();
	return 0;
}