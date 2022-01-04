#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "supportLib.cpp"
#include "pbPlots.cpp"
using namespace std;

int main(){
    
    // vectors to save x, y plotting data using "outputYearData.txt"
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

    // vectors to save x, y plotting data using "outputMonthData.txt"
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

    // for 4 plots
	RGBABitmapImageReference *imageReference1 = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *imageReference2 = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *imageReference3 = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *imageReference4 = CreateRGBABitmapImageReference();

	ScatterPlotSeries *series1 = GetDefaultScatterPlotSeriesSettings();
	series1->xs = &yearX;
	series1->ys = &yearY1;
	series1->linearInterpolation = true;
	series1->lineType = toVector(L"solid");
	series1->lineThickness = 1;
	series1->color = GetBlack();

	ScatterPlotSettings *settings1 = GetDefaultScatterPlotSettings();
	settings1->width = 600;
	settings1->height = 400;
	settings1->autoBoundaries = true;
	settings1->autoPadding = true;
	settings1->title = toVector(L"Max Temp vs Year");
	settings1->xLabel = toVector(L"Max Temp");
	settings1->yLabel = toVector(L"Year");
	settings1->scatterPlotSeries->push_back(series1);

	ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
	series2->xs = &yearX;
	series2->ys = &yearY2;
	series2->linearInterpolation = true;
	series2->lineType = toVector(L"solid");
	series2->lineThickness = 1;
	series2->color = GetBlack();

	ScatterPlotSettings *settings2 = GetDefaultScatterPlotSettings();
	settings2->width = 600;
	settings2->height = 400;
	settings2->autoBoundaries = true;
	settings2->autoPadding = true;
	settings2->title = toVector(L"Min Temp vs Year");
	settings2->xLabel = toVector(L"Min Temp");
	settings2->yLabel = toVector(L"Year");
	settings2->scatterPlotSeries->push_back(series2);

	ScatterPlotSeries *series3 = GetDefaultScatterPlotSeriesSettings();
	series3->xs = &monthX;
	series3->ys = &monthY1;
	series3->linearInterpolation = true;
	series3->lineType = toVector(L"solid");
	series3->lineThickness = 1;
	series3->color = GetBlack();

	ScatterPlotSettings *settings3 = GetDefaultScatterPlotSettings();
	settings3->width = 600;
	settings3->height = 400;
	settings3->autoBoundaries = true;
	settings3->autoPadding = true;
	settings3->title = toVector(L"Max Temp vs Month");
	settings3->xLabel = toVector(L"Max Temp");
	settings3->yLabel = toVector(L"Month");
	settings3->scatterPlotSeries->push_back(series3);

	ScatterPlotSeries *series4 = GetDefaultScatterPlotSeriesSettings();
	series4->xs = &monthX;
	series4->ys = &monthY2;
	series4->linearInterpolation = true;
	series4->lineType = toVector(L"solid");
	series4->lineThickness = 1;
	series4->color = GetBlack();

	ScatterPlotSettings *settings4 = GetDefaultScatterPlotSettings();
	settings4->width = 600;
	settings4->height = 400;
	settings4->autoBoundaries = true;
	settings4->autoPadding = true;
	settings4->title = toVector(L"Min Temp vs Month");
	settings4->xLabel = toVector(L"Min Temp");
	settings4->yLabel = toVector(L"Month");
	settings4->scatterPlotSeries->push_back(series4);

	DrawScatterPlotFromSettings(imageReference1, settings1);
    DrawScatterPlotFromSettings(imageReference2, settings2);
    DrawScatterPlotFromSettings(imageReference3, settings3);
    DrawScatterPlotFromSettings(imageReference4, settings4);

	vector<double> *pngdata1 = ConvertToPNG(imageReference1->image);
	WriteToFile(pngdata1, "YearPlotMax.png");
	DeleteImage(imageReference1->image);

	vector<double> *pngdata2 = ConvertToPNG(imageReference2->image);
	WriteToFile(pngdata2, "YearPlotMin.png");
	DeleteImage(imageReference2->image);

	vector<double> *pngdata3 = ConvertToPNG(imageReference3->image);
	WriteToFile(pngdata3, "MonthPlotMax.png");
	DeleteImage(imageReference3->image);

	vector<double> *pngdata4 = ConvertToPNG(imageReference4->image);
	WriteToFile(pngdata4, "MonthPlotMin.png");
	DeleteImage(imageReference4->image);

	return 0;
}