#include <stdexcept>
#include <vector>
#include <cmath>

const int POWERS_OF_TWO[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

bool isPowerOfTwo(int n) {
    for (int i = 0; i < 14; i++) {
        if (n == POWERS_OF_TWO[i]) {
            return true;
        }
    }
    return false;
}

void DFT(std::vector<double>& x, int N) {
    for (int k = 0; k < N; k++) {
        double sum = 0;
        for (int n = 0; n < N; n++) {
            double angle = 2 * M_PI * n * k / N;
            sum += x[n] * std::cos(angle) + x[n] * std::sin(angle);
        }
        x[k] = sum;
    }
}

void IDFT(std::vector<double>& x, int N) {
    for (int k = 0; k < N; k++) {
        double sum = 0;
        for (int n = 0; n < N; n++) {
            double angle = 2 * M_PI * n * k / N;
            sum += x[n] * std::cos(angle) + x[n] * std::sin(angle);
        }
        x[k] = sum / N;
    }
}

std::vector<double> LossyCompress(std::vector<double> data, int new_size) {
    int N = data.size();
    if (!isPowerOfTwo(N)) {
        throw std::range_error("Data size must be a power of two");
    }
    if (new_size <= 0 || new_size > N) {
        throw std::range_error("Bad new size");
    }
    DFT(data, N);
    data.resize(new_size);
    data.push_back(N);
    return data;
}

std::vector<double> LossyDecompress(std::vector<double> compressed) {
    int N = compressed.back();
    compressed.pop_back();
    if (!isPowerOfTwo(N) || N < compressed.size()) {
        throw std::logic_error("Bad compressed sequence");
    }
    compressed.resize(N, 0);
    IDFT(compressed, N);
    return compressed;
}

int main() {
    return 0;
}