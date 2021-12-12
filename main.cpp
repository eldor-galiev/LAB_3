#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void console();

void createCountry();
void createCity();

bool isFound(char a[50]);

void printCountries();
void printCities();

void database_query();
void printCountries_with_condition();
void printCities_with_condition();

struct Countries {
  char name[50];
  char capital[50];
  int area;
};

struct Cities {
  char name[50];
  int population;
  char country[50];
};

const char *FILE_Countries = "DataBase_Countries.dat";
const char *FILE_Cities = "DataBase_Cities.dat";

int count_Countries = 0;

int main(){
  console();
  return 0;
}


void console() {
    int num_prog = 10;
    while (num_prog != 0) {
        cout << "Select one of the programs and enter it's number:" << endl;
        cout << "0 - Terminate the program." << endl;
        cout << "1 - Add a new country." << endl;
        cout << "2 - Add a new city." << endl;
        cout << "3 - Print the <Countries> database." << endl;
        cout << "4 - Print the <Cities> database." << endl;
        cout << "5 - Execute a query to the database." << endl;

        cout << " " << endl;
        cout << ">> ";
        cin >> num_prog;
        cout << " " << endl;

        if (num_prog == 1) {
          createCountry();
        }
        if (num_prog == 2) {
          createCity();
        }
        if (num_prog == 3) {
          printCountries();
        }
        if (num_prog == 4) {
          printCities();
        }
        /*if (num_prog == 5) {
          database_query();
        }*/
        
    }
}

void createCountry() {
  Countries *newCountry = new Countries;
    cout << "Input arguments:" << endl;
    cout << "Name of the country >> ";
    cin >> newCountry->name;
    cout << " " << endl;

    cout << "Capital of country  >> ";
    cin >> newCountry -> capital;
    cout << " " << endl;

    cout << "Country area >> ";
    cin >> newCountry -> area;
    cout << " " << endl;

    FILE *Database_Countries = fopen(FILE_Countries, "a");
    if (Database_Countries == NULL) {
      cout << "Error" << endl;
    }
    else {
      fwrite(newCountry, sizeof(Countries), 1, Database_Countries);
    }
    fclose(Database_Countries);
    count_Countries++;
    
}
void createCity() {
  Cities *newCity = new Cities;
    cout << "Input arguments:" << endl;

    cout << "name of the city >> ";
    cin >> newCity->name;
    cout << " " << endl;

    cout << "country >> ";
    cin >> newCity -> country;
    cout << " " << endl;

    if (isFound(newCity -> country)) {

      cout << "population >> ";
      cin >> newCity -> population;
      cout << " " << endl;

      FILE *Database_Cities = fopen(FILE_Cities, "a");
      if (Database_Cities == NULL) {
        cout << "Error" << endl;
      }
      else {
        fwrite(newCity, sizeof(Cities), 1, Database_Cities);
      }
      fclose(Database_Cities);
    }
    else {
      cout << "ERROR" << endl;
      cout << "You can enter the city only of the country that is already in the database." << endl;
      cout << " " << endl;
    }
}

bool isFound(char a[50]) {
  FILE *readDateBase = fopen(FILE_Countries,"r");
  if (readDateBase==NULL){
      return false;
  }
  struct Countries Buffer;
  while(fread(&Buffer, sizeof(Countries), 1, readDateBase)){
      string CNTRY = Buffer.name;
      if (CNTRY == a) {
        return true;
      } 
  }
  return false;
  
}

void printCountries() {
  printf("%8s %10s %12s\n", "Name", "Capital", "Area");
  FILE *readDateBase = fopen(FILE_Countries,"r");
  if (readDateBase==NULL){
      return;
  }
  struct Countries Buffer;
  int i =0;
  while(fread(&Buffer, sizeof(Countries), 1, readDateBase)){
    printf("%8s %10s %12d\n", Buffer.name, Buffer.capital, Buffer.area);
    i++;
  }
  cout << " " << endl;
}
void printCities() {
  printf("%8s %10s %12s\n", "Name", "Country", "Population");
  FILE *readDateBase = fopen(FILE_Cities,"r");
  if (readDateBase==NULL){
      return;
  }
  struct Cities Buffer;
  while(fread(&Buffer, sizeof(Cities), 1, readDateBase)){
    printf("%8s %10s %12d\n", Buffer.name, Buffer.country, Buffer.population);
  }
  cout << " " << endl;
}

void database_query();
void printCountries_with_condition();
void printCities_with_condition();