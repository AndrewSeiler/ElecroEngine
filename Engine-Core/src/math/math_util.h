#pragma once

#define _USE_MATH_DEFINES

#include "math.h"
#include <math.h>

namespace electro_engine { namespace math {

	inline float toRadians(float degrees)
	{
		return degrees * ((float)M_PI / 180.0f);
	}
} }