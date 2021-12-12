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
void printCountries_with_condition(string field_1,string field_2,string field_3,string condition[3]);
void printCities_with_condition(string field_1,string field_2,string field_3,string condition[3]);

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
        if (num_prog == 5) {
          database_query();
        }
        
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

void database_query() {
  string field_1, field_2,field_3;
  string DataBase;
  string condition[3];

  cout << "SELECT" << endl;
  cin >> field_1;
  cin >> field_2;
  cin >> field_3;
  cout << "FROM" << endl;
  cin >> DataBase;
  if ((DataBase != "Countries") && (DataBase != "countries") && (DataBase != "Cities") && (DataBase != "cities")) {
    cout << "There is no such database.";
  }
  else {
    cout << "WHERE" << endl;
    for (int i =0; i < 3; i++) {
      cin >> condition[i];
    }
    
    cout << "Database Response:" << endl;
    if ((DataBase == "Countries") || (DataBase == "countries")) {
      printCountries_with_condition(field_1,field_2,field_3,condition);
    }
    /*else {
      printCities_with_condition(field_1,field_2,field_3,condition);
    }*/
  }
  

  
}

void printCountries_with_condition(string field_1,string field_2,string field_3,string condition[3]) {
  FILE *readDateBase = fopen(FILE_Countries,"r");
  if (readDateBase==NULL){
      return;
  }
  struct Countries Buffer[100];
  int i = 0;
  while(fread(&(Buffer[i]), sizeof(Countries), 1, readDateBase)){
    i++;
  }

  if (condition[0] == "Name") {
    if (condition[1] == "=") {
      if ((field_1 == "Name") && (field_2 == "Capital") && (field_3 == "Area")) {
        printf("%8s %10s %12s\n", "Name", "Capital", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%8s %10s %12d\n", Buffer[j].name, Buffer[j].capital, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "Capital") && (field_3 == "-")) {
        printf("%8s %10s\n", "Name", "Capital");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%8s %10s\n", Buffer[j].name, Buffer[j].capital);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "Area") && (field_3 == "-")) {
        printf("%8s %12s\n", "Name", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%8s %12d\n", Buffer[j].name, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "-") && (field_3 == "-")) {
        printf("%8s\n", "Name");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%8s\n", Buffer[j].name);
          }
        }
      }
      if ((field_1 == "Capital") && (field_2 == "Area") && (field_3 == "-")) {
        printf("%8s %12s\n", "Capital", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%10s %12d\n", Buffer[j].capital, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Capital") && (field_2 == "-") && (field_3 == "-")) {
        printf("%10s\n", "Capital");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%10s\n", Buffer[j].capital);
          }
        }
      }
      if ((field_1 == "Area") && (field_2 == "-") && (field_3 == "-")) {
        printf("%12s\n", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%12d\n", Buffer[j].area);
          }
        }
      }
    } 
  }

  if (condition[0] == "Name") {
    if (condition[1] == "=") {
      if ((field_1 == "Name") && (field_2 == "Capital") && (field_3 == "Area")) {
        printf("%8s %10s %12s\n", "Name", "Capital", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%8s %10s %12d\n", Buffer[j].name, Buffer[j].capital, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "Capital") && (field_3 == "-")) {
        printf("%8s %10s\n", "Name", "Capital");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%8s %10s\n", Buffer[j].name, Buffer[j].capital);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "Area") && (field_3 == "-")) {
        printf("%8s %12s\n", "Name", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%8s %12d\n", Buffer[j].name, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "-") && (field_3 == "-")) {
        printf("%8s\n", "Name");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%8s\n", Buffer[j].name);
          }
        }
      }
      if ((field_1 == "Capital") && (field_2 == "Area") && (field_3 == "-")) {
        printf("%8s %12s\n", "Capital", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%10s %12d\n", Buffer[j].capital, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Capital") && (field_2 == "-") && (field_3 == "-")) {
        printf("%10s\n", "Capital");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%10s\n", Buffer[j].capital);
          }
        }
      }
      if ((field_1 == "Area") && (field_2 == "-") && (field_3 == "-")) {
        printf("%12s\n", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].name == condition[2]) {
            printf("%12d\n", Buffer[j].area);
          }
        }
      }
    } 
  }

  if (condition[0] == "Capital") {
    if (condition[1] == "=") {
      if ((field_1 == "Name") && (field_2 == "Capital") && (field_3 == "Area")) {
        printf("%8s %10s %12s\n", "Name", "Capital", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].capital == condition[2]) {
            printf("%8s %10s %12d\n", Buffer[j].name, Buffer[j].capital, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "Capital") && (field_3 == "-")) {
        printf("%8s %10s\n", "Name", "Capital");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].capital == condition[2]) {
            printf("%8s %10s\n", Buffer[j].name, Buffer[j].capital);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "Area") && (field_3 == "-")) {
        printf("%8s %12s\n", "Name", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].capital == condition[2]) {
            printf("%8s %12d\n", Buffer[j].name, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "-") && (field_3 == "-")) {
        printf("%8s\n", "Name");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].capital == condition[2]) {
            printf("%8s\n", Buffer[j].name);
          }
        }
      }
      if ((field_1 == "Capital") && (field_2 == "Area") && (field_3 == "-")) {
        printf("%8s %12s\n", "Capital", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].capital == condition[2]) {
            printf("%10s %12d\n", Buffer[j].capital, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Capital") && (field_2 == "-") && (field_3 == "-")) {
        printf("%10s\n", "Capital");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].capital == condition[2]) {
            printf("%10s\n", Buffer[j].capital);
          }
        }
      }
      if ((field_1 == "Area") && (field_2 == "-") && (field_3 == "-")) {
        printf("%12s\n", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].capital == condition[2]) {
            printf("%12d\n", Buffer[j].area);
          }
        }
      }
    } 
  }
  if (condition[0] == "Area") {
    int area_condition =  stoi(condition[2]);
    if (condition[1] == "=") {
      if ((field_1 == "Name") && (field_2 == "Capital") && (field_3 == "Area")) {
        printf("%8s %10s %12s\n", "Name", "Capital", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].area == area_condition) {
            printf("%8s %10s %12d\n", Buffer[j].name, Buffer[j].capital, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "Capital") && (field_3 == "-")) {
        printf("%8s %10s\n", "Name", "Capital");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].area == area_condition) {
            printf("%8s %10s\n", Buffer[j].name, Buffer[j].capital);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "Area") && (field_3 == "-")) {
        printf("%8s %12s\n", "Name", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].area == area_condition) {
            printf("%8s %12d\n", Buffer[j].name, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Name") && (field_2 == "-") && (field_3 == "-")) {
        printf("%8s\n", "Name");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].area == area_condition) {
            printf("%8s\n", Buffer[j].name);
          }
        }
      }
      if ((field_1 == "Capital") && (field_2 == "Area") && (field_3 == "-")) {
        printf("%8s %12s\n", "Capital", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].area == area_condition) {
            printf("%10s %12d\n", Buffer[j].capital, Buffer[j].area);
          }
        }
      }
      if ((field_1 == "Capital") && (field_2 == "-") && (field_3 == "-")) {
        printf("%10s\n", "Capital");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].area == area_condition) {
            printf("%10s\n", Buffer[j].capital);
          }
        }
      }
      if ((field_1 == "Area") && (field_2 == "-") && (field_3 == "-")) {
        printf("%12s\n", "Area");
        for (int j = 0; j < i; j++) {
          if (Buffer[j].area == area_condition) {
            printf("%12d\n", Buffer[j].area);
          }
        }
      }
    } 
  }
  cout << " " << endl;
}
void printCities_with_condition(string field_1,string field_2,string field_3,string condition[3]);