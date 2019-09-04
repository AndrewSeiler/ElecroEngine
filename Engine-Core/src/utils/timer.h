#pragma once

#include <chrono>

namespace electro_engine {

	class Timer
	{
	private:
		std::chrono::high_resolution_clock::time_point m_Start;
	public:
		Timer()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		void reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		float elapsed()
		{
			double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_Start).count();
			return (float)elapsed;
		}
	};

}