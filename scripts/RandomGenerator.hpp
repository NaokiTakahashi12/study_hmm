
/**
  *
  * @file RandomGenerator.hpp
  * @brief Normal distribution
  * @author Naoki Takahashi
  *
  **/

#pragma once

#include <random>

class RandomGenerator {
	public :
		RandomGenerator();

		//! Setting random scale
		RandomGenerator(const float &scale);

		float get(),
			  get_max(),
			  get_min();

	private :
		float min, max;

		std::unique_ptr<std::random_device> device;
		std::unique_ptr<std::mt19937_64> generator;
		std::unique_ptr<std::normal_distribution<float>> distribution;

		void initialize();
		void get_min_and_max();

};

