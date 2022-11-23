#include <vector>
#include <thread>
#include <iostream>

class Test {
    public:
        Test() {};
        std::vector<float> getData(std::vector<size_t> &indexes) {
            int threadCount = 30;
            std::vector<float> res(indexes.size());
            std::thread threads[threadCount];
            for (size_t i=0; i<threadCount; ++i) {
                threads[i] = std::thread(&Test::setRes, this, i, (i+1), std::ref(indexes), std::ref(res));
            }
            for (size_t i=0; i<threadCount; ++i) {
                threads[i].join();
            }
            return res;
        };
    private:
        void setRes(size_t start, size_t end, std::vector<size_t> &indexes, std::vector<float> &res) {
            for (size_t i = start; i<end; ++i) {
                res[i] = data[indexes[i]];
            }
        };
        std::vector<float> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
};

int main()
{
    Test t;
    std::vector<size_t> indexes(1000, 0);
    auto res = t.getData(indexes);
    for (auto x : res) {
        std::cout << x << std::endl;
    }
}
