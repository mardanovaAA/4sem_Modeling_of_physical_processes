#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include <iterator>
#include <fstream>

class Gas{
private:
	int amount_m1;
	int amount_m2;
	double k; // = m1:m2

	double right_border = 100;
	double left_border = 0;

	std::vector<double> coordinates_1;
	std::vector<double> velocity_1;

	std::vector<double> coordinates_2;
	std::vector<double> velocity_2;


	double time_step = 0.1;


	bool collision_of_two(double& coord1, double& vel1, double& coord2, double& vel2){
		bool collision_exist = false;

		if (!(((coord1 < coord2) && (vel1 < 0) && (vel2 > 0)) || ((coord2 < coord1) && (vel2 < 0) && (vel1 < 0)))){
			double vel_rel = std::abs(vel1 - vel2);
			double time_collision = std::abs(coord1 - coord2) / vel_rel;
			if (time_collision <= time_step){
				double new_vel1 = (2*vel2 + vel1*(k-1))/(k+1);
				double new_vel2 = (2*k*vel1 + vel2*(1-k))/(k+1);

				coord1 = coord1 + vel1*time_collision + new_vel1 * (time_step - time_collision);
				coord2 = coord2 + vel2*time_collision + new_vel1 * (time_step - time_collision);

				vel1 = new_vel1;
				vel2 = new_vel2;

				collision_exist = true;

			}
		}

		return collision_exist;
	}



	void check_wall(double &coord, double& vel){
		if (coord + vel*time_step > right_border){
			if (coord >= right_border) {
				coord = right_border;
				vel = -vel;
			} else {
				coord = coord + 2*(right_border - coord) - vel*time_step;
				vel = -vel;
			}
		}

		if (coord + vel*time_step < left_border){
			if (coord <= left_border) {
				coord = left_border;
				vel = -vel;
			} else {
				coord = coord + 2*(left_border - coord) - vel*time_step;
				vel = -vel;
			}
		}
	}

public:
	Gas(int m1, int m2, int k, bool flag_normal_distr, double stddev = 1.): amount_m1(m1), amount_m2(m2), k(k){

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distrib_coor(left_border, right_border);
		std::normal_distribution<> distrib_vel1(0., sqrt(k)*stddev);
		std::normal_distribution<> distrib_vel2(0., stddev);

		// auto coor = std::bind(distrib_coor, gen);
		std::generate_n(std::back_inserter(coordinates_1), amount_m1, [&distrib_coor, &gen](){return distrib_coor(gen);});
		std::generate_n(std::back_inserter(coordinates_2), amount_m2, [&distrib_coor, &gen](){return distrib_coor(gen);});

		auto vel1 = std::bind(distrib_vel1, gen);
		auto vel2 = std::bind(distrib_vel2, gen);
		std::generate_n(std::back_inserter(velocity_1), amount_m1, vel1);
		std::generate_n(std::back_inserter(velocity_2), amount_m2, vel2);
	}

	Gas(int m1, int m2, int k, double stddev = 1.): amount_m1(m1), amount_m2(m2), k(k){

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distrib_coor(left_border, right_border);

		std::generate_n(std::back_inserter(coordinates_1), amount_m1, [&distrib_coor, &gen](){return distrib_coor(gen);});
		std::generate_n(std::back_inserter(coordinates_2), amount_m2, [&distrib_coor, &gen](){return distrib_coor(gen);});

		std::generate_n(std::back_inserter(velocity_1), amount_m1, [](){return 1;});
		std::generate_n(std::back_inserter(velocity_2), amount_m2, [](){return 1;});

	}


	void next_step(){
		std::vector<bool> status_1(amount_m1, false);
		std::vector<bool> status_2(amount_m2, false);

		for (int first = 0; first < amount_m1; first++){
			for (int second = 0; second < amount_m2; second++){
				bool collision = collision_of_two(coordinates_1[first], velocity_1[first], 
													coordinates_2[second], velocity_2[second]);
				status_1[first] = collision;
				status_2[second] = collision;

			}
		}
		
		for (int i = 0; i < amount_m1; i++){
			if (!status_1[i]){
				coordinates_1[i] += velocity_1[i]*time_step; 
			}
			check_wall(coordinates_1[i], velocity_1[i]);
		}

		for (int i = 0; i < amount_m2; i++){
			if (!status_2[i]){
				coordinates_2[i] += velocity_2[i]*time_step; 
			}
			check_wall(coordinates_2[i], velocity_2[i]);
		}

	}


