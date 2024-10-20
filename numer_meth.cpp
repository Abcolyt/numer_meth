



#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <utility> 
#include <array>
#include<chrono>
#include <stdio.h> 
#include <time.h> 

double example_function(double x) {
	return x * x - 2;
}

double f1(double x) {
	return ((1 + cos(x)) * (3 - sin(x)) - x);
}

double f14(double x) //for simple iteretion meetod 
{
	//was 

	return sin(exp(-x * x)) * (1 + x * x) * (1 / 2);
}

double first_derivative_function(double(*func)(double), long double x0)
{
	return (func(x0 + 100 * LDBL_EPSILON) - func(x0)) / (100 * LDBL_EPSILON);
}

double second_derivative_function(double(*func)(double), long double x0)
{
	long double loceps = 0.5;

	return (-func(x0 + 2 * (loceps)) + 16 * func(x0 + (loceps)) - 30 * func(x0) + 16 * func(x0 - loceps) - func(x0 - 2 * loceps) / (12 * loceps * loceps));
}

std::pair<double, int> solve_tangents(double(*f)(double), double b, double e) {
	int iterations = 0;
	long double x_old = 0.1, x_new = b;
	while (std::abs(x_new - x_old) > e) {
		x_old = x_new;
		x_new = x_old - (f(x_old) / first_derivative_function(f, x_old));

		iterations++;

	}

	return { x_new, iterations };
}

std::pair<double, int> solve_tangents_simpled(double(*f)(double), double b, double e) {
	int iterations = 0;
	long double x_old = 0.1, x_new = b;
	const long double f_ = first_derivative_function(f, x_old);
	while (std::abs(x_new - x_old) > e) {
		x_old = x_new;
		x_new = x_old - (f(x_old) / f_);

		iterations++;

	}

	return { x_new, iterations };
}

std::pair<double, int> solve_2division(double(*f)(double), double leftborder, double rightborder, double e)
{
	if ((f(leftborder)) * (f(rightborder)) >= 0) {
		return { NAN, 0 };
	}

	int iterations = 0;

	while (((rightborder - leftborder) / 2) > e) {
		double c = (leftborder + rightborder) / 2;
		iterations++;
		if (f(c) == 0) {
			return { c, iterations };
		}
		else if (f(c) * f(leftborder) < 0) {
			rightborder = c;
		}
		else {
			leftborder = c;
		}
	}

	return { (leftborder + rightborder) / 2, iterations };
}

std::pair<double, int> solve_chord(double(*f)(double), double x_new, double x_old, double e)
{
	if ((f(x_new)) * (f(x_old)) >= 0) {
		return { NAN, 0 };
	}

	int iterations = 0;

	while (abs((x_old - x_new)) > e) {
		x_new = x_old - (x_old - x_new) * f(x_new) / (f(x_old) - f(x_new));
	}

	return { (x_new + x_old) / 2, iterations };
}//

std::pair<double, int> solve_chord_lar(double(*f)(double), double leftborder, double rightborder, double e)
{
	if ((f(leftborder)) * (f(rightborder)) >= 0) {
		return { NAN, 0 };
	}

	int iterations = 0;

	while (abs((rightborder - leftborder)) > e) {
		leftborder = leftborder - (rightborder - leftborder) * f(leftborder) / (f(rightborder) - f(leftborder));
		rightborder = rightborder - (leftborder - rightborder) * f(rightborder) / (f(leftborder) - f(rightborder));
	}

	return { (leftborder + rightborder) / 2, iterations };
}


#define SOLVE_AND_PRINT(func,except_name , ...) \
	std::cout << "name_function:"<<#func << "\n " ; \
	try { \
		clock_t start_r = clock();\
		auto begin_pr = std::chrono::steady_clock::now();\
\
		auto result = func(__VA_ARGS__); \
\
		clock_t end_r = clock(); \
\
		auto end_pr = std::chrono::steady_clock::now();\
\
\
		std::ios_base::fmtflags fs(std::cout.flags()); \
		std::streamsize prec(std::cout.precision()); \
		std::cout << std::fixed << std::setprecision(64); \
		std::cout << "time in real of work:" << (double)(end_r - start_r)<< "\n"; \
		std::cout << "The time (hight presision): " << std::chrono::duration_cast<std::chrono::milliseconds>(end_pr - begin_pr).count() << " ms\n";\
		if (!(0)) {  \
			std::cout << "root:\n " << result.first << "\n" \
					  << "The value of the function is at the root:\n " << f1(result.first) << "\n" \
					  << "Number of iterations: \n" << result.second << "\n";} \
		std::cout.flags(fs); \
		std::cout.precision(prec); \
		std::cout << "\n\n\n\n";} \
		catch (const std::exception& e) { \
		std::cerr << "Er:" << #except_name << "what():" << e.what(); \
	}


