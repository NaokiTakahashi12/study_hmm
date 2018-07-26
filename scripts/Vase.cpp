
/**
  *
  * @file Vase.hpp
  * @brief HMM ball vese model
  * @author Naoki Takahahsi
  *
  **/

#include <cmath>
#include <thread>
#include <algorithm>

#include "Vase.hpp"

namespace HMM {
	Vase::Vase() {
		random_generator = std::make_unique<RandomGenerator>();

		initialize_initial();

		auto transition_initialize_thread = std::make_unique<std::thread>(&Vase::initialize_transition, this);
		auto emission_initialize_thread = std::make_unique<std::thread>(&Vase::initialize_emission, this);

		transition_initialize_thread->join();
		emission_initialize_thread->join();
	}

	Vase &Vase::update_transition_matrix() {
		for(auto &&t_cols : this->transition) {
			for(auto &&t : t_cols) {
				t = get_absolute_random();
			}
		}
		return *this;
	}

	Vase &Vase::update_emission_matrix() {
		for(auto &&e_cols : this->emission) {
			for(auto &&e : e_cols) {
				e = get_absolute_random();
			}
		}
		return *this;
	}

	std::vector<float> Vase::get_initial_probabilities() {
		return initial;
	}

	std::vector<std::vector<float>> Vase::get_transition_probabilities() {
		return transition;
	}

	std::vector<std::vector<float>> Vase::get_emission_probabilities() {
		return emission;
	}

	void Vase::initialize_initial() {
		initial.resize(number_of_ball_category);

		for(auto &&i : initial) {
			i = get_absolute_random();
		}
	}

	void Vase::initialize_emission() {
		emission.resize(initial.size());

		for(auto &&e : emission) {
			e.resize(initial.size());
		}

		update_emission_matrix();
	}

	void Vase::initialize_transition() {
		transition.resize(initial.size());

		for(auto &&t : transition) {
			t.resize(initial.size());
		}

		update_transition_matrix();
	}

	float Vase::get_absolute_random() const {
		float hander;
		do {
			hander = fabs(random_generator->get()) / random_generator->get_max();
		}
		while(hander < 0.5);

		return hander;
	}
}

