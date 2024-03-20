#pragma once

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std; 


struct client {
    int id;
    string name;
    string surname;
    string patronymic;
    int arr[3];
    vector<double> prod;
    long long int number;

    client(int _id, const string& _surname, const string& _name, const string& _patronymic, const int _arr[3], const long long int _number, const vector<double> _prod)
        : id(_id), surname(_surname), name(_name), patronymic(_patronymic), number(_number){
        for (int i = 0; i < 3; ++i) {
            arr[i] = _arr[i];
        }
        prod = _prod;
    }
};



class client_data {
private:
    vector<client> clients;
    int id_next;

public:
    //......................................................................................................................................
    //helpful functions
    void getlen() { cout << id_next-1; };

    double sumpr(const client cl) {
        double s = 0;
        for (auto it = cl.prod.begin(); it != cl.prod.end(); it++) {
            s = s + *it; 
        }return s;
    }

    float avgpr(const client cl) {
        float s = 0; int n = 0; float m;
        for (auto it = cl.prod.begin(); it != cl.prod.end(); it++) {
            m = *it;
            s = s + m; n++; 
        }s = s / n;
        return s;
    }

    long int dt(const client cl) {
        int s=0;
        s = (cl.arr[2]) * 10000 + (cl.arr[1] * 100) + cl.arr[0];
        return s;
    }

    void mfiletovector(const string& filename, vector<string>& words) {
        ifstream file(filename);
        string word;
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
    };

    void mfiletovector(const string& filename, vector<double>& words) {
        ifstream file(filename);
        double word;
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
    };

    int let1(int n, const client cl) {
        if (n <= cl.surname.size()) { int s = cl.surname[n]; return s; }
        else return -1000;
    }
    int let2(int n, const client cl) {
        if (n <= cl.name.size()) { int s = cl.name[n]; return s; }
        else return -1000;
    }
    int let3(int n, const client cl) {
        if (n <= cl.patronymic.size()) { int s = cl.patronymic[n]; return s; }
        else return -1000;
    }
    //......................................................................................................................................
    client_data() : id_next(1) {};

    void additself(client_data cl) {
        for (auto it = clients.begin(); it != clients.end(); it++) {
            cl.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
        }
    }
    //......................................................................................................................................
    //editing metods