int main() {

	SOLVE_AND_PRINT(solve_2division, 1, f1, -LDBL_MAX, LDBL_MAX, LDBL_EPSILON)
		    /*std::cout << "solve_2division " << "\n\n\n\n";
		    try {
		        auto result = solve_2division(f1, -LDBL_MAX, LDBL_MAX, LDBL_EPSILON);

		        std::ios_base::fmtflags fs(std::cout.flags());
		        std::streamsize prec(std::cout.precision());

		        if (!(0)) {
		            std::cout << std::fixed << std::setprecision(64);
		            std::cout << "root: " << result.first << "\n";
		            std::cout << "The value of the function is at the root: " << f1(result.first) << "\n";
		            std::cout << "Number of iterations: " << result.second << "\n";
		        }

		        std::cout.flags(fs);
		        std::cout.precision(prec);
		    }
		    catch (const std::exception& e) {
		        std::cerr << "Ошибка: 1" << e.what() << std::endl;
		    }*/
	SOLVE_AND_PRINT(solve_tangents, 2, f1, 1, LDBL_EPSILON)
		    /*std::cout << "solve_tangents " << "\n\n\n\n";

		    try {
		        auto result = solve_tangents(f1, 1, LDBL_EPSILON);

		        std::ios_base::fmtflags fs(std::cout.flags());
		        std::streamsize prec(std::cout.precision());

		        if (!(0)) {
		            std::cout << std::fixed << std::setprecision(64);
		            std::cout << "root: " << result.first << "\n";
		            std::cout << "The value of the function is at the root: " << f1(result.first) << "\n";
		            std::cout << "Number of iterations: " << result.second << "\n";
		        }

		        std::cout.flags(fs);
		        std::cout.precision(prec);
		    }
		    catch (const std::exception& e) {
		        std::cerr << "Ошибка: 2" << e.what() << std::endl;
		    }
		*/
	SOLVE_AND_PRINT(solve_tangents_simpled, 3, f1, 1, LDBL_EPSILON)
		    /*std::cout << "solve_tangents_simpled " << "\n\n\n\n";
		    try {
		        auto result = solve_tangents_simpled(f1, 1, LDBL_EPSILON);

		        std::ios_base::fmtflags fs(std::cout.flags());
		        std::streamsize prec(std::cout.precision());

		        if (!(0)) {
		            std::cout << std::fixed << std::setprecision(64);
		            std::cout << "root: " << result.first << "\n";
		            std::cout << "The value of the function is at the root: " << f1(result.first) << "\n";
		            std::cout << "Number of iterations: " << result.second << "\n";
		        }

		        std::cout.flags(fs);
		        std::cout.precision(prec);
		    }
		    catch (const std::exception& e) {
		        std::cerr << "Ошибка:3 " << e.what() << std::endl;
		    }*/
	SOLVE_AND_PRINT(solve_chord_lar, 4, f1, -100, 100, LDBL_EPSILON)


		//std::cout << "solve_chord_lar " << "\n\n\n\n";
		//try {
		//    auto result = solve_chord_lar(f1, -100, 100, LDBL_EPSILON);
		//    std::ios_base::fmtflags fs(std::cout.flags());
		//    std::streamsize prec(std::cout.precision());
		//    if (!(0)) {
		//        std::cout << std::fixed << std::setprecision(64);
		//        std::cout << "root: " << result.first << "\n";
		//        std::cout << "The value of the function is at the root: " << f1(result.first) << "\n";
		//        std::cout << "Number of iterations: " << result.second << "\n";
		//    }
		//    std::cout.flags(fs);
		//    std::cout.precision(prec);
		//}
		//catch (const std::exception& e) {
		//    std::cerr << "Ошибка:4" << e.what() << std::endl;
		//}

		//SOLVE_AND_PRINT(, 4, f1, -100, 100, LDBL_EPSILON)

		std::cout << "beta " << "\n\n\n\n";
	try {
		auto result = second_derivative_function(f1, 0.124);

		std::ios_base::fmtflags fs(std::cout.flags());
		std::streamsize prec(std::cout.precision());

		std::cout << std::fixed << std::setprecision(64);
		std::cout << "res      :" << result << "\n";

		std::cout.flags(fs);
		std::cout.precision(prec);
	}
	catch (const std::exception& e) {
		std::cerr << "Ошибка:4" << e.what() << std::endl;
	}




	system("pause");
	return 0;
}