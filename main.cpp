#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;

struct Employee{
    char *name;
    char *gender;
    int age;
    char *job; // должность
    double salary; // оклад
};

int find_by_name(Employee *employees, int n, const char *name){
    for (int i = 0; i < n; ++i){
        if (strcmp(employees[i].name, name) == 0){ //если 0, то строки равны
            return i;
        }
    }
    return -1; // если не нашёл никого с таким именем, возвращает -1, при испльзовании надо будет проверять
}

int *find_by_age(Employee *employees, int n, int left, int right){
    int *idx = new int[n + 1]; // тут из функции будет возвращаться указатель на массив, у которого первый элемент хранит его размер, поэтому n + 1
                               //и ещё индексация начинается с 1
    idx[0] = 1;
    
    for (int i = 0; i < n; ++i){
        if (left <= employees[i].age && employees[i].age <= right){
            idx[idx[0]] = i;
            ++idx[0]; // увеличивается размер массива
        }
    }
    
    return idx;
}

int *find_by_salary(Employee *employees, int n, double left, double right){
    int *idx = new int[n + 1]; // то же самое, что и в возрасте
    idx[0] = 1;
    
    for (int i = 0; i < n; ++i){
        if (left <= employees[i].salary && employees[i].salary <= right){
            idx[idx[0]] = i;
            ++idx[0];
        }
    }
    
    return idx;
}

int main(){
    int n;
    cin >> n;
    Employee employees[n];
    
    for (int i = 0; i < n; ++i){
        char tmp;
        employees[i] = Employee();
        char *name = new char[100];
        cout << "Enter name\n";
        cin.ignore(); // это надо, потому что c++ дурацкий язык и cin.getline() считывает предыдущую строку, поэтому её надо прогнорировать
        cin.getline(name, 100);
        employees[i].name = new char[strlen(name)]; // тут создаётся массив ровно такой длины, какая нужна, чтобы вместить введённое имя
        strcpy(employees[i].name, name); // копировать строку
        
        char *gender = new char[100];
        cout << "Enter gender\n";
        cin.getline(gender, 100);
        employees[i].gender = new char[strlen(gender)];
        strcpy(employees[i].gender, gender);
        
        int age;
        cout << "Enter age\n";
        cin >> age;
        employees[i].age = age;
        
        char *job = new char[100];
        cout << "Enter job\n";
        cin.ignore();
        cin.getline(job, 100);
        employees[i].job = new char[strlen(job)];
        strcpy(employees[i].job, job);
        
        double salary;
        cout << "Enter salary\n";
        cin >> salary;
        employees[i].salary = salary;
    }
    
    for (int i = 0; i < n; ++i){ // вывод всех введённых рабочих
        cout << employees[i].name << "\n"
             << employees[i].gender << "\n"
             << employees[i].age << "\n"
             << employees[i].job << "\n"
             << employees[i].salary << "\n\n";
    }
    
    int left, right;

    cout << "Enter age range";
    cin >> left >> right; // можно через пробел, а можно с новой строки

    int *ages = find_by_age(employees, n, left, right); // создаётся указатель на int

    ofstream out; // создаётся потоковый вывод для файлов, для этого нужен include<fstream>
    out.open("out.txt"); // открывается файл out.txt, если его нет в директории, то создаётся

    double salary = 0;

    for (int i = 1; i < ages[0]; ++i){
        out << employees[i].name << "\n"
            << employees[i].gender << "\n"
            << employees[i].age << "\n"
            << employees[i].job << "\n"
            << employees[i].salary << "\n\n";
        salary += employees[i].salary;
    }

    out << "Average salary " << salary / (ages[0] - 1); // -1, потому что длина массива на 1 больше из-за того, что 0 элемент хранит размер

    out.close(); // закрытие файла
}