    void add_cl(const string& surname, const string& name, const string& patronymic, const int arr[3], const long long int number, const vector<double> prod) {
        clients.push_back(client(id_next++, surname, name, patronymic, arr, number, prod));
    }

    
    void delete_cl(int id) {
        int c = 0;
        int m;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->id == id) {
                clients.erase(it);
                id_next--;
                break;
            }
        }
        //cout << "go1\n\n";
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->id > id) {
                m=it->id;
                it->id = m - 1;
            }
        }
    }

    void delete_cl(const string& surname,const string& name,const string& patronymic) {
        vector<int> c;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == name && it->surname == surname && it->patronymic == patronymic) {
                c.push_back(it->id);
            }
        }
        for (auto it = c.begin(); it != c.end(); it++) {
            delete_cl(*it);
        }
    }

    void delete_cl(const string& surname, const string& name, const string& patronymic, const int arr[3], const long long int number, const vector<double> prod) {
        vector<int> c; int n=0;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == name && it->surname == surname && it->patronymic == patronymic && it->arr==arr && it->number == number && it->prod==prod) {
                c.push_back(it->id);
            }
        }
        for (auto it = c.begin(); it != c.end(); it++) {
            delete_cl(*it - n); n++;
        }
    }
    

    void edit_cl(int id, const string& surname, const string& name, const string& patronymic, const int arr[3], const long long int number, const vector<double> prod) {
        for (auto& client : clients) {
            if (client.id == id) {
                client.surname = surname;
                client.name = name;
                client.patronymic = patronymic;
                client.number = number;
                for (int i = 0; i < 3; i++) {
                    client.arr[i] = arr[i];
                }
                    client.prod = prod;
            }
        }
    }

    void edit_cl(string surnames, string names, string patronymics, const string& surname, const string& name, const string& patronymic, const int arr[3], const long long int number, const vector<double> prod) {
        vector<int> c;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == names && it->surname == surnames && it->patronymic == patronymics) {
                c.push_back(it->id);
            }
        }
        for (auto it = c.begin(); it != c.end(); it++) {
            edit_cl(*it, surname, name, patronymic, arr, number, prod);
        }
    }

    void edit_cl(string surnames, string names, string patronymics, const int arr1[3], const long long int number1, const vector<double> prod1, const string& surname, const string& name, const string& patronymic, const int arr[3], const long long int number, const vector<double> prod) {
        vector<int> c;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == name && it->surname == surname && it->patronymic == patronymic && it->arr == arr1 && it->number == number1 && it->prod == prod1) {
                c.push_back(it->id);
            }
        }
        for (auto it = c.begin(); it != c.end(); it++) {
            edit_cl(*it, surname, name, patronymic, arr, number, prod);
        }
    }
    
    //......................................................................................................................................
    //printing methods
    void print_base() {
        for (auto& client : clients) {
            cout << client.surname << " " << client.name << " " << client.patronymic << " ";
            for (int i = 0; i < 3; i++) {
                cout << client.arr[i] << ".";
            }
            cout << " \n" << client.number << " "<< client.id << "\n";
            for (auto it = client.prod.begin(); it != client.prod.end(); it++) {
                cout << *it << " ";
            };
            cout << setprecision(10) << "\n (sum: " << sumpr(client) << "  avg spent:" << avgpr(client) << ")";
            cout << endl << endl;
        }
    };

    void print_base_file(const string& filename) {
        ofstream file(filename);
        for (auto& client : clients) {
            file << client.surname << " " << client.name << " " << client.patronymic << " ";
            for (int i = 0; i < 3; i++) {
                file << client.arr[i] << ".";
            }
            file << " \n" << client.number<<"\n";
            for (auto it = client.prod.begin(); it != client.prod.end(); it++) {
                 file << *it << " ";
            };
            file << setprecision(10) << "\n (sum: " << sumpr(client) << "  avg spent:" << avgpr(client) << ")";
            file << endl << endl;
        }
        file.close();
    }

    //......................................................................................................................................
    //sorting junk
    int partitionnum(int start, int end)
    {

        client pivot = clients[start];
        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (clients[i].number <= pivot.number)
                count++;
        }
        int pivotIndex = start + count;
        swap(clients[pivotIndex], clients[start]);
        swap(clients[pivotIndex].id, clients[start].id);

        int i = start, j = end;


        while (i < pivotIndex && j > pivotIndex) {

            while (clients[i].number <= pivot.number) {
                i++;
            }

            while (clients[j].number > pivot.number) {
                j--;
            }

            if (i < pivotIndex && j > pivotIndex) {
                swap(clients[i++], clients[j--]);
                swap(clients[i-1].id, clients[j+1].id);
            }
        }

        return pivotIndex;
    }

    void quickSortnum(int start, int end)
    {
        if (start >= end)
            return;
        int p = partitionnum(start, end);
        quickSortnum(start, p - 1);
        quickSortnum(p + 1, end);
    }

    int partitionsum(int start, int end)
    {

        client pivot = clients[start];
        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (sumpr(clients[i]) <= sumpr(pivot))
                count++;
        }
        int pivotIndex = start + count;
        swap(clients[pivotIndex], clients[start]);
        swap(clients[pivotIndex].id, clients[start].id);

        int i = start, j = end;


        while (i < pivotIndex && j > pivotIndex) {

            while (sumpr(clients[i]) <= sumpr(pivot)) {
                i++;
            }

            while (sumpr(clients[j]) > sumpr(pivot)) {
                j--;
            }

            if (i < pivotIndex && j > pivotIndex) {
                swap(clients[i++], clients[j--]);
                swap(clients[i-1].id, clients[j+1].id);
            }
        }

        return pivotIndex;
    }

    void quickSortsum(int start, int end)
    {
        if (start >= end)
            return;
        int p = partitionsum(start, end);
        quickSortsum(start, p - 1);
        quickSortsum(p + 1, end);
    }

    int partitionavg(int start, int end)
    {

        client pivot = clients[start];
        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (avgpr(clients[i]) <= avgpr(pivot))
                count++;
        }
        int pivotIndex = start + count;
        swap(clients[pivotIndex], clients[start]);
        swap(clients[pivotIndex].id, clients[start].id);

        int i = start, j = end;


        while (i < pivotIndex && j > pivotIndex) {

            while (avgpr(clients[i]) <= avgpr(pivot)) {
                i++;
            }

            while (avgpr(clients[j]) > avgpr(pivot)) {
                j--;
            }

            if (i < pivotIndex && j > pivotIndex) {
                swap(clients[i++], clients[j--]);
                swap(clients[i-1].id, clients[j+1].id);
            }
        }

        return pivotIndex;
    }

    void quickSortavg(int start, int end)
    {
        if (start >= end)
            return;
        int p = partitionavg(start, end);
        quickSortavg(start, p - 1);
        quickSortavg(p + 1, end);
    }

    int partitiondate(int start, int end)
    {

        client pivot = clients[start];
        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (dt(clients[i]) <= dt(pivot))
                count++;
        }
        int pivotIndex = start + count;
        swap(clients[pivotIndex], clients[start]);
        swap(clients[pivotIndex].id, clients[start].id);

        int i = start, j = end;


        while (i < pivotIndex && j > pivotIndex) {

            while (dt(clients[i]) <= dt(pivot)) {
                i++;
            }

            while (dt(clients[j]) > dt(pivot)) {
                j--;
            }

            if (i < pivotIndex && j > pivotIndex) {
                swap(clients[i++], clients[j--]);
                swap(clients[i-1].id, clients[j+1].id);
            }
        }

        return pivotIndex;
    }

    void quickSortdate(int start, int end)
    {
        if (start >= end)
            return;
        int p = partitiondate(start, end);
        quickSortdate(start, p - 1);
        quickSortdate(p + 1, end);
    }

    //......................................................................................................................................
    //sorting metods

    /*void sortby_alph() {
       sort(clients.begin(), clients.end(),
           [](const client& x, const client& y) {
           if (x.surname != y.surname) {
               return x.surname < y.surname;
           }
           else {
               if (x.name != y.name) {
                   return x.name < y.name;
               }
               else {
                   return x.patronymic < y.patronymic;
               }
           }
           });
    };*/

    void sortby_date() {
        quickSortdate(0, id_next - 2);
    };
    
    void sortby_spendings() {
        quickSortsum(0, id_next - 2);
    };

    void sortby_avgspent() {
        quickSortavg(0, id_next - 2);
    };

    void sortby_number() {
        quickSortnum(0, id_next - 2);
    };
    
    //.....................................................................................................................................
    //selection methods

    client_data select_(string surname, string name, string patronymic) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == name && it->surname == surname && it->patronymic == patronymic) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    client_data select_(string surname, string name, string patronymic, int* arr,long long int num, vector<double> prod) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->name == name && it->surname == surname && it->patronymic == patronymic && it->arr==arr && it->number==num && it->prod==prod) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    client_data select_(vector<double> prod) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->prod == prod) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }
   
    client_data select_(int* arr1,int* arr2) {
        int d1 = (arr1[2] * 10000) + (arr1[1] * 100) + arr1[0];
        int d2 = (arr2[2] * 10000) + (arr2[1] * 100) + arr2[0];
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            //cout << "(" << d1 << ") ";
            if (dt(*it) >= d1 && dt(*it) <= d2) {
                out.add_cl(it->surname,it->name,it->patronymic,it->arr,it->number,it->prod);
            }
        }
        return out;
    }

    client_data select_(int* d1) {
        return select_(d1, d1);
    }

    client_data select_(float d1, float d2) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            //cout << "(" << avgpr(*it) << ") ";
            if (avgpr(*it) > d1 && avgpr(*it) < d2) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    client_data select_(float d1) {
        return select_(d1-1, d1+1);
    }

    client_data select_(double d1, double d2) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            //cout << "(" << avgpr(*it) << ") ";
            if (sumpr(*it) > d1 && sumpr(*it) < d2) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    client_data select_(double d1) {
        return select_(d1-1, d1+1);
    }

    client_data select_(long long int d1,long long int d2) {
        client_data out;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            //cout << "(" << it->number << ") ";
            if (it->number >= d1 && it->number <= d2) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
            }
        }
        return out;
    }

    client_data select_(long long int d1) {
        return select_(d1, d1);
    }

    client_data select_(int* arr1, int* arr2, float d1, float d2, double d3, double d4, long long int d5, long long int d6) {
        client_data out = select_(arr1, arr2);
        out = out.select_(d1, d2);
        out = out.select_(d3, d4);
        out = out.select_(d5, d6);
        return out;
    }

    client_data select_(string surname, string name, string patronymic,int* arr1, float d1, double d3, long long int d6) {
        client_data out = select_(arr1); //out.print_base(); //cout << "\n000\n";
        out = out.select_(d1-1,d1+1); //out.print_base();// cout << "\n111\n";
        out = out.select_(d3-1,d3+1); ///out.print_base();// cout << "\n111\n";
        out = out.select_(d6); //out.print_base();// cout << "\n111\n";
        out = out.select_(surname, name, patronymic);
        return out;
    }

    client_data select_( int* arr1, float d1, double d3, long long int d6) {
        client_data out = select_(arr1); //out.print_base(); //cout << "\n000\n";
        out = out.select_(d1 - 1, d1 + 1); //out.print_base(); //cout << "\n111\n";
        out = out.select_(d3 - 1, d3 + 1); //out.print_base(); //cout << "\n111\n";
        out = out.select_(d6); //out.print_base(); //cout << "\n111\n";
        return out;
    }


    //......................................................................................................................................
    //correctness

    client_data correct() {
        client_data out; vector<int> f;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (dt(*it) < 20000101 || dt(*it) >= 20240701) {
                out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
                f.push_back(it->id);
            }
            else {
                long long int m = it->number;
                if (m < 74950000000 || ((m > 74959999999 && m < 74990000000)) || ((m > 74999999999) && (m < 79160000000)) || ((m > 79179999999) && (m < 79250000000)) || ((m > 79269999999) && (m < 79680000000)) || ((m > 79689999999) && (m < 79770000000)) || ((m > 79779999999) && (m < 7985000000)) ||
                    ((m > 79859999999) && (m < 84950000000)) || ((m > 84959999999 && m < 84990000000)) || ((m > 84999999999) && (m < 89160000000)) || ((m > 89179999999) && (m < 89250000000)) || ((m > 89269999999) && (m < 89680000000)) || ((m > 89689999999) && (m < 89770000000)) || ((m > 89779999999) && (m < 8985000000)) || m>89859999999) {
                    out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
                    f.push_back(it->id);
                }
                else {
                    for (auto it1 = it->prod.begin(); it1 != it->prod.end(); it1++) {
                        if (*it1 < 20000 || *it1>500000) {
                            out.add_cl(it->surname, it->name, it->patronymic, it->arr, it->number, it->prod);
                            f.push_back(it->id);
                            break;
                        }
                    }
                }
            }
        }
        int n=0; sort(f.begin(), f.end());
        for (auto it = f.begin(); it != f.end(); it++) {
            delete_cl(*it - n); n++;
        }
        return out;
    }


    //......................................................................................................................................
    //data generator

    void generate_base(int n) {
        setlocale(LC_ALL, "Russian");
        srand(time(0));
        long long int value = 0;

        vector<string> name_male;
        vector<string> surname_male;
        vector<string> sec_name_male;
        vector<string> name_fem;
        vector<string> surname_fem;
        vector<string> sec_name_fem;

        //vector<double> prod1;

        mfiletovector("namem.txt", name_male);
        mfiletovector("surnamem.txt", surname_male);
        mfiletovector("2namem.txt", sec_name_male);
        mfiletovector("namef.txt", name_fem);
        mfiletovector("surnamef.txt", surname_fem);
        mfiletovector("2namef.txt", sec_name_fem);
        //mfiletovector("costs.txt",prod1);

        for (int i = 0; i < n; i++) {
            int month = rand() % 12 +1;
            int day = rand();
            int year = rand() % 24 + 2000;
            int arr[3]; //cout << "(" << month << ") ";

            int numprod = rand() % 20 + 1;
            double cost,cost1 ;

            vector<double> prod = { };
            for (int c = 0; c < numprod; c++) {
                cost = rand() % 48000; cost = cost * 10;
                cost1 = rand() % 1000; cost1 = cost1 / 100;
                cost = cost + cost1 +20000;
                prod.push_back(cost);
            }

            if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                arr[0] = day % 31 + 1; arr[1] = month; arr[2] = year;
            }
            if (month == 4 || month == 6 || month == 9 || month == 11) {
                arr[0] = day % 30 + 1; arr[1] = month; arr[2] = year;
            }
            if (month == 2 && year % 4 == 0) {
                arr[0] = day % 29 + 1; arr[1] = month; arr[2] = year;
            };
            if (month == 2 && year % 4 != 0) {
                arr[0] = day % 28 + 1; arr[1] = month; arr[2] = year;
            };

            const long long int c = rand() % 10 + (rand() % 10) * 10 + (rand() % 10) * 100 + (rand() % 10) * 100 + (rand() % 10) * 1000 + (rand() % 10) * 10000 + (rand() % 10) * 100000 + (rand() % 10) * 1000000;
            const int m = rand() % 9; //cout << " (" << m << ") \n"; 
            value = 0;
            if (m == 0) { value = 74950000000 + c; }
            if (m == 1) { value = 74990000000 + c; }
            if (m == 2) { value = 79160000000 + c; }
            if (m == 3) { value = 79170000000 + c; }
            if (m == 4) { value = 79250000000 + c; }
            if (m == 5) { value = 79260000000 + c; }
            if (m == 6) { value = 79850000000 + c; }
            if (m == 7) { value = 79770000000 + c; }
            if (m == 8) { value = 79680000000 + c; }
            //cout << " (" << value << ") \n";

            if (rand() % 2 == 0) {

                add_cl(surname_male[rand() % surname_male.size()], name_male[rand() % name_male.size()],
                    sec_name_male[rand() % sec_name_male.size()], arr, value,prod);
            }
            else {
                add_cl(surname_fem[rand() % surname_fem.size()], name_fem[rand() % name_fem.size()],
                    sec_name_fem[rand() % sec_name_fem.size()], arr, value,prod);
            }
        };
        //......................................................................................................................................
        //......................................................................................................................................
    };

}; 