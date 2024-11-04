//
//  convertCSVtoROOT.C
//  ROOT_presentation
//
//  Created by Negoro Takumi on 2024/11/01.
//
// content of convertCSVtoROOT.C
#include <TFile.h>
#include <TTree.h>
#include <fstream>
#include <sstream>
#include <iostream>

//void: the return type of the function(this function does not return a value)
//void name(first_parameter, second_parameter)
//         {
//           function body
//          }
//  const char* csvFileName; *(const = char) = ptr
//so I can't change the variable for pointer because its variable is constant!

//check whether input file is correctly working

void convertCSVtoROOT(const char* csvFileName, const char* rootFileName)
   {
//std::ifstream: a type C++ from <fstream> library
    // input_file_stream( reading from files )
//syntax
//std::ifstream name (constructor argument)
    std::ifstream csvFile(csvFileName);
    
//1.dot operator: access {members, class, structure} of object
//syntax variable-name . member
//
//2.is_open():function check if the file stream is open and returns true if it is open, or false otherwise
//3. std:cerr: error messages and diagnostics developers and users expect std::ceer for errors
    
    
    if (!csvFile.is_open()) {
        std::cerr << "Error opening CSV file: " << csvFileName << std::endl;
        return;
    }
//finish checking the data////////////
    
    
//main function///////////
    
    TFile *rootFile = new TFile(rootFileName, "RECREATE");
    TTree *tree = new TTree("tree_name", "Converted CSV Data");

    int date;
    float temperature;
    tree->Branch("x", &date);
    tree->Branch("y", &temperature);

    std::string line;
    while (std::getline(csvFile, line)) {
        std::stringstream ss(line);
        std::string dateStr, tempStr;

        if (!std::getline(ss, dateStr, ',') || !std::getline(ss, tempStr, ',')) {
            continue;
        }

        try {
            date = std::stoi(dateStr);
            temperature = std::stof(tempStr);
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid data in line: " << line << std::endl;
            continue;
        }

        tree->Fill();
    }

    tree->Write();
    rootFile->Close();
    csvFile.close();

    std::cout << "Successfully converted " << csvFileName << " to " << rootFileName << std::endl;
}

