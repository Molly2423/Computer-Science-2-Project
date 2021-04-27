//  main.cpp
//  FinalProject
//  My Health Foods
//  purpose of this part of the project is to make sure that you know how to write a
//  program that declare and use classes and objects, and extends the practice into the
//  use of queues. You have signed a contract with several major restaurants to run
//  their healthy food choices for their respective clients.
//
//  Created by Molly Kendrick on 2/6/19.
//  Copyright © 2019 Molly Kendrick. All rights reserved.

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <fstream>
#include <map>
#include <queue>

using std::cout;            //declare for namespace
using std::cin;
using std::endl;
using std::setw;
using std::string;
using std::setfill;
using std::fstream;
using std::make_pair;
using std::map;
using std::queue;

class Restaurant                 //restaurant class
{
    short int restaurantNum;
    short int tableNum;
    int ID;
    string name;
    string mealTime;
    short int mealNum;
    //char timestamp[20];
    
public:
    Restaurant();            //constructor
    
    void setID(int num)        //getmethods setmethods
    { ID = num; }
    
    void setName(string str)
    { name = str; }
    
    void setMealNum(int num)
    { mealNum = num; }
    
   /* void setTimestamp(string t)
    { timestamp = t; }*/
    
    int getID() const
    { return ID; }
    
    string getName() const
    { return name; }
    
    short int getMealNum() const
    { return mealNum; }
    
    /*string getTimestamp() const
    { return timestamp; }*/

};

class Meals //to make a class static make all member values static  //meal class
{
    string mealName;
    int calories;
    int protein;
    int vitamins;
    
public:
    Meals();
    
    Meals(string mName, int cal, int pro, int vit);
    
    string getMealName()
    { return mealName; }
    
    int getCalories()
    { return calories; }
    
    int getProtein()
    { return protein; }
    
    int getVitamins()
    { return vitamins; }
    
};

void displayMain();              //function prototypes
void IDgenerator(int &);
void displayMenu();
void getUserChoice(int &);
bool validateChoice(int);
void login(Restaurant *[], fstream &, int [], int [], int [7][24]);
void logoff(Restaurant *[]);
void search(Restaurant *[]);
void displayRest(Restaurant *[], int [], int [], int [7][24]);
void printLog(fstream &);


// Global Constants
const int NUMHFCS = 8;            // Number of restaurants
const int HFCSIZES[NUMHFCS] = {19, 15, 24, 33, 61, 17, 55, 37};         // Number of tables in each restaurant
const string RESTAURANT[NUMHFCS] = {"The Salubrious Bistro", "What the Kale?", "Lettuce Enjoy", "Vegan Nights", "Pasta is a Planet", "The Meatless Miracle", "The Pesky Pescatarian", "The Fine Fettle"};     // Names of restaurant
const int NUMMEALS = 10;  //number of meals
const string MEALNAMES[NUMMEALS] = {"Mexican Quinoa Salad", "Kale and Eggs", "Chickpea Vegetable Curry", "Vegetable Pot Pie", "Eggplant Carbonara", "Butternut Squash Black Bean Chili", "Seafood Medley", "Sweet Potato Black Bean Enchiladas", "Pesto Pasta Salad", "Tomato Soup and Salad Supremo"};  // Names of restaurant
const int CALORIES[NUMMEALS]    = {202, 119, 304, 398, 215, 157, 222, 341, 143, 233};  // calories (int)
const short int PROTEIN[NUMMEALS]    = {1, 12, 16, 22, 17, 7, 11, 20, 27, 9};  // grams of protein (short)
const short int VITAMINS[NUMMEALS]    = {12, 10, 23, 31, 20, 17, 24, 19, 22, 13};  // milligrams of vitamins (short)


