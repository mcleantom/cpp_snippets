#include <vector>
#include <mutex>
#include <thread>
#include <iostream>
#include <shared_mutex>


template<class T>
class ThreadVector {
public:
	ThreadVector() {};
	ThreadVector(int n) : v(n) {};
	void push_back(T x) {
		std::unique_lock<std::shared_mutex> lock(mutex_);
		v.push_back(x);
	}
	size_t size() {
		std::unique_lock<std::shared_mutex> lock(mutex_);
		return this->v.size();
	}
	void set(int i, T x) {
		std::unique_lock<std::shared_mutex> lock(mutex_);
		v[i] = x;
	}
	T get(int i) {
		std::shared_lock<std::shared_mutex> lock(mutex_);
		return v[i];
	}
	auto begin() {
		return v.begin();
	}
private:
	std::vector<T> v;
	mutable std::shared_mutex mutex_;
};

void push_to_vector(ThreadVector<int>* v, int start, int end) {
	for (auto i = start; i < end; i++) {
		v->set(i, i);
	}
}


int main() {
	int v_size = 10;
	ThreadVector<int> v(v_size);
	std::thread t1(push_to_vector, &v, 0, v_size / 2);
	std::thread t2(push_to_vector, &v, (v_size/2), v_size);
	t1.join();
	t2.join();
	for (int i = 0; i < v_size; i++) {
		std::cout << v.get(i);
	}
	return 0;
}