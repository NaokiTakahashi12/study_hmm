
/**
  *
  * @file main.cpp
  * @author Naoki Takahashi
  *
  **/

#include <iostream>
#include <algorithm>

#include <HMM.hpp>

int main(int argc, char **argv) {
	using namespace HMM;

	auto model_calc = std::make_unique<ModelCalculator>();

	model_calc->set_number_of_node(3);
	model_calc->set_number_of_state_probability(3);
	model_calc->set_number_of_state(4);

	std::vector<std::vector<float>> model;
	std::vector<float> maximums;
	std::vector<float> forward;

	for(int i = 0; i < 10; i++) {
		model.push_back(model_calc->get_observation());
		maximums.push_back(model_calc->get_maximum_element());
		forward.push_back(model_calc->get_forward());

		model_calc->update();
	}

	std::cout << " - - - - - Result - - - - -" << std::endl;

	std::cout << "Maximum" << std::endl;
	for(auto &&m : maximums) {
		std::cout << m << " ";
	}
	std::cout << std::endl;

	std::cout << "Forward" << std::endl;
	for(auto &&f : forwards) {
		std::cout << f << " ";
	}
	std::cout << std::endl;
	std::cout << " - - - - - Result - - - - -" << std::endl;

	return 0;
}

