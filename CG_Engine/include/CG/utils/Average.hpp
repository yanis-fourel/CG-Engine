#pragma once

#include <initializer_list>

namespace CG {

template <typename T>
class Average
{
public:
	Average() = default;
	explicit Average(std::initializer_list<T> init)
	{
		for (const auto &e : init)
			add(e);
	}

	const T &add(const T &val) noexcept
	{
		m_size++;
		m_current = ((m_size -1) * m_current + val) / (m_size);

		return m_current;
	}

	const T &get() const noexcept { return m_current; }
private:
	T m_current = {0};
	size_t m_size = 0;
};
}