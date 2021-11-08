//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   W E I G H T E D   S Q U A R E D   E R R O R   T E S T   C L A S S     
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "weighted_squared_error_test.h"


WeightedSquaredErrorTest::WeightedSquaredErrorTest() : UnitTesting()
{
    weighted_squared_error.set(&neural_network, &data_set);

    weighted_squared_error.set_regularization_method(LossIndex::RegularizationMethod::NoRegularization);
}


WeightedSquaredErrorTest::~WeightedSquaredErrorTest()
{
}


void WeightedSquaredErrorTest::test_constructor()
{
   cout << "test_constructor\n";

   // Default

   WeightedSquaredError weighted_squared_error_1;

   assert_true(!weighted_squared_error_1.has_neural_network(), LOG);
   assert_true(!weighted_squared_error_1.has_data_set(), LOG);

   // Neural network and data set

   WeightedSquaredError weighted_squared_error_2(&neural_network, &data_set);

   assert_true(weighted_squared_error_2.has_neural_network(), LOG);
   assert_true(weighted_squared_error_2.has_data_set(), LOG);
}


void WeightedSquaredErrorTest::test_back_propagate()
{
    cout << "test_back_propagate\n";
/*
    // Empty test does not work
    // weighted_squared_error.back_propagate(batch, forward_propagation, back_propagation);

    // Test approximation all zero
    {
        samples_number = 1;
        inputs_number = 1;
        outputs_number = 1;
        neurons_number = 1;

        // Data set

        data_set.set(samples_number, inputs_number, outputs_number);
        data_set.set_data_constant(type(0));

        data_set.set_training();

        training_samples_indices = data_set.get_training_samples_indices();

        input_variables_indices = data_set.get_input_variables_indices();
        target_variables_indices = data_set.get_target_variables_indices();

        batch.set(samples_number, &data_set);
        batch.fill(training_samples_indices, input_variables_indices, target_variables_indices);

        // Neural network

        neural_network.set(NeuralNetwork::ProjectType::Approximation, {inputs_number, neurons_number, outputs_number});
        neural_network.set_parameters_constant(type(0));

        forward_propagation.set(samples_number, &neural_network);
        neural_network.forward_propagate(batch, forward_propagation);

        // Loss index

        weighted_squared_error.set_weights();

        back_propagation.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate(batch, forward_propagation, back_propagation);

        assert_true(back_propagation.errors.dimension(0) == samples_number, LOG);
        assert_true(back_propagation.errors.dimension(1) == outputs_number, LOG);

        assert_true(abs(back_propagation.error) < NUMERIC_LIMITS_MIN, LOG);
        assert_true(back_propagation.gradient.size() == inputs_number+inputs_number*neurons_number+outputs_number+outputs_number*neurons_number, LOG);

        assert_true(is_zero(back_propagation.gradient) , LOG);
    }

    // Test approximation all random
    {
        samples_number = 1 + rand()%5;
        inputs_number = 1 + rand()%5;
        outputs_number = 1 + rand()%5;
        neurons_number = 1 + rand()%5;

        // Data set

        data_set.set(samples_number, inputs_number, outputs_number);
        data_set.set_data_random();

        data_set.set_training();

        training_samples_indices = data_set.get_training_samples_indices();
        input_variables_indices = data_set.get_input_variables_indices();
        target_variables_indices = data_set.get_target_variables_indices();

        batch.set(samples_number, &data_set);
        batch.fill(training_samples_indices, input_variables_indices, target_variables_indices);

        // Neural network

        neural_network.set(NeuralNetwork::ProjectType::Approximation, {inputs_number, neurons_number, outputs_number});
        neural_network.set_parameters_random();

        forward_propagation.set(samples_number, &neural_network);
        neural_network.forward_propagate(batch, forward_propagation);

        // Loss index

        weighted_squared_error.set_weights();

        back_propagation.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate(batch, forward_propagation, back_propagation);

        gradient_numerical_differentiation = weighted_squared_error.calculate_gradient_numerical_differentiation();


        assert_true(back_propagation.errors.dimension(0) == samples_number, LOG);
        assert_true(back_propagation.errors.dimension(1) == outputs_number, LOG);

        assert_true(are_equal(back_propagation.gradient, gradient_numerical_differentiation, type(1.0e-2)), LOG);
    }

    // Test binary classification trivial
    {
        inputs_number = 1;
        outputs_number = 1;
        samples_number = 1;

        // Data set

        data_set.set(samples_number, inputs_number, outputs_number);
        data_set.set_data_constant(type(0));

        training_samples_indices = data_set.get_training_samples_indices();
        input_variables_indices = data_set.get_input_variables_indices();
        target_variables_indices = data_set.get_target_variables_indices();

        batch.set(samples_number, &data_set);
        batch.fill(training_samples_indices, input_variables_indices, target_variables_indices);

        // Neural network

        neural_network.set(NeuralNetwork::ProjectType::Classification, {inputs_number, outputs_number});
        neural_network.set_parameters_constant(type(0));

        forward_propagation.set(samples_number, &neural_network);
        neural_network.forward_propagate(batch, forward_propagation);

        // Loss index

        weighted_squared_error.set_weights();

        back_propagation.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate(batch, forward_propagation, back_propagation);

        gradient_numerical_differentiation = weighted_squared_error.calculate_gradient_numerical_differentiation();


        assert_true(back_propagation.errors.dimension(0) == samples_number, LOG);
        assert_true(back_propagation.errors.dimension(1) == outputs_number, LOG);

        assert_true(back_propagation.errors.dimension(0) == 1, LOG);
        assert_true(back_propagation.errors.dimension(1) == 1, LOG);
        assert_true(back_propagation.error - type(0.25) < type(NUMERIC_LIMITS_MIN), LOG);

        assert_true(are_equal(back_propagation.gradient, gradient_numerical_differentiation, 1.0e-3), LOG);

    }

    // Test binary classification random samples, inputs, outputs, neurons
    {
        samples_number = 1 + rand()%10;
        inputs_number = 1 + rand()%10;
        outputs_number = 1;
        neurons_number = 1 + rand()%10;

        // Data set

        data_set.set(samples_number, inputs_number, outputs_number);
        data_set.set_data_binary_random();
        data_set.set_training();

        training_samples_indices = data_set.get_training_samples_indices();
        input_variables_indices = data_set.get_input_variables_indices();
        target_variables_indices = data_set.get_target_variables_indices();

        batch.set(samples_number, &data_set);
        batch.fill(training_samples_indices, input_variables_indices, target_variables_indices);

        // Neural network

        neural_network.set(NeuralNetwork::ProjectType::Classification, {inputs_number, neurons_number, outputs_number});
        neural_network.set_parameters_random();

        forward_propagation.set(samples_number, &neural_network);
        neural_network.forward_propagate(batch, forward_propagation);

        // Loss index

        weighted_squared_error.set_weights();

        back_propagation.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate(batch, forward_propagation, back_propagation);

        gradient_numerical_differentiation = weighted_squared_error.calculate_gradient_numerical_differentiation();


        assert_true(back_propagation.errors.dimension(0) == samples_number, LOG);
        assert_true(back_propagation.errors.dimension(1) == outputs_number, LOG);

        assert_true(are_equal(back_propagation.gradient, gradient_numerical_differentiation, 1.0e-2), LOG);
    }


    // Test forecasting trivial
    {
        inputs_number = 1;
        outputs_number = 1;
        samples_number = 1;

        // Data set

        data_set.set(samples_number, inputs_number, outputs_number);
        data_set.set_data_constant(type(0));

        training_samples_indices = data_set.get_training_samples_indices();
        input_variables_indices = data_set.get_input_variables_indices();
        target_variables_indices = data_set.get_target_variables_indices();

        batch.set(samples_number, &data_set);
        batch.fill(training_samples_indices, input_variables_indices, target_variables_indices);

        // Neural network

        neural_network.set(NeuralNetwork::ProjectType::Forecasting, {inputs_number, outputs_number});
        neural_network.set_parameters_constant(type(0));

        forward_propagation.set(samples_number, &neural_network);
        neural_network.forward_propagate(batch, forward_propagation);

        // Loss index

        weighted_squared_error.set_weights();

        back_propagation.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate(batch, forward_propagation, back_propagation);


        assert_true(back_propagation.errors.dimension(0) == samples_number, LOG);
        assert_true(back_propagation.errors.dimension(1) == outputs_number, LOG);

        assert_true(back_propagation.error < type(NUMERIC_LIMITS_MIN), LOG);
        assert_true(is_zero(back_propagation.gradient), LOG);
    }
*/
    // Test forecasting random samples, inputs, outputs, neurons
    {
        samples_number = 2;// + rand()%10;
        inputs_number = 2;// + rand()%10;
        outputs_number = 2;// + rand()%10;
        neurons_number = 2;// + rand()%10;

        Tensor<type,2> data(samples_number, inputs_number+outputs_number);
        type max = 10;
        type min = -10;

        data.setValues({{2,-4,6,2},{6,-1,-2.5,9.6}});

        /*for(Index i=0; i<=data.size();i++)
        {
            data(i) = static_cast<type>((max-min)/static_cast<type>(RAND_MAX)*(type(rand()))) + min;
        }*/

        cout << data << endl;

        // Data set

        data_set.set(samples_number, inputs_number, outputs_number);
        data_set.set(data);
        data_set.set_training();

        training_samples_indices = data_set.get_training_samples_indices();
        input_variables_indices = data_set.get_input_variables_indices();
        target_variables_indices = data_set.get_target_variables_indices();

        batch.set(samples_number, &data_set);
        batch.fill(training_samples_indices, input_variables_indices, target_variables_indices);

        // Neural network

        neural_network.set(NeuralNetwork::ProjectType::Forecasting, {inputs_number, neurons_number, outputs_number});
        neural_network.set_parameters_random();

        forward_propagation.set(samples_number, &neural_network);
        neural_network.forward_propagate(batch, forward_propagation);

        // Loss index

        weighted_squared_error.set_weights();

        cout << "Positives weight: " << weighted_squared_error.get_positives_weight() << endl;
        cout << "Negatives weight: " << weighted_squared_error.get_negatives_weight() << endl;

        back_propagation.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate(batch, forward_propagation, back_propagation);

        back_propagation.print();

        gradient_numerical_differentiation = weighted_squared_error.calculate_gradient_numerical_differentiation();

        assert_true(back_propagation.errors.dimension(0) == samples_number, LOG);
        assert_true(back_propagation.errors.dimension(1) == outputs_number, LOG);

        assert_true(back_propagation.error >= type(0), LOG);

        assert_true(are_equal(back_propagation.gradient, gradient_numerical_differentiation, type(1.0e-2)), LOG);
    }
}


