#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

double next_elem(double r, double prev_x){
	return (r * prev_x * (1 - prev_x));
}


template <typename A>
std::ostream& operator<< (std::ostream& out, std::vector<A> vec2print){
	for (auto i : vec2print){
		out << i << " ";
	}
	out << "\n";
	return out;
}


void print (std::ostream& out, std::vector<double>::iterator it_1, std::vector<double>::iterator it_2){
	for (auto i = it_1; i < it_2; i++){
		out << *i << " ";
	}
	out << "\n";
}


int main(){

	std::ofstream out;
	out.open("Data.txt");

	std::vector<double> param_r;
	for (double i = 3; i < 3.7; i += 0.05){
		param_r.push_back(i);
	};

	std::vector<double> initial_x (param_r.size(), 0.5);

	for (int number = 0; number < param_r.size(); number++){
		double r = param_r[number];
		std::vector<double> sequence;
		sequence.push_back(initial_x[number]);

		bool flag = true;
		int amount = 0;
		while (flag){
			double what2add = next_elem(r, *std::prev(sequence.end()));
			
			auto res = std::find(std::begin(sequence), std::end(sequence), what2add);

			amount ++;

			if (amount > 10000){
				flag = false;
			}

			if (res != std::end(sequence)){
				out << r << " ";
				for (auto it = res; it < std::end(sequence); it++){
					out << *it << " ";
				}
				out << "\n";
				flag = false;
			} else {
				sequence.push_back(what2add);
			}

		}
	}

	// std::vector<double> initial_x;
	// for (double i = 0.5; i < 4; i += 0.5){
	// 	initial_x.push_back(i);
	// }

	// std::vector<double> param_r (initial_x.size(), 0.5);

	// for (auto r : param_r){
	// 	out << r << " ";
	// }
	// out << "\n";

	// int amount = 100;
	// std::vector<double> current_x = initial_x;
	// out << current_x;

	// for (int i = 0; i < amount; i++){
	// 	std::transform(std::begin(current_x), std::end(current_x), std::begin(param_r), std::begin(current_x),
	// 		[](double prev_x, double r){return (r * prev_x * (1 - prev_x));});

	// 	out << current_x;
	// }

	out.close();

	return 0;
}
