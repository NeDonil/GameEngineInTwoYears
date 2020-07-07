#include "enpch.h"
#include "Random.h"

std::mt19937 Engine::Random::s_RandomEngine;
std::uniform_int_distribution<std::mt19937::result_type> Engine::Random::s_Distribution;