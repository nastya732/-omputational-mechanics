#pragma once
#include "OrbitalCoordinates.hpp"
KeplerovElements RVToKeplerov(const Vector_3D& r, const Vector_3D& v, const double mu);
