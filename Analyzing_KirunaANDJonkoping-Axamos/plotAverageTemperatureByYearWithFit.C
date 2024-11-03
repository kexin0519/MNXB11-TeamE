//
//  Untitled.h
//  ROOT_presentation
//
//  Created by Negoro Takumi on 2024/11/02.
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TLegend.h>
#include <TF1.h>
#include <map>
#include <vector>
#include <numeric>
#include <string>
#include <iostream>

void plotAverageTemperatureByYearWithFit(const char* fileKiruna = "KirunaAirport.root", const char* fileJonkoping = "Jonkoping-Axamos.root") {
    TFile *fileK = TFile::Open(fileKiruna);
    TFile *fileJ = TFile::Open(fileJonkoping);

    if (!fileK || !fileJ) {
        std::cerr << "Error: don't open the ROOT file" << std::endl;
        return;
    } else {
        std::cout << "Open the ROOT file correctly" << std::endl;
    }

    TTree *treeK = (TTree*)fileK->Get("tree_name");
    TTree *treeJ = (TTree*)fileJ->Get("tree_name");

    if (!treeK || !treeJ) {
        std::cerr << "Error: there are no tree" << std::endl;
        return;
    } else {
        std::cout << "Great! Kiruna tree is correctly working" << std::endl;
        std::cout << "Great! Jonkoping tree is correctly working" << std::endl;
    }
    //main function/////////////////////////////////////
    
    //definition of each of variables///////////////////
    
    Int_t dateK, dateJ;
    Float_t tempK, tempJ;
    
    // declare the value (carefully check, what the variable is correct)
    
    treeK->SetBranchAddress("x", &dateK);
    treeK->SetBranchAddress("y", &tempK);

    treeJ->SetBranchAddress("x", &dateJ);
    treeJ->SetBranchAddress("y", &tempJ);
    
    //role; to store the data of two Temperature per year
    //std::map<int, std::vector<float>> yearlyTempsK
    //std:map this is the array holding key-value pair.
    //in this case int->key = year, float->value = temperature
    //quite useful method!
    
    
    std::map<int, std::vector<float>> yearlyTempsK;//store the Temp for Kiruna
    std::map<int, std::vector<float>> yearlyTempsJ;//store the Temp for Jonkoping

   
    //Long64_t nEntriesK = treeK->GetEntries();
    //treeK->GetEntries() gets the numbers of entry and this numbers store as nEntriesK
    //Long64_t can apply in the case of huge entries like this sesseion
    //(integer form, 64bit)
    
    Long64_t nEntriesK = treeK->GetEntries();
    
    //for loop from 0 to before nEntriesK
    for (Long64_t i = 0; i < nEntriesK; i++) {
        treeK->GetEntry(i);
    //quite cool method how to only get the YYYY
    //for this date data in YYYYMMDD
    //devided by 10000, we'll get only the YYYY
        
        int year = dateK / 10000;
        //get the year data
        
        //yearlyTempsK has key as year(int type)and have a map as the value of Temps data list at the appropriate year (std::vector<float> see 60 lines)
        //yearlyTempsK[year].push back(tempK)
        //if there are no key(year) in yearTempsK, this code can create new empty data and oush back into the data store "TempK"(quite cool)
        yearlyTempsK[year].push_back(tempK);
    }

    Long64_t nEntriesJ = treeJ->GetEntries();
    for (Long64_t i = 0; i < nEntriesJ; i++) {
        treeJ->GetEntry(i);
        int year = dateJ / 10000;
        // get the year data
        
        yearlyTempsJ[year].push_back(tempJ);
    }

    std::vector<double> years;
    std::vector<double> avgTempsK;
    std::vector<double> avgTempsJ;

    //for loop
    //entry;variable to refer each of entries of yearly TempsK
    //entries.first;year
    //entries.second;temperature (of course vector)
    
    for (const auto& entry : yearlyTempsK) {
        int year = entry.first;
    
        //condition
        //check whether year data really exists in yearlyTempsJ
        //.count(year); function return the number of times "year" appears in
        //yearlyTempsJ (0 or 1)
        if (yearlyTempsJ.count(year) > 0) {
        
        //caluculation for average
        //std::accummulate (sums up/accumulate)　(numeric library)
        //grammar
        //std:accumulate(start, end, initialValue)
        //entry.second.begin(), entry.second.end();define the range
        //sums up all for entry.second
            double avgK = std::accumulate(entry.second.begin(), entry.second.end(), 0.0) / entry.second.size();
            double avgJ = std::accumulate(yearlyTempsJ[year].begin(), yearlyTempsJ[year].end(), 0.0) / yearlyTempsJ[year].size();
            years.push_back(static_cast<double>(year));
            avgTempsK.push_back(avgK);
            avgTempsJ.push_back(avgJ);
        }
    }

    //setting the graph
    TCanvas *c1 = new TCanvas("c1", "Average Temperature by Year", 800, 600);
    TGraph *graphK = new TGraph(years.size(), &years[0], &avgTempsK[0]);
    TGraph *graphJ = new TGraph(years.size(), &years[0], &avgTempsJ[0]);

    graphK->SetLineColor(kBlue);
    graphK->SetLineWidth(2);
    graphK->SetTitle("Average Temperature in Kiruna (Blue) and Jonkoping (Red) with Single Linear Fit");
    graphK->GetXaxis()->SetTitle("Year");
    graphK->GetYaxis()->SetTitle("Average Temperature (Celsius)");
    graphK->GetXaxis()->SetLimits(1965, 2024); // renge of X
    graphK->GetYaxis()->SetRangeUser(-5, 10);  // range of y
    graphK->Draw("AL");

    graphJ->SetLineColor(kRed);
    graphJ->SetLineWidth(2);
    graphJ->SetLineStyle(2);
    graphJ->Draw("L SAME");

    TLegend *legend = new TLegend(0.7, 0.8, 0.9, 0.9);
    legend->AddEntry(graphK, "Kiruna", "l");
    legend->AddEntry(graphJ, "Jonkoping", "l");
    legend->Draw();

    c1->SaveAs("averageTemperatureWithSingleFitByYear.png");

    delete fileK;
    delete fileJ;
    delete c1;
}
