#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

struct conica{
    double A, B, C, D, E, F, pi=3.141593;
};

//Verifica que tipo de conica es la forma cuadratica
string TipoDeConica (conica &conica){
    float discriminante=conica.B*conica.B -4 *conica.A * conica.C;
    if(conica.A==conica.C && conica.B==0){

        return "circunferencia";

    } else if(discriminante>0){

        return "hiperbola";

    } else if(discriminante==0){

        return "parabola";

    } else{

        return "elipse";

    }

}
//forma la forma cuadradica de la conica y la imprime en pantalla
void generarConica(conica &conica){


    cout<<"digite la constante A: ";
    cin>>conica.A;

    cout<<"digite la constante B: ";
    cin>>conica.B;

    cout<<"digite la constante C: ";
    cin>>conica.C;

    cout<<"digite la constante D: ";
    cin>>conica.D;

    cout<<"digite la constante E: ";
    cin>>conica.E;

    cout<<"digite la constante F: ";
    cin>>conica.F;

    cout<<endl<<"la ecuacion general de segundo grado formada es: "<<conica.A<<"x^2 + "<<conica.B<<"xy + "<<conica.C<<"y^2 + "<<conica.D<<"x + "<<conica.E<<"y + "<<conica.F<<"=0"<<endl<<endl;
}


string vectorToCartesian(double p0_x, double p0_y, double d_x, double d_y) {
    // Solve the x component equation for t: t = (x - p0_x) / d_x
    // Substitute t into the y component equation: y = p0_y + ((x - p0_x) / d_x) * d_y
    // Simplify to get the Cartesian equation: y = (d_y / d_x) * x + (p0_y - (d_y / d_x) * p0_x)

    double slope = d_y / d_x;
    double y_intercept = p0_y - slope * p0_x;

    return "y = " + std::to_string(slope) + " * x + " + std::to_string(y_intercept);
}


//encuentra el angulo de rotación, si esta es negativa se le suma 360 grados
float AnguloDeRotacion(conica &conica){

    double angulo=atan((conica.B/(conica.A-conica.C)))*90/3.141592;

    if(angulo>0){
        return angulo;}
    else if(angulo<0){
        return 360+angulo;
    }
    else{
        return 0;
    }
}

