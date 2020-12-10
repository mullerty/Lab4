#include "Prog4.h"
#include <iostream>

namespace prog4 {

    //**************************************//
    //            Дата и Время              //
    //**************************************//



    //**************************************//
    //              Маршрут                 //
    //**************************************//

    string Route::get_plase_name(int station_num) {
        return stations[station_num].plase_name;
    };
    string Route::get_sight_name(int station_num) {
        return stations[station_num].sight_name;
    };
    int Route::get_start_time(int station_num) {
        return stations[station_num].start_time;
    };
    int Route::get_duration(int station_num) {
        return stations[station_num].duration;
    };

    //**************************************//
    //              Экскурсия               //
    //**************************************//
    
    void Excurtion::show_info() {  // Вывод информации об экскурсии

        cout << "\tHere is information about current excurtion:";
        cout << "\n\t  Excurtion name-> " << excurtion_name;
        cout << "\n\t  Date-> " << date;
        cout << "\n\t  Excurtion duration (days)-> " << exc_length;
        cout << "\n\t  Excurtion price-> " << price;
        cout << "\n\t  Number of plases-> " << max_busy;
        cout << "\n\t  Number of busy plases-> " << busy << endl;

    }; 

    void create_exc_route() {

    }

    //**************************************//
    //               Таблица                //
    //**************************************//

    int Tabl::add_elem(int code, Excurtion* excurtion) {
        Item* ptr = elems[hash(code)];
        if (ptr == nullptr) 
        {
            elems[hash(code)] = new Item;
            elems[hash(code)]->canceled = false;
            elems[hash(code)]->code = code;
            elems[hash(code)]->excurtion = excurtion;
            elems[hash(code)]->next = NULL;
        }
        else 
        {
            Item* pptr = ptr;
            while (pptr != NULL) 
            {
                if (pptr->excurtion->get_date() == excurtion->get_date()) {
                    cout << "\n\tExcurtion on this date already exist!\n";
                    return 1;
                };
                pptr = pptr->next;
            }
            pptr = new Item;
            pptr->canceled = false;
            pptr->code = code;
            pptr->excurtion = excurtion;
            pptr->next = elems[hash(code)];
            elems[hash(code)] = pptr;
        }
        return 0;
    };

    int Tabl::del_elem(int code, int date) {
        Item* ptr = elems[hash(code)];
        if (ptr != nullptr)
        {
            if (ptr->next == NULL) 
            {
                if (ptr->code == code && ptr->excurtion->get_date() == date) {
                    elems[hash(code)] = ptr->next;
                    delete[] ptr;
                    cout << "\n\tExcurtion was succesfully deleted!\n";
                    return 0;
                }
                cout << "\n\tNo excurtion with such date was found!\n";
            }
            else
            {
                Item* pptr = ptr;
                while (pptr != NULL)
                {
                    if (pptr->code == code && pptr->excurtion->get_date() == date) {
                        while (ptr->next != pptr) ptr = ptr->next;
                        ptr->next = pptr->next;
                        delete[] pptr;
                        cout << "\n\tExcurtion was succesfully deleted!\n";
                        return 0;
                    };
                    pptr = pptr->next;
                }
                cout << "\n\tNo excurtion with such date was found!\n";
            }
            
        }
        else 
        {
            cout << "\n\tNo excurtion with such code was found!\n";
            return 1;
        }

        return 1;
    };

    Item* Tabl::find_elem(int code, int date) {
        Item* ptr = elems[hash(code)];
        if (ptr != nullptr)
        {
            Item* pptr = ptr;
            while (pptr != NULL)
            {
                if ((pptr->code == code && pptr->excurtion->get_date() == date)) {
                    cout << "\n\tExcurtion was succesfully found!\n";
                    return pptr;
                };
                pptr = pptr->next;
            }
            cout << "\n\tNo excurtion with such date was found!\n";
        }
        else
        {
            cout << "\n\tNo excurtion with such code was found!\n";
            return NULL;
        }

        return NULL;
    };

