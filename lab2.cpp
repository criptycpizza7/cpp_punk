#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

struct Car{
    char *number; // гос номер
    char *brand; // марка
    char *color;
    int year;
    double mass;

    Car *next; // указатель на следующую
};

void add_car(Car *root, Car car, char *number){ // добавление машины в ребёнки по гос номеру
    Car *node = root;
    if(node->next == nullptr && strcmp(number, node->number) != 0)
        return;
    do{
        if (strcmp(node->number, number) == 0){

            Car *next = node->next;
            node->next = new Car();

            node->next->number = car.number;
            node->next->brand = car.brand;
            node->next->color = car.color;
            node->next->year = car.year;
            node->next->mass = car.mass;
            node->next->next = next;
            return;
        }
        node = node->next;
    }while ((node != nullptr));
    cout << "Wrong number\n";
}

void delete_car(Car *root, char *number){ // удаление машины
    if (strcmp(root->number, number) == 0){
        Car *next = root->next;
        delete root;
        root = next;
        return;
    }
    Car *node = root;
    if(node->next == nullptr)
        return;
    do{
        if (strcmp(node->next->number, number) == 0){
            Car *tmp = node->next;
            node->next = tmp->next;
            return;
        }
        node = node->next;
    }while (node->next != nullptr);
}

Car *find_cars(Car *root, int year, int *size){ // поиск по году
    *size = 0;

    Car *node = root;

    Car *cars = new Car[100];
    while (node != nullptr){
        if (node->year == year){
            Car car = Car();

            car.number = new char[strlen(node->number)];
            car.brand = new char[strlen(node->brand)];
            car.color = new char[strlen(node->color)];
            strcpy(car.number, node->number);
            strcpy(car.brand, node->brand);
            strcpy(car.color, node->color);
            car.year = node->year;
            car.mass = node->mass;
            car.next = node->next;

            cars[*size] = car;
            
            ++(*size);
        }
        node = node->next;
    }
    return cars;
}

int main(){

    // freopen("lab2_in.txt", "r", stdin);
    // freopen("lab2_out.txt", "w", stdout);
    Car *node = new Car();
    Car *root = node;
    Car *prev_node = nullptr;

    cout << "Enter number of cars\n";
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i){

        if (prev_node != nullptr){
            prev_node->next = node;
        }
        cout << "Enter number\n";
        char *number = new char[100];
        cin.getline(number, 100);

        cout << "Enter brand\n";
        char *brand = new char[100];
        cin.getline(brand, 100);

        cout << "Enter color\n";
        char *color = new char[100];
        cin.getline(color, 100);
        
        cout << "Enter year\n";
        int year;
        cin >> year;

        cout << "Enter mass\n";
        double mass;
        cin >> mass;
        cin.ignore();

        node->number = new char[strlen(number)];
        node->brand = new char[strlen(brand)];
        node->color = new char[strlen(color)];
        strcpy(node->number, number);
        strcpy(node->brand, brand);
        strcpy(node->color, color);
        node->year = year;
        node->mass = mass;
        node->next = nullptr;
        prev_node = node;
        node = new Car();
    }
    char *num2 = new char[2];
    strcpy(num2, "2");
    if(root->next != nullptr)
        add_car(root, *(root->next), num2);

    if(root -> next != nullptr)
        delete_car(root, root->next->number);

    int size;

    Car *cars = new Car[100];
    cars = find_cars(root, 2025, &size);
    
    for (int i = 0; i < size; ++i){
        cout << cars[i].number << "\n" <<
        cars[i].brand << "\n" <<
        cars[i].color << "\n" <<
        cars[i].year << "\n" <<
        cars[i].mass << "\n\n";
    }
    Car *car = root;
    Car *prev_car = car;

    while(car != nullptr){
        car = prev_car->next;
        delete prev_car;
    }


    delete[] cars;
    delete[] num2;
}