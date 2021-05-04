#pragma once

#include <functional>

namespace CG {

class CustomPhysicResolver {
	using callback_t = std::function<void()>;

public:
	explicit CustomPhysicResolver(callback_t c) noexcept : m_callback(std::move(c))
	{}

	inline void call() const { m_callback(); }
private:
	callback_t m_callback;
};

}
