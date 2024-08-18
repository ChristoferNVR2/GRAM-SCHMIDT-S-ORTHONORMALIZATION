#include <iostream>
#include <vector>
#include <cmath>

#ifdef __unix__
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

void mySleep(int sleepMs)
{
#ifdef __unix__
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef WINDOWS
    Sleep(sleepMs);
#endif
}

void clearScreen() {
#ifdef __unix__
    system("clear");
#endif
#ifdef WINDOWS
    system("cls");
#endif
}

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

/*
Las subopciones son
Combinacion lineal
Producto escalar
Angulo entre ellos
Proyeccion de un vector sobre otro
Determinar si son parallelos, ortogonales o ninguno
 */
void menu_1() {
    clearScreen();

    // Pedir la dimension de los vectores
    int n;
    cout << "INGRESE LA DIMENSION DE LOS VECTORES (n):";
    cin >> n;

    // Pedir los valores de los vectores
    vector<vector<double>> vectors(2, vector<double>(n));
    for (int i = 0; i < 2; i++) {
        cout << "INGRESE EL VECTOR " << i + 1 << ":";

        for (int j = 0; j < n; j++) {
            cout << "   VALOR " << j + 1 << ":";
            cin >> vectors[i][j];
        }
    }

    // Mostrar los vectores
    cout << "VECTORES INGRESADOS" << endl;
    for (const auto& vec : vectors) {
        cout << "   ";
        for (double val : vec) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Submenu
    int option;
    while (true) {
        cout << "SUBMENU" << endl;
        cout << "1. COMBINACION LINEAL" << endl;
        cout << "2. PRODUCTO ESCALAR" << endl;
        cout << "3. ANGULO ENTRE VECTORES" << endl;
        cout << "4. PROYECCION DE UN VECTOR SOBRE OTRO" << endl;
        cout << "5. DETERMINAR SI SON PARALELOS, ORTOGONALES O NINGUNO" << endl;
        cout << "6. SALIR" << endl;
        cout << "INGRESE UNA OPCION:";

        cin >> option;

        switch (option) {
            case 1:
                cout << "1. COMBINACION LINEAL" << endl;
                {
                    cout << "INGRESE LOS COEFICIENTES DE LA COMBINACION LINEAL" << endl;
                    vector<double> coefficients(n);
                    for (int i = 0; i < n; i++) {
                        cout << "   COEFICIENTE " << i + 1 << ":";
                        cin >> coefficients[i];
                    }

                    vector<double> result(n);
                    for (int i = 0; i < n; i++) {
                        result[i] = vectors[0][i] * coefficients[0] + vectors[1][i] * coefficients[1];
                    }

                    cout << "RESULTADO DE LA COMBINACION LINEAL" << endl;
                    cout << "   ";
                    for (double val : result) {
                        cout << val << " ";
                    }
                    cout << endl;
                }
                break;
            case 2:
                cout << "2. PRODUCTO ESCALAR" << endl;
                {
                    double result = dotProduct(vectors[0], vectors[1]);
                    cout << "PRODUCTO ESCALAR: " << result << endl;
                }
                break;
            case 3:
                cout << "3. ANGULO ENTRE VECTORES" << endl;
                {
                    double dot = dotProduct(vectors[0], vectors[1]);
                    double norm1 = sqrt(dotProduct(vectors[0], vectors[0]));
                    double norm2 = sqrt(dotProduct(vectors[1], vectors[1]));
                    double angle = acos(dot / (norm1 * norm2));
                    cout << "ANGULO ENTRE VECTORES: " << angle << " rad" << endl;

                    double angleDegrees = angle * 180 / M_PI;

                    cout << "ANGULO ENTRE VECTORES: " << angleDegrees << "°" << endl;
                }
                break;
            case 4:
                cout << "4. PROYECCION DE UN VECTOR SOBRE OTRO" << endl;
                {
                    double dot = dotProduct(vectors[0], vectors[1]);
                    double norm2 = sqrt(dotProduct(vectors[1], vectors[1]));
                    vector<double> projection(n);
                    for (int i = 0; i < n; i++) {
                        projection[i] = (dot / (norm2 * norm2)) * vectors[1][i];
                    }

                    cout << "PROYECCION DE UN VECTOR SOBRE OTRO" << endl;
                    cout << "   ";
                    for (double val : projection) {
                        cout << val << " ";
                    }
                    cout << endl;
                }
                break;
            case 5:
                cout << "5. DETERMINAR SI SON PARALELOS, ORTOGONALES O NINGUNO" << endl;
                {
                    double dot = dotProduct(vectors[0], vectors[1]);
                    double norm1 = sqrt(dotProduct(vectors[0], vectors[0]));
                    double norm2 = sqrt(dotProduct(vectors[1], vectors[1]));

                    if (dot == 0) {
                        cout << "LOS VECTORES SON ORTOGONALES" << endl;
                    } else if (dot == norm1 * norm2) {
                        cout << "LOS VECTORES SON PARALELOS" << endl;
                    } else {
                        cout << "LOS VECTORES NO SON PARALELOS NI ORTOGONALES" << endl;
                    }
                }
                break;
            case 6:
                cout << "SALIENDO..." << endl;
                return;
            default:
                cout << "OPCION NO VALIDA" << endl;
                break;
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
                menu_1();
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

                    mySleep(1000);
                    for (const auto& vec : vectors) {
                        cout << "   ";
                        for (double val : vec) {
                            cout << val << " ";
                        }
                        cout << endl;
                    }

                    mySleep(1000);
                    vector<vector<double>> orthogonalizedVectors = gramSchmidt(vectors);
                    cout << "   VECTORES ORTOGONALIZADOS" << endl;

                    mySleep(1000);
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

                    mySleep(1000);
                    vector<vector<double>> normalizedVectors = normalizeVectors(orthogonalizedVectors);
                    cout << "   VECTORES ORTONORMALIZADOS" << endl;

                    mySleep(1000);
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
