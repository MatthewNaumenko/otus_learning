#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <windows.h>

using std::cin;
using std::cout;
using std::endl;

std::string start_hello()
{
    std::string name;
    cout << "Привет, как тебя зовут? (Без кириллицы)" << endl;
    std::getline(cin, name);
    cout << "Супер, сейчас загадаю число..." << endl;
    return name;
}

int start_game(int max)
{
    std::srand(std::time(nullptr));
    const int max_value = max;
    const int random_value = std::rand() % max_value;
    cout << "Загадал, угадывай!" << endl;
    return random_value;
}

int process_game(int secret_number)
{

    bool game_win = false;
    int counter{0};

    while (!game_win)
    {

        int value{0};
        cin >> value;
        if (cin.fail())
        {
            cout << "Число не распознано. Повтори попытку:" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        else
        {
            if (value > secret_number)
            {
                cout << "greater than " << value << endl;
                counter++;
                continue;
            }
            else if (value < secret_number)
            {
                cout << "less than " << value << endl;
                counter++;
                continue;
            }
            else
            {
                counter++;
                cout << "you win! " << "attempts = " << counter << endl;
                game_win = true;
            }
        }
    }
    return counter;
}

bool rating_table_write(const std::string &name, int &rating)
{

    std::fstream os;
    os.open("../homework_3/rating_table.txt", std::fstream::out | std::fstream::app);

    if (!os.is_open())
    {
        cout << "Ошибка, файл не открыт" << endl;
        return false;
    }

    os << name << " " << rating << endl;

    os.close();

    return true;
}

void rating_table_read()
{
    std::fstream os;

    std::string str_name;

    os.open("../homework_3/rating_table.txt", std::fstream::in | std::fstream::app);

    if (!os.is_open())
    {
        cout << "Рейтинг не существует" << endl
             << endl;
        return;
    }

    cout << "High scores table:" << endl
         << endl;

    std::getline(os, str_name);

    do
    {
        cout << str_name << endl;
        std::getline(os, str_name);
    } while (str_name.size() > 0);
}

int game_level(const int &level)
{
    switch (level)
    {
    case 1:
        return 10;
    case 2:
        return 50;
    case 3:
        return 100;
    default:
        return 100;
    }
}

int main(int argc, char *argv[])
{

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int max{100};
    int level{0};

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-table") == 0)
        {
            rating_table_read();
            return 0;
        }
        else if (strcmp(argv[i], "-max") == 0)
        {
            if (i + 1 < argc)
                max = std::atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-level") == 0)
        {
            if (i + 1 < argc)
                level = std::atoi(argv[i + 1]);
            max = game_level(level);
        }
    }

    std::string name = start_hello();

    int rating = process_game(start_game(max));

    if (!rating == 0)
    {
        if (rating_table_write(name, rating))
        {
            cout << "Рейтинг успешно обновлен" << endl;
        }
        rating_table_read();
    }
    else
    {
        return 1;
    }
    return 0;
}