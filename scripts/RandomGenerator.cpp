
/**
  *
  * @file RandomGenerator.cpp
  * @author Naoki Takahashi
  *
  **/

#include "RandomGenerator.hpp"

RandomGenerator::RandomGenerator() {
	initialize();

	distribution = std::make_unique<std::normal_distribution<float>>();

	get_min_and_max();
}

RandomGenerator::RandomGenerator(const float &scale) {
	initialize();

	distribution = std::make_unique<std::normal_distribution<float>>(0, scale);

	get_min_and_max();
}

float RandomGenerator::get() {
	return (*distribution)(*generator);
}

float RandomGenerator::get_max() {
	return max;
}

float RandomGenerator::get_min() {
	return min;
}

void RandomGenerator::initialize() {
	device = std::make_unique<std::random_device>();
	generator = std::make_unique<std::mt19937_64>((*device)());
}

void RandomGenerator::get_min_and_max() {
	while(1) {
		for(int i = 0; i < 1000000; i ++) {
			float random = get();
			
			if(max < random) {
				max = random;
			}
			if(min > random) {
				min = random;
			}
		}
		if(max < 100 && min > -100) {
			break;
		}
		else {
			max = 0;
			min = 0;
		}
	}
}