int main()
{
    int choice = 0;
    bool loopFlag = true;
    fstream entryLog;
    int restFav[NUMHFCS] = {0};   //OPT#1 to hold favorites for option 4
    int mealFav[NUMMEALS] = {0};  //OPT#2 to hold favorites for option 4
    int day_time[7][24] = {{0}, {0}}; //OPT#3 to hold days and times
    
    srand(time(0));
    
    //entryLog.open("restLog.txt", std::ios::in |std::ios::out |std::ios::app);
    entryLog.open("restaurantLog.txt", std::ios::in | std::ios::out |std::ios::trunc);
    if(!entryLog)
    {
        cout << "file open failed" << endl;
    }
    
    Restaurant *restValue[NUMHFCS];
    for(int i = 0; i < NUMHFCS; ++i)
    {
        restValue[i] = new Restaurant[HFCSIZES[i]];
    }
    
    map<int, Meals> mealMap;
    for(int i = 0; i < NUMMEALS; ++i)
    {
        mealMap.insert(make_pair<int, Meals>(int(i), Meals(MEALNAMES[i], CALORIES[i], PROTEIN[i], VITAMINS[i])));
    }
    
    displayMain();
    
    if (choice == 6)
    {
        return 0;
    }
    
    do
    {
        displayMenu();
        do
        {
            getUserChoice(choice);
            loopFlag = validateChoice(choice);
        }while (loopFlag == true);
        
        if (choice == 1)
        {
            login(restValue, entryLog, restFav, mealFav, day_time);
        }
        else if (choice == 2)
        {
            logoff(restValue);
        }
        else if (choice == 3)
        {
            search(restValue);
        }
        else if (choice == 4)
        {
            displayRest(restValue, restFav, mealFav, day_time);
        }
        else if (choice == 5)
        {
            printLog(entryLog);
        }
        
    }while(choice != 6);
    entryLog.close();
}

//pre constructor function
//post initializes variables
Meals::Meals()
{
    mealName = " ";
    calories = 0;
    protein = 0;
    vitamins = 0;
}

//pre constructor function accepts 4 parameters
//post initializes variables
Meals::Meals(string mName, int cal, int pro, int vit)
{
    mealName = mName;
    calories = cal;
    protein = pro;
    vitamins = vit;
}

//pre constructor function
//post initializes variables
Restaurant::Restaurant()
{
   /* time_t now = time(0);
    char* timeOf = ctime(&now);
    strcpy(timestamp, timeOf);
    timeOf[20] = '\0';*/
    
    restaurantNum = 0;
    tableNum = 0;
    ID = 0;
    name = ' ';
    mealTime = ' ';
    mealNum = 0;
}

//pre seed random
//post generates user id number
void IDgenerator(int &userID)
{
    userID =(rand() % 10000) + 1;
    return;
}

//precondition start
//postcondition restraunt names are displayed
void displayMenu()
{
    cout << setw(47) << "Welcome - here is our list of available restaurants" << endl;
    for (int i = 0; i < NUMHFCS; ++i)
    {
        cout << "Restaurant #" << i + 1 << " " << RESTAURANT[i] << endl;
    }
    return;
}

//precondition start
//postcondition menu is displayed
void displayMain()
{
    cout << setw(15) << "----------------------------------------------------- " << endl;
    cout << setw(15) << "|                  Molly Kendrick's                 |" << endl;
    cout << setw(15) << "|             Healthy Food Choices system           |" << endl;
    cout << setw(15) << "----------------------------------------------------- " << endl;
    cout << setw(15) << "|                     Main Menu                     |" << endl;
    cout << setw(15) << "|                1) Request Table                   |" << endl;
    cout << setw(15) << "|                2) Free up a Table                 |" << endl;
    cout << setw(15) << "|                3) Find a Patron                   |" << endl;
    cout << setw(15) << "|                4) Display Restaurant Usage        |" << endl;
    cout << setw(15) << "|                5) Print Transaction Log           |" << endl;
    cout << setw(15) << "|                6) Quit                            |" << endl;
    cout << setw(15) << "|___________________________________________________|" << endl;
}

//pre
//post choice has value
void getUserChoice(int &choice)
{
    cout << "Please enter a choice from the Menu, 6 to quit: " ;
    cin >> choice;
}

//precondition choice is entered by user
//postcondition validates choice
bool validateChoice(int choice)
{
    bool goodOrNot = false;
    if ((cin.fail()) || ((choice < 1) || (choice > 6)))
    {
        cout << "The choice entered is invalid" << endl;
        goodOrNot = true;
    }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return goodOrNot;
}

