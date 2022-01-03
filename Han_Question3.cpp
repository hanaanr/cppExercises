#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// function to get date as an integer from one line of the txt file
int get_date(string line)
{
  int date_int = stoi(line.substr(0,2));
  return date_int;
}

// function to get month as an integer from one line of the txt file
int get_month(string line)
{
  int month_int = stoi(line.substr(3,5));
  return month_int;
}

// function to get year as an integer from one line of the txt file
int get_year(string line)
{
  int year_int = stoi(line.substr(6, 10));
  return year_int;
}

// function to get tmax as a double from one line of the txt file
double get_tmax(string line)
{
  double tmax_double = stod(line.substr(11, 15));
  return tmax_double;
}

// function to get tmin as a double from one line of the txt file
double get_tmin(string line)
{
  double tmin_double = stod(line.substr(15, 20));
  return tmin_double;
}

// function to convert a date to julian date 
int julian_conversion(int date_int, int month_int, int year_int)
{
  int julian = (1461 * (year_int + 4800 + (month_int - 14)/12))/4 +(367 * (month_int - 2 - 12 * ((month_int - 14)/12)))/12 - (3 * ((year_int + 4900 + (month_int - 14)/12)/100))/4 + date_int - 32075;
  return julian;
}

// to check whether a given string contains a digit or not. we will use this function to isolate those lines in the file which contain numeric data
bool isNumber(const string& line)
{
    for (char const &c : line) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

// to remove blank lines from the file
void blank_line(const char *file)
{   
  ifstream fin(file);    
  
  ofstream fout;                
  fout.open("temp.txt", ios::out);
  
  string str;
  while(getline(fin,str))
  { 
    while (str.length() == 0) 
       getline(fin,str);   
  
    fout << str <<endl;
  }

  fout.close();  
  fin.close();  
  
  remove(file);        
  rename("temp.txt", file);
}

int main()
{
  // setting up output file
  fstream outputFile;
  outputFile.open("outputFile.txt",  ios::out);
  outputFile << "day;month;year;JulianDay;MaxTemp;MinTemp" << endl; // header 

  // setting up input file
  blank_line("SevilleTemp1960-2020.txt");
  fstream inputFile;
  inputFile.open("SevilleTemp1960-2020.txt", ios::in); 

  if (inputFile.is_open()){
      string line; // for each line of the file
      while (getline(inputFile, line)) { 

        if (isNumber(line.substr(0, 1)) && line.length()>=17){ // check first character in line if it starts with a digit and if the length
        // of the string is bigger than a certain number to skip rows with missing values

            int d = get_date(line);
            int m = get_month(line);
            int y = get_year(line);
            double tmax = get_tmax(line);
            double tmin = get_tmin(line);
            int julian = julian_conversion(d, m, y);
            outputFile << d << ";" << m << ";" << y << ";" << julian << ";" << tmax << ";" << tmin << ";" << endl;
            
        }

        else if (line[0] == 'A'){ // this is to find the lines that start with "ANOS" so we can add two blank lines as required
          outputFile << "  " << endl;
          outputFile << "  " << endl;
        }

        else {
          // to skip random blank lines and the lines with "FECHA etc headers"
          continue;
        }

       }
       inputFile.close();
 }

  outputFile.close();
  return 0;
}