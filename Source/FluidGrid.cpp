#include "FluidGrid.h"

FluidGrid::FluidGrid(uint32_t size, double diffusion, double viscocity, double dt)
	: m_Size(size), m_Diff(diffusion), m_Visc(viscocity), m_dt(dt)
{
	m_s = new double[m_Size * m_Size]{ 0 };
	m_Density = new double[m_Size * m_Size]{ 0 };
	m_Vx = new double[m_Size * m_Size]{ 0 };
	m_Vy = new double[m_Size * m_Size]{ 0 };
	m_Vx0 = new double[m_Size * m_Size]{ 0 };
	m_Vy0 = new double[m_Size * m_Size]{ 0 };
}

FluidGrid::~FluidGrid()
{
	delete[] m_s;
	delete[] m_Density;
	delete[] m_Vx;
	delete[] m_Vy;
	delete[] m_Vx0;
	delete[] m_Vy0;
}

void FluidGrid::Step()
{
	Diffuse(1, m_Vx0, m_Vx, m_Visc);
	Diffuse(2, m_Vy0, m_Vy, m_Visc);

	Project(m_Vx0, m_Vy0, m_Vx, m_Vy);

	Advect(1, m_Vx, m_Vx0, m_Vx0, m_Vy0);
	Advect(2, m_Vy, m_Vy0, m_Vx0, m_Vy0);

	Project(m_Vx, m_Vy, m_Vx0, m_Vy0);

	Diffuse(0, m_s, m_Density, m_Diff);
	Advect(0, m_Density, m_s, m_Vx, m_Vy);
}

void FluidGrid::AddDensity(uint32_t x, uint32_t y, double amount)
{
	m_Density[Index(x, y)] += amount;
}

void FluidGrid::AddVelocity(uint32_t x, uint32_t y, double amount_x, double amount_y)
{
	m_Vx[Index(x, y)] += amount_x;
	m_Vy[Index(x, y)] += amount_y;
}

double FluidGrid::GetDensity(uint32_t x, uint32_t y) const
{
	return m_Density[Index(x, y)];
}

void FluidGrid::Diffuse(int32_t b, double* x, double* x0, double diff)
{
	float a = m_dt * diff * (m_Size - 2) * (m_Size - 2);
	LinSolve(b, x, x0, a, 1 + 6 * a);
}

void FluidGrid::SetBounds(int32_t b, double* x)
{
	for (uint32_t i = 1; i < m_Size - 1; i++) {
		x[Index(i, 0)] = b == 2 ? -x[Index(i, 1)] : x[Index(i, 1)];
		x[Index(i, m_Size - 1)] = b == 2 ? -x[Index(i, m_Size - 2)] : x[Index(i, m_Size - 2)];
	}

	for (uint32_t j = 1; j < m_Size - 1; j++) {
		x[Index(0, j)] = b == 1 ? -x[Index(1, j)] : x[Index(1, j)];
		x[Index(m_Size - 1, j)] = b == 1 ? -x[Index(m_Size - 2, j)] : x[Index(m_Size - 2, j)];
	}

	x[Index(0, 0)] = 0.5 * (x[Index(1, 0)] + x[Index(0, 1)]);
	x[Index(0, m_Size - 1)] = 0.5 * (x[Index(1, m_Size - 1)] + x[Index(0, m_Size - 2)]);
	x[Index(m_Size - 1, 0)] = 0.5 * (x[Index(m_Size - 2, 0)] + x[Index(m_Size - 1, 1)]);
	x[Index(m_Size - 1, m_Size - 1)] = 0.5 * (x[Index(m_Size - 2, m_Size - 1)] + x[Index(m_Size - 1, m_Size - 2)]);
}

void FluidGrid::Project(double* velocX, double* velocY, double* p, double* div)
{
	for (uint32_t j = 1; j < m_Size - 1; j++) {
		for (uint32_t i = 1; i < m_Size - 1; i++) {
			div[Index(i, j)] = -0.5f * (
				velocX[Index(i + 1, j)]
				- velocX[Index(i - 1, j)]
				+ velocY[Index(i, j + 1)]
				- velocY[Index(i, j - 1)]
				) / m_Size;
			p[Index(i, j)] = 0;
		}
	}

	SetBounds(0, div);
	SetBounds(0, p);
	LinSolve(0, p, div, 1, 6);

	for (uint32_t j = 1; j < m_Size - 1; j++) {
		for (uint32_t i = 1; i < m_Size - 1; i++) {
			velocX[Index(i, j)] -= 0.5f * (p[Index(i + 1, j)]
				- p[Index(i - 1, j)]) * m_Size;
			velocY[Index(i, j)] -= 0.5f * (p[Index(i, j + 1)]
				- p[Index(i, j - 1)]) * m_Size;
		}
	}

	SetBounds(1, velocX);
	SetBounds(2, velocY);
}

void FluidGrid::Advect(int32_t b, double* d, double* d0, double* velocX, double* velocY)
{
	double i0, i1, j0, j1;

	double dtx = m_dt * (m_Size - 2);
	double dty = m_dt * (m_Size - 2);

	double s0, s1, t0, t1;
	double tmp1, tmp2, x, y;

	double Nfloat = m_Size;
	double ifloat, jfloat;
	uint32_t i, j;

	for (j = 1, jfloat = 1; j < m_Size - 1; j++, jfloat++) {
		for (i = 1, ifloat = 1; i < m_Size - 1; i++, ifloat++) {
			tmp1 = dtx * velocX[Index(i, j)];
			tmp2 = dty * velocY[Index(i, j)];
			x = ifloat - tmp1;
			y = jfloat - tmp2;

			if (x < 0.5f) x = 0.5f;
			if (x > Nfloat + 0.5f) x = Nfloat + 0.5f;
			i0 = floorf(x);
			i1 = i0 + 1.0f;

			if (y < 0.5f) y = 0.5f;
			if (y > Nfloat + 0.5f) y = Nfloat + 0.5f;
			j0 = floorf(y);
			j1 = j0 + 1.0f;

			s1 = x - i0;
			s0 = 1.0f - s1;
			t1 = y - j0;
			t0 = 1.0f - t1;

			int32_t i0i = i0;
			int32_t i1i = i1;
			int32_t j0i = j0;
			int32_t j1i = j1;

			d[Index(i, j)] =
				s0 * (t0 * d0[Index(i0i, j0i)])
				+ (t1 * d0[Index(i0i, j1i)])
				+ s1 * (t0 * d0[Index(i1i, j0i)])
				+ (t1 * d0[Index(i1i, j1i)]);
		}

	}
	SetBounds(b, d);
}

void FluidGrid::LinSolve(int32_t b, double* x, double* x0, double a, double c)
{
	double cRecip = 1.0 / c;
	for (uint32_t k = 0; k < 4; k++) {
		for (uint32_t j = 1; j < m_Size - 1; j++) {
			for (uint32_t i = 1; i < m_Size - 1; i++) {
				x[Index(i, j)] =
					(x0[Index(i, j)]
						+ a * (x[Index(i + 1, j)]
							+ x[Index(i - 1, j)]
							+ x[Index(i, j + 1)]
							+ x[Index(i, j - 1)]
							)) * cRecip;
			}
		}
		SetBounds(b, x);
	}
}
