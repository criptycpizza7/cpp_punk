#include<iostream>
#include<random>
#include<ctime>

// заменяет все вхождения pi на 3.1415
#define pi 3.1415

using namespace std;

// струтура точки, чтоб было удобно
struct Point{
    double x;
    double y;
};

class Ellipse{
private:
    Point center; // центр
    double a; //полуось
    double b; //полуось

public:
    // геттеры
    Point get_center(){
        return center;
    }
    double get_a(){
        return a;
    }
    double get_b(){
        return b;
    }
    double get_square(){
        return pi * a * b;
    }

    // сеттеры
    void set_center(Point c){
        center = c;
    }
    void set_a(double a_){
        a = a_;
    }
    void set_b(double b_){
        b = b_;
    }
};

void print_ellipse(Ellipse ellipse){
    cout << "Center:\n"
         << ellipse.get_center().x << " " << ellipse.get_center().y << "\n"
         << "Axes:\n"
         << ellipse.get_a() << " " << ellipse.get_b()
         << "\n\n";
}

void find_smallest_squares(Ellipse *ellipses){
    int min_mas_idx[] = {-1, -1, -1};
    int min_mas[] = {100000, 100000, 100000};

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 20; ++j){
            if(j != min_mas_idx[0] & j != min_mas_idx[1] & j != min_mas_idx[2])
                if(ellipses[j].get_square() < min_mas[i]){
                    min_mas[i] = ellipses[j].get_square();
                    min_mas_idx[i] = j;
                }
        }
    }

    cout << min_mas[0] << "\n"
         << min_mas[1] << "\n"
         << min_mas[2] << "\n\n";
}

int main(){
    random_device rd; // https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
    mt19937 gen(rd());
    uniform_real_distribution<> point(-10.0, 10.0);
    uniform_real_distribution<> dist(1, 10.0);
    
    Ellipse mas[20];

    for(int i = 0; i < 20; ++i){
        Point tmp_point;
        tmp_point.x = point(gen);
        tmp_point.y = point(gen);

        Ellipse tmp_ellipse;
        tmp_ellipse.set_a(dist(gen));
        tmp_ellipse.set_b(dist(gen));
        tmp_ellipse.set_center(tmp_point);
        mas[i] = tmp_ellipse;
    }

    print_ellipse(mas[0]);
    find_smallest_squares(mas);
}