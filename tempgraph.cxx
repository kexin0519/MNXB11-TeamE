#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <TH1F.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TString.h>
#include <TStyle.h>

void createTempHistogram() {
    std::ifstream inputFile("filtered_gote_temp.csv");
    
    if (!inputFile.is_open()) {    //check if open the file successful
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::vector<double> temperatures;   //define the format of temperature
    std::string line;
    std::getline(inputFile, line);    //the first line is the head of table

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string tempString;
        std::string fromDate, toDate;
        std::getline(ss, fromDate, ';');    //useless
        std::getline(ss, toDate, ';');    //useless

        std::string dateString;
        std::getline(ss, dateString, ';');    //the column contain the date of temperature
        std::getline(ss, tempString, ';');    //the column contain the number of temperature

        if (!tempString.empty()) {    //change the temperature to double, make it present in historgram
            double temperature;
            try {
                temperature = std::stod(tempString);           
                } catch (const std::invalid_argument&) {
                std::cerr << "Invalid temperature value: " << tempString << std::endl;
                continue;    //remove the value if it conversion fails
            } catch (const std::out_of_range&) {
                std::cerr << "Temperature value out of range: " << tempString << std::endl;
                continue;    // remove the value if it is out of range
            }

            temperatures.push_back(temperature);    //add the value to the vector
        }
    }

    inputFile.close();

    const int nBins = 50;    //start for histogram
    TH1F *histogram = new TH1F("tempHistogram", "Temperature Histogram;Temperature (°C);Counts", nBins, -20, 30);    //the range of highest and lowest temperature

    for (const auto& temperature : temperatures) {
        histogram->Fill(temperature);
    }

    for (int bin = 1; bin <= histogram->GetNbinsX(); ++bin) {   //use loop to check the bins
        double binContent = histogram->GetBinContent(bin);
        histogram->SetBinError(bin, sqrt(binContent));   //set error for the bins
    }

    TCanvas *c1 = new TCanvas("c1", "Temperature Histogram", 1000, 600);    //set the size of canvas
    histogram->Draw("E");   // set the histogram with error bars

    c1->SaveAs("temperature_histogram.png");    //save in png

    std::cout << "Histogram saved as 'temperature_histogram.png'" << std::endl;
}
