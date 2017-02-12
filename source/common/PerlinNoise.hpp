/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
#include <cstring> // memcpy

namespace common
{
	template<int GRID_SIZE = 256>
	class PerlinNoise
	{
	public:
		explicit PerlinNoise(uint32_t seed) : m_rnd_state(seed)
		{
			initPermutation();
		}

		PerlinNoise(const PerlinNoise& other)
		{
			std::memcpy(m_permut, other.m_permut, sizeof(m_permut));
		}

		~PerlinNoise() = default;

		PerlinNoise& operator=(const PerlinNoise& other)
		{
			std::memcpy(m_permut, other.m_permut, sizeof(m_permut));
			return *this;
		}

		float operator()(float x, float y, float z)
		{
			// find unit cube that contains the point (256x256x256 grid)
			int X = (int)x % GRID_SIZE,
				Y = (int)y % GRID_SIZE,
				Z = (int)z % GRID_SIZE;

			if (X < 0) X += GRID_SIZE;
			if (Y < 0) Y += GRID_SIZE;
			if (Z < 0) Z += GRID_SIZE;

			// find relative coordinates of point in unit cube
			x -= (int)x;
			y -= (int)y;
			z -= (int)z;

			// find hash values for each of the 8 cube coordinates
			int A = m_permut[X] + Y,
				AA = m_permut[A] + Z,
				AB = m_permut[A + 1] + Z,
				B = m_permut[X + 1] + Y,
				BA = m_permut[B] + Z,
				BB = m_permut[B + 1] + Z;

			// compute hermite curve for x,y,z
			float u = smootherstep(x),
				  v = smootherstep(y),
				  w = smootherstep(z);

			float a = mix(u, gradientDotVec(m_permut[AA], x, y, z), gradientDotVec(m_permut[BA], x - 1, y, z));
			float b = mix(u, gradientDotVec(m_permut[AB], x, y - 1, z), gradientDotVec(m_permut[BB], x - 1, y - 1, z));
			float ab = mix(v, a, b);

			float c = mix(u, gradientDotVec(m_permut[AA + 1], x, y, z - 1), gradientDotVec(m_permut[BA + 1], x - 1, y, z - 1));
			float d = mix(u, gradientDotVec(m_permut[AB + 1], x, y - 1, z - 1), gradientDotVec(m_permut[BB + 1], x - 1, y - 1, z - 1));
			float cd = mix(v, c, d);

			float abcd = mix(w, ab, cd);

			return abcd;
		}

	private:
		void initPermutation()
		{
			for (int i = 0; i < 2 * GRID_SIZE; ++i)
				m_permut[i] = rand();
		}

		float gradientDotVec(int hash, float x, float y, float z) const
		{
			int h = hash & 0xF;

			// Compute dot product between the gradient vector corresponding 
			// to h and (x,y,z)
			float u = h < 8 ? x : y;
			float v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
			return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
		}

		uint32_t rand()
		{
			m_rnd_state = (1664525 * m_rnd_state + 1013904223);
			return (m_rnd_state >> 16) % GRID_SIZE;
		}

		float smootherstep(float t) const
		{
			return t*t*t*(t*(t*6.f - 15.f) + 10.f);
		}

		float mix(float t, float a, float b) const
		{
			return a + t*(b - a);
		}

		uint32_t m_rnd_state;
		uint32_t m_permut[GRID_SIZE * 2];
	};

	template<class NOISE_FUNC>
	float turbulence(float x, float y, float z, float a, float b, int l0, int lmax, NOISE_FUNC n)
	{
		float sum = 0.f;
		for (int i = l0; i < lmax; ++i)
		{
			float f = pow(a, i);//(1 << i);
			float pui = pow(b, i);   // 2^i
			sum += n(f*x, f*y, f*z) / pui;
		}
		return sum;
	}
};
