#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
int main() {
    std::ifstream inputFile("goteborg.csv");
    std::ofstream outputFile("filtered_gote_temp.csv");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> headers;
    bool isHeader = true;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);

        if (isHeader) {
            outputFile << line << std::endl; 
            isHeader = false;
            continue;
        }

        std::string fromDate, toDate, temperature;
        std::getline(ss, fromDate, ',');
        std::getline(ss, toDate, ',');

        for (int i = 0; i < 4; ++i) 
            ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        std::getline(ss, temperature, ',');

        if (fromDate >= "2010-01-01" && fromDate <= "2020-12-31") {
            outputFile << line << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Filtered data has been saved to 'filtered_gote_temp.csv'" << std::endl;
    return 0;
}