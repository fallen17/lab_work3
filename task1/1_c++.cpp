#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

void print_table(const vector<pair<double,double>> &table, const string &title){
    cout << "\n========================================" << endl;
    cout << "          " << title << endl;
    cout << "========================================" << endl;
    cout << setw(10) << "X" << setw(15) << "Y" << endl;
    cout << "----------------------------------------" << endl;

    for (const auto &[x, y] : table){
        cout << setw(10) << fixed << setprecision(4) << x 
             << setw(15) << fixed << setprecision(4) << y << endl;
    }
    
    cout << "========================================\n" << endl;
}

void func_circle(vector<pair<double,double>> &tabXY){
    int R = 2;
    double step = 0.5;

    for (double x = -10; x <= -6 + 0.001; x+=step){
        double y = -2 + sqrt(pow(R, 2) - pow((x + 8), 2));

        if (!isnan(y)) { 
            tabXY.push_back({x, y});}    }
}

void func_line(vector<pair<double,double>> &tabXY){
    double k = 0.6;
    double b = 1.6;
    double step = 0.6;

    for (double x = -6; x <= -1 + 0.001; x++){
        double y = k*x + b;

        tabXY.push_back({x, y});
    }
}

void func_const(vector<pair<double,double>> &tabXY){
    double step = 0.5;

    for (double x = -1; x <= 2; x+=step){
        double y = 0;

        tabXY.push_back({x, y});
    }
}

void func_parabola(vector<pair<double,double>> &tabXY){
    double step = 0.2;

    for (double x = 2; x <= 3 + 0.001; x+=step){
        double y = pow((x - 2), 2);

        tabXY.push_back({x, y});
    }
}

int main(){
    vector<pair<double,double>> tabCircle;
    vector<pair<double,double>> tabLine;
    vector<pair<double,double>> tabConst;
    vector<pair<double,double>> tabParabola;

    func_circle(tabCircle);
    func_line(tabLine);
    func_const(tabConst);
    func_parabola(tabParabola);

    print_table(tabCircle, "Circle (upper half)");
    print_table(tabLine, "Line");
    print_table(tabConst, "Constant");
    print_table(tabParabola, "Parabola");

    return 0;
}