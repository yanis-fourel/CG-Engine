#pragma once

#include <functional>
#include "CG/GameObject.hpp"

namespace CG {

// Callback will be called right before rendering
class OnCollision {
	using callback_t = std::function<void(AGameObject &)>;

public:
	explicit OnCollision(callback_t c) noexcept : m_callback(std::move(c))
	{}

	inline void call(AGameObject &obj) const { m_callback(obj); }
private:
	callback_t m_callback;
};

}
