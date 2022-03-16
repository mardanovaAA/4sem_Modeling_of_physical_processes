#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <algorithm>

int main(){
	int K = 100;

	std::ofstream out;
	out.open("probability.txt");

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr (1,K);

	for (int N = 10; N < 1600; N += 10){
		double sucess = 0;
		double count = 0;
		while (count != 200){
			std::vector<int> check (K, 0);
			count++;

			for (int i = 1; i < N; i++){
				check[distr(gen) - 1] = 1;
			}

			if (std::accumulate(std::begin(check), std::end(check), 0) == K) sucess++;
		}

		out << N << " " << sucess / count << "\n";
	}

	return 0;
}