    void Tabl::show_tabl() {
        for (int i = 0; i < maxsize; i++) {
            if (elems[i] != nullptr) 
            {
                Item* ptr = elems[i];
                cout << "Excurtions with key " << i << ": \n";
                while (ptr != NULL) 
                {
                    cout << "\tCode-> " << ptr->code<<endl;
                    cout << "\tStatus-> ";
                    if (ptr->canceled) cout << "Canceled\n";
                    else cout << "Active\n";
                    ptr->excurtion->show_info();
                    ptr = ptr->next;
                }
                cout << endl;
            }
        }
        cout << "\n---------------------------------------------------\n";
    };

    //**************************************//
    //         Диалоговые функции           //
    //**************************************//

    void NumInput(int& a) 
    {
        string err = "";
        do
        {
            cout << err;
            cin >> a;
            err = "\n\tError! Wrong number\n";
        } while (a<=0);
    }

    int dialog_AddOneDayRoute(Tabl& tab) 
    {
        string name, pname, sname;
        int date, price, max_busy, stnum, sttime, dur, code;
        cout << "\n!!! Please, replase spaces with '_' !!!";
        cout << "\nTo create an excurtion you should enter next list of data:";
        cout << "\n\tEnter the name of excurtion--> ";
        cin >> name;
        cout << "\n\tEnter the start date of excurtion--> ";
        NumInput(date);
        cout << "\n\tEnter the one place price--> ";
        NumInput(price);
        cout << "\n\tEnter the max number of places on excurtion--> ";
        NumInput(max_busy);

        OneDayRoute* one = new OneDayRoute(name, date, price, max_busy);
        cout << "\n\tEnter the number of stations on this excurtion--> ";
        NumInput(stnum);
        one->set_route_stnum(stnum);
        cout << "Now you should fill route information:\n";
        for (int i = 0; i < stnum; i++) 
        {
            cout << "\nRoute number " << i + 1 << ":";
            cout << "\n\tEnter the place name--> ";
            cin >> pname;
            cout << "\n\tEnter the sight name--> ";
            cin >> sname;
            cout << "\n\tEnter the start time--> ";
            NumInput(sttime);
            cout << "\n\tEnter the duration(in hours)--> ";
            NumInput(dur);
            one->set_route_station(i, pname, sname, sttime, dur);
        }
        cout << "\n\nNow enter the code of excurtion--> ";
        NumInput(code);

        tab.add_elem(code, one);

        return 0;
    }

    int dialog_AddManyDaysRoute(Tabl& tab)
    {
        string name, pname, sname;
        int date, price, max_busy, stnum, sttime, dur, code, exc_length;
        cout << "\n!!! Please, replase spaces with '_' !!!";
        cout << "\nTo create an excurtion you should enter next list of data:";
        cout << "\n\tEnter the name of excurtion--> ";
        cin >> name;
        cout << "\n\tEnter the start date of excurtion--> ";
        NumInput(date);
        cout << "\n\tEnter how long it would be (in days)--> ";
        NumInput(exc_length);
        cout << "\n\tEnter the one place price--> ";
        NumInput(price);
        cout << "\n\tEnter the max number of places on excurtion--> ";
        NumInput(max_busy);

        ManyDaysRoute* many = new ManyDaysRoute(name, date, price, max_busy, exc_length);
        for (int j = 0; j < exc_length; j++) 
        {
            cout << "\n\tEnter the number of stations on " << j + 1 << " day of excurtion--> ";
            NumInput(stnum);
            many->set_route_stnum(j, stnum);
            cout << "Now you should fill route information:\n";
            for (int i = 0; i < stnum; i++)
            {
                cout << "\nRoute number " << i + 1 << ":";
                cout << "\n\tEnter the place name--> ";
                cin >> pname;
                cout << "\n\tEnter the sight name--> ";
                cin >> sname;
                cout << "\n\tEnter the start time--> ";
                NumInput(sttime);
                cout << "\n\tEnter the duration(in hours)--> ";
                NumInput(dur);
                many->set_route_station(j, i, pname, sname, sttime, dur);
            }
        }
        cout << "\n\nNow enter the code of excurtion--> ";
        NumInput(code);

        tab.add_elem(code, many);

        return 0;
    }

