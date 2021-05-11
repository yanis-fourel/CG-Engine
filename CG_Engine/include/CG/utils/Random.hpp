#pragma once

namespace CG {

template <typename TResult = double, typename T1, typename T2>
TResult RandomRange(T1 min, T2 max) noexcept
{
	const auto between_zero_and_one = (static_cast<TResult>(rand()) / RAND_MAX);
	return  static_cast<TResult>(min) + between_zero_and_one * (static_cast<TResult>(max) - static_cast<TResult>(min));
}

}