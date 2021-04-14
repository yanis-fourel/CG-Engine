#pragma once

#include <memory>

#include "CG/internal/ShaderProgram.hpp"
#include "CG/Game.hpp"

namespace CG {

class Core
{
public:
	Core(std::unique_ptr<AGame> game);
	
	int run();
private:
	void tick(double deltatime);

	void updateGame(double deltatime);
	void cleanupDeadGameobjects();

public:
	std::unique_ptr<AGame> m_game;

	ShaderProgram m_onlyShader; // TODO: delegate shader responsability to material
};

}
