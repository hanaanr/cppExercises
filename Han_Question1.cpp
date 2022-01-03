#include<iostream>
#include<cmath>
#include<string>
using namespace std;
 
// defining a function for f(x), the roots of which we have to find
double f(double x)
{
    return sin(x*x);
}
 
// defining a structure of the type "output" which will store one integer (number of iterations) and one double (location of the root)
struct output
{ 
    int n;
    double c;
    string s;
};

// function for performing the bisection method given the interval and tolerance
output bisection_method(double a, double b, double e) // a and b define the interval, and e is the tolerance value
// it returns a value of the type 'output' which we defined earlier

{  
    output bisection_output;
    if (f(a)*f(b) < 0){ // if the product is negative, it means that the root lies between a and b (because f(a) and f(b) have opposite signs)
       
        //output bisection_output; 
        bisection_output.n = 0; // to store number of iterations

        while ((b-a) >= e) { 
       
        bisection_output.n++;    
        bisection_output.c = (a+b)/2; // midpoint of the interval
       
        if (f(bisection_output.c) == 0) // if the root lies at the midpoint c, then print it
            cout << "The root of f(x) is " << bisection_output.c << endl;
            
        else // we consider the intervals to the left and right of the midpoint and evaluate the same condition as before
            if (f(bisection_output.c)*f(a) < 0) 
                b = bisection_output.c;
            else 
                a = bisection_output.c;

        }
           
        return bisection_output;

    }
       
    else{
        bisection_output.s = "NOT FOUND";
    }
        
}


int main()
{  
    string ans; // string to store user's answer to the question in line 77
    do {
        cout << "Enter the value of the lower bound a: " << endl;
        double a;
        cin >> a;
       
        cout << "Enter the value of the upper bound b: " << endl;
        double b;
        cin >> b;
       
        cout << "Enter the tolerance value e: " << endl;
        double e;
        cin >> e;
       
        if (bisection_method(a, b, e).s== "NOT FOUND"){
            cout << "Root not found" << endl;
        }

        else{
            cout << "Root: " << bisection_method(a, b, e).c << endl;
            cout << "Number of iterations N = " << bisection_method(a, b, e).n << endl;      
        }

        cout << "Do you want to do another calculation? (yes/no) " << endl;
        cin >> ans;
    }
    while (ans == "yes"); //the use of the do while loop means that the program runs once, and then asks the user if they want to repeat it

    return 0;
}
