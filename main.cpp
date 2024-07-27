#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double dotProduct(const vector<double>& a, const vector<double>& b) {
    double result = 0;
    for (size_t i = 0; i < a.size(); i++) {
        result += a[i] * b[i];
    }
    return result;
}

vector<double> subtractScaledVector(const vector<double>& a, const vector<double>& b, double scale) {
    vector<double> result(a.size());
    for (size_t i = 0; i < a.size(); i++) {
        result[i] = a[i] - b[i] * scale;
    }
    return result;
}

vector<double> normalize(const vector<double>& v) {
    double norm = sqrt(dotProduct(v, v));
    vector<double> result(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        result[i] = v[i] / norm;
    }
    return result;
}

vector<vector<double>> gramSchmidt(const vector<vector<double>>& vectors) {
    size_t n = vectors.size();
    vector<vector<double>> orthogonalizedVectors;

    for (size_t i = 0; i < n; i++) {
        vector<double> v = vectors[i];

        for (const auto & orthogonalizedVector : orthogonalizedVectors) {
            double projScale = dotProduct(vectors[i], orthogonalizedVector) / dotProduct(orthogonalizedVector, orthogonalizedVector);
            v = subtractScaledVector(v, orthogonalizedVector, projScale);
        }

        orthogonalizedVectors.push_back(v);
    }

    for (auto & orthogonalizedVector : orthogonalizedVectors) {
        orthogonalizedVector = normalize(orthogonalizedVector);
    }

    return orthogonalizedVectors;

}

[[maybe_unused]] bool verifyBase(const vector<vector<double>>& vectors) {
    size_t length = vectors[0].size();
    for (const auto & vector : vectors) {
        if (vector.size() != length) {
            return false;
        }
    }
}

int main() {
//    vector<vector<double>> vectors = {
//            {1, 0, 0},
//            {0, 1, 0},
//            {0, 0, 1},
//    };

    vector<vector<double>> vectors = {
            {0, 2, 0},
            {4, -1, -3},
            {3, 2, 4},
    };

    vector<vector<double>> orthogonalizedVectors = gramSchmidt(vectors);

    for (const auto& vec : orthogonalizedVectors) {
        for (double val : vec) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