//pre needs user ID
//post puts user ID into array at lab and station
void login(Restaurant *restValue[], fstream &entryLog, int restFav[], int mealFav[], int day_time[7][24])
{
    int rest = 0;
    static int table = 0;
    int userID = 0;
    string name = " ";
    int mealNumber = 0;
    string mTime = " ";
    
    //queue <Restaurant> waitingList;
    queue <string> waitingList;
    
    IDgenerator(userID);
    
    cout << "Please enter the restaurant choice from 1 through " << NUMHFCS << ": " ;
    cin >> rest;
    if ((cin.fail()) || rest > NUMHFCS || rest < 1)     // lab validation
    {
        cout << "That is not a valid restaurant" << endl;
        cout << endl;
        cout << "Please pick a valid restaurant (1-" << NUMHFCS << ")"<< endl;
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(),'\n');
        cin >> rest;
    }
    
    ++restFav[rest - 1];   //opt#1 adding tallys for every restaurant entry
    
    cout << "You have chosen " << RESTAURANT[rest - 1] << " " << endl;
    
    if (table == HFCSIZES[rest - 1])
    {
        cout << "All tables are currently in use, you will be added to the waiting list" << endl;
        cin.ignore();
        cout << "Please enter the name of the Patron: " << endl;
        getline(cin,name);
        if (name.length() <= 0 || name.length() > 35)
        {
            cout << "That is not a valid name" << endl;
            cout << "Enter the patron's name again" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<int>::max(),'\n');
            getline(cin,name);
        }
        waitingList.push(name);
    }
    else
    {
        cout << "Your table number is " << ++table;
        cout << " and your ID number is " << std::setfill('0') << setw(5) << userID << std::setfill(' ');
        cout << endl;
        restValue[rest - 1][table - 1].setID(userID);
    
        cin.ignore();
        cout << "Please enter the name of the Patron: " << endl;
        getline(cin,name);
        if (name.length() <= 0 || name.length() > 35)
        {
            cout << "That is not a valid name" << endl;
            cout << "Enter the patron's name again" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<int>::max(),'\n');
            getline(cin,name);
        }
        restValue[rest - 1][table - 1].setName(name);
        
        cout << "Please enter the meal number from the following choices" << endl;
        for (int i = 0; i < NUMMEALS; ++i)
        {
            cout << i + 1 << ")   " << MEALNAMES[i] << endl;
        }
        cout << "Meal: " ;
        cin >> mealNumber;
        cout << "Your choice was the " << MEALNAMES[mealNumber - 1] << endl;
        cout << "Your meal has " << CALORIES[mealNumber - 1] << " calories, " << PROTEIN[mealNumber - 1] << " protein, and " << VITAMINS[mealNumber - 1] << " vitamins" << endl;
        restValue[rest - 1][table - 1].setMealNum(mealNumber);
        
        //restValue[rest - 1][table - 1].setTimestamp(mTime);
        
        ++mealFav[mealNumber - 1];  //opt#2 adding tallys for every meal entry
        
        cout << "Login successful" << endl;
    }

    //write to log
    time_t now = time(0);
    char* timeOf = ctime(&now);
    //timeOf[20] = '\0'; //put this into class constructor but it gave way too many errors
    
    //reset everything and go to the end of the file
    entryLog.clear();
    entryLog.seekg(0, std::ios::end);
    
    entryLog << rest << " ";
    entryLog << table << " ";
    entryLog << userID << " ";
    entryLog << name << " ";
    entryLog << mealNumber << " ";
    entryLog << timeOf << endl;
    
    //get timeof info into jagged array
    string timeStr;
    int d = 0;
    int t = 0;
    timeStr = timeOf;
    t = std::stoi(timeStr.substr(11,12));
    if(timeStr.substr(0,3) == "Sun")
    {
        d = 0;
    }
    else if(timeStr.substr(0,3) == "Mon")
    {
        d = 1;
    }
    else if (timeStr.substr(0,3) == "Tue")
    {
        d = 2;
    }
    else if(timeStr.substr(0,3) == "Wed")
    {
        d = 3;
    }
    else if(timeStr.substr(0,3) == "Thu")
    {
        d = 4;
    }
    else if(timeStr.substr(0,3) == "Fri")
    {
        d = 5;
    }
    else if(timeStr.substr(0,3) == "Sat")
    {
        d = 6;
    }
    ++day_time[d][t];
}

