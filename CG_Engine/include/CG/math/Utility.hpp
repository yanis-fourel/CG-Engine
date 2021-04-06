#pragma

#include "Vector2.hpp"
#include "Ray.hpp"

#include "CG/Camera.hpp"

namespace CG {

// Gets ray of visible points at given normalized position on screen
auto getRayFromScreenPos(const Camera &cam, const Vector2 &screenPosNorm) -> Ray;

}