#pragma once

#include <functional>

namespace CG {

// Callback will be called right before rendering
class OnLateUpdate {
	using callback_t = std::function<void(double)>;

public:
	explicit OnLateUpdate(callback_t c) noexcept : m_callback(std::move(c))
	{}

	inline void call(double d) const { m_callback(d); }
private:
	callback_t m_callback;
};

}