//pre needs to accept a name
//post takes name out of array
void logoff(Restaurant *restValue[])
{
    int rest = 0;
    int table = 0;
    
    cout << "Please enter the restaurant choice from 1 through " << NUMHFCS << ": " ;
    cin >> rest;
    if ((cin.fail()) || rest > NUMHFCS || rest < 1)     // lab validation
    {
        cout << "That is not a valid restaurant" << endl;
        cout << endl;
        cout << "Please pick a valid restaurant (1-" << NUMHFCS << ")"<< endl;
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(),'\n');
        cin >> rest;
    }
    
   cout << "You have chosen " << RESTAURANT[rest - 1] << " " << endl;
    
    cout << "Please enter the table number of the Patron: ";
    cin >> table;
    if ((cin.fail()) || table > HFCSIZES[rest - 1]  || table < 1)     // lab validation
    {
        cout << "That is not a table we offer" << endl;
        cout << endl;
        cout << "Please pick a valid table (1-" << HFCSIZES[rest - 1] << ")" << ": " << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(),'\n');
        cin >> table;
    }
    
    cout << endl;
        
        cout << restValue[rest - 1][table - 1].getName();  //cout patron name
        cout << " has enjoyed another meal ... bye!" << endl;
}

//pre needs to accept an name to search for
//post outputs which restraunt and table the user is at or says that user is not found
void search(Restaurant *restValue[])
{
    string name;
    //int favMeal = 0;
    bool flag = false;
    
    cout << "Please enter the patron by name: " ;
    getline(cin,name);
    if (name.length() <= 0 || name.length() > 35)
    {
        cout << "That is not a valid name" << endl;
        cout << "Enter the patron's name again" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(),'\n');
        getline(cin,name);
    }
    cout << endl;
    
    for(int i = 0; i < NUMHFCS; ++i)
    {
        for(int j = 0; j < HFCSIZES[i]; ++j)
        {
            if(restValue[i][j].getName() == name )
            {
                flag = true;
                cout << name ;
                if (restValue[i][j].getMealNum() == 0)
                {
                    cout << " has no favorite" << endl;
                }
                else
                {
                    cout << " likes " << MEALNAMES[restValue[i][j].getMealNum() - 1] << endl;
                }
            }
        }
    }
    if(flag == false)
    {
        cout << "That patron was not found" << endl;
    }
}


