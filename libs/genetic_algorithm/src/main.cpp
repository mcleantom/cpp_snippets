#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include <algorithm>
#include <string>

struct Solution
{
	Solution(double x, double y, double z) : x(x), y(y), z(z) {
		fitness();
	};
	double rank, x, y, z;
	void fitness()
	{
		double ans = (6 * x + -y + std::pow(z, 200)) - 25;
		rank  = (ans == 0) ? 9999 : std::abs(1 / ans);
	}
};

int main()
{
	// Create initial random solutions
	std::random_device device;
	std::uniform_real_distribution<double> unif(-100, 100);
	std::vector<Solution>  solutions;

	const int NUM = 100000;
	for (size_t i = 0; i < NUM; ++i) {
		solutions.push_back(Solution{
			unif(device),
			unif(device),
			unif(device)
		});
	}

	while (true) {
		// Sort out solutions by rank

		std::sort(solutions.begin(), solutions.end(), [](const Solution& lhs, const Solution& rhs) {
			return (lhs.rank > rhs.rank);
			});


		std::for_each(
			solutions.begin(),
			solutions.begin() + 1,
			[](const Solution& s) {
				std::cout << std::fixed
					<< "Rank: " << static_cast<int>(s.rank)
					<< "\n x:" << s.x << " y:" << s.y << " z:" << s.z
					<< "\n";
			}
		);

		// Take top K solutions
		const int SAMPLE_SIZE = 1000;
		std::vector<Solution> sample;
		std::copy(
			solutions.begin(),
			solutions.begin() + SAMPLE_SIZE,
			std::back_inserter(sample)
		);
		solutions.clear();

		// Mutate top solutions by %
		std::uniform_real_distribution<double> m(0.99, 1.01);
		std::for_each(
			sample.begin(),
			sample.end(),
			[&](auto& s) {
				s.x *= m(device);
				s.y *= m(device);
				s.z *= m(device);
			}
		);

		// Cross over
		// Interchanging values from different solutions
		std::uniform_int_distribution<int> cross(0, SAMPLE_SIZE - 1);
		for (size_t i = 0; i < NUM; ++i) {
			solutions.push_back(Solution{
					sample[cross(device)].x,
					sample[cross(device)].y,
					sample[cross(device)].z
				}
			);
		}
	}
};