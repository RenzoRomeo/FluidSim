#pragma once

#include <cstdint>
#include <memory>
#include <array>

class FluidGrid
{
public:
	FluidGrid(uint32_t size, double diffusion, double viscocity, double dt);
	~FluidGrid();

	void Step();

	void AddDensity(uint32_t x, uint32_t y, double amount);
	void AddVelocity(uint32_t x, uint32_t y, double amount_x, double amount_y);

	double GetDensity(uint32_t x, uint32_t y) const;
	uint32_t GetSize() const { return m_Size; };

private:
	uint32_t Index(uint32_t x, uint32_t y) const
	{
		if (x < 0) x = 0;
		if (x >= m_Size) x = m_Size - 1;
		if (y < 0) y = 0;
		if (y >= m_Size) y = m_Size - 1;
		return y * m_Size + x;
	};
	void Diffuse(int32_t b, double* x, double* x0, double diff);
	void SetBounds(int32_t b, double* x);
	void Project(double* velocX, double* velocY, double* p, double* div);
	void Advect(int32_t b, double* d, double* d0, double* velocX, double* velocY);
	void LinSolve(int32_t b, double* x, double* x0, double a, double c);

private:
	uint32_t m_Size;
	double m_dt, m_Diff, m_Visc;
	double* m_s, * m_Density;
	double* m_Vx, * m_Vy;
	double* m_Vx0, * m_Vy0;
};