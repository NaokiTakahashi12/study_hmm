
/**
  *
  * @file Vase.hpp
  * @brief HMM ball and vese model
  * @author Naoki Takahahsi
  *
  **/

#pragma once

#include <vector>

#include <RandomGenerator.hpp>
#include <Ball.hpp>

namespace HMM {
	struct VaseProbability {
		std::vector<float> initial;
		std::vector<std::vector<float>> transition, emission;

	};

	class Vase : private Ball, private VaseProbability {
		public :
			Vase();

			Vase &update_transition_matrix(),
				 &update_emission_matrix();

			std::vector<float> get_initial_probabilities();
			std::vector<std::vector<float>> get_transition_probabilities(),
											get_emission_probabilities();

		private :
			std::unique_ptr<RandomGenerator> random_generator;

			void initialize_initial(),
				 initialize_emission(),
				 initialize_transition();

			float get_absolute_random() const;
	};
}

