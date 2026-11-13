#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "Models.h"

using namespace std;

int main() {
    system("chcp 1251 > nul");

    map<string, Book> bookMap;                      
    set<string> genreSet;                           
    multimap<string, Sale> saleMultimap;            
    multiset<double> priceMultiset;                 
    unordered_map<string, Magazine> magUnorderedMap;
    unordered_set<string> printeryUnorderedSet;     
    unordered_multimap<string, string> custMultimap;
    unordered_multiset<int> yearUnorderedMultiset;  

    Printery pr1("Дом печати", "Минск"), pr2("Печатник", "Брест");

    Book b1("978-985-01-1", "Мастер и Маргарита", 2023, 5000, 25.0, pr1, "Роман", 480, Author("Булгаков М.", "Россия", 1891));
    Book b2("978-985-01-2", "Чистый код", 2022, 2000, 45.0, pr2, "IT", 464, Author("Мартин Р.", "США", 1952));
    bookMap.insert({ b1.getCode(), b1 });
    bookMap.insert({ b2.getCode(), b2 });
    priceMultiset.insert(b1.getPrice());
    priceMultiset.insert(b2.getPrice());

    genreSet.insert("Роман");
    genreSet.insert("IT");

    saleMultimap.insert({ b1.getCode(), Sale(b1.getCode(), "Книжный мир", 100, 2500.0) });
    saleMultimap.insert({ b1.getCode(), Sale(b1.getCode(), "Белкнига", 250, 6250.0) });

    Magazine m1("ISSN-101", "Наука и жизнь", 2026, 8000, 7.0, pr1, 5, "Ежемесячно");
    magUnorderedMap.insert({ m1.getCode(), m1 });
    priceMultiset.insert(m1.getPrice());

    printeryUnorderedSet.insert(pr1.getName());
    printeryUnorderedSet.insert(pr2.getName());

    int choice;
    do {
        cout << "\n=== СИСТЕМА УЧЕТА ИЗДАТЕЛЬСТВА (ВАРИАНТ 19) ===\n"
            << "1. Управление каталогом книг (std::map) - просмотр, добавление, поиск\n"
            << "2. Управление каталогом журналов (std::unordered_map) - просмотр, добавление, поиск\n"
            << "3. Учет реализации продаж (std::multimap) - просмотр, добавление\n"
            << "4. Управление жанрами (std::set) - добавление, просмотр\n"
            << "5. Анализ цен всей продукции (std::multiset)\n"
            << "6. Справочник типографий (std::unordered_set)\n"
            << "7. Выгрузить все данные в отчет (publishing_report.txt)\n"
            << "0. Выход\n"
            << "Выберите пункт меню: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: { 
            cout << "\n--- МЕНЮ: КНИГИ (std::map) ---\n"
                << "1. Показать все книги\n"
                << "2. Добавить новую книгу\n"
                << "3. Найти книгу по ISBN\n"
                << "4. Удалить книгу по ISBN\n"
                << "Выбор: ";
            int sub; cin >> sub; cin.ignore();
            if (sub == 1) {
                cout << left << setw(18) << "ISBN" << setw(22) << "Название" << setw(16) << "Автор" << setw(12) << "Жанр" << setw(8) << "Цена" << "\n";
                cout << string(76, '-') << "\n";
                for (auto& p : bookMap) p.second.print(cout);
            }
            else if (sub == 2) {
                string isbn, title, author, genre; double price; int year, copies;
                cout << "ISBN: "; getline(cin, isbn);
                if (bookMap.find(isbn) != bookMap.end()) { cout << "Книга с таким ISBN уже существует!\n"; break; }
                cout << "Название: "; getline(cin, title);
                cout << "Автор: "; getline(cin, author);
                cout << "Жанр: "; getline(cin, genre);
                cout << "Год: "; cin >> year;
                cout << "Тираж: "; cin >> copies;
                cout << "Цена: "; cin >> price; cin.ignore();

                Book newBook(isbn, title, year, copies, price, pr1, genre, 300, Author(author, "РБ", 1980));
                bookMap[isbn] = newBook;
                genreSet.insert(genre); 
                priceMultiset.insert(price); 
                cout << "Книга успешно добавлена!\n";
            }
            else if (sub == 3) {
                string key; cout << "Введите ISBN для поиска: "; getline(cin, key);
                auto it = bookMap.find(key);
                if (it != bookMap.end()) {
                    cout << "\nНайдена книга:\n";
                    it->second.print(cout);
                }
                else {
                    cout << "Книга не найдена.\n";
                }
            }
            else if (sub == 4) {
                string key; cout << "Введите ISBN для удаления: "; getline(cin, key);
                if (bookMap.erase(key) > 0) cout << "Книга удалена.\n";
                else cout << "Книга не найдена.\n";
            }
            break;
        }
        case 2: { 
            cout << "\n--- МЕНЮ: ЖУРНАЛЫ (std::unordered_map) ---\n"
                << "1. Показать все журналы\n"
                << "2. Добавить новый журнал\n"
                << "3. Найти журнал по ISSN\n"
                << "4. Удалить журнал по ISSN\n"
                << "Выбор: ";
            int sub; cin >> sub; cin.ignore();
            if (sub == 1) {
                cout << left << setw(12) << "ISSN" << setw(22) << "Название" << setw(8) << "Выпуск" << setw(15) << "Периодика" << setw(8) << "Цена" << "\n";
                cout << string(70, '-') << "\n";
                for (auto& p : magUnorderedMap) p.second.print(cout);
            }
            else if (sub == 2) {
                string issn, title, period; int issue, year, copies; double price;
                cout << "ISSN: "; getline(cin, issn);
                if (magUnorderedMap.find(issn) != magUnorderedMap.end()) { cout << "Журнал с таким ISSN уже есть!\n"; break; }
                cout << "Название: "; getline(cin, title);
                cout << "Номер выпуска: "; cin >> issue; cin.ignore();
                cout << "Периодичность (например, Ежемесячно): "; getline(cin, period);
                cout << "Год: "; cin >> year;
                cout << "Тираж: "; cin >> copies;
                cout << "Цена: "; cin >> price; cin.ignore();

                Magazine newMag(issn, title, year, copies, price, pr1, issue, period);
                magUnorderedMap[issn] = newMag;
                priceMultiset.insert(price);
                cout << "Журнал успешно добавлен!\n";
            }
            else if (sub == 3) {
                string key; cout << "Введите ISSN для поиска: "; getline(cin, key);
                auto it = magUnorderedMap.find(key);
                if (it != magUnorderedMap.end()) {
                    cout << "\nНайден журнал:\n";
                    it->second.print(cout);
                }
                else {
                    cout << "Журнал не найден.\n";
                }
            }
            else if (sub == 4) {
                string key; cout << "Введите ISSN для удаления: "; getline(cin, key);
                if (magUnorderedMap.erase(key) > 0) cout << "Журнал удален.\n";
                else cout << "Журнал не найден.\n";
            }
            break;
        }
        case 3: { 
            cout << "\n--- МЕНЮ: ПРОДАЖИ (std::multimap) ---\n"
                << "1. Показать все продажи\n"
                << "2. Зарегистрировать новую продажу\n"
                << "Выбор: ";
            int sub; cin >> sub; cin.ignore();
            if (sub == 1) {
                cout << left << setw(15) << "Код товара" << setw(20) << "Покупатель" << setw(10) << "Кол-во" << setw(10) << "Сумма" << "\n";
                cout << string(55, '-') << "\n";
                for (auto& p : saleMultimap) p.second.print(cout);
            }
            else if (sub == 2) {
                string code, cust; int qty; double sum;
                cout << "Код продукции (ISBN или ISSN): "; getline(cin, code);
                cout << "Покупатель (организация): "; getline(cin, cust);
                cout << "Количество экземпляров: "; cin >> qty;
                cout << "Общая сумма продажи (руб.): "; cin >> sum; cin.ignore();

                saleMultimap.insert({ code, Sale(code, cust, qty, sum) });
                cout << "Продажа успешно зарегистрирована в multimap!\n";
            }
            break;
        }
        case 4: { 
            cout << "\n--- МЕНЮ: ЖАНРЫ (std::set) ---\n"
                << "1. Показать список жанров\n"
                << "2. Добавить новый жанр\n"
                << "Выбор: ";
            int sub; cin >> sub; cin.ignore();
            if (sub == 1) {
                cout << "Уникальные жанры литературы (в алфавитном порядке):\n";
                for (const auto& g : genreSet) cout << "- " << g << "\n";
            }
            else if (sub == 2) {
                string g; cout << "Введите новый жанр: "; getline(cin, g);
                genreSet.insert(g);
                cout << "Жанр добавлен в set.\n";
            }
            break;
        }
        case 5: { 
            cout << "\n--- МЕНЮ: ЦЕНЫ (std::multiset) ---\n"
                << "Все цены в ассортименте (автосортировка по возрастанию):\n";
            for (double p : priceMultiset) cout << p << " руб. ";
            cout << "\n";
            break;
        }
        case 6: { 
            cout << "\n--- МЕНЮ: ТИПОГРАФИИ (std::unordered_set) ---\n"
                << "Список уникальных типографий-партнеров:\n";
            for (const auto& pr : printeryUnorderedSet) cout << "- " << pr << "\n";
            break;
        }
        case 7: { 
            ofstream fout("publishing_report.txt");
            fout << "=== СВОДНЫЙ ОТЧЕТ ИЗДАТЕЛЬСТВА ===\n\n[КНИГИ (MAP)]\n";
            for (auto& p : bookMap) p.second.print(fout);

            fout << "\n[ЖУРНАЛЫ (UNORDERED_MAP)]\n";
            for (auto& p : magUnorderedMap) p.second.print(fout);

            fout << "\n[ПРОДАЖИ (MULTIMAP)]\n";
            for (auto& p : saleMultimap) p.second.print(fout);

            fout.close();
            cout << "Полный отчет успешно выгружен в файл 'publishing_report.txt'!\n";
            break;
        }
        }
    } while (choice != 0);

    return 0;
}