//pre needs to be passed pointer
//post displays report of chosen restaurant
void displayRest(Restaurant *restValue[], int restFav[], int mealFav[], int day_time[7][24])
{
    char choice;
    int highest = 0;
    int secondHighest = 0;
    int thirdHighest = 0;
    int highMeal = 0;
    int secHighMeal = 0;
    int thirdHighMeal = 0;
    int max = 0;
    int secondMax = 0;
    int thirdMax = 0;
    
    highest = restFav[0];
    highMeal = mealFav[0];
    max = day_time[0][0];
   
    cout << "A) Favorite restaurants" << endl;
    cout << "B) Favorite meals" << endl;
    cout << "C) Favorite days and times (Military Time)" << endl;
    cout << "Pick your favorite report from the list: ";
    cin >> choice;
    cout << endl;
    
    choice = toupper(choice);
    
    while (choice != 'A' && choice != 'B' && choice != 'C')
    {
        cout << "Error invalid input please try again " << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(),'\n');
        cin >> choice;
        choice = toupper(choice);
    }
    
    switch(choice)
    {
        case 'A' : case 'a' :
            for(int i = 0; i < NUMHFCS; ++i)
            {
                if(restFav[i] > highest)
                {
                    thirdHighest = secondHighest;
                    secondHighest = highest;
                    highest = restFav[i];
                    cout << "The most popular restaurant is " << RESTAURANT[i] << endl;
                }
                if (restFav[i] < highest && restFav[i] > secondHighest)
                {
                    secondHighest = restFav[i];
                    cout << "The second most popular restaurant is " << RESTAURANT[i] << endl;
                }
                if(restFav[i] < secondHighest && restFav[i] > thirdHighest)
                {
                    thirdHighest = restFav[i];
                    cout << "The third most popular restaurant is " << RESTAURANT[i] << endl;
                }
            }
            break;
        case 'B' : case 'b' :
            for(int i = 0; i < NUMMEALS; ++i)
            {
                if(mealFav[i] > highest)
                {
                    thirdHighMeal = secHighMeal;
                    secHighMeal = highMeal;
                    highMeal = mealFav[i];
                    cout << "The most popular meal is " << MEALNAMES[i] << endl;
                }
                if (mealFav[i] < highMeal && mealFav[i] > secHighMeal)
                {
                    secHighMeal = mealFav[i];
                    cout << "The second most popular meal is " << MEALNAMES[i] << endl;
                }
                if(mealFav[i] < secHighMeal && mealFav[i] > thirdHighMeal)
                {
                    thirdHighMeal = mealFav[i];
                    cout << "The third most popular meal is " << MEALNAMES[i] << endl;
                }
            }
            break;
        case 'C' : case 'c' :
            string day;
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 24; j++)
                {
                    if (day_time[i][j] > max)
                    {
                        thirdMax = secondMax;
                        secondMax = max;
                        max = day_time[i][j];
                        if(i == 0)
                        {
                            day = "Sunday";
                        }
                        else if(i == 1)
                        {
                            day = "Monday";
                        }
                        else if (i == 2)
                        {
                            day = "Tuesday";
                        }
                        else if(i == 3)
                        {
                            day = "Wednesday";
                        }
                        else if(i == 4)
                        {
                            day = "Thursday";
                        }
                        else if(i == 5)
                        {
                            day = "Friday";
                        }
                        else if(i == 6)
                        {
                            day = "Saturday";
                        }
                        cout << "The most popular day and times are " << day << " between " << j << " and " << j + 1 << endl;
                    }
                    if(day_time[i][j] < max && day_time[i][j] > secondMax)
                    {
                        if(i == 0)
                        {
                            day = "Sunday";
                        }
                        else if(i == 1)
                        {
                            day = "Monday";
                        }
                        else if (i == 2)
                        {
                            day = "Tuesday";
                        }
                        else if(i == 3)
                        {
                            day = "Wednesday";
                        }
                        else if(i == 4)
                        {
                            day = "Thursday";
                        }
                        else if(i == 5)
                        {
                            day = "Friday";
                        }
                        else if(i == 6)
                        {
                            day = "Saturday";
                        }
                        secondMax = day_time[i][j];
                        cout << "The second most popular day and times are " << day << " between " << j << " and " << j + 1 << endl;
                    }
                    if(day_time[i][j] < secondMax && day_time[i][j] > thirdMax)
                    {
                        if(i == 0)
                        {
                            day = "Sunday";
                        }
                        else if(i == 1)
                        {
                            day = "Monday";
                        }
                        else if (i == 2)
                        {
                            day = "Tuesday";
                        }
                        else if(i == 3)
                        {
                            day = "Wednesday";
                        }
                        else if(i == 4)
                        {
                            day = "Thursday";
                        }
                        else if(i == 5)
                        {
                            day = "Friday";
                        }
                        else if(i == 6)
                        {
                            day = "Saturday";
                        }
                        thirdMax = day_time[i][j];
                        cout << "The third most popular day and times are " << day << " between " << j << " and " << j + 1 << endl;
                    }
                }
            }
            break;
    }
}

//pre needs file to read from
//post displays all restaurants and their contents
void printLog(fstream &entryLog)
{
    cout << "Restaurant\t" << "Table\t" << "UserID\t" << "Name\t" << "Meal\t" << "Time Stamp" << endl;
    
    //reset everything and go to the beginning of the file
    entryLog.clear();
    entryLog.seekg(0, std::ios::beg);
    
    int rest = 0;
    static int table = 0;
    int userID = 0;
    string name;
    int mealNumber = 0;
    char timeOf[20];
    
    while (!entryLog.eof())
    {
        entryLog >> rest;
        entryLog >> table;
        entryLog >> userID;
        getline(entryLog, name, '$');
        entryLog >> mealNumber;
        entryLog.read(timeOf, sizeof(timeOf));
        
        cout << std::left << setw(12) << rest << std::left << setw(8) << table;
        cout << setw(3) << userID;
        cout << std::right << setw(7) << name;
        cout << std:: right << setw(6)  << mealNumber;
        cout << std::right << setw(15) << timeOf << endl;
    }
    
    return;
}
