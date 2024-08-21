#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


double dotProduct(const vector<double>& a, const vector<double>& b) {
    double result = 0;
    for (size_t i = 0; i < a.size(); i++) {
        result += a[i] * b[i];
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

pair<vector<double>, vector<vector<double>>> calculateEigen(double A, double B, double C) {
    vector<double> eigenvalues;
    vector<vector<double>> eigenvectors;

    double trace = A + C;
    double determinant = A * C - (B / 2) * (B / 2);
    double discriminant = sqrt(trace * trace - 4 * determinant);

    double lambda1 = (trace + discriminant) / 2;
    double lambda2 = (trace - discriminant) / 2;

    eigenvalues.push_back(lambda1);
    eigenvalues.push_back(lambda2);

    for (auto & lambda : eigenvalues) {
        vector<double> eigenvector(2);
        if (B != 0) {
            eigenvector[0] = lambda - C;
            eigenvector[1] = B / 2;
        } else {
            eigenvector[0] = 1;
            eigenvector[1] = 0;
        }
        eigenvectors.push_back(normalize(eigenvector));
    }

    return {eigenvalues, eigenvectors};
}



void calculateEigenvectors(float a, float b, float c, float lambda, float& v1x, float& v1y) {
    if (b != 0) {
        v1x = lambda - c;
        v1y = b;
    } else {
        v1x = 1;
        v1y = 0;
    }

    // Normalizar el autovector
    float norm = sqrt(v1x * v1x + v1y * v1y);
    v1x /= norm;
    v1y /= norm;
}

void typeConic(float A, float B, float C) {
    float discriminant = (B * B) - (4 * A * C);
    if (discriminant == 0)
        cout << "The quadratic form is parabolic." << endl;
    else if (discriminant < 0)
        cout << "The quadratic form is hyperbolic." << endl;
    else if (discriminant > 0)
        cout << "The quadratic form is elliptical." << endl;
}

void calculateAsymptotes(float A_new, float C_new, float x0, float y0) {
    if (A_new * C_new < 0) {
        float slope1 = sqrt(fabs(C_new / A_new));
        float slope2 = -sqrt(fabs(C_new / A_new));

        cout << slope1 << endl;
        cout << slope2 << endl;
    } else {
        cout << "No asymptotes for this conic section." << endl;
    }
}

void calculateCenterFociVertices(float A_new, float C_new, float D_new, float E_new, float F_new, float x0, float y0, const string& type) {
    if (type == "ellipse") {
        cout << "Center: (" << x0 << ", " << y0 << ")" << endl;

        float a = 1 / sqrt(fabs(A_new));
        float b = 1 / sqrt(fabs(C_new));
        float c = sqrt(fabs(a * a - b * b));

        cout << "Focus 1: (" << x0 + c << ", " << y0 << ")" << endl;
        cout << "Focus 2: (" << x0 - c << ", " << y0 << ")" << endl;
        cout << "Vertex 1: (" << x0 + a << ", " << y0 << ")" << endl;
        cout << "Vertex 2: (" << x0 - a << ", " << y0 << ")" << endl;
        cout << "Directrix 1: x = " << x0 + (a / sqrt(A_new)) << endl;
        cout << "Directrix 2: x = " << x0 - (a / sqrt(A_new)) << endl;
    } else if (type == "hyperbola") {
        cout << "Center: (" << x0 << ", " << y0 << ")" << endl;

        float a = 1 / sqrt(fabs(A_new));
        float b = 1 / sqrt(fabs(C_new));
        float c = sqrt(fabs(a * a + b * b));

        cout << "Focus 1: (" << x0 + c << ", " << y0 << ")" << endl;
        cout << "Focus 2: (" << x0 - c << ", " << y0 << ")" << endl;
        cout << "Vertex 1: (" << x0 + a << ", " << y0 << ")" << endl;
        cout << "Vertex 2: (" << x0 - a << ", " << y0 << ")" << endl;

        calculateAsymptotes(A_new, C_new, x0, y0);
    } else if (type == "parabola") {
        cout << "Vertex: (" << x0 << ", " << y0 << ")" << endl;
        float p = 1 / (4 * fabs(A_new));
        cout << "Focus: (" << x0 << ", " << y0 + p << ")" << endl;
        cout << "Directrix: y = " << y0 - p << endl;
    }
}

void conicTransform(float A, float B, float C, float D, float E, float F) {
    float lambda1, lambda2;
//    calculateEigenvalues(A, B / 2, C, lambda1, lambda2);

    float v1x, v1y, v2x, v2y;
    calculateEigenvectors(A, B / 2, C, lambda1, v1x, v1y);
    calculateEigenvectors(A, B / 2, C, lambda2, v2x, v2y);

    float theta = atan2(v1y, v1x); // Angulo de rotación
    float theta_degrees = theta * 180.0 / M_PI;

    float x0 = (2 * C * D - B * E) / (B * B - 4 * A * C);
    float y0 = (2 * A * E - B * D) / (B * B - 4 * A * C);

    float cos_theta = cos(theta);
    float sin_theta = sin(theta);
    float A_new = A * cos_theta * cos_theta + B * cos_theta * sin_theta + C * sin_theta * sin_theta;
    float B_new = 0;
    float C_new = A * sin_theta * sin_theta - B * cos_theta * sin_theta + C * cos_theta * cos_theta;
    float D_new = D * cos_theta + E * sin_theta;
    float E_new = -D * sin_theta + E * cos_theta;
    float F_new = F;

    cout << "Autovalor 1: " << lambda1 << endl;
    cout << "Autovector 1: (" << v1x << ", " << v1y << ")" << endl;
    cout << "Autovalor 2: " << lambda2 << endl;
    cout << "Autovector 2: (" << v2x << ", " << v2y << ")" << endl;
    cout << "Angulo de rotacion (grados): " << theta_degrees << endl;
    cout << "Traslacion: (" << x0 << ", " << y0 << ")" << endl;
    cout << "Nueva ecuacion conica: " << A_new << "x^2 + " << B_new << "xy + " << C_new << "y^2 + " << D_new << "x + " << E_new << "y + " << F_new << " = 0" << endl;

    string type;
    float discriminant = (B * B) - (4 * A * C);
    if (discriminant == 0)
        type = "parabola";
    else if (discriminant < 0)
        type = "hyperbola";
    else if (discriminant > 0)
        type = "ellipse";

    calculateCenterFociVertices(A_new, C_new, D_new, E_new, F_new, x0, y0, type);
}
