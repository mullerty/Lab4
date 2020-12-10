#pragma once
#pragma once
#ifndef Prog4_h
#define Prog4_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include "MyVector.h"
#endif /* Prog2_hpp */
using namespace std;
namespace prog4 {

    #define ERMSG "Incorrect input.\n"
    #define INFO "Enter a number --> "
    #define SIZE 74

    template <class T>
    int get_num(T& a, const char* info = INFO, const char* ermsg = ERMSG) {
        cout << info;

        while (!(cin >> a)) {
            if (cin.eof())
                return 1;
            cout << ermsg;
            cout << info;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        return 0;
    }

    //**************************************//
    //            Дата и Время              //
    //**************************************//

    class DateTime {

    };

    //**************************************//
    //               Пункт                  //
    //**************************************//
    
    struct Station {
        string plase_name;
        string sight_name;
        int start_time;
        int duration; // в часах
        
        Station() : plase_name(""), sight_name(""), start_time(0), duration(0) {} // Конструктор пункта по умолчанию
        Station(string plase_name, string sight_name, int start_time, int duration) : 
            plase_name(plase_name), sight_name(sight_name), start_time(start_time), duration(duration) {} // Конструктор пункта
        Station(Station* stations) : plase_name(stations->plase_name), sight_name(stations->sight_name), start_time(stations->start_time), duration(stations->duration) {} // Конструктор пункта
    };

    //**************************************//
    //              Маршрут                 //
    //**************************************//

    class Route {
    private:

        int station_count;
        Station* stations;

    public:
        Route() : station_count(0), stations(nullptr) {} // Конструктор маршрута по умолчанию
        Route(int station_count, Station* stations) : station_count(station_count){
            this->stations = new Station[station_count];
            this->stations = stations;
        } // Конструктор маршрута
        Route(Route* route) : station_count(route->station_count), stations(route->stations) {} // Конструктор маршрута
        
        void set_plase_name(int station_num, string a) 
        {
            stations[station_num].plase_name = a;
        }

        void set_sight_name(int station_num, string a)
        {
            stations[station_num].sight_name = a;
        }

        void set_start_time(int station_num, int a)
        {
            stations[station_num].start_time = a;
        }

        void set_duration(int station_num, int a)
        {
            stations[station_num].duration = a;
        }

        string get_plase_name(int station_num);
        string get_sight_name(int station_num);
        int get_start_time(int station_num);
        int get_duration(int station_num);
    };

    //**************************************//
    ///              Экскурсия               //
    //**************************************//

    class Excurtion {
    private:
        string excurtion_name;
        int date;
        int exc_length;
        int price;
        int max_busy;
        int busy;
    public:
        Excurtion() : excurtion_name(""), date(0), exc_length(0), price(0), max_busy(0), busy(0) {} // Конструктор экскурсии по умолчанию
        Excurtion(string excurtion_name, int date, int exc_length, int price, int max_busy, int busy) : //Конструктор экскурсии
            excurtion_name(excurtion_name), date(date), exc_length(exc_length), price(price), max_busy(max_busy), busy(busy) {}

        
        void set_busy(int busy) // Изменение числа занятых мест
        {
            this->busy = busy;
        }
        void set_date(int date) // Изменение даты начала экскурсии
        {
            this->date = date;
        }
        int get_max_busy() {  // Вывод максимального числа мест
            return max_busy;
        }
        int get_busy() {
            return busy;
        }
        int get_date() {  // Вывод даты начала экскурсии
            return date;
        };
        int get_exc_length() {  // Вывод длительности экскурсии
            return exc_length;
        };
        void show_info(); // Вывод информации об экскурсии
    };

     //**************************************//
    //         Однодневная Экскурсия         //
    //**************************************//

    class OneDayRoute: public Excurtion {
    private:
        Route route;

    public:
        OneDayRoute() : Excurtion(), route(Route()) {} // Конструктор однодневной экскурсии по умолчанию
        OneDayRoute(string excurtion_name, int date, int price, int max_busy) :
            Excurtion(excurtion_name, date, 1, price, max_busy, 0) {}
        
        void set_route_stnum(int a) 
        {
            Station* stations = new Station[a];
            route = Route(a, stations);
        }
        void set_route_station(int stnum, string plase_name, string sight_name, int start_time, int duration) 
        {
            route.set_duration(stnum, duration);
            route.set_plase_name(stnum, plase_name);
            route.set_sight_name(stnum, sight_name);
            route.set_start_time(stnum, start_time);
        }
    };

    //**************************************//
    //      Многодневная Экскурсия          //
    //**************************************//

    class ManyDaysRoute: public Excurtion {
    private:
        Route* routes;

    public:
        ManyDaysRoute() : Excurtion(), routes(nullptr) {} // Конструктор многодневной экскурсии по умолчанию
        ManyDaysRoute(string excurtion_name, int date, int price, int max_busy, int exc_length) :
            Excurtion(excurtion_name, date, exc_length, price, max_busy, 0)
        {
            routes = new Route[exc_length];
        }

        void set_route_stnum(int i, int a)
        {
            Station* stations = new Station[a];
            routes[i] = Route(a, stations);
        }
        void set_route_station(int i, int stnum, string plase_name, string sight_name, int start_time, int duration)
        {
            routes[i].set_duration(stnum, duration);
            routes[i].set_plase_name(stnum, plase_name);
            routes[i].set_sight_name(stnum, sight_name);
            routes[i].set_start_time(stnum, start_time);
        }
    };

    //**************************************//
    //            Элемент таблицы           //
    //**************************************//

    struct Item {
        int code;
        bool canceled;
        Excurtion* excurtion;
        Item* next;
    };

    //**************************************//
    //               Таблица                //
    //**************************************//

    class Tabl {
    private:
        static const int maxsize = 100;
        Myvector<Item*> elems;

        int hash(int key) 
        {
            return (key % maxsize);
        }
    public:
        Tabl() {
            elems.resize(maxsize);
            for (int i = 0; i < maxsize; i++) elems[i] = nullptr;
        }

        int add_elem(int code, Excurtion* excurtion);
        int del_elem(int code, int date);
        Item* find_elem(int code, int date);
        void show_tabl();
    };

    void create_exc_route();
    void cancel_exc();
    void buy_refund_ticket();

    int dialog_AddOneDayRoute(Tabl&);
    int dialog_AddManyDaysRoute(Tabl&);
    int dialog_CancelExcurtion(Tabl&);
    int dialog_BuyTicket(Tabl&);
    int dialog_RefundTicket(Tabl&);
    int dialog_ShowInfo(Tabl&);
    void display_menu();
    bool get_command(int&);
    void calc(int, Tabl&);
};