void WeightedSquaredErrorTest::test_back_propagate_lm()
{
    cout << "test_back_propagate_lm\n";
/*
    // Test trivial approximation
    {
        samples_number = 1;// + rand()%10;
        inputs_number = 1;// + rand()%10;
        outputs_number = 1;// + rand()%10;
        neurons_number = 1;// + rand()%10;

        // Data set

        data_set.set(samples_number, inputs_number, outputs_number);
        data_set.set_data_constant(type(0));
        data_set.set_training();

        training_samples_indices = data_set.get_training_samples_indices();
        input_variables_indices = data_set.get_input_variables_indices();
        target_variables_indices = data_set.get_target_variables_indices();

        batch.set(samples_number, &data_set);
        batch.fill(training_samples_indices, input_variables_indices, target_variables_indices);

        // Neural network

        neural_network.set(NeuralNetwork::ProjectType::Approximation, {inputs_number, neurons_number, outputs_number});
        neural_network.set_parameters_constant(type(0));

        forward_propagation.set(samples_number, &neural_network);
        neural_network.forward_propagate(batch, forward_propagation);

        // Loss index

        weighted_squared_error.set_weights();

        back_propagation.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate(batch, forward_propagation, back_propagation);

        back_propagation_lm.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate_lm(batch, forward_propagation, back_propagation_lm);

        gradient_numerical_differentiation = weighted_squared_error.calculate_gradient_numerical_differentiation();
        jacobian_numerical_differentiation = weighted_squared_error.calculate_jacobian_numerical_differentiation();

        assert_true(back_propagation_lm.errors.dimension(0) == samples_number, LOG);
        assert_true(back_propagation_lm.errors.dimension(1) == outputs_number, LOG);

        assert_true(back_propagation_lm.error >= type(0), LOG);
        assert_true(abs(back_propagation.error-back_propagation_lm.error) < type(1.0e-2), LOG);

        assert_true(are_equal(back_propagation_lm.gradient, gradient_numerical_differentiation, type(1.0e-2)), LOG);
        assert_true(are_equal(back_propagation_lm.squared_errors_jacobian, jacobian_numerical_differentiation, type(1.0e-2)), LOG);

        }

    // Test approximation all random
    {
        samples_number = 2;// + rand()%10;
        inputs_number = 2;// + rand()%10;
        outputs_number = 2;// + rand()%10;
        neurons_number = 2;// + rand()%10;

        // Data set

        data_set.set(samples_number, inputs_number, outputs_number);
        data_set.set_data_random();
        data_set.set_training();

        data_set.print();
        data_set.print_data();

        training_samples_indices = data_set.get_training_samples_indices();
        input_variables_indices = data_set.get_input_variables_indices();
        target_variables_indices = data_set.get_target_variables_indices();

        batch.set(samples_number, &data_set);
        batch.fill(training_samples_indices, input_variables_indices, target_variables_indices);

        // Neural network

        neural_network.set(NeuralNetwork::ProjectType::Approximation, {inputs_number, neurons_number, outputs_number});
        neural_network.set_parameters_random();

        forward_propagation.set(samples_number, &neural_network);
        neural_network.forward_propagate(batch, forward_propagation);

        // Loss index

        weighted_squared_error.set_weights();

        back_propagation.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate(batch, forward_propagation, back_propagation);

        back_propagation_lm.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate_lm(batch, forward_propagation, back_propagation_lm);

        gradient_numerical_differentiation = weighted_squared_error.calculate_gradient_numerical_differentiation();
        jacobian_numerical_differentiation = weighted_squared_error.calculate_jacobian_numerical_differentiation();

        assert_true(back_propagation_lm.errors.dimension(0) == samples_number, LOG);
        assert_true(back_propagation_lm.errors.dimension(1) == outputs_number, LOG);

        back_propagation.print();
        back_propagation_lm.print();

        assert_true(back_propagation_lm.error >= type(0), LOG);
        assert_true(abs(back_propagation.error-back_propagation_lm.error) < type(1.0e-2), LOG);

        assert_true(are_equal(back_propagation_lm.gradient, gradient_numerical_differentiation, type(1.0e-2)), LOG);
        assert_true(are_equal(back_propagation_lm.squared_errors_jacobian, jacobian_numerical_differentiation, type(1.0e-2)), LOG);

        }
/*
    // Test classification random samples, inputs, outputs, neurons
    {
        samples_number = 1 + rand()%10;
        inputs_number = 1 + rand()%10;
        outputs_number = 1 + rand()%10;
        neurons_number = 1 + rand()%10;

        // Data set

        data_set.set(samples_number, inputs_number, outputs_number);
        data_set.set_data_random();
        data_set.set_training();

        training_samples_indices = data_set.get_training_samples_indices();
        input_variables_indices = data_set.get_input_variables_indices();
        target_variables_indices = data_set.get_target_variables_indices();

        batch.set(samples_number, &data_set);
        batch.fill(training_samples_indices, input_variables_indices, target_variables_indices);

        // Neural network

        neural_network.set(NeuralNetwork::ProjectType::Classification, {inputs_number, neurons_number, outputs_number});
        neural_network.set_parameters_random();

        forward_propagation.set(samples_number, &neural_network);
        neural_network.forward_propagate(batch, forward_propagation);

        // Loss index

        back_propagation.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate(batch, forward_propagation, back_propagation);

        back_propagation_lm.set(samples_number, &weighted_squared_error);
        weighted_squared_error.back_propagate_lm(batch, forward_propagation, back_propagation_lm);

        gradient_numerical_differentiation = weighted_squared_error.calculate_gradient_numerical_differentiation();
        jacobian_numerical_differentiation = weighted_squared_error.calculate_jacobian_numerical_differentiation();

        assert_true(back_propagation_lm.errors.dimension(0) == samples_number, LOG);
        assert_true(back_propagation_lm.errors.dimension(1) == outputs_number, LOG);

        assert_true(back_propagation_lm.error >= type(0), LOG);
        assert_true(abs(back_propagation.error-back_propagation_lm.error) < type(1.0e-2), LOG);

        assert_true(are_equal(back_propagation_lm.gradient, gradient_numerical_differentiation, type(1.0e-2)), LOG);
        assert_true(are_equal(back_propagation_lm.squared_errors_jacobian, jacobian_numerical_differentiation, type(1.0e-2)), LOG);
    }
*/
    // Forecasting incompatible with LM

}


