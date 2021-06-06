#pragma once

namespace CG::random {

template <typename TResult = double, typename T1, typename T2>
TResult range(T1 min, T2 max) noexcept
{
	const auto between_zero_and_one = (static_cast<TResult>(rand()) / RAND_MAX);
	return  static_cast<TResult>(min) + between_zero_and_one * (static_cast<TResult>(max) - static_cast<TResult>(min));
}

// Has one change in `total` to return `true`
inline bool oneIn(std::uint16_t total) noexcept
{
	return rand() % total == 0;
}

}