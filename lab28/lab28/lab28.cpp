// Melissa Ochoa Flores
// COMSC 210
// STL Algorithms

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat>& trip);
void add_goat(list<Goat>& trip, string[], string[]);
void display_trip(list<Goat> trip);
int main_menu();
void sort_goats(list<Goat>& trip);
void find_goat(list<Goat>& trip);
void count_goats_by_age(list<Goat>& trip);
void calculate_average_age(list<Goat>& trip);
void remove_goats_older_than(list<Goat>& trip);
void display_random_order(list<Goat>& trip);
void display_unique_ages(list<Goat>& trip);
void reverse_goats(list<Goat>& trip);


int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }

    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
        case 1:
            cout << "Adding a goat.\n";
            add_goat(trip, names, colors);
            break;
        case 2:
            cout << "Removing a goat.\n";
            delete_goat(trip);
            break;
        case 3:
            cout << "Displaying goat data.\n";
            display_trip(trip);
            break;
        default:
            cout << "Invalid selection.\n";
            break;
        case 4: 
            sort_goats(trip);
            break;
        case 5:
            find_goat(trip);
            break;
        case 6:
            count_goats_by_age(trip);
            break;
        case 7:
            calculate_average_age(trip);
            break;
        case 8:
            remove_goats_older_than(trip);
            break;
        case 9:
            display_random_order(trip);
            break;
        case 10:
            display_unique_ages(trip);
            break;
        }
        sel = main_menu();
    }


    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats by name\n";
    cout << "[5] Find a goat by name\n";
    cout << "[6] Count goats of certain age\n";
    cout << "[7] Calculate average age\n";
    cout << "[8] Remove goats older than certian age\n";
    cout << "[9] Display goats in random order\n";
    cout << "[10] Display specific ages\n";
    cout << "[11] Reverse the order of goats\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat>& trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index - 1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat>& trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt : trp)
        cout << "\t"
        << "[" << i++ << "] "
        << gt.get_name()
        << " (" << gt.get_age()
        << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void sort_goats(list<Goat>& trip) {
    trip.sort();
    cout << "Goats sorted by name" << endl;
}

void find_goat(list<Goat>& trip) {
    string name;
    cout << "Enter the name of goat: ";
    cin >> name;

    auto it = find_if(trip.begin(), trip.end(), [&name](const Goat& g) {return g.get_name() == name; });
    if (it != trip.end()) {
        cout << "Found goat: " << it->get_name() << " (Age: " << it->get_age() << ", Color: " << it->get_color() << ")" << endl;
    }
}

void count_goats_by_age(list<Goat>& trip) {
    int age;
    cout << "Enter age to count: ";
    cin >> age;

    int count = count_if(trip.begin(), trip.end(), [age](const Goat& g) {return g.get_age() == age; });
    cout << "Number of goats aged " << age << ": " << count << endl;

}

void calculate_average_age(list<Goat>& trip) {
    if (trip.empty()) {
        cout << "No goats avaiable to calculate." << endl;
        return;
    }
    double avg_age = accumulate(trip.begin(), trip.end(), 0.0, [](double sum, const Goat& g) {return sum + g.get_age(); }) /trip.size();
    cout << "Average age of goats: " << avg_age << endl;
}

void remove_goats_older_than(list<Goat>& trip) {
    int age;
    cout << "Enter age limit: ";
    cin >> age;

    trip.remove_if([age](const Goat& g) {return g.get_age() > age; });
    cout << "Goats older than " << age << " have been removed" << endl;
}

void display_random_order(list<Goat>& trip) {

}

void display_unique_ages(list<Goat>& trip) {

}