void WeightedSquaredErrorTest::test_calculate_error()
{
   cout << "test_calculate_error\n";

   Tensor<type, 2> data;

   Index samples_number;
   Index inputs_number;
   Index outputs_number;
   Index neurons_number;

   Tensor<type, 1> parameters; 

   Tensor<Index,1> samples_indices;
   Tensor<Index,1> input_variables_indices;
   Tensor<Index,1> target_variables_indices;

   // Test

   samples_number = 2;
   inputs_number = 1;
   outputs_number = 1;
   neurons_number = 1;

   data.resize(2, 2);
   data.setValues({
       {type(0),type(0)},
       {type(1),type(1)}});
   data_set.set(data);

   data_set.set_training();

   samples_indices = data_set.get_used_samples_indices();
   input_variables_indices = data_set.get_input_variables_indices();
   target_variables_indices = data_set.get_target_variables_indices();

   neural_network.set(NeuralNetwork::ProjectType::Classification, {1, 2});

   neural_network.set_parameters_constant(type(1));

   weighted_squared_error.set_weights();

   batch.set(samples_number, &data_set);
   batch.fill(samples_indices, input_variables_indices, target_variables_indices);

   forward_propagation.set(samples_number, &neural_network);
   neural_network.forward_propagate(batch, forward_propagation);

   back_propagation.set(samples_number, &weighted_squared_error);
   weighted_squared_error.calculate_error(batch, forward_propagation, back_propagation);

   assert_true(back_propagation.error == 1, LOG);

   // Test

   data_set.set(3, 3, 1);

   data.resize(3, 3);
   data(0,0) = 0.0;
   data(0,1) = 0.0;
   data(0,2) = 0.0;
   data(1,0) = type(1);
   data(1,1) = type(1);
   data(1,2) = type(1);
   data(2,0) = type(1);
   data(2,1) = 0.0;
   data(2,2) = 0.0;
   data_set.set_data(data);

  neural_network.set(NeuralNetwork::ProjectType::Approximation, {3, 1});

  neural_network.set_parameters_constant(type(0));

  weighted_squared_error.set_weights();

  assert_true(weighted_squared_error.get_positives_weight() != weighted_squared_error.get_negatives_weight(), LOG);

}


