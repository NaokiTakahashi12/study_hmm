
/**
  * 
  * @file HMM.cpp
  * @author Naoki Takahashi
  * 
  **/

#include <cmath>

#include <exception>

#include "HMM.hpp"

namespace HMM {
	ModelCalculator::ModelCalculator() {
		vase = std::make_unique<Vase>();

		cycle_state = std::make_unique<std::vector<CycleState>>();

		number_of_node = 0;
		number_of_state_probabikity = 0;
		number_of_state = 0;
	}

	ModelCalculator &ModelCalculator::set_number_of_node(const int &number) {
		this->number_of_node = abs(number);

		return *this;
	}
	
	ModelCalculator &ModelCalculator::set_number_of_state_probability(const int &number) {
		this->number_of_state_probabikity = abs(number);

		return *this;
	}

	ModelCalculator &ModelCalculator::set_number_of_state(const int &number) {
		this->number_of_state = number;

		return *this;
	}

	ModelCalculator &ModelCalculator::update() {
		vase->update_transition_matrix();
		vase->update_emission_matrix();

		cycle_state.reset();
		cycle_state = std::make_unique<std::vector<CycleState>>();

		return *this;
	}

	int ModelCalculator::get_maximum_element_id() {
		return maximum_id;
	}

	float ModelCalculator::get_maximum_element() {
		return maximum_vecttor_element(cycle_state->back().observation);
	}

	float ModelCalculator::get_forward() {
		float forward = 0;

		for(auto &&o : cycle_state->back().observation) {
			forward += o;
		}

		return forward;
	}

	std::vector<float> ModelCalculator::get_observation() {
		if(number_of_node <= 1) {
			throw std::runtime_error("Error output size");
		}

		return create_observation();
	}

	float ModelCalculator::maximum_vecttor_element(const  std::vector<float> &v) {
		float max = 0;
		int id = 0, i = 0;

		for(auto &&value : v) {
			if(max < value) {
				max = value;
				id = i;
			}

			i ++;
		}

		maximum_id = id;

		return max;
	}

	std::vector<float> ModelCalculator::create_observation() {
		cycle_state->push_back(CycleState());

		int i = 0;

		int number_of_output = abs(number_of_state - number_of_node) + 1;

		for(auto &&ip : vase->get_initial_probabilities()) {
			cycle_state->back().observation.push_back(ip);

			i ++;
			if(i >= number_of_state) {
				break;
			}
		}

		cycle_state->push_back(CycleState());

		float step_probability = 0.0;

		for(int j = 0; j < number_of_output; j ++) {
			for(i = 0; i < number_of_node; i ++) {
				if(i >= cycle_state->front().observation.size()) {
					step_probability = cycle_state->front().observation.back();
				}
				else {
					step_probability = cycle_state->front().observation.at(i);
				}
				
				step_probability *= vase->get_transition_probabilities().at(j).at(i);
			}
			step_probability *= vase->get_emission_probabilities().at(j).at(i);

			cycle_state->back().observation.push_back(step_probability);
		}
		return cycle_state->back().observation;
	}
}

