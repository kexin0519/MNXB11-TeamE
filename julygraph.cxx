#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>

void plotJulyTemp() {
    std::ifstream inputFile("filtered_july_temp.csv");

    if (!inputFile.is_open()) {    //make sure input the file
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    std::vector<int> years;
    std::vector<double> temperatures;
    std::map<int, std::vector<double>> yearlyTemperatures;    //use map to fine the temperature of july

    while (std::getline(inputFile, line)) {
        std::size_t datePos = line.find("Date: ");
        std::size_t tempPos = line.find("Temperature: ");

        if (datePos != std::string::npos && tempPos != std::string::npos) {
            std::string date = line.substr(datePos + 6, 10);    //take the date, which is after the word'date'
            std::string tempString = line.substr(tempPos + 13);    //take the temperature, which is after word 'temperature'
            tempString = tempString.substr(0, tempString.find(" "));    //remove the unit followed
            double temperature = std::stod(tempString);

            int year = std::stoi(date.substr(0, 4));    //only select the year from date

            years.push_back(year);    //store the data
            temperatures.push_back(temperature);
            yearlyTemperatures[year].push_back(temperature);
        }
    }

    inputFile.close();

    std::vector<int> meanYears;    //calculated the mean of each year
    std::vector<double> meanTemperatures;    //store the mean value in double format
    for (const auto& entry : yearlyTemperatures) {
        int year = entry.first;
        const std::vector<double>& temps = entry.second;

        double meanTemp = std::accumulate(temps.begin(), temps.end(), 0.0) / temps.size();
        //sum of temperature in each year divided the number of temperature entry for each year
        meanYears.push_back(year);
        meanTemperatures.push_back(meanTemp);    //store the mean into corresponding years
    }

    TGraph *graphPoints = new TGraph(years.size());    //the scatterplot for all temperature in july of the 10 year
    for (size_t i = 0; i < years.size(); ++i) {
        graphPoints->SetPoint(i, years[i], temperatures[i]);
    }
    graphPoints->SetMarkerStyle(20);
    graphPoints->SetTitle("Daily Temperatures");

    TGraph *graphMean = new TGraph(meanYears.size());    //draw a line with the mean temerature of each year
    for (size_t i = 0; i < meanYears.size(); ++i) {
        graphMean->SetPoint(i, meanYears[i], meanTemperatures[i]);
    }
    graphMean->SetLineColor(kRed);    //use red for the line
    graphMean->SetLineWidth(2);
    graphMean->SetTitle("Mean Temperatures");

    TMultiGraph *mg = new TMultiGraph();    //combine the two graph in one diagram
    mg->Add(graphPoints, "P");    //the point for daily temperatures
    mg->Add(graphMean, "L");    //the line for mean temperatures

    TCanvas *c1 = new TCanvas("c1", "July Temperature Change", 800, 600);
    mg->SetTitle("July Temperature Change Over 10 Years;Year;Temperature (°C)");
    mg->Draw("A");

    c1->BuildLegend();
    c1->SaveAs("july_temperature_trend.png");
}
