// «Доставка пиццы»: ассортимент, клиенты, заказы, скидки …

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>

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
const int numPizzas = 5;
Pizza pizzas[numPizzas] = {
    Pizza("Пеперонни", 12, 800),
    Pizza("Маргаритта", 10, 900),
    Pizza("Вегатерианская", 14, 1100),
    Pizza("Мясная", 12, 1200),
    Pizza("Карбонара", 10, 900)
};








// Объявление функций, чтобы их можно было вызывать из main()
void order(vector<string>& cart);
void menu();
string getCouponDiscount(const string& coupon);
void read_file(string cin_file);





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
    // Ассортимент
    if (numUser == 1) {
        menu();
    }

    // Клиенты
    else if (numUser == 2) {
        read_file("clients.txt");
    }

    // Заказы
    else if (numUser == 3) {
        read_file("orders.txt");
    }
    
    // Скидки
    else if (numUser == 4) {
        read_file("sales.txt");
    }
    
    // Оформить заказ
    else if (numUser == 5) {
        vector<string> cart; // Создаем вектор для хранения заказанных пицц
        order(cart); // Передаем вектор по ссылке для сохранения заказов
    } else {
        cout << "Пожалуйста, выберите вариант меню (1-5)" << endl;
    }

    return 0;
}


















void read_file(string cin_file) {
    ifstream file(cin_file); // Открытие файла для чтения
    string line;

    if (file.is_open()) {
        // Чтение файла построчно и вывод содержимого на экран
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close(); // Закрытие файла после использования
    } else {
        cerr << "Невозможно открыть файл" << endl;
    }
}














// Определение функции menu()
void menu() {
    cout << "Доступное меню:" << endl;
    for (int i = 0; i < numPizzas; ++i) {
        cout << "Пицца " << i + 1 << ":" << endl;
        cout << "Наименование: " << pizzas[i].name << endl;
        cout << "Размер: " << pizzas[i].size << " см" << endl;
        cout << "Цена: " << pizzas[i].price << "₽" << endl;
        cout << endl;
    }
}














// Определение функции order()
void order(vector<string>& cart) { // Принимаем вектор по ссылке для сохранения заказов
    string userName;
    ofstream users; // Заменяем ofstream на ifstream
    ofstream orders;
    int price = 0;
    
    menu(); // Показываем меню пицц
    
    cout << "Введите Ваше имя (используйте латиницу)" << endl;
    cin >> userName;
    
    // Запись имени клиента в файл clients.txt
    users.open("clients.txt", ios::app);
    if (users.is_open()) {
        users << userName << endl;
    }    

    // Начало записи заказа клиента в orders.txt
    orders.open("orders.txt", ios::app);
    if (orders.is_open()) {
        orders << "------------------" << endl;
        orders << "Имя: " << userName << endl;
    }

    // Заказ пиццы
    char userWant = 'y'; // Используем символьный тип для ответа пользователя
    while (userWant == 'y' || userWant == 'Y') { // Проверяем на 'y' или 'Y' для продолжения цикла
        cout << "Выберите пиццу (введите ее номер), которую хотите заказать" << endl;
        int selectUser;
        cin >> selectUser;
        if (selectUser < 1 || selectUser > numPizzas) {
            cout << "Вы ввели неверное число" << endl;
        } else {
            cart.push_back(pizzas[selectUser - 1].name); // Добавляем название выбранной пиццы в корзину
            price += pizzas[selectUser - 1].price;
        }
    
        cout << "Хотите заказать еще? (y/n)" << endl;
        cin >> userWant;
    
        // Добавляем проверку, чтобы выйти из цикла, если пользователь ввел 'n' или 'N'
        if (userWant != 'y' && userWant != 'Y') {
            // Выводим список заказанных пицц в файл заказов
            for (const auto& pizza : cart) {
                orders << "Пицца: " << pizza << endl;
            }
            break;
        }
    }
    orders << "Цена заказа: " << price << "₽" << endl;

    // Проверка наличия купона у покупателя
    cout << "У Вас есть купон на скидку? (y/n)" << endl;
    char userSale;
    cin >> userSale;
    if (userSale == 'y' || userSale == 'Y') {
        // Запрос купона у пользователя
        cout << "Введите купон: ";
        string userCoupon;
        cin >> userCoupon;

        // Получение и вывод скидки по купону
        string userDiscount = getCouponDiscount(userCoupon);
        int discount = stoi(userDiscount);

        price -= price*discount/100;
        orders << "Цена заказа со скидкой: " << price << "₽" << endl;
    }


    // Заканчиваем запись заказа клиента и закрываем файл
    orders << "------------------" << "\n" << endl;
    orders.close();
}
 




string getCouponDiscount(const string& coupon) {
    ifstream file("sales.txt"); // Открытие файла с купонами и скидками для чтения
    map<string, string> coupons; // Контейнер для хранения купонов и скидок

    if (!file.is_open()) {
        cerr << "Не получилось открыть файл." << endl;
        return "Error: Не получилось открыть файл.";
    }

    // Чтение купонов и скидок из файла
    string fileCoupon, discount;
    while (file >> fileCoupon >> discount) {
        coupons[fileCoupon] = discount;
    }

    file.close(); // Закрытие файла

    // Поиск скидки по купону
    auto it = coupons.find(coupon);
    if (it != coupons.end()) {
        return it->second;
    } else {
        return "Купон не найден.";
    }
}





