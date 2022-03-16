#include <iostream>
#include <random>
#include <fstream>
#include <functional>


class triangle{
	private:
		double left;
		double right;
		double height;
		double middle;

	public:

		triangle(double l, double r): left(l), right(r){
			height = 2 / (right - left);
			middle = (left + right) / 2;
		};

		triangle(): triangle(0., 2.){};

		double distribution (double x){
			double res = 0;
			if (x <= middle){
				res = 2 * height*(x - left) / (left + right);
			} else {
				res = -2 * height * (x - right) / (left + right);
			}		
			return res;
		}
};

template <typename A>
class Density_distrubution{
	private:
		A type_dist;

	public:
		Density_distrubution(A type_dist): type_dist(type_dist){};

		double equation(double x){
			return type_dist.distribution(x);
		}
};


int main(){
	int N = 10000;
	double a = 0.;
	double b = 2.;

	std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> distrib(a, b);

    std::ofstream out;
	out.open("./number_6.txt");

	triangle Triangle(a, b);
	Density_distrubution<triangle> density(Triangle);

    for (int i = 0; i < N; i++){
    	bool flag = false; //the flag is true if number was found.

    	while (!flag){
    		double y = distrib(gen);
    		double x = distrib(gen);

    		if (density.equation(x) > y){
    			flag = true;
    			out << x << ' ';
    		}
    	}
    }

    out.close();



    return 0;

}
