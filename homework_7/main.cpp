#include <iostream>

#include "IVector.hpp"
#include "IList.hpp"

int main() {

    // Создаем объект IVector<int>
    IVector<int> vect; 

    // Выделяем память под 9 элементов (но пока не заполняем массив)
    // Это демонстрирует резервирование памяти перед вставкой данных
    vect.capacity(9);

    // Выводим текущий логический размер контейнера (количество элементов)
    std::cout << "Current size (logical): " << vect.size() << std::endl;        

    // Выводим реальный (зарезервированный) размер контейнера (размер выделенной памяти)
    std::cout << "Real size (reserved) after insertion: " << vect.get_real_size() << std::endl; 

    // Добавляем в контейнер 10 элементов (числа от 0 до 9)
    // Каждый вызов `insert(i, i)` вставляет число `i` на позицию `i`
    for (int i{0}; i < 10; ++i) {
        vect.insert(i, i);
    }

    // Выводим текущее содержимое контейнера
    // Ожидаемый результат: 0 1 2 3 4 5 6 7 8 9
    vect.check();

    // Выводим логический размер контейнера (количество вставленных элементов)
    std::cout << "Current size (logical): " << vect.size() << std::endl; 

    // Выводим реальный размер контейнера (зарезервированную память после вставки)
    // После вставки 10-го элемента контейнер увеличивает память, следуя стратегии роста
    std::cout << "Real size (reserved) after insertion: " << vect.get_real_size() << std::endl; 

    // Удаляем 3, 5, 7 элементы
    vect.erase(6); //т.к. нумерация элементов с 0
    vect.erase(4);
    vect.erase(2);

    // Выводим текущее содержимое контейнера
    // Ожидаемый результат: 0 1 3 5 7 8 9
    vect.check();

    // Добавляем элемент 10 в начало контейнера
    vect.insert(0, 10);

    // Ожидаемый результат: 10 0 1 3 5 7 8 9
    vect.check();

    // Добавляем элемент 20 в середину контейнера
    vect.insert(4, 20);

    // Ожидаемый результат: 10 0 1 3 20 5 7 8 9
    vect.check();

    // Добавляем элемент 30 в конец контейнера
    vect.push_back(30);

    // Ожидаемый результат: 10 0 1 3 20 5 7 8 9 30
    vect.check();

    std::cout << "Current size (logical): " << vect.size() << std::endl; 
    std::cout << "Real size (reserved) after insertion: " << vect.get_real_size() << std::endl; 

    IVector<int> vect_copy = vect; // Конструктор копирования
    IVector<int> vect_copy_op; 
    vect_copy_op = vect_copy; // Оператор присваивания копирования

    IVector<int> vect_copy_move = std::move(vect_copy_op); // Конструктор перемещения
    IVector<int> vect_copy_move_op; 
    vect_copy_move_op = std::move(vect_copy_move);; // Оператор присваивания перемещения

    vect.resize(20); // Определяем новый размер вектора
    vect.check();
    std::cout << "Current size (logical): " << vect.size() << std::endl; 
    std::cout << "Real size (reserved) after insertion: " << vect.get_real_size() << std::endl; 

    vect.resize(5); // Определяем новый размер вектора
    vect.check();
    std::cout << "Current size (logical): " << vect.size() << std::endl; 
    std::cout << "Real size (reserved) after insertion: " << vect.get_real_size() << std::endl;

    // Получаем доступ к элементам контейнера через индексацию и метод at с проверкой границ
    std::cout << "Vect: " << vect[3] << " " << vect.at(3) << std::endl; 

    /* ---------------------------------------------------------------------------------- */

    std::cout << std::string(20, '.') << std::string("List") << std::string(20, '.') <<std::endl;
    
    IList<int> list;

    // Добавляем в контейнер 10 элементов (числа от 0 до 9)
    // Каждый вызов `insert(i, i)` вставляет число `i` на позицию `i`
    for (int i{0}; i < 10; ++i) {
        list.insert(i, i);
    }

    // Демонстрируем работу итератора
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    } 
    std::cout << std::endl;

    // Выводим размер контейнера
    std::cout << "Current List size: " << list.size() << std::endl; 

    // Удаляем 3, 5 и 7 элемент по счету
    list.erase(6);
    list.erase(4);
    list.erase(2);

    // Выводим контейнер
    // Ожидаемый результат: 0 1 3 5 7 8 9
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    } 
    std::cout << std::endl;

    // Добавляем элемент 10 в начало контейнера
    list.insert(0,10);
   
    // Выводим контейнер
    // Ожидаемый результат: 10 0 1 3 5 7 8 9
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    } 
    std::cout << std::endl;

    // Добавляем элемент 20 в середину контейнера
    list.insert(4, 20);
   
    // Выводим контейнер
    // Ожидаемый результат: 10 0 1 3 20 5 7 8 9
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    } 
    std::cout << std::endl;

    // Добавляем элемент 30 в конец контейнера
    list.push_back(30);
   
    // Выводим контейнер
    // Ожидаемый результат: 10 0 1 3 20 5 7 8 9 30
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    } 
    std::cout << std::endl;

    // Получаем доступ к элементам контейнера через индексацию итератора
    auto it = list.begin();
    std::cout << "List: " << it[3]  <<" "<< *(++it) <<" "<< *(--it) <<std::endl; 

    IList<int> list_copy = list;

    IList<int> list_copy_op; // Конструктор копирования
    list_copy_op = list_copy; // Оператор присваивания копирования

    return 0;
}
