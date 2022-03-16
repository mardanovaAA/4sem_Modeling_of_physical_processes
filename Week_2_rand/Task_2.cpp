#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>
#include <fstream>


int main(){

	std::vector<int> dict; //consist of all possible sequences

	for (int i = 1; i < 4; i++){
		for (int j = 1; j < 4; j++){
	 		for (int k = 1; k < 4; k++){
	 			dict.push_back(i*100 + j*10 + k);
	 		}
	 	}
	}

	std::ofstream out;

	out.open("Task_2.txt");

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 3);


	for (int number = 0; number < dict.size(); number++){
		int search = dict[number];
		int sum = 0;
		int amount = 100000;
		for (int i = 0; i < amount; i++){
			int count = 0;
			bool flag = true;

			std::vector<int> period (3, 0);

			while (flag){
				int rand_num = distrib(gen);
				if (period[count % 3] == search){
					flag = false;
				} else {
					period[count % 3] = 0;
					if (count % 3 == 0){
						period[0] += rand_num * 100;
						period[1] += rand_num * 1;
						period[2] += rand_num * 10;
					} else if (count % 3 == 1){
						period[0] += rand_num * 10;
						period[1] += rand_num * 100;
						period[2] += rand_num * 1;
					} else if (count % 3 == 2){
						period[0] += rand_num * 1;
						period[1] += rand_num * 10;
						period[2] += rand_num * 100;
					}
					count++;
				}
			}

			sum += count;
		}
		out << number+1 << " " << search << " " << static_cast<double>(sum) / amount << "\n";


	}

	out.close();

	return 0;
}