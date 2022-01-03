#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "supportLib.cpp"
#include "pbPlots.cpp"
using namespace std;

int main()
{   
    vector<double> yearX;
    vector<double> yearY1, yearY2;
    int year_x;
    double year_y1, year_y2;
    ifstream yearFile("outputYearData.txt");
    while (yearFile >> year_x >> year_y1 >> year_y2)
    {
        yearX.push_back(static_cast<double>(year_x));
        yearY1.push_back(year_y1);
        yearY2.push_back(year_y2);

    }

    vector<double> monthX;
    vector<double> monthY1, monthY2;
    int month_x;
    double month_y1, month_y2;
    ifstream monthFile("outputMonthData.txt");
    while (monthFile >> month_x >> month_y1 >> month_y2)
    {
        monthX.push_back(static_cast<double>(month_x));
        monthY1.push_back(month_y1);
        monthY2.push_back(month_y2);

    }

    RGBABitmapImageReference *imageRef1 = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *imageRef2 = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *imageRef3 = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *imageRef4 = CreateRGBABitmapImageReference();
    
    DrawScatterPlot(imageRef1, 600, 400, &yearX, &yearY1);
    DrawScatterPlot(imageRef2, 600, 400, &yearX, &yearY2);
    DrawScatterPlot(imageRef3, 600, 400, &monthX, &monthY1);
    DrawScatterPlot(imageRef4, 600, 400, &monthX, &monthY2);

    vector<double> *pngData1 = ConvertToPNG(imageRef1->image);
    WriteToFile(pngData1, "yearPlotMax.png");
    DeleteImage(imageRef1->image); 

    vector<double> *pngData2 = ConvertToPNG(imageRef2->image);
    WriteToFile(pngData2, "yearPlotMin.png");
    DeleteImage(imageRef2->image); 

    vector<double> *pngData3 = ConvertToPNG(imageRef3->image);
    WriteToFile(pngData3, "monthPlotMax.png");
    DeleteImage(imageRef3->image); 

    vector<double> *pngData4 = ConvertToPNG(imageRef4->image);
    WriteToFile(pngData4, "monthPlotMin.png");
    DeleteImage(imageRef4->image); 

    return 0;
}

