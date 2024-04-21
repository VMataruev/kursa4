// «Доставка пиццы»: ассортимент, клиенты, заказы, скидки …

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Pizza {
public:
    string name;
    int size;
    double price;

    // Конструктор
    Pizza(string t, int s, double p) : name(t), size(s), price(p) {}
};

// Глобальный массив объектов Pizza
const int numPizzas = 3;
Pizza pizzas[numPizzas] = {
    Pizza("Пеперонни", 12, 9.99),
    Pizza("Маргаритта", 10, 8.99),
    Pizza("Вегатерианская", 14, 10.99)
};


int main() {
    // Вывод всех пицц


    int numUser;
    string userName;
    ofstream users;

    cout << "Добро пожаловать в нашу пиццерию!" << endl;
    cout << "-Ассортимент (1)" << endl;
    cout << "-Клиенты (2)" << endl;
    cout << "-Заказы (3)" << endl;
    cout << "-Скидки (4)" << endl;
    cout << "-Оформить заказ (5)" << endl;
    cin >> numUser;

    switch (numUser)
    {
    case 1:
        cout << "Доступное меню:" << endl;
        for (int i = 0; i < numPizzas; ++i) {
            cout << "Пицца " << i+1 << ":" << endl;
            cout << "Наименование: " << pizzas[i].name << endl;
            cout << "Размер: " << pizzas[i].size << " inches" << endl;
            cout << "Цена: $" << pizzas[i].price << endl;
            cout << endl;
        }
        break;
    
    case 2:
        /* code */
        break;
    
    case 3:
        /* code */
        break;

    case 4:
        /* code */
        break;

    case 5:
        cout << "Доступное меню:" << endl;
        for (int i = 0; i < numPizzas; ++i) {
            cout << "Пицца " << i+1 << ":" << endl;
            cout << "Наименование: " << pizzas[i].name << endl;
            cout << "Размер: " << pizzas[i].size << " inches" << endl;
            cout << "Цена: $" << pizzas[i].price << endl;
            cout << endl;
        }

        cout << "Введите Ваше имя" << endl;
        cin >> userName;
        
        users.open("clients.txt", std::ios::app);
        if (users.is_open()) {
            users << userName << endl;
        }
        users.close();

        cout << "Выберите пиццу (введите ее номер), которую хотите заказать" << endl;
        int selectUser;
        cin >> selectUser;
        if (selectUser < 1 || selectUser > numPizzas) {
            cout << "Вы ввели неверное число" << endl;
        } 
        else {
            vector<int> cart;
            cart.push_back(selectUser);
        }

        break;
    
    default:
        cout << "Пожалуйста, выберите вариант меню (1-4)" << endl;
        break;
    }

    return 0;
}