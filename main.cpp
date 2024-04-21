// «Доставка пиццы»: ассортимент, клиенты, заказы, скидки …

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


// Создаем класс для пиццы
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



// Главная функция
// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");

    // Инициализация переменных
    int numUser;
    string userName;
    ofstream users;
    ofstream orders;
    ofstream sales;

    // Главная менюшка
    cout << "Добро пожаловать в нашу пиццерию!" << endl;
    cout << "-Ассортимент (1)" << endl;
    cout << "-Клиенты (2)" << endl;
    cout << "-Заказы (3)" << endl;
    cout << "-Скидки (4)" << endl;
    cout << "-Оформить заказ (5)" << endl;
    cin >> numUser;

    // Действия после выбора пользователя
    if (numUser == 1) {
        cout << "Доступное меню:" << endl;
        for (int i = 0; i < numPizzas; ++i) {
            cout << "Пицца " << i+1 << ":" << endl;
            cout << "Наименование: " << pizzas[i].name << endl;
            cout << "Размер: " << pizzas[i].size << " inches" << endl;
            cout << "Цена: $" << pizzas[i].price << endl;
            cout << endl;
        }
    }
    else if (numUser == 2) {
        /* code */
    }
    else if (numUser == 3) {
        /* code */
    }
    else if (numUser == 4) {
        /* code */
    }
    else if (numUser == 5) {
        // Вывод полного меню для заказа
        cout << "Доступное меню:" << endl;
        for (int i = 0; i < numPizzas; ++i) {
            cout << "Пицца " << i+1 << ":" << endl;
            cout << "Наименование: " << pizzas[i].name << endl;
            cout << "Размер: " << pizzas[i].size << " inches" << endl;
            cout << "Цена: $" << pizzas[i].price << endl;
            cout << endl;
        }

        cout << "Введите Ваше имя (используйте латиницу)" << endl;
        cin >> userName;
        
        // Запись имени клиента в файл clients.txt
        users.open("clients.txt", std::ios::app);
        if (users.is_open()){
            users << userName << endl;
        }
        users.close();

        // Начало записи заказа клиента в orders.txt
        orders.open("orders.txt", std::ios::app);
        if (orders.is_open()) {
            orders << "------------" << endl;
            orders << "Имя:" << userName << endl;
        }

        // Выбор клиентом пиццы
        char userWant = 'y'; // Используем символьный тип для ответа пользователя
        while (userWant == 'y' || userWant == 'Y') { // Проверяем на 'y' или 'Y' для продолжения цикла
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
        
            cout << "Хотите заказать еще? (y/n)" << endl;
            cin >> userWant;
        
            // Добавляем проверку, чтобы выйти из цикла, если пользователь ввел 'n' или 'N'
            if (userWant != 'y' && userWant != 'Y') {
                break;
            }
        }

        orders.close();
    }
    else {
        cout << "Пожалуйста, выберите вариант меню (1-4)" << endl;
    }

    return 0;
}