void WeightedSquaredErrorTest::test_calculate_error_gradient()
{
   cout << "test_calculate_error_gradient\n";

   Tensor<type, 2> data;

   Tensor<Index,1> samples_indices;
   Tensor<Index,1> input_variables_indices;
   Tensor<Index,1> target_variables_indices;

   Tensor<type, 1> error_gradient;
   Tensor<type, 1> numerical_error_gradient;
   Tensor<type, 0> maximum_difference;

   Index samples_number;
   Index inputs_number;
   Index outputs_number;
   Index neurons_number;

   ScalingLayer* scaling_layer = new ScalingLayer;

   RecurrentLayer* recurrent_layer = new RecurrentLayer;

   LongShortTermMemoryLayer* long_short_term_memory_layer = new LongShortTermMemoryLayer;

   PerceptronLayer* perceptron_layer_1 = new PerceptronLayer;
   PerceptronLayer* perceptron_layer_2 = new PerceptronLayer;

   ProbabilisticLayer* probabilistic_layer = new ProbabilisticLayer;

   Tensor<type, 1> parameters;

   Tensor<type, 2> inputs;

   Tensor<type, 2> outputs;

   // Test trivial

   samples_number = 2;
   inputs_number = 1;
   outputs_number = 1;

   data_set.set(1, 1, 1);

   data.resize(2, 2);
   data(0,0) = 0.0;
   data(0,1) = 0.0;
   data(1,0) = type(1);
   data(1,1) = type(1);

   data_set.set_data(data);
   data_set.set_training();

   samples_indices = data_set.get_used_samples_indices();
   input_variables_indices = data_set.get_input_variables_indices();
   target_variables_indices = data_set.get_target_variables_indices();

   neural_network.set(NeuralNetwork::ProjectType::Classification, {1, 1});

   neural_network.set_parameters_constant(type(1));

   weighted_squared_error.set_weights();

   batch.set(samples_number, &data_set);
   batch.fill(samples_indices, input_variables_indices, target_variables_indices);

   forward_propagation.set(samples_number, &neural_network);
   neural_network.forward_propagate(batch, forward_propagation);

   back_propagation.set(samples_number, &weighted_squared_error);
   weighted_squared_error.back_propagate(batch, forward_propagation, back_propagation);

//       weighted_squared_error.calculate_error(batch, forward_propagation, back_propagation);

   numerical_error_gradient = weighted_squared_error.calculate_gradient_numerical_differentiation();

   assert_true(back_propagation.gradient(0)-1.1499 < type(1e-3), LOG); // @todo 1e-2 precission
   assert_true(back_propagation.gradient(1)-0 < type(1e-3), LOG);

   // Test perceptron and probabilistic

   samples_number = 10;
   inputs_number = 3;
   outputs_number = 1;
   neurons_number = 2;

   data_set.set(samples_number, inputs_number, outputs_number);

   inputs.resize(samples_number,inputs_number);

   inputs.setRandom();

   outputs.resize(samples_number, outputs_number);

   neural_network.set();

   data_set.set_training();

   perceptron_layer_1->set(inputs_number, neurons_number);
   perceptron_layer_2->set(neurons_number, outputs_number);
   probabilistic_layer->set(outputs_number, outputs_number);

   neural_network.add_layer(perceptron_layer_1);
   neural_network.add_layer(perceptron_layer_2);
   neural_network.add_layer(probabilistic_layer);

   neural_network.set_parameters_random();

//   error_gradient = weighted_squared_error.calculate_error_gradient();

   numerical_error_gradient = weighted_squared_error.calculate_gradient_numerical_differentiation();

   maximum_difference = (error_gradient - numerical_error_gradient).abs().maximum();

   assert_true(maximum_difference(0) < 1.0e-3, LOG);

   // Test lstm

   neural_network.set();

   samples_number = 10;
   inputs_number = 3;
   outputs_number = 1;
   neurons_number = 2;

   data_set.set(samples_number, inputs_number, outputs_number);

   inputs.resize(samples_number,inputs_number);

   data_set.set_data(data);

   data_set.set_training();

   long_short_term_memory_layer->set(inputs_number, neurons_number);
   perceptron_layer_2->set(neurons_number, outputs_number);

   neural_network.add_layer(long_short_term_memory_layer);
   neural_network.add_layer(perceptron_layer_2);

   neural_network.set_parameters_random();

//   error_gradient = weighted_squared_error.calculate_error_gradient();

//   numerical_error_gradient = weighted_squared_error.calculate_gradient_numerical_differentiation();

   maximum_difference = (error_gradient - numerical_error_gradient).abs().sum();

   assert_true(maximum_difference(0) < 1.0e-3, LOG);

   // Test recurrent

   neural_network.set();

   samples_number = 10;
   inputs_number = 3;
   outputs_number = 1;

   neurons_number = 2;

   data_set.set(samples_number, inputs_number, outputs_number);

   data_set.set_data(data);

   data_set.set_training();

   recurrent_layer->set(inputs_number, neurons_number);
   perceptron_layer_2->set(neurons_number, outputs_number);

   neural_network.add_layer(recurrent_layer);
   neural_network.add_layer(perceptron_layer_2);

   neural_network.set_parameters_random();

   numerical_error_gradient = weighted_squared_error.calculate_gradient_numerical_differentiation();

   maximum_difference = (error_gradient - numerical_error_gradient).abs().sum();

   assert_true(maximum_difference(0) < 1.0e-3, LOG);

   // Test convolutional

//   samples_number = 5;
//   inputs_number = 147;
//   outputs_number = 1;

//   data_set.set(samples_number, inputs_number, outputs_number);

//   Tensor<type, 2> inputs(samples_number,inputs_number);
//   inputs.setRandom();

//   Tensor<type, 1> outputs(samples_number, outputs_number);
//   outputs[0] = 1.0;
//   outputs[1] = 0.0;

//   for(Index i = 2; i < samples_number; i++)
//   {
//        if((static_cast<Index>(inputs.calculate_row_sum(i))%2)) < NUMERIC_LIMITS_MIN)
//        {
//            outputs[i] = 0.0;
//        }
//        else
//        {
//            outputs[i] = 1.0;
//        }
//   }

//   const Tensor<type, 2> data = inputs.append_column(outputs);

//   data_set.set_data(data);
//   data_set.set_input_variables_dimensions(Tensor<Index, 1>({3,7,7}));
//   data_set.set_target_variables_dimensions(Tensor<Index, 1>({1}));
//   data_set.set_training();

//   const type parameters_minimum = -100.0;
//   const type parameters_maximum = 100.0;

//   ConvolutionalLayer* convolutional_layer_1 = new ConvolutionalLayer({3,7,7}, {2,2,2});
//   Tensor<type, 2> filters_1({2,3,2,2}, 0);
//   filters_1.setRandom(parameters_minimum,parameters_maximum);
//   convolutional_layer_1->set_synaptic_weights(filters_1);
//   Tensor<type, 1> biases_1(2, 0);
//   biases_1.setRandom(parameters_minimum, parameters_maximum);
//   convolutional_layer_1->set_biases(biases_1);

//   ConvolutionalLayer* convolutional_layer_2 = new ConvolutionalLayer(convolutional_layer_1->get_outputs_dimensions(), {2,2,2});
//   convolutional_layer_2->set_padding_option(OpenNN::ConvolutionalLayer::Same);
//   Tensor<type, 2> filters_2({2,2,2,2}, 0);
//   filters_2.setRandom(parameters_minimum, parameters_maximum);
//   convolutional_layer_2->set_synaptic_weights(filters_2);
//   Tensor<type, 1> biases(2, 0);
//   biases.setRandom(parameters_minimum, parameters_maximum);
//   convolutional_layer_2->set_biases(biases);

//   PoolingLayer* pooling_layer_1 = new PoolingLayer(convolutional_layer_2->get_outputs_dimensions(), {2,2});

//   ConvolutionalLayer* convolutional_layer_3 = new ConvolutionalLayer(pooling_layer_1->get_outputs_dimensions(), {1,2,2});
//   convolutional_layer_3->set_padding_option(OpenNN::ConvolutionalLayer::Same);
//   Tensor<type, 2> filters_3({1,2,2,2}, 0);
//   filters_3.setRandom(parameters_minimum, parameters_maximum);
//   convolutional_layer_3->set_synaptic_weights(filters_3);
//   Tensor<type, 1> biases_3(1, 0);
//   biases_3.setRandom(parameters_minimum, parameters_maximum);
//   convolutional_layer_3->set_biases(biases_3);

//   PoolingLayer* pooling_layer_2 = new PoolingLayer(convolutional_layer_3->get_outputs_dimensions(), {2,2});
//   pooling_layer_2->set_pooling_method(PoolingLayer::MaxPooling);

//   PoolingLayer* pooling_layer_3 = new PoolingLayer(pooling_layer_2->get_outputs_dimensions(), {2,2});
//   pooling_layer_3->set_pooling_method(PoolingLayer::MaxPooling);

//   PerceptronLayer* perceptron_layer = new PerceptronLayer(pooling_layer_3->get_outputs_dimensions().calculate_product(), 3, OpenNN::PerceptronLayer::ActivationFunction::Linear);
//   perceptron_layer->set_parameters_random(parameters_minimum, parameters_maximum);

//   ProbabilisticLayer* probabilistic_layer = new ProbabilisticLayer(perceptron_layer->get_neurons_number(), outputs_number);
//   probabilistic_layer->set_parameters_random(parameters_minimum, parameters_maximum);

//   neural_network.set();
//   neural_network.add_layer(convolutional_layer_1);
//   neural_network.add_layer(convolutional_layer_2);
//   neural_network.add_layer(pooling_layer_1);
//   neural_network.add_layer(convolutional_layer_3);
//   neural_network.add_layer(pooling_layer_2);
//   neural_network.add_layer(pooling_layer_3);
//   neural_network.add_layer(perceptron_layer);
//   neural_network.add_layer(probabilistic_layer);

//   numerical_error_gradient = weighted_squared_error.calculate_gradient_numerical_differentiation();

//   error_gradient = weighted_squared_error.calculate_error_gradient();

       maximum_difference = (error_gradient - numerical_error_gradient).abs().sum();

       assert_true(maximum_difference(0) < 1.0e-3, LOG);

}


void WeightedSquaredErrorTest::run_test_case()
{
   cout << "Running weighted squared error test case...\n";

   // Constructor and destructor methods

   test_constructor();

   // Back-propagation methods

   test_back_propagate();

   test_back_propagate_lm();

   cout << "End of weighted squared error test case.\n\n";
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2021 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lewser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lewser General Public License for more details.

// You should have received a copy of the GNU Lewser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
