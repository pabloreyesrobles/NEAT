#include <vector>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <NEAT>

#define INPUTS 2
#define OUTPUTS 1

using namespace std;
using namespace ANN_USM;

vector <double> inputVector;
vector <double> outputVector;

Population *cppn_neat;

double fitness_neat(Genetic_Encoding);

int main(int argc, char *argv[])
{
	clog << "Initializing..." << endl;
	srand (time(0));
		
	for (unsigned int i = 0; i < INPUTS; i++){
		inputVector.push_back(0.0);
	}

	for (unsigned int i = 0; i < OUTPUTS; i++){
		outputVector.push_back(0.0);
	}

	clog << "Initializing ANN" << endl;
	cppn_neat = new Population(argv[1], argv[2], (char*)"NEAT", argv[3]);

	cppn_neat->survivalSelection = true;
	cppn_neat->allowClones = true;

	cppn_neat->survivalThreshold = 0.3;
	cppn_neat->eliteOffspringParam = 0.02;

	double fitness;

	clog << "Initialized!" << endl;

	for(int i = 0; i < cppn_neat->GENERATIONS; i++)
	{
		clog << "Generation: " << i << endl;
		for (int j = 0; j < cppn_neat->POPULATION_MAX; j++)
		{
			cppn_neat->organisms[j].fitness = fitness_neat(cppn_neat->organisms[j]);				
		}

		cppn_neat->Epoch();
	}

	cout << "Fitness champion: " << cppn_neat->champion << "\n\n" << endl;
	cout << cppn_neat->champion.ANN_function() << endl;
	cout << cppn_neat->champion << endl;
	
	return 0;
}

double fitness_neat(Genetic_Encoding organism){

	vector<double> output;
	vector<double> input;

	double error_sum = 0;
	//cout << organism << endl;

	// XOR(0,0) -> 0
	input.push_back(0);
	input.push_back(0);

	output = organism.eval(input);

	error_sum += abs(output.at(0));
	input.clear();

	// XOR(0,1) -> 1
	input.push_back(0);
	input.push_back(1);
	output = organism.eval(input);
	error_sum += abs(1 - output.at(0));
	input.clear();

	// XOR(1,0) -> 1
	input.push_back(1);
	input.push_back(0);
	output = organism.eval(input);
	error_sum += abs(1 - output.at(0));
	input.clear();

	// XOR(1,1) -> 0
	input.push_back(1);
	input.push_back(1);
	output = organism.eval(input);
	error_sum += abs(output.at(0));
	input.clear();

	return pow(4 - error_sum, 2);
}