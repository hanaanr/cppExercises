#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

// Important note: I created two separate functions in this program to answer Question 4c(i) and 4c(ii). These are called in lines
// 347 and 348, one at a time - resulting in the desired output in the files called "outputYearData.txt" and "outputMonthData.txt".
// The plotting was done in a separate program (check "Han_PlotsQuestion4.cpp").
// Please note that only one of these functions should be called at a time (while the other can be called in another run)
// for optimal results :) 

class DailyMeteoEvent{

    private:

        string theCityName;
        int theDay, theMonth, theYear, theJulianDate;
        double theMaxT, theMinT;

    public:
    
        string getCityName()
        {
            return theCityName;
        }
        void setCityName(string str)
        {
            theCityName = str;
        }

        int getDay()
        {
            return theDay;
        }
        void setDay(int d)
        {
            theDay = d;
        }

        int getMonth()
        {
            return theMonth;
        }
        void setMonth(int m)
        {
            theMonth = m;
        }

        int getYear()
        {
            return theYear;
        }
        void setYear(int y)
        {
            theYear = y;
        }

        int getJulian()
        {
            return theJulianDate;
        }
        void setJulian(int j)
        {
            theJulianDate = j;
        }

        double getMaxT()
        {
            return theMaxT;
        }
        void setMaxT(double max)
        {
            theMaxT = max;
        }

        double getMinT()
        {
            return theMinT;
        }
        void setMinT(double min)
        {
            theMinT = min;
        }

        double GetMeanTOfDate(int d, int m, int y)
        {
            double mean = (theMaxT + theMinT)/2;
            return mean;
        }
};

// defining structure to hold year, max temp for that year, min temp for that year
struct absMinMax_Year
{
    int year;
    double absmin_year;
    double absmax_year;
};

// defining structure to hold month, max temp for that month, min temp for that month
struct absMinMax_Month
{
    int month;
    double absmin_month;
    double absmax_month;
};


// a function to answer the first part of Q4c
void question4c_one(DailyMeteoEvent entries[], int number_of_Entries)
{   
    // output all the required data to this file directly from cout
    freopen("outputYearData.txt","w",stdout);

    // setting initial values
    int yearNow = entries[0].getYear();
    double minT_yearNow = entries[0].getMinT();
    double maxT_yearNow = entries[0].getMaxT();

    // array containing structs absMinMax_Year corresponding to each year
    absMinMax_Year answer1[41]; // since there are 41 years

    int x = 0; // iterates over each object in entries[] (an array containing objects corresponding to each line in the input file)
    int b = 0; // iterates over the array answer1

    while (x <= number_of_Entries)
    {
        if (entries[x].getYear() != yearNow)
        {
            std::cout << yearNow << " " << maxT_yearNow << " " << minT_yearNow << endl;

            // setting the corresponding element in answer1 to the correct values
            answer1[b].year = yearNow;
            answer1[b].absmin_year = minT_yearNow;
            answer1[b].absmax_year= maxT_yearNow;
            b++;
            
            // resetting the temp variables to appropriate starting points
            yearNow = entries[x].getYear();
            minT_yearNow = entries[x].getMinT();
            maxT_yearNow = entries[x].getMaxT();
        }
        
        else
        {   // in order to get to the min and max values for each year - minT_yearNow and maxT_yearNow will be updated accordingly
            if (entries[x].getMinT() < minT_yearNow)
            {
                minT_yearNow = entries[x].getMinT();
            }
            if (entries[x].getMaxT() > maxT_yearNow)
            {
                maxT_yearNow = entries[x].getMaxT();
            }

        }

        x++;

    }
    
    // now to answer the question about the min and max temp along the entire interval

    double absmin_year_overall = answer1[0].absmin_year;  //min temp along entire interval
    double absmax_year_overall = answer1[0].absmax_year;  //max temp along entire interval
    
    int k = 0;
    while (k < 41)  //41 years
    {
        if (answer1[k].absmin_year < absmin_year_overall)
        {
            absmin_year_overall = answer1[k].absmin_year;
        }
        
        if (answer1[k].absmax_year > absmax_year_overall)
        {
            absmax_year_overall = answer1[k].absmax_year;
        }
        k++;
    }
    
    std::cout << "Absolute Max Temperature across entire period is : " << absmax_year_overall << endl;
    std::cout << "Absolute Min Temperature across entire period is : " << absmin_year_overall << endl;

    fclose (stdout);

}

