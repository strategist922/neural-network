/*
 * Neural Network Library
 * Copyright 2012, Mickael Lebedev
 */
#include <iostream>
#include "./perceptron.h"
#include "./activation_function.h"
#include "./random.h"
#include "./neural_network_exception.h"

using namespace NeuralNetwork;

const double learning_rate = 0.1;

Perceptron::Perceptron(int inputs_nb) :
    learning_rate_(learning_rate),
    activation(ActivationFunction::heavyside),
    weights_(inputs_nb),
    size_(inputs_nb) {
  Random::initialize();
  randomizeWeights();
}

void Perceptron::randomizeWeights(int min, int max) {
  for (int i = 0; i < size_; ++i) {
    weights_[i] = Random::rand(min, max);
  }
  threshold_ = Random::rand(min, max);
}

double Perceptron::getOutput(const std::vector<double>& inputs) {
  float sum = 0;

  inputs_ = inputs;
  for (int i = 0; i < size_; ++i) {
    sum += inputs[i] * weights_[i];
  }
  return output_ = activation(sum + threshold_);
}

void Perceptron::trainOnData(const std::vector<std::vector<double> >& input_set,
  const std::vector<double>& target_output_set,
  int max_epochs) {
    for (int i = 0; i < max_epochs; i++) {
    	for (unsigned int j = 0; j < input_set.size(); j++) {
			double out = getOutput(input_set[j]);
			if (target_output_set[j] != out) {
				updateWeights(target_output_set[j] - out);
			}
	    }
    }
}

void Perceptron::updateWeights(double delta) {
  for (int i = 0; i < size_; ++i) {
    weights_[i] += (delta * learning_rate_ * inputs_[i]);
  }
  threshold_ += (delta * learning_rate_);
}

const std::vector<double>& Perceptron::getWeights() const {
  return weights_;
}

double Perceptron::getThreshold() const {
  return threshold_;
}

double Perceptron::getLastOutput() const {
  return output_;	
}

void Perceptron::setActivationFunction(double (*f)(double)) {
  activation = f;	
}

Perceptron::~Perceptron() {}
