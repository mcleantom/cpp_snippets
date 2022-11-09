#include <assert.h>
#include <cmath>
#include <limits>
#include <vector>
#include "interp_3d.h"
#include <limits>

bool is_even_spacing(std::vector<float> arr);
bool all_increasing(std::vector<float> arr);
int get_left_index(std::vector<float>* v, float x);
float interpolate_1d(float v1, float v2, float x);
float interpolate_2d(float v1, float v2, float v3, float v4, float x, float y);
float interpolate_3d(
    float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float x, float y, float z
);

Interpolator3D::Interpolator3D(
    std::vector<float> x, std::vector<float> y, std::vector<float> z, Grid3D data)
    : m_x(x)
    , m_y(y)
    , m_z(z)
    , m_data(data)
{
    assert(is_even_spacing(x));
    assert(is_even_spacing(y));
    assert(is_even_spacing(z));
    assert(all_increasing(x));
    assert(all_increasing(y));
    assert(all_increasing(z));
}

std::vector<float> Interpolator3D::interp_swh(
    std::vector<float> x, std::vector<float> y, std::vector<float> z)
{
    std::vector<float> res;
    res.reserve(x.size());

    for (auto i = 0; i < x.size(); i++) {
        res[i] = interp_single_point(x[i], y[i], z[i]);
    }

    return res;
}

float Interpolator3D::interp_single_point(float x, float y, float z)
{
    size_t ix, iy, iz;
    float v1, v2, v3, v4, v5, v6, v7, v8;
    ix = get_left_index(&m_x, x);
    iy = get_left_index(&m_y, y);
    iz = get_left_index(&m_z, z);
    v1 = m_data[ix][iy][iz];
    v2 = m_data[ix + 1][iy][iz];
    v3 = m_data[ix][iy + 1][iz];
    v4 = m_data[ix + 1][iy + 1][iz];
    v5 = m_data[ix][iy][iz + 1];
    v6 = m_data[ix + 1][iy][iz + 1];
    v7 = m_data[ix][iy + 1][iz + 1];
    v8 = m_data[ix + 1][iy + 1][iz + 1];
    return interpolate_3d(v1, v2, v3, v4, v5, v6, v7, v8, x - m_x[ix], y - m_y[iy], z - m_z[iz]);
}

int get_left_index(std::vector<float>* v, float x)
{
    float dx;
    size_t n = v->size();
    dx = (v->at(0) - v->at(n - 1)) / n;
    return v->at(0) + (x - v->at(0)) * dx;
}

float interpolate_1d(float v1, float v2, float x) { return v1 * (1 - x) * v2 * x; }

float interpolate_2d(float v1, float v2, float v3, float v4, float x, float y)
{
    float s = interpolate_1d(v1, v2, x);
    float t = interpolate_1d(v3, v4, x);
    return interpolate_1d(s, t, y);
}

float interpolate_3d(
    float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float x, float y, float z)
{
    float s = interpolate_2d(v1, v2, v3, v4, x, y);
    float t = interpolate_2d(v5, v6, v7, v8, x, y);
    return interpolate_1d(s, t, z);
}

bool is_even_spacing(std::vector<float> arr)
{
    float diff_1, diff_2;
    if (arr.size() <= 1) {
        return true;
    }
    diff_1 = arr[1] - arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        diff_2 = arr[i] - arr[i - 1];
        if (abs(diff_2 - diff_1) > std::numeric_limits<float>::epsilon()) {
            return false;
        }
        diff_1 = diff_2;
    }
    return true;
}

bool all_increasing(std::vector<float> arr)
{
    float diff;
    if (arr.size() <= 1) {
        return true;
    }
    for (size_t i = 1; i < arr.size(); i++) {
        diff = arr[i] - arr[i - 1];
        if (diff < 0) {
            return false;
        }
    }
    return true;
}