#include <iostream>
#include <random>
#include <fstream>

int main(){
	double mean = 0;
	double stddev = 1;
	int N = 10000;

	std::ofstream out;
	out.open("./number_3.txt");

	std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::normal_distribution<> distrib(mean, stddev);



	for (int i = 0; i < N; i++){
		out << distrib(gen) << ' ';
	}
	std::cout << std::endl;

	out.close();

	return 0;
}