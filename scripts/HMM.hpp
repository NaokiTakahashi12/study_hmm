
/**
  * 
  * @file HMM.hpp
  * @author Naoki Takahashi
  * 
  **/

#pragma once

#include <Vase.hpp>

namespace HMM {
	struct CycleState {
		std::vector<float> observation;
	};

	class ModelCalculator {
		public :
			ModelCalculator();

			ModelCalculator &set_number_of_outpt(const int &number),
							&set_number_of_node(const int &number),
							&set_number_of_state_probability(const int &number),
							&set_number_of_state(const int &number);

			ModelCalculator &update();

			int get_maximum_element_id();

			float get_maximum_element();

			float get_forward();

			std::vector<float> get_observation();

		private :
			int number_of_node,
				number_of_state_probabikity,
				number_of_state;

			int maximum_id;

			float maximum;

			std::unique_ptr<std::vector<CycleState>> cycle_state;

			std::unique_ptr<Vase> vase;

			float maximum_vecttor_element(const std::vector<float> &);
			
			std::vector<float> create_observation();

	};
}

