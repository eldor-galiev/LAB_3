#include <iostream>
#include <string.h>

using namespace std;

void console();

void createCountry();
void createCity();

bool isFound();

void printCountries();
void printCities();

void database_query();
void printCountries_with_condition();
void printCities_with_condition();

struct Countries {
  char name[50];
  int area;
  char country[50];
};

struct Cities {
  char name[50];
  int population;
  char country[50];
};

const char *FILE_Countries = "DataBase_Countries.dat";
const char *FILE_Cities = "DataBase_Cities.dat";

int main(){
  console();
  return 0;
}


void console() {
    int num_prog = 10;
    while (num_prog != 0) {
        cout << "Select one of the programs and enter it's number:" << endl;
        cout << "0 - Terminate the program." << endl;
        cout << "1 - Add a new country" << endl;
        cout << "2 - Add a new city." << endl;
        cout << "3 - Search for a queue item." << endl;
        cout << "4 - Print the queue." << endl;
        cout << "5 - Change the queue order according to the task." << endl;

        cout << ">> " << endl;
        cin >> num_prog;

        
    }
}