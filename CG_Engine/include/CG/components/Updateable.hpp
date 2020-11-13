#pragma once

#include <functional>

namespace CG {

class Updateable {
	using callback_t = std::function<void(double)>;

public:
	explicit Updateable(callback_t c) noexcept : m_callback(std::move(c))
	{}

	inline void call(double deltatime) const { m_callback(deltatime); }
private:
	callback_t m_callback;
};

}
