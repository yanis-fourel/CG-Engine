#pragma once

#include <CG/Game.hpp>


namespace Level {


constexpr double kWidth = 5.f;
constexpr double kHeight = 3.f;
constexpr double kDepth = 20.f;


constexpr CG::Color kFrontEdgesColor = CG::Color::Blue();
constexpr CG::Color kBackEdgesColor = CG::Color::Red();
constexpr CG::Color kMiddleEdgesColor = CG::Color::White();
constexpr CG::Color kFourEdgesColor = CG::Color::Yellow();

constexpr int kMiddleRingsCount = 5;

// Creates level and moves camera correctly
void create(CG::AGame &game);

}
