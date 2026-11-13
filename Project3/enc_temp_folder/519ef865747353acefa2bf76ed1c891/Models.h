#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// Класс Автор (Композиция)
class Author {
private:
    string fullName;
    string country;
    int birthYear;
public:
    Author(string n = "", string c = "", int y = 2000)
        : fullName(n), country(c), birthYear(y) {
    }

    string getName() const { return fullName; }
    void input() {
        cout << "  ФИО автора: "; getline(cin, fullName);
        cout << "  Страна: "; getline(cin, country);
        cout << "  Год рождения: "; cin >> birthYear; cin.ignore();
    }
};

// Класс Типография (Агрегация)
class Printery {
private:
    string name;
    string city;
public:
    Printery(string n = "Дом печати", string c = "Минск") : name(n), city(c) {}
    string getName() const { return name; }
};

// Базовый класс Печатная продукция
class PrintProduct {
protected:
    string code;
    string title;
    int year;
    int copies;
    double price;
    Printery printery;
public:
    PrintProduct(string cd = "", string t = "", int y = 2026, int c = 1000, double p = 10.0, Printery pr = Printery())
        : code(cd), title(t), year(y), copies(c), price(p), printery(pr) {
    }

    virtual ~PrintProduct() {}
    virtual string kind() const = 0;

    string getCode() const { return code; }
    string getTitle() const { return title; }
    int getYear() const { return year; }
    int getCopies() const { return copies; }
    double getPrice() const { return price; }
    string getPrinteryName() const { return printery.getName(); }

    void setTitle(string t) { title = t; }
    void setPrice(double p) { price = p; }
};

// Класс Книга (Наследование)
class Book : public PrintProduct {
private:
    string genre;
    int pages;
    Author author;
public:
    Book(string cd = "", string t = "", int y = 2026, int c = 1000, double p = 15.0,
        Printery pr = Printery(), string g = "Роман", int pg = 300, Author a = Author())
        : PrintProduct(cd, t, y, c, p, pr), genre(g), pages(pg), author(a) {
    }

    string kind() const override { return "Книга"; }
    string getGenre() const { return genre; }
    string getAuthorName() const { return author.getName(); }

    void print(ostream& os) const {
        os << left << setw(18) << code << setw(22) << title << setw(16) << author.getName()
            << setw(12) << genre << setw(6) << year << setw(8) << copies << setw(8) << price << "\n";
    }
};

// Класс Журнал (Наследование)
class Magazine : public PrintProduct {
private:
    int issueNumber;
    string periodicity;
public:
    Magazine(string cd = "", string t = "", int y = 2026, int c = 5000, double p = 5.0,
        Printery pr = Printery(), int issue = 1, string period = "Ежемесячно")
        : PrintProduct(cd, t, y, c, p, pr), issueNumber(issue), periodicity(period) {
    }

    string kind() const override { return "Журнал"; }
    int getIssueNumber() const { return issueNumber; }
    string getPeriodicity() const { return periodicity; }

    void print(ostream& os) const {
        os << left << setw(12) << code << setw(22) << title << setw(8) << issueNumber
            << setw(15) << periodicity << setw(6) << year << setw(8) << copies << setw(8) << price << "\n";
    }
};

// Класс Реализация (Продажа)
class Sale {
public:
    string productCode;
    string customer;
    int quantity;
    double totalSum;

    Sale(string pCode = "", string cust = "", int qty = 0, double sum = 0.0)
        : productCode(pCode), customer(cust), quantity(qty), totalSum(sum) {
    }

    void print(ostream& os) const {
        os << left << setw(15) << productCode << setw(20) << customer
            << setw(10) << quantity << setw(10) << totalSum << "\n";
    }
};