// function to answer the second part of 4c
void question4c_two(DailyMeteoEvent entries[], int number_of_Entries)
{   
    // setting intiial values
    int monthNow = entries[0].getMonth();
    double minT_monthNow = entries[0].getMinT();
    double maxT_monthNow = entries[0].getMaxT();

    // array to store answers
    absMinMax_Month answer2[12]; //since there are 12 months

    // set up the months in answer2
    for (int i = 1; i <= 12; i++)
    {
        answer2[i-1].month = i;
    }
    
    int x = 0; // iterates over each object in entries[] (an array containing objects corresponding to each line in the input file)
    int b = 0; // iterates over each element in the array answer2

    while (x <= number_of_Entries)
    {
        if (entries[x].getMonth() != monthNow) // when we change months
        {
            if (entries[x].getYear() == 1960) // for the first line of code we read
            {   
                answer2[b].absmax_month = maxT_monthNow; // we simply set the answer[2] values to the "now" values
                answer2[b].absmin_month = minT_monthNow;
            }

            else // here we change the answer[2] values (which are supposed to the 'correct' ones) if needed
            {
                if (answer2[b].absmax_month < maxT_monthNow)
                {
                    answer2[b].absmax_month = maxT_monthNow;
                }

                if (answer2[b].absmin_month > minT_monthNow)
                {
                    answer2[b].absmin_month = minT_monthNow;
                }
            }

            b++;

            if (b==12) // we reset it to zero when b = 12 because our array answer2 contains only 12 months ie 12 elements
                b=0;
            
            
            // resetting the temp variables
            monthNow = entries[x].getMonth();
            minT_monthNow = entries[x].getMinT();
            maxT_monthNow = entries[x].getMaxT();
        }
        
        else 
        {   // to find the min and max T values within a particular month
            if (entries[x].getMinT() < minT_monthNow)
            {
                minT_monthNow = entries[x].getMinT();
            }
            if (entries[x].getMaxT() > maxT_monthNow)
            {
                maxT_monthNow = entries[x].getMaxT();
            }

        }

        x++;

    }

    fstream outputMonthData;
    outputMonthData.open("outputMonthData.txt",  ios::out);
    for (int i = 0; i < 12; i++)
    {
        outputMonthData << answer2[i].month << " " << answer2[i].absmax_month << " " << answer2[i].absmin_month << endl;
    }
    outputMonthData.close();
    
}

// function to check whether a string contains a digit
bool isNumber(const string& line)
{
    for (char const &c : line) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

int main()
{   
    // first we want to count the number of lines in our files
    fstream countFile;
    countFile.open("outputFile.txt", ios::in); 
    int number_of_Entries = 0; //aka number of lines
    string line;
    if (countFile.is_open()){
        while (getline(countFile, line)) { 
            if (isNumber(line.substr(0, 1))){
                number_of_Entries++;}
        }
      }
    countFile.close();

    // -----------------------------------------------------------------
    // now we start the actual part
    
    DailyMeteoEvent entries[number_of_Entries]; // defining an array where each element is an object of class DailyMeteoEvent   
    fstream inputFile;
    int x = -1; // to iterate through the lines in the file
    int t = 0; // to iterate over each element in the string called details 
    string temp;
    string details[6]; // to store details related to a particular date after original string is broken into component strings for day, date, month, etc
    inputFile.open("outputFile.txt", ios::in); 

    if (inputFile.is_open()){

        while (getline(inputFile, line)) { 

            if (isNumber(line.substr(0, 1)))
            {// now we have a line of the form 18;1;1960;2436952;10.8;-1.4; that we need to assign correctly
             // to each "pocket" of the object to fill it up
                t = 0;

                for (int j = 0; j < (int)line.size(); j++) { // interating through each character in the line string

                    if (line[j] != ';') { // if we encounter a character that is not ';' then
                        temp += line[j]; // that character gets added to the temp string
                    } 
                    else { // if we encounter a ';' then
                        details[t] = temp; //  
                        t++;
                        temp = "";
                    }
                }

                x++;
            
            // now the array details[] has all the items but in string form. we feed it into the object after typecasting correctly.
            // iterator that iterates around the entries[] ie the array of objects is : x
            entries[x].setDay(stoi(details[0]));
            entries[x].setMonth(stoi(details[1]));
            entries[x].setYear(stoi(details[2]));
            entries[x].setJulian(stoi(details[3]));
            entries[x].setMaxT(stod(details[4])); 
            entries[x].setMinT(stod(details[5])); 
            }
        }
    }
      
    // at this stage, we have a completely filled array of objects called entries[], all data from the file is  input-ed into this array.

    // in the beginning of this program, we have defined the following functions which allow us to get the results that we require:
     question4c_one(entries, number_of_Entries);
    // question4c_two(entries, number_of_Entries);
    // NOTE: only call one of the functions at a time
    
    // THE RESULTS ARE STORED IN "outputMonthData.txt" AND "outputYearData.txt"
    inputFile.close();

}
