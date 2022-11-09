#ifndef INTERPOLATOR_3D_H
#define INTERPOLATOR_3D_H

#include <vector>

typedef std::vector<std::vector<float>> Grid2D;
typedef std::vector<Grid2D> Grid3D;

class Interpolator3D {
public:
	Interpolator3D(
		std::vector<float> x, std::vector<float> y, std::vector<float> z, Grid3D data
	);
	std::vector<float> interp_swh(std::vector<float> speed, std::vector<float> tws, std::vector<float> twa);
private:
	float interp_single_point(float x, float y, float z);
	std::vector<float> m_x;
	std::vector<float> m_y;
	std::vector<float> m_z;
	Grid3D m_data;
};

#endif