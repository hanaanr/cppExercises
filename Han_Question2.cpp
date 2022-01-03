#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <fstream>
#include <iomanip>
using namespace std;

// this is a function to create the initial points
double f(double x)
{
    return 2*x + 3;
}

// function to generate a random double between two doubles
double random_double(double min, double max)
{
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double> distr(min, max);
    return distr(eng);
}

// function to find y for (x,y) between (x1, y1) and (x2, y2)
double interpolation(double x, double x1, double y1, double x2, double y2)
{
    double y = y1 + ((x - x1)*(y2 - y1)/(x2 - x1));
    return y;
}

int main()
{   
    // setting up an output file to dump the data to
    fstream interpFile;
    interpFile.open("interpFile.txt", ios::out);
    interpFile << "x" << ";" << "f(x)" << endl; //header

    // arrays to store the precalculated x and corresponding y points
    double x_arr[5];
    double y_arr[5];
    double x; //elements of x_arr

    // loop to find 5 random x points between 0 and 10
    for (int i=0; i<5; i++)
    {
        x = random_double(0.0, 10.0);
        x_arr[i] = x; // add it to the array x_arr
    }

    // loop to arrange x_arr elements in ascending order
    for (int i=0; i<5; i++)
    {
        for (int j=i+1; j<5; j++)
        {
            if (x_arr[j] < x_arr[i])
            {
                x = x_arr[i];
                x_arr[i] = x_arr[j];
                x_arr[j] = x;
            }
        }
    }
    // now our x_arr is ready. it consists of 5 random values between 0 and 10, arranged in ascending order. let us find the corresponding 
    // array for y values now using y = f(x)
    for(int i=0; i<5; i++)
    {
        y_arr[i] = f(x_arr[i]);
        interpFile << x_arr[i] << ";" << y_arr[i] << endl;
    }

    // now the user can enter N
    int N; // number of new points calculated by interpolation between 2 consecutive points of the dataset
    cout << "Enter N (please enter a whole number): ";
    cin >> N;

    //  generate N new points in each interval. 
    // i am not using a loop for this, because my code was super buggy and nothing would work. ultimately doing it this way was easier (sorry)
    double xnew1[N]; //xnew1 stands for array for new x points in interval 1 
    double ynew1[N];
    for (int i = 0; i < N; ++i){
        xnew1[i] = random_double(x_arr[0], x_arr[1]);
        ynew1[i] = interpolation(xnew1[i], x_arr[0], y_arr[0], x_arr[1], y_arr[1]);
        interpFile << xnew1[i] << ";" << ynew1[i] << endl;
    }

    double xnew2[N];
    double ynew2[N];
    for (int i = 0; i < N; ++i){
        xnew2[i] = random_double(x_arr[1], x_arr[2]);
        ynew2[i] = interpolation(xnew2[i], x_arr[1], y_arr[1], x_arr[2], y_arr[2]);
        interpFile << xnew2[i] << ";" << ynew2[i] << endl;

    }

    double xnew3[N];
    double ynew3[N];
    for (int i = 0; i < N; ++i){
        xnew3[i] = random_double(x_arr[2], x_arr[3]);
        ynew3[i] = interpolation(xnew3[i], x_arr[2], y_arr[2], x_arr[3], y_arr[3]);
        interpFile << xnew3[i] << ";" << ynew3[i] << endl;
    }

    double xnew4[N];
    double ynew4[N];
    for (int i = 0; i < N; ++i){
        xnew4[i] = random_double(x_arr[3], x_arr[4]);
        ynew4[i] = interpolation(xnew4[i], x_arr[3], y_arr[3], x_arr[4], y_arr[4]);
        interpFile << xnew4[i] << ";" << ynew4[i] << endl;
    }

    interpFile.close();
    return 0;

}
   
