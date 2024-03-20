#include "base.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;



int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    client_data clients;
    printf("Размер базы данных: ");
    cin >> n;
    cout << "\n";

    clients.generate_base(n);
    clients.print_base();
    //clients.print_base_file("out");
    cout << "next base.........................................................................\n"; cout << "\n\n";

    //clients.getlen();
    clients.delete_cl(3);
    clients.print_base();
    //clients.print_base_file("out");
    cout << "0()next base.........................................................................\n"; cout << "\n\n";

    int arr[3] = { 29,9,2004 };
    int arr1[3] = { 1,1,2000 };
    vector<double> prod = { 95699.55, 120499.99 };
    float avg = (95699.55 + 120499.99) / 2;
    double sum = 95699.55 + 120499.99;
    vector<double> prod1 = { 95699.55, 120499.99,501000.9 };

    //clients.getlen();
    clients.edit_cl(5,"Морозов","Андрей","Александрович",arr,79175294117,prod);
    clients.edit_cl(6, "Жепчанов", "Константин", "Холович", arr, 79175554678, prod);
    clients.edit_cl("Жепчанов", "Константин", "Холович","Штольц","Александр","Владимирович", arr, 79175554678, prod1);
    clients.delete_cl("Жепчанов", "Константин", "Холович"); 
    clients.print_base();

    cout << "1()next base.........................................................................\n"; cout << "\n\n";

    clients.correct();
    clients.sortby_date();
    clients.print_base();
    clients.print_base_file("out");

    cout << "2()next base.........................................................................\n"; cout << "\n\n";

    client_data oldclients;
    oldclients = clients.select_(arr,avg,sum,79175294117);
    oldclients.print_base_file("out2.txt");
    oldclients.print_base();

    cout << "3()next base.........................................................................\n"; //cout << "\n\n";
    cout << "..................................................................................\n"; cout << "\n\n";

    return 0;
}