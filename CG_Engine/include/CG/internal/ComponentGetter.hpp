#pragma once

#include <functional>
#include <entt/entt.hpp>

namespace CG {

template <typename T>
class ComponentGetter {
public:
	ComponentGetter(std::function<T &()> getter) : m_getter(getter)
	{}

	inline T &get() const noexcept { return m_getter(); }

private:
	std::function<T &()> m_getter;
};

template<typename TAs, typename RealType = TAs>
ComponentGetter<TAs> &&makeComponentGetter(entt::entity e, entt::registry &world)
{
	return ComponentGetter<TAs>([&]() { return world.get<RealType>(e); });
}

}