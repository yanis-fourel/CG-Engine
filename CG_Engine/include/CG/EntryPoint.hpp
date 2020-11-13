#pragma once

#include <iostream>
#include <memory>
#include <cstdlib>

#include "CG/Core.hpp"

namespace CG {
template <typename Game>
int run(int ac, char **av)
{
	try {
		return Core(std::make_unique<Game>()).run();
	} catch (const std::exception &e) {
		std::cerr << "Fatal : " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
}
