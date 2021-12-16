#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

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

int count_Countries = 0;

const char *FILE_Countries = "DataBase_Countries.dat";
const char *FILE_Cities = "DataBase_Cities.dat";

void console();

void createCountry();
void createCity();

bool isFound(char a[50]);

void printCountries();
void printCities();

void database_query();
void requestDataBase_Countries(string field_1,string field_2,string field_3,string condition[3]);
void requestDataBase_Cities(string field_1,string field_2,string field_3,string condition[3]);

void printCountries_with_condition(string field_1,string field_2,string field_3, Countries Buffer[100], int i);
void printCities_with_condition(string field_1,string field_2,string field_3, Cities Buffer[100], int i);

void sorting_request();

void sortingCountries_name(Countries Buffer[100], int left, int right);
void sortingCountries_capital(Countries Buffer[100], int left, int right);
void sortingCountries_area(Countries Buffer[100], int left, int right);

void sortingCities_name(Cities Buffer[100], int left, int right);
void sortingCities_country(Cities Buffer[100], int left, int right);
void sortingCities_population(Cities Buffer[100], int left, int right);

int main() {
    console();
    return 0;
}


void console() {
    int num_prog = 12;
    while (num_prog != 0) {
        cout << "Select one of the programs and enter it's number:" << endl;
        cout << "0 - Terminate the program." << endl;
        cout << "1 - Add a new country." << endl;
        cout << "2 - Add a new city." << endl;
        cout << "3 - Print the <Countries> database." << endl;
        cout << "4 - Print the <Cities> database." << endl;
        cout << "5 - Execute a query to the database." << endl;
        cout << "6 - Sort by the specified field." << endl;

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
        if (num_prog == 6) {
            sorting_request();
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
    FILE *readDateBase = fopen(FILE_Countries,"r");
    if (readDateBase==NULL){
        cout << "The database is empty." << endl;
        cout << " " << endl;
        return;
    }
    printf("%12s %12s %12s\n", "Name", "Capital", "Area");
    struct Countries Buffer;
    int i =0;
    while(fread(&Buffer, sizeof(Countries), 1, readDateBase)){
        printf("%12s %12s %12d\n", Buffer.name, Buffer.capital, Buffer.area);
        i++;
    }
    cout << " " << endl;
}
void printCities() {
    FILE *readDateBase = fopen(FILE_Cities,"r");
    if (readDateBase==NULL){
        cout << "The database is empty." << endl;
        cout << " " << endl;
        return;
    }
    printf("%12s %12s %12s\n", "Name", "Country", "Population");
    struct Cities Buffer;
    while(fread(&Buffer, sizeof(Cities), 1, readDateBase)){
        printf("%12s %12s %12d\n", Buffer.name, Buffer.country, Buffer.population);
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
        cout << " " << endl;

        cout << "Database Response:" << endl;
        if ((DataBase == "Countries") || (DataBase == "countries")) {
            requestDataBase_Countries(field_1,field_2,field_3,condition);
        }
        else {
            requestDataBase_Cities(field_1,field_2,field_3,condition);
        }
    }
}

void requestDataBase_Countries(string field_1,string field_2,string field_3,string condition[3]) {
    FILE *readDateBase = fopen(FILE_Countries, "r");
    if (readDateBase == NULL) {
        return;
    }
    struct Countries All_Countries[100];
    struct Countries Buffer[100];

    int i = 0;
    while (fread(&(All_Countries[i]), sizeof(Countries), 1, readDateBase)) {
        i++;
    }
    int k = 0;
    for (int j = 0; j < i; j++) {
        if (condition[0] == "Name") {
            if(All_Countries[j].name == condition[2]) {
                Buffer[k] = All_Countries[j];
                k++;
            }
        }
        if (condition[0] == "Capital") {
            if(All_Countries[j].capital == condition[2]) {
                Buffer[k] = All_Countries[j];
                k++;
            }
        }
        if (condition[0] == "Area") {
            int area_condition = stoi(condition[2]);
            if (condition[1] == "=") {
                if(All_Countries[j].area == area_condition) {
                    Buffer[k] = All_Countries[j];
                    k++;
                }
            }
            if (condition[1] == ">") {
                if(All_Countries[j].area > area_condition) {
                    Buffer[k] = All_Countries[j];
                    k++;
                }
            }
            if (condition[1] == "<") {
                if(All_Countries[j].area < area_condition) {
                    Buffer[k] = All_Countries[j];
                    k++;
                }
            }
            if (condition[1] == ">=") {
                if(All_Countries[j].area >= area_condition) {
                    Buffer[k] = All_Countries[j];
                    k++;
                }
            }
            if (condition[1] == "<=") {
                if(All_Countries[j].area <= area_condition) {
                    Buffer[k] = All_Countries[j];
                    k++;
                }
            }
        }
    }
    printCountries_with_condition(field_1, field_2, field_3, Buffer, k);
}

void printCountries_with_condition(string field_1,string field_2,string field_3, Countries Buffer[100], int i) {
    if (i == 0) {
        return;
      }
    if ((field_1 == "Name") && (field_2 == "Capital") && (field_3 == "Area")) {
        printf("%12s %12s %12s\n", "Name", "Capital", "Area");
        for (int j = 0; j < i; j++) {
            printf("%12s %12s %12d\n", Buffer[j].name, Buffer[j].capital, Buffer[j].area);
        }
    }
    if ((field_1 == "Name") && (field_2 == "Capital") && (field_3 == "-")) {
        printf("%12s %12s\n", "Name", "Capital");
        for (int j = 0; j < i; j++) {
            printf("%12s %12s\n", Buffer[j].name, Buffer[j].capital);
        }
    }
    if ((field_1 == "Name") && (field_2 == "Area") && (field_3 == "-")) {
        printf("%12s %12s\n", "Name", "Area");
        for (int j = 0; j < i; j++) {
            printf("%12s %12d\n", Buffer[j].name, Buffer[j].area);
        }
    }
    if ((field_1 == "Name") && (field_2 == "-") && (field_3 == "-")) {
        printf("%12s\n", "Name");
        for (int j = 0; j < i; j++) {
            printf("%12s\n", Buffer[j].name);
        }
    }
    if ((field_1 == "Capital") && (field_2 == "Area") && (field_3 == "-")) {
        printf("%12s %12s\n", "Capital", "Area");
        for (int j = 0; j < i; j++) {
            printf("%12s %12d\n", Buffer[j].capital, Buffer[j].area);
        }
    }
    if ((field_1 == "Capital") && (field_2 == "-") && (field_3 == "-")) {
        printf("%12s\n", "Capital");
        for (int j = 0; j < i; j++) {
            printf("%12s\n", Buffer[j].capital);
        }
    }
    if ((field_1 == "Area") && (field_2 == "-") && (field_3 == "-")) {
        printf("%12s\n", "Area");
        for (int j = 0; j < i; j++) {
            printf("%12d\n", Buffer[j].area);
        }
    }
    cout << " " << endl;
}

void requestDataBase_Cities(string field_1,string field_2,string field_3,string condition[3]) {
    FILE *readDateBase = fopen(FILE_Cities, "r");
    if (readDateBase == NULL) {
        return;
    }
    struct Cities All_Cities[100];
    struct Cities Buffer[100];

    int i = 0;
    while (fread(&(All_Cities[i]), sizeof(Cities), 1, readDateBase)) {
        i++;
    }
    int k = 0;
    for (int j = 0; j < i; j++) {
        if (condition[0] == "Name") {
            if(All_Cities[j].name == condition[2]) {
                Buffer[k] = All_Cities[j];
                k++;
            }
        }
        if (condition[0] == "Country") {
            if(All_Cities[j].country == condition[2]) {
                Buffer[k] = All_Cities[j];
                k++;
            }
        }
        if (condition[0] == "Population") {
            int population_condition = stoi(condition[2]);
            if (condition[1] == "=") {
                if(All_Cities[j].population == population_condition) {
                    Buffer[k] = All_Cities[j];
                    k++;
                }
            }
            if (condition[1] == ">") {
                if(All_Cities[j].population > population_condition) {
                    Buffer[k] = All_Cities[j];
                    k++;
                }
            }
            if (condition[1] == "<") {
                if(All_Cities[j].population < population_condition) {
                    Buffer[k] = All_Cities[j];
                    k++;
                }
            }
            if (condition[1] == ">=") {
                if(All_Cities[j].population >= population_condition) {
                    Buffer[k] = All_Cities[j];
                    k++;
                }
            }
            if (condition[1] == "<=") {
                if(All_Cities[j].population <= population_condition) {
                    Buffer[k] = All_Cities[j];
                    k++;
                }
            }
        }
    }
    printCities_with_condition(field_1, field_2, field_3, Buffer, k);
}

void printCities_with_condition(string field_1,string field_2,string field_3, Cities Buffer[100], int i) {
    if (i == 0) {
      return;
    }
    if ((field_1 == "Name") && (field_2 == "Country") && (field_3 == "Population")) {
        printf("%12s %12s %12s\n", "Name", "Country", "Population");
        for (int j = 0; j < i; j++) {
            printf("%12s %12s %12d\n", Buffer[j].name, Buffer[j].country, Buffer[j].population);
        }
    }
    if ((field_1 == "Name") && (field_2 == "Country") && (field_3 == "-")) {
        printf("%12s %12s\n", "Name", "Country");
        for (int j = 0; j < i; j++) {
            printf("%12s %12s\n", Buffer[j].name, Buffer[j].country);
        }
    }
    if ((field_1 == "Name") && (field_2 == "Population") && (field_3 == "-")) {
        printf("%12s %12s\n", "Name", "Population");
        for (int j = 0; j < i; j++) {
            printf("%12s %12d\n", Buffer[j].name, Buffer[j].population);
        }
    }
    if ((field_1 == "Name") && (field_2 == "-") && (field_3 == "-")) {
        printf("%12s\n", "Name");
        for (int j = 0; j < i; j++) {
            printf("%12s\n", Buffer[j].name);
        }
    }
    if ((field_1 == "Country") && (field_2 == "Population") && (field_3 == "-")) {
        printf("%12s %12s\n", "Country", "Population");
        for (int j = 0; j < i; j++) {
            printf("%12s %12d\n", Buffer[j].country, Buffer[j].population);
        }
    }
    if ((field_1 == "Country") && (field_2 == "-") && (field_3 == "-")) {
        printf("%12s\n", "Country");
        for (int j = 0; j < i; j++) {
            printf("%12s\n", Buffer[j].country);
        }
    }
    if ((field_1 == "Population") && (field_2 == "-") && (field_3 == "-")) {
        printf("%12s\n", "Population");
        for (int j = 0; j < i; j++) {
            printf("%12d\n", Buffer[j].population);
        }
    }
    cout << " " << endl;
}

void sorting_request() {
    string field_1, field_2,field_3;
    string DataBase;
    string condition_field;
    int limit;

    cout << "SELECT" << endl;
    cin >> field_1;
    if ((field_1 == "-") || ((field_1 != "Name") && (field_1 != "Capital") && (field_1 != "Area") && (field_1 != "Country") && (field_1 != "Population"))) {
      cout << "ERROR" << endl;
      cout << "There is no such field" << endl;
      return;
    }
    cin >> field_2;
    if ((field_2 == "Name") || (field_1 == field_2) || ((field_2 != "-") && (field_2 != "Capital") && (field_2 != "Area") && (field_2 != "Country") && (field_2 != "Population"))) {
      cout << "ERROR" << endl;
      cout << "There is no such field" << endl;
      return;
    }
    cin >> field_3;
    if ((field_3 != "-") && (field_3!= "Area") && (field_3 != "Population")) {
      cout << "ERROR" << endl;
      cout << "There is no such field" << endl;
      return;
    }
    cout << "FROM" << endl;
    cin >> DataBase;
    if ((DataBase != "Countries") && (DataBase != "countries") && (DataBase != "Cities") && (DataBase != "cities")) {
        cout << "There is no such database.";
    }
    else {
        cout << "ORDER BY" << endl;
        cin >> condition_field;
        if ((condition_field != "Name") && (condition_field != "Capital") && (condition_field != "Area")) {
          cout << "ERROR" << endl;
          cout << "There is no such field" << endl;
          return;
        }
        cout << "LIMIT" << endl;
        cin >> limit;
        cout << " " << endl;

        cout << "Database Response:" << endl;
        if ((DataBase == "Countries") || (DataBase == "countries")) {
            FILE *readDateBase = fopen(FILE_Countries, "r");
            if (readDateBase == NULL) {
                return;
            }
            struct Countries Buffer[100];
            int count_countries = 0;
            int i = 0;
            while (fread(&(Buffer[i]), sizeof(Countries), 1, readDateBase)) {
                i++;
            }

            if (condition_field == "Name") {
                sortingCountries_name(Buffer, 0, i-1);
                printCountries_with_condition(field_1, field_2, field_3, Buffer, limit);
            }
            if (condition_field == "Capital") {
                sortingCountries_capital(Buffer, 0, i-1);
                printCountries_with_condition(field_1, field_2, field_3, Buffer, limit);
            }
            if (condition_field == "Area") {
                sortingCountries_area(Buffer, 0, i-1);
                printCountries_with_condition(field_1, field_2, field_3, Buffer, limit);
            }
        }
        else {
            FILE *readDateBase = fopen(FILE_Cities, "r");
            if (readDateBase == NULL) {
                return;
            }
            struct Cities Buffer[100];
            int i = 0;
            while (fread(&(Buffer[i]), sizeof(Cities), 1, readDateBase)) {
                i++;
            }

            if (condition_field == "Name") {
                sortingCities_name(Buffer, 0, i-1);
                printCities_with_condition(field_1, field_2, field_3, Buffer, limit);
            }
            if (condition_field == "Country") {
                sortingCities_country(Buffer, 0, i-1);
                printCities_with_condition(field_1, field_2, field_3, Buffer, limit);
            }
            if (condition_field == "Population") {
                sortingCities_population(Buffer, 0, i-1);
                printCities_with_condition(field_1, field_2, field_3, Buffer, limit);
            }

        }
    }
        
}


void sortingCountries_name(Countries Buffer[100], int left, int right) {
    Countries All_Countries[100];
    for (int k = 0; k < 100; k++) {
        All_Countries[k] = Buffer[k];
    }
    Countries pivot; 
    int l_hold = left; 
    int r_hold = right; 
    pivot = All_Countries[left];
    while (left < right) 
    {
        while (((All_Countries[right].name)[0] >= (pivot.name)[0]) && (left < right))
            right--; 
        if (left != right) 
        {
            All_Countries[left] = All_Countries[right]; 
            left++; 
        }
        while (((All_Countries[left].name)[0] <= (pivot.name)[0]) && (left < right))
            left++; 
        if (left != right) 
        {
            All_Countries[right] = All_Countries[left]; 
            right--; 
        }
    }
    All_Countries[left] = pivot; 
    int count = left;
    left = l_hold;
    right = r_hold;
    for (int k = 0; k < 100; k++) {
        Buffer[k] = All_Countries[k];
    }
    if (left < count) 
        sortingCountries_name(Buffer, left, count - 1);
    if (right > count)
        sortingCountries_name(Buffer, count + 1, right);
}

void sortingCountries_capital(Countries Buffer[100], int left, int right) {
    Countries All_Countries[100];
    for (int k = 0; k < 100; k++) {
        All_Countries[k] = Buffer[k];
    }
    Countries pivot; 
    int l_hold = left; 
    int r_hold = right; 
    pivot = All_Countries[left];
    while (left < right) 
    {
        while (((All_Countries[right].capital)[0] >= (pivot.capital)[0]) && (left < right))
            right--; 
        if (left != right) 
        {
            All_Countries[left] = All_Countries[right]; 
            left++; 
        }
        while (((All_Countries[left].capital)[0] <= (pivot.capital)[0]) && (left < right))
            left++; 
        if (left != right) 
        {
            All_Countries[right] = All_Countries[left]; 
            right--; 
        }
    }
    All_Countries[left] = pivot; 
    int count = left;
    left = l_hold;
    right = r_hold;
    for (int k = 0; k < 100; k++) {
        Buffer[k] = All_Countries[k];
    }
    if (left < count) 
        sortingCountries_name(Buffer, left, count - 1);
    if (right > count)
        sortingCountries_name(Buffer, count + 1, right);
}
void sortingCountries_area(Countries Buffer[100], int left, int right) {
    Countries All_Countries[100];
    for (int k = 0; k < 100; k++) {
        All_Countries[k] = Buffer[k];
    }
    Countries pivot; 
    int l_hold = left; 
    int r_hold = right; 
    pivot = All_Countries[left];
    while (left < right) 
    {
        while ((All_Countries[right].area >= pivot.area) && (left < right))
            right--; 
        if (left != right) 
        {
            All_Countries[left] = All_Countries[right]; 
            left++; 
        }
        while ((All_Countries[left].area <= pivot.area) && (left < right))
            left++; 
        if (left != right) 
        {
            All_Countries[right] = All_Countries[left]; 
            right--; 
        }
    }
    All_Countries[left] = pivot; 
    int count = left;
    left = l_hold;
    right = r_hold;
    for (int k = 0; k < 100; k++) {
        Buffer[k] = All_Countries[k];
    }
    if (left < count) 
        sortingCountries_area(Buffer, left, count - 1);
    if (right > count)
        sortingCountries_area(Buffer, count + 1, right);
}

void sortingCities_name(Cities Buffer[100], int left, int right) {
    Cities All_Cities[100];
    for (int k = 0; k < 100; k++) {
        All_Cities[k] = Buffer[k];
    }
    Cities pivot;
    int l_hold = left;
    int r_hold = right;
    pivot = All_Cities[left];
    while (left < right)
    {
        while (((All_Cities[right].name)[0] >= (pivot.name)[0]) && (left < right))
            right--;
        if (left != right)
        {
            All_Cities[left] = All_Cities[right];
            left++;
        }
        while (((All_Cities[left].name)[0] <= (pivot.name)[0]) && (left < right))
            left++;
        if (left != right)
        {
            All_Cities[right] = All_Cities[left];
            right--;
        }
    }
    All_Cities[left] = pivot;
    int count = left;
    left = l_hold;
    right = r_hold;
    for (int k = 0; k < 100; k++) {
        Buffer[k] = All_Cities[k];
    }
    if (left < count)
        sortingCities_name(Buffer, left, count - 1);
    if (right > count)
        sortingCities_name(Buffer, count + 1, right);
}

void sortingCities_country(Cities Buffer[100], int left, int right) {
    Cities All_Cities[100];
    for (int k = 0; k < 100; k++) {
        All_Cities[k] = Buffer[k];
    }
    Cities pivot;
    int l_hold = left;
    int r_hold = right;
    pivot = All_Cities[left];
    while (left < right)
    {
        while (((All_Cities[right].country)[0] >= (pivot.country)[0]) && (left < right))
            right--;
        if (left != right)
        {
            All_Cities[left] = All_Cities[right];
            left++;
        }
        while (((All_Cities[left].country)[0] <= (pivot.country)[0]) && (left < right))
            left++;
        if (left != right)
        {
            All_Cities[right] = All_Cities[left];
            right--;
        }
    }
    All_Cities[left] = pivot;
    int count = left;
    left = l_hold;
    right = r_hold;
    for (int k = 0; k < 100; k++) {
        Buffer[k] = All_Cities[k];
    }
    if (left < count)
        sortingCities_name(Buffer, left, count - 1);
    if (right > count)
        sortingCities_name(Buffer, count + 1, right);
}
void sortingCities_population(Cities Buffer[100], int left, int right) {
    Cities All_Cities[100];
    for (int k = 0; k < 100; k++) {
        All_Cities[k] = Buffer[k];
    }
    Cities pivot;
    int l_hold = left;
    int r_hold = right;
    pivot = All_Cities[left];
    while (left < right)
    {
        while ((All_Cities[right].population >= pivot.population) && (left < right))
            right--;
        if (left != right)
        {
            All_Cities[left] = All_Cities[right];
            left++;
        }
        while ((All_Cities[left].population <= pivot.population) && (left < right))
            left++;
        if (left != right)
        {
            All_Cities[right] = All_Cities[left];
            right--;
        }
    }
    All_Cities[left] = pivot;
    int count = left;
    left = l_hold;
    right = r_hold;
    for (int k = 0; k < 100; k++) {
        Buffer[k] = All_Cities[k];
    }
    if (left < count)
        sortingCities_population(Buffer, left, count - 1);
    if (right > count)
        sortingCities_population(Buffer, count + 1, right);
}