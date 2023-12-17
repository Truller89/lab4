#include <iostream>
#include <vector>
#include <thread>
size_t amountOfCompletedThreads;

struct date {
    int day;
    int mounth;
    int year;
};

bool operator <(date one, date two) {
    if (one.year < two.year) return true;
    else if (one.year > two.year) return false;
    if (one.mounth < two.mounth) return true;
    else if (one.mounth > two.mounth) return false;
    if (one.day < two.day) return true;
    return false;
}

std::vector<date> isBeetween(std::vector<date> dates, int number, int maxNumber, date leftDate, date rightDate) {
    std::vector<date>  result;
    for (size_t i = number; i < dates.size(); i += maxNumber) {
        if (dates[i] < rightDate and leftDate < dates[i]) {
            result.push_back(dates[i]);
        }
    }
    ++amountOfCompletedThreads;
    return result;
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    std::cout << "Введите количество данных: ";
    int size;
    std::cin >> size;
    std::cout << "Введите количество параллельных потоков: ";
    int count;
    std::cin >> count;
    std::cout << "Случайные?: ";
    bool isRand;
    std::cin >> isRand;
    date d1 = { 01, 01 , 2010 }, d2 = {18, 3 ,2023};
    std::vector<date> dates;
    if (!isRand) {
        for (int i = 0; i < size; i++) {
            int a, b, c;
            std::cout << "Введите день #" << i + 1 << ": ";
            std::cin >> a;
            std::cout << "Введите месяц #" << i + 1 << ": ";
            std::cin >> b;
            std::cout << "Введите год #" << i + 1 << ": ";
            std::cin >> c;
            date nowDate = { a, b, c };
            dates.push_back(nowDate);
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            date nowDate = { (rand()%12)+1, (rand() % 12)+1, (rand() % 100) + 2000};
            dates.push_back(nowDate);
        }
    }

    int solostart = clock();
    std::vector<date> soloResult = isBeetween(dates, 0, 1, d1, d2);
    int soloend = clock();

    amountOfCompletedThreads = 0;
    int multiStart = clock();
    for (int i = 0; i < count; i++) {
        std::thread potok(isBeetween, dates, i, count, d1, d2);
        potok.detach();
    }

    while (amountOfCompletedThreads < count) {};
    int multiEnd = clock();
    std::cout << "Время при одном потоке: " << soloend - solostart << std::endl << "Время при многопоточности: " << multiEnd - multiStart;
}