    int dialog_CancelExcurtion(Tabl& tab)
    {
        int key, date;
        Item* elem;
        cout << "\nEnter the excurtion code --> ";
        cin >> key;
        cout << "\nEnter the excurtion date --> ";
        cin >> date;
        
        elem = tab.find_elem(key, date);
        if (elem != NULL)
        {
            if (!elem->canceled)
            {
                elem->canceled = true;
                cout << "\n\tExcution was succesfully canceled!\n";
            }
            else cout << "\n\tExcution is already canceled!\n";
        }
        else cout << "\n\tExcurtion wasn't found!\n";

        return 0;
    }

    int dialog_BuyTicket(Tabl& tab)
    {
        int key, date;
        Item* elem;
        cout << "\nEnter the excurtion code --> ";
        cin >> key;
        cout << "\nEnter the excurtion date --> ";
        cin >> date;

        elem = tab.find_elem(key, date);
        if (elem != NULL)
        {
            if (!elem->canceled)
            {
                if (elem->excurtion->get_busy() != elem->excurtion->get_max_busy())
                {
                    elem->excurtion->set_busy(elem->excurtion->get_busy() + 1);
                    cout << "\n\tYou've got plase number "<< elem->excurtion->get_busy()<< " of "<< elem->excurtion->get_max_busy()<< endl;
                    return 0;
                }
                else
                {
                    cout << "\n\tSorry, but all plases are already busy.\n";
                    return 1;
                }
            }
            else
            {
                cout << "\n\tExcution is already canceled!\n";
                return 1;
            }

        }
        else cout << "\n\tExcurtion wasn't found!\n";
        return 1;
    }

    int dialog_RefundTicket(Tabl& tab)
    {
        int key, date;
        Item* elem;
        cout << "\nEnter the excurtion code --> ";
        cin >> key;
        cout << "\nEnter the excurtion date --> ";
        cin >> date;
        
        elem = tab.find_elem(key, date);
        if (elem != NULL)
        {
            if (!elem->canceled)
            {
                if (elem->excurtion->get_busy() != 0)
                {
                    elem->excurtion->set_busy(elem->excurtion->get_busy() - 1);
                    cout << "\n\tYou've succesfully refunded the ticket.\n";
                    return 0;
                }
                else
                {
                    cout << "\n\tSorry, but there are no tickets to refund.\n";
                    return 1;
                }
            }
            else 
            {
                cout << "\n\tExcution is already canceled!\n";
                return 1;
            }
                
        }
        else cout << "\n\tExcurtion wasn't found!\n";

        return 0;
    }

    int dialog_ShowInfo(Tabl& tab)
    {
        tab.show_tabl();
        return 0;
    }

    void display_menu()
    {
        const char* dialog_menu[] = {
            "1. Add one day excurtion",
            "2. Add many days excurtion",
            "3. Cancel an excurtion",
            "4. Buy a ticket on excurtion",
            "5. Refund a ticket on excurtion",
            "6. Show all information",
            "0. Quit",
        };
        for (int i = 0; i < 7; i++)
        {
            std::cout << dialog_menu[i] << std::endl;
        }
    }

    bool get_command(int& a) {
        const char* err = "";
        int n = 0;
        n = 0;
        cout << err;
        //err = ERMSG;
        if (get_num(n, "Enter command --> ")) {
            return false;
        }
        std::cout << endl;
        if (n <= 0 || n > 6)
            return false;
        a = n;
        return true;
    }

    void calc(int num, Tabl& tabl) {
        switch (num) {
        case 1:

            dialog_AddOneDayRoute(tabl);
            break;
        case 2:

            dialog_AddManyDaysRoute(tabl);
            break;
        case 3:

            dialog_CancelExcurtion(tabl);
            break;
        case 4:

            dialog_BuyTicket(tabl);
            break;
        case 5:

            dialog_RefundTicket(tabl);
            break;
        case 6:

            dialog_ShowInfo(tabl);
            break;
        default:
            cout << "Some thing's wrong... I can feel it." << endl;
            break;
        }
    }
}