	const std::vector<double>& return_coordinates_1(){
		return std::cref(coordinates_1);
	}

	void run(double T, std::ostream& out){
		double time = 0;
		while (time < T){
			std::copy(coordinates_1.begin(), coordinates_1.end(), std::ostream_iterator<double>(out, " "));
			std::copy(coordinates_2.begin(), coordinates_2.end(), std::ostream_iterator<double>(out, " "));
			out << "\n";

			next_step();

			time += time_step;
		}
	}


	void run(double T, std::ostream& out, std::ofstream& out_for_vel1, std::ofstream& out_for_vel2, bool flag_vel = true){
		//if flag is true, all data of velocity will be written. if false, only first and last velocities.
		double time = 0;
		if (!flag_vel){
			std::copy(velocity_1.begin(), velocity_1.end(), std::ostream_iterator<double>(out_for_vel1, " "));
			std::copy(velocity_2.begin(), velocity_2.end(), std::ostream_iterator<double>(out_for_vel2, " "));
			out_for_vel1 << "\n";
			out_for_vel2 << "\n";
		}

		while (time < T){
			std::copy(coordinates_1.begin(), coordinates_1.end(), std::ostream_iterator<double>(out, " "));
			std::copy(coordinates_2.begin(), coordinates_2.end(), std::ostream_iterator<double>(out, " "));
			if (flag_vel){
				std::copy(velocity_1.begin(), velocity_1.end(), std::ostream_iterator<double>(out_for_vel1, " "));
				std::copy(velocity_2.begin(), velocity_2.end(), std::ostream_iterator<double>(out_for_vel2, " "));
				out_for_vel1 << "\n";
				out_for_vel2 << "\n";
			}
			out << "\n";

			next_step();

			time += time_step;
		}

		if (!flag_vel){
			std::copy(velocity_1.begin(), velocity_1.end(), std::ostream_iterator<double>(out_for_vel1, " "));
			std::copy(velocity_2.begin(), velocity_2.end(), std::ostream_iterator<double>(out_for_vel2, " "));
			out_for_vel1 << "\n";
			out_for_vel2 << "\n";
		}
	}

	void run(double T, std::ostream& out, std::ofstream& out_for_vel1, std::ofstream& out_for_vel2, std::ofstream& out_en, bool flag_vel = true){
		//if flag is true, all data of velocity will be written. if false, only first and last velocities.
		double time = 0;
		if (!flag_vel){
			std::copy(velocity_1.begin(), velocity_1.end(), std::ostream_iterator<double>(out_for_vel1, " "));
			std::copy(velocity_2.begin(), velocity_2.end(), std::ostream_iterator<double>(out_for_vel2, " "));
			out_for_vel1 << "\n";
			out_for_vel2 << "\n";
		}

		int number = 0;
		std::vector<double> energy = {velocity_1[number]*velocity_1[number]};

		while (time < T){
			std::copy(coordinates_1.begin(), coordinates_1.end(), std::ostream_iterator<double>(out, " "));
			std::copy(coordinates_2.begin(), coordinates_2.end(), std::ostream_iterator<double>(out, " "));
			if (flag_vel){
				std::copy(velocity_1.begin(), velocity_1.end(), std::ostream_iterator<double>(out_for_vel1, " "));
				std::copy(velocity_2.begin(), velocity_2.end(), std::ostream_iterator<double>(out_for_vel2, " "));
				out_for_vel1 << "\n";
				out_for_vel2 << "\n";
			}
			out << "\n";

			next_step();

			energy.push_back(velocity_1[number]*velocity_1[number]);
			out_en << time << " " << *std::prev(std::end(energy)) << "\n";


			time += time_step;
		}

		if (!flag_vel){
			std::copy(velocity_1.begin(), velocity_1.end(), std::ostream_iterator<double>(out_for_vel1, " "));
			std::copy(velocity_2.begin(), velocity_2.end(), std::ostream_iterator<double>(out_for_vel2, " "));
			out_for_vel1 << "\n";
			out_for_vel2 << "\n";
		}

	}

	~Gas(){};


};



int main(){

	Gas model_gas (300, 300, 5, 4.);

	std::ofstream vel1;
	std::ofstream vel2;
	std::ofstream energy;

	energy.open("Energy.txt");
	vel1.open("Vel1.txt");
	vel2.open("Vel2.txt");

	std::ofstream out;
	out.open("Data.txt");
	model_gas.run(100, out, vel1, vel2, energy, true);
	out.close();

	return 0;
}