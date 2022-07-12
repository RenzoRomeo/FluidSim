#include <GLFW/glfw3.h>

#include "Simulation.h"

int main()
{
	Simulation sim(20, 600);
	sim.Run();
	return 0;
}