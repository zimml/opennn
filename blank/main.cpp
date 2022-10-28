//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   B L A N K   A P P L I C A T I O N
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

// System includes

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

// OpenNN includes

#include "../opennn/opennn.h"
using namespace opennn;

int main(int argc, char* argv[])
{
    try
    {
        cout << "Hello OpenNN" << endl;

        DataSet data_set("C:/Users/rodrigo ingelmo/Desktop/Nueva carpeta/opennn/blank/data/sum.csv",';',false);

        const Index input_variables_number = data_set.get_input_variables_number();

        const Index target_variables_number = data_set.get_target_variables_number();

        const Index hidden_neurons_number = 1;

        // Neural Network

        NeuralNetwork neural_network(NeuralNetwork::ProjectType::Approximation,
            { input_variables_number, hidden_neurons_number, target_variables_number });

        // Training Strategy

        TrainingStrategy training_strategy(&neural_network, &data_set);

        training_strategy.set_optimization_method(TrainingStrategy::OptimizationMethod::QUASI_NEWTON_METHOD);

        training_strategy.set_display_period(1000);

        training_strategy.perform_training();

        GeneticAlgorithm genetic_algorithm(&training_strategy);

        genetic_algorithm.set_individuals_number(10);

        genetic_algorithm.set_maximum_epochs_number(1000);

        InputsSelectionResults inputs_selection_results=genetic_algorithm.perform_inputs_selection();

        cout<<"MTEH"<<endl;
        cout<<inputs_selection_results.mean_training_error_history<<endl;
        cout<<"MSEH"<<endl;
        cout<<inputs_selection_results.mean_selection_error_history<<endl;

        cout << "Bye OpenNN" << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;

        return 1;
    }
}

// OpenNN: Open Neural Networks Library.
// Copyright (C) Artificial Intelligence Techniques SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