//dependiedo de que cocina sea, encuentra su forma canocina y todos sus datos respectivos
void FormaCanonica(conica &conica){

    double angulo=0, Ap, Cp, Dp, Ep, Fp, a, b, p, h, hp, kp, k, Angulo;

    float u1, u2, fx1, fy1, fx2, fy2, vx1, vy1, vx2, vy2, dx1, dy1, dx2, dy2, c;

    Angulo=AnguloDeRotacion(conica);

    angulo=Angulo*3.141592/180;

    //variables comunes de las canocinas
    Ap = conica.A*cos(angulo)*cos(angulo)+conica.B*sin(angulo)*cos(angulo)+conica.C*sin(angulo)*sin(angulo);
    Cp = conica.A*sin(angulo)*sin(angulo)-conica.B*sin(angulo)*cos(angulo)+conica.C*cos(angulo)*cos(angulo);
    Dp = conica.D*cos(angulo)+conica.E*sin(angulo);
    Ep = -conica.D*sin(angulo)+conica.E*cos(angulo);
    Fp = conica.F-(Dp*Dp/(4*Ap))-(Ep*Ep/(4*Cp));
    a = sqrt(abs(-Fp/Ap));
    b = sqrt(abs(-Fp/Cp));
    hp = -Dp/(2*Ap);
    kp= -Ep/(2*Cp);
    h = cos(angulo)*hp-sin(angulo)*kp;
    k= sin(angulo)*hp+cos(angulo)*kp;
    string tipo=TipoDeConica(conica);

    //tipo se iguala al tipo de canonica y luego para cada canonica se hallan sus datos respectivos
    if(tipo=="circunferencia"){

        double radio;
        radio=sqrt(abs(-Fp/Ap));
        cout<<endl<<endl<<"la forma canonica de la circunferencia es: "<<Ap<<"x''^2 + "<<Cp<<"y''^2 = "<<-Fp;

        cout<<endl<<endl<<"el centro es ("<<h<<", "<<k<<") ";
        cout<<endl<<endl<<"el radio de la cincunferencia es: "<<radio;

    } else if(tipo=="elipse"){

        c = sqrt(pow(a,2)-pow(b,2));
        u1 = cos(angulo);
        u2 = sin(angulo);
        fx1 = h + abs(c)*cos(angulo);
        fy1 = k + abs(c)*sin(angulo);
        fx2 = h - abs(c)*cos(angulo);
        fy2 = k - abs(c)*sin(angulo);
        vx1 = h + abs(a)*cos(angulo);
        vy1 = k + abs(a)*sin(angulo);
        vx2 = h - abs(a)*cos(angulo);
        vy2 = k - abs(a)*sin(angulo);
        dx1= h + (pow(a,2)/c)*cos(angulo);
        dy1= k + (pow(a,2)/c)*sin(angulo);
        dx2= h - (pow(a,2)/c)*cos(angulo);
        dy2= k - (pow(a,2)/c)*sin(angulo);

        cout<<endl<<endl<<" la forma canonica de la elipse es: "<<pow(abs(a),2)<<"^-1x''^2'' +" <<pow(abs(b),2)<<"^-1y''^2 = "<<1;
        cout<<endl<<endl<<"el centro es ("<<h<<", "<<k<<") ";
        cout<<endl<<endl<<"La longitud del semi-eje mayor es: "<<a;
        cout<<endl<<endl<<"la Longitud del semi-eje menor es: "<<b;
        cout<<endl<<endl<<"el foco 1 es =("<<fx1<<", "<<fy1<<") ";
        cout<<endl<<endl<<"el foco 2 es =("<<fx2<<", "<<fy2<<") ";
        cout<<endl<<endl<<"el vertice 1 es =("<<vx1<<", "<<vy1<<") ";
        cout<<endl<<endl<<"el vertice 2 es =("<<vx2<<", "<<vy2<<") ";
        cout<<endl<<endl<<"la directriz 1 es =("<<dx1<<", "<<dy1<<") ";
        cout<<endl<<endl<<"la directriz 2 es ("<<dx2<<", "<<dy2<<") " << endl << endl;
        cout<<"la ecuacion vectorial del eje mayor es P=("<<h<<", "<<k<<") + t("<<cos(angulo)<<", "<<sin(angulo)<<")" << endl;
        cout<<"la ecuacion vectorial del eje menor es P=("<<h<<", "<<k<<") + t("<<-sin(angulo)<<", "<<cos(angulo)<<")" << endl;
        cout<<"la ecuacion vectorial de la directriz 1 es P=("<<dx1<<", "<<dy1<<") + t("<<-sin(angulo)<<", "<<cos(angulo)<<")" << endl;
        cout<<"la ecuacion vectorial de la directriz 2 es P=("<<dx2<<", "<<dy2<<") + t("<<-sin(angulo)<<", "<<cos(angulo)<<")" << endl;
        cout<<"la ecuacion cartesiana del ejes mayor es: " << vectorToCartesian(h, k, cos(angulo), sin(angulo)) << endl;
        cout<<"la ecuacion cartesiana del ejes menor es: " << vectorToCartesian(h, k, -sin(angulo), cos(angulo)) << endl;
        cout<<"la ecuacion cartesiana de la directriz 1 es: " << vectorToCartesian(dx1, dy1, -sin(angulo), cos(angulo)) << endl;
        cout<<"la ecuacion cartesiana de la directriz 2 es: " << vectorToCartesian(dx2, dy2, -sin(angulo), cos(angulo)) << endl;


    } else if (tipo=="parabola"){

        p = -Ap/(4*Cp);
        u1 = cos(angulo);
        u2 = sin(angulo);
        fx1 = h + p*cos(angulo);
        fy1 = k + p*sin(angulo);
        dx1 = h - p*cos(angulo);
        dy1 = k - p*sin(angulo);

        cout<<endl<<endl<<" la forma canonica de la parabola es: "<<"y''^2 = "<<4*p<<"x´´^2";
        cout<<endl<<endl<<"su vertice es ("<<h<<", "<<k<<") ";
        cout<<endl<<endl<<"el foco es =("<<fx1<<", "<<fy1<<") ";
        cout<<endl<<endl<<"el foco 2 es =("<<fx2<<", "<<fy2<<") ";
        cout<<endl<<endl<<"la directriz es =("<<dx1<<", "<<dy1<<") " << endl << endl;
        cout<<"la ecuacion vectorial del eje mayor es P=("<<h<<", "<<k<<") + t("<<cos(angulo)<<", "<<sin(angulo)<<")" << endl;
        cout<<"la ecuacion vectorial del eje menor es P=("<<h<<", "<<k<<") + t("<<-sin(angulo)<<", "<<cos(angulo)<<")" << endl;
        cout<<"la ecuacion vectorial de la directriz es P=("<<dx1<<", "<<dy1<<") + t("<<-sin(angulo)<<", "<<cos(angulo)<<")" << endl;
        cout<<"la ecuacion cartesiana del ejes mayor es: " << vectorToCartesian(h, k, cos(angulo), sin(angulo)) << endl;
        cout<<"la ecuacion cartesiana del ejes menor es: " << vectorToCartesian(h, k, -sin(angulo), cos(angulo)) << endl;
        cout<<"la ecuacion cartesiana de la directriz es: " << vectorToCartesian(dx1, dy1, -sin(angulo), cos(angulo)) << endl;


    } else{ //es una hiperbola

        double Vx = cos(angulo) * a / b;
        double Vy = sin(angulo) * a / b;
        double Wx = -cos(angulo) * a / b;
        double Wy = -sin(angulo) * a / b;

        c = sqrt(pow(a,2)+pow(b,2));
        u1 = cos(angulo);
        u2 = sin(angulo);
        fx1 = h + abs(c)*cos(angulo);
        fy1 = k + abs(c)*sin(angulo);
        fx2 = h - abs(c)*cos(angulo);
        fy2 = k - abs(c)*sin(angulo);
        vx1 = h + abs(a)*cos(angulo);
        vy1 = k + abs(a)*sin(angulo);
        vx2 = h - abs(a)*cos(angulo);
        vy2 = k - abs(a)*sin(angulo);
        dx1= h + (pow(a,2)/c)*cos(angulo);
        dy1= k + (pow(a,2)/c)*sin(angulo);
        dx2= h - (pow(a,2)/c)*cos(angulo);
        dy2= k - (pow(a,2)/c)*sin(angulo);
        cout<<endl<<endl<<" la forma canonica de la hiperbola es: "<<pow(abs(a), 2)<<"^-1x''^2  -"<<pow(abs(b), 2)<<"^-1y''^2 = "<<1;
        cout<<endl<<endl<<"el centro es ("<<h<<", "<<k<<") ";
        cout<<endl<<endl<<"La longitud del semi-eje mayor es: "<<a;
        cout<<endl<<endl<<"la Longitud del semi-eje menor es: "<<b;
        cout<<endl<<endl<<"el foco 1 es =("<<fx1<<", "<<fy1<<") ";
        cout<<endl<<endl<<"el foco 2 es =("<<fx2<<", "<<fy2<<") ";
        cout<<endl<<endl<<"el vertice 1 es =("<<vx1<<", "<<vy1<<") ";
        cout<<endl<<endl<<"el vertice 2 es =("<<vx2<<", "<<vy2<<") ";
        cout<<endl<<endl<<"la directriz 1 es =("<<dx1<<", "<<dy1<<") ";
        cout<<endl<<endl<<"la directriz 2 es ("<<dx2<<", "<<dy2<<") ";
        cout<<endl<<endl<<"la ecuacion vectorial del eje mayor es P=("<<h<<", "<<k<<") + t("<<cos(angulo)<<", "<<sin(angulo)<<")";
        cout<<endl<<endl<<"la ecuacion vectorial del eje menor es P=("<<h<<", "<<k<<") + t("<<-sin(angulo)<<", "<<cos(angulo)<<")";
        cout<<endl<<endl<<"la ecuacion vectorial de la directriz 1 es P=("<<dx1<<", "<<dy1<<") + t("<<-sin(angulo)<<", "<<cos(angulo)<<")";
        cout<<endl<<endl<<"la ecuacion vectorial de la directriz 1 es P=("<<dx2<<", "<<dy2<<") + t("<<-sin(angulo)<<", "<<cos(angulo)<<")";
        cout<<endl<<endl<<"la ecuacion vectorial de la asitota 1 es Q=("<<h<<", "<<k<<") + t("<<Vx<<", "<<Vy<<")";
        cout<<endl<<endl<<"la ecuacion vectorial de la asintota 2 es R=("<<h<<", "<<k<<") + t("<<Wx<<", "<<Wy<<")" << endl << endl;
        cout<<"la ecuacion cartesiana del ejes mayor es: " << vectorToCartesian(h, k, cos(angulo), sin(angulo)) << endl;
        cout<<"la ecuacion cartesiana del ejes menor es: " << vectorToCartesian(h, k, -sin(angulo), cos(angulo)) << endl;
        cout<<"la ecuacion cartesiana de la directriz 1 es: " << vectorToCartesian(dx1, dy1, -sin(angulo), cos(angulo)) << endl;
        cout<<"la ecuacion cartesiana de la directriz 2 es: " << vectorToCartesian(dx2, dy2, -sin(angulo), cos(angulo)) << endl;
        cout<<"la ecuacion cartesiana de la asintota 1 es: " << vectorToCartesian(h, k, Vx, Vy) << endl;
        cout<<"la ecuacion cartesiana de la asintota 2 es: " << vectorToCartesian(h, k, Wx, Wy) << endl;
    }

}
