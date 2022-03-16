#include <iostream>
#include <random>
#include <fstream>


int main(){
	double K = 2.;
	int N = 100;

	std::ofstream out;
	out.open("./number_2.txt");

	std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> distrib(1., K);

	for (int i = 0; i < N; i++){
		out << distrib(gen) << ' ';
	}

	out.close();

	return 0;
}