#include <iostream>
#include <vector>
#include <cmath>
#include <synchapi.h>

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

//    for (auto & orthogonalizedVector : orthogonalizedVectors) {
//        orthogonalizedVector = normalize(orthogonalizedVector);
//    }

    return orthogonalizedVectors;
}

vector<vector<double>> normalizeVectors(const vector<vector<double>>& vectors) {
    vector<vector<double>> normalizedVectors;
    for (const auto & vector : vectors) {
        normalizedVectors.push_back(normalize(vector));
    }
    return normalizedVectors;
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

    int option;

    while (true) {
        cout << "MENU" << endl;
        cout << "1. OPERACIONES CON DOS VECTORES EN Rn" << endl;
        cout << "2. ORTGONALIZAR Y NORMALIZAR VECTORES" << endl;
        cout << "3. AUTOVALORES Y AUTOVECTORES" << endl;
        cout << "4. FORMAS CUADRATICAS" << endl;
        cout << "INGRESE UNA OPCION:";

        cin >> option;


        switch (option) {
            case 1:
                cout << "1. OPERACIONES CON DOS VECTORES EN Rn" << endl;
                break;
            case 2:
                cout << "2. ORTGONALIZAR Y NORMALIZAR VECTORES" << endl;
                cout << "   INGRESE EL NUMERO DE VECTORES (n):";
                int n;
                cin >> n;
                cout << "   TENGA EN CUENTA QUE EL CONJUNTO DE n VECTORES DEBE SER BASE DE Rn" << endl;
                {
                    vector<vector<double>> vectors(n, vector<double>(n));
                    for (int i = 0; i < n; i++) {
                        cout << "   INGRESE EL VECTOR " << i + 1 << ":";
                        for (int j = 0; j < n; j++) {
                            cin >> vectors[i][j];
                        }
                    }

                    cout << "   VECTORES SIN ORTOGONALIZAR NI NORMALIZAR" << endl;

                    Sleep(1000);
                    for (const auto& vec : vectors) {
                        cout << "   ";
                        for (double val : vec) {
                            cout << val << " ";
                        }
                        cout << endl;
                    }

                    Sleep(1000);
                    vector<vector<double>> orthogonalizedVectors = gramSchmidt(vectors);
                    cout << "   VECTORES ORTOGONALIZADOS" << endl;

                    Sleep(1000);
                    for (const auto& vec : orthogonalizedVectors) {
                        cout << "   ";
                        for (double val : vec) {
                            if (val <= 0.000001) {
                                val = 0;
                            }
                            cout << val << " ";
                        }
                        cout << endl;
                    }

                    Sleep(1000);
                    vector<vector<double>> normalizedVectors = normalizeVectors(orthogonalizedVectors);
                    cout << "   VECTORES ORTONORMALIZADOS" << endl;

                    Sleep(1000);
                    for (const auto& vec : normalizedVectors) {
                        cout << "   ";
                        for (double val : vec) {
                            if (val <= 0.000001) {
                                val = 0;
                            }
                            cout << val << " ";
                        }
                        cout << endl;
                    }
                }
                break;
            case 3:
                cout << "3. AUTOVALORES Y AUTOVECTORES" << endl;
                break;
            case 4:
                cout << "4. FORMAS CUADRATICAS" << endl;
                break;
            case 5:
                cout << "SALIENDO..." << endl;
                return 0;
            default:
                cout << "OPCION NO VALIDA" << endl;
                break;
        }

    }
}
