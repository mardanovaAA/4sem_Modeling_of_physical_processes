#include <iostream>
#include <random>

#include <fstream>




int main(){

	int K = 100;
	int N = 100000;

	std::ofstream out;
	out.open("./number_1.txt");

	std::random_device rd;

	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, K);

	for (int i = 0; i < N; i++){
		out << distrib(gen) << std::endl;
	}

	out.close();

	return 0;
}