#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

int main() {
    std::ifstream inputFile("filtered_gote_temp.csv");    //use the data after filtered
    std::ofstream outputFile("filtered_july_temp.csv");

    if (!inputFile.is_open()) {    //make sure the file can open
        std::cerr << "Error opening file!" << std::endl;
        return 1; 
    }

    std::string line;
    std::vector<std::pair<std::string, double>> julyTemperatures;    //define the format of data
    std::getline(inputFile, line);

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string ignored, date, temperatureString;

        std::getline(ss, ignored, ';');    //useless
        std::getline(ss, date, ';');    //collect the date
        std::getline(ss, ignored, ';');     //useless
        std::getline(ss, temperatureString, ';');    //collect the temperature
        
        if (!date.empty() && temperatureString.find(';') == std::string::npos) {    //select the data of july
            std::string month = date.substr(5, 2);    //the month is start from 5th character, 2 characters
            if (month == "07") {    //make sure the selection is 07, july
                try {
                    double temperature = std::stod(temperatureString);    //change the format of temperature
                    julyTemperatures.emplace_back(date, temperature);
                } catch (const std::exception& e) {     //catch the wrong place
                    std::cerr << "Error converting temperature: " << e.what() << std::endl;
                }
            }
        }
    }

    inputFile.close();

    std::cout << "Temperature data for July:" << std::endl;    //print the result in outputfile
    for (const auto& entry : julyTemperatures) {
        outputFile << "Date: " << entry.first << ", Temperature: " << entry.second << " °C" << std::endl;
    }

    return 0;
}