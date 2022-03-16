#include <iostream>
#include <random>
#include <cmath>
#include <fstream>

template <typename A>
class Inverse_function{
	private:
		A type_dist;
	
	public:
		Inverse_function(A type_dist): type_dist(type_dist){};

		double equation(double y){
			return type_dist.distribution(y);
		};
};


class exponential_dist{
	private:
		double lambda;

	public:
		exponential_dist(double lambda): lambda(lambda){};

		exponential_dist(): exponential_dist(1.){};

		double distribution(double y){
			return -std::log(1 - y) / lambda;
		};
};


int main(){
	int N = 1000000;
	double lambda = 1.5;

	exponential_dist exp (lambda);

	Inverse_function<exponential_dist> inv_func (exp);

	std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> distrib(0., 1.);

    std::ofstream out;
	out.open("./number_7.txt");

	for (int i = 0; i < N; i++){
		double y = distrib(gen);

		out << inv_func.equation(y) << " ";
	}

	out.close();

	return 0;
}
