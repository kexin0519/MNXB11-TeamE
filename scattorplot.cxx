#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TDatime.h> 

void createDateTempPlot() {
    std::ifstream inputFile("filtered_gote_temp.csv");
    
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::vector<double> temperatures;    //define the format of temperature
    std::vector<double> dates;    //define the format of date
    std::string line;
    std::getline(inputFile, line);    //read the head of the table

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string tempString, dateString;
        std::string fromDate, toDate;
        std::getline(ss, fromDate, ';');    //useless
        std::getline(ss, toDate, ';');    //useless

        std::getline(ss, dateString, ';');    //select the column of date
        std::getline(ss, tempString, ';');    //select the column of temperature

        if (!tempString.empty() && !dateString.empty()) {
            double temperature;
            try {
                temperature = std::stod(tempString);   // tranform format to double
            } catch (const std::invalid_argument&) {
                std::cerr << "Invalid temperature value: " << tempString << std::endl;
                continue;
            } catch (const std::out_of_range&) {
                std::cerr << "Temperature value out of range: " << tempString << std::endl;
                continue;
            }    //if the transform or value is not valid, just skip and continue

            dateString += " 00:00:00"; // transform date to the required format, add 00:00:00

            TDatime date(dateString.c_str());
            double dateNum = date.Convert();    //transform date to make the graph understand

            temperatures.push_back(temperature);    //add the data in correct form
            dates.push_back(dateNum);
        }
    }

    inputFile.close();

    TGraph *graph = new TGraph(temperatures.size(), dates.data(), temperatures.data());    //create graph with TGraph function

    graph->SetTitle("Date vs. Temperature;Date;Temperature (°C)");
    graph->SetMarkerStyle(21);
    graph->SetMarkerColor(kBlue);

    TCanvas *c1 = new TCanvas("c1", "Date vs. Temperature", 800, 600);
    graph->Draw("AP");    //"AP" means Axis and Points

    c1->SaveAs("date_temperature_plot.png");    //save graph

    std::cout << "Plot saved as 'date_temperature_plot.png'" << std::endl;

}
