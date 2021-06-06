#include <CG/EntryPoint.hpp>
#include "PongGame.hpp"

int main(int ac, char **av)
{
	return CG::run<PongGame>(ac, av);
}
