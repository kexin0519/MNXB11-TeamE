//
//  plotTemperatureDistribution.C
//  ROOT_presentation
//
//  Created by Negoro Takumi on 2024/11/02.
//
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iostream>
#include <map>

//define the variable 
void plotSimpleTemperatureDifference(const char* fileKiruna = "KirunaAirport.root", const char* fileJonkoping = "Jonkoping-Axamos.root") {
    // open the file and get tree
    TFile *fileK = TFile::Open(fileKiruna);
    TFile *fileJ = TFile::Open(fileJonkoping);
    TTree *treeK = (TTree*)fileK->Get("tree_name");
    TTree *treeJ = (TTree*)fileJ->Get("tree_name");

    // condition of variables
    Int_t xK, xJ;
    Float_t yK, yJ;
    treeK->SetBranchAddress("x", &xK);
    treeK->SetBranchAddress("y", &yK);
    treeJ->SetBranchAddress("x", &xJ);
    treeJ->SetBranchAddress("y", &yJ);

    // collect the difference betwenn two cities per year
    std::map<int, std::pair<double, int>> yearlyData;
    Long64_t nEntries = std::min(treeK->GetEntries(), treeJ->GetEntries());

    for (Long64_t i = 0; i < nEntries; i++) {
        treeK->GetEntry(i);
        treeJ->GetEntry(i);

        // calculate the difference
        int year = xK / 10000;
        double tempDifference = yJ - yK;
        
        // update the count and total difference per year
        yearlyData[year].first += tempDifference;
        yearlyData[year].second += 1;
    }

    // calculate the average of temperature difference and CREATE THE DATA FOR MAKING GRAPH
    std::vector<double> years, avgTempDiffs;
    for (const auto& entry : yearlyData) {
        int year = entry.first;
        double avgDiff = entry.second.first / entry.second.second;
        years.push_back(year);
        avgTempDiffs.push_back(avgDiff);
    }

    // Draw graph
    TCanvas *c1 = new TCanvas("c1", "Average Temperature Difference", 800, 600);
    TGraph *graph = new TGraph(years.size(), &years[0], &avgTempDiffs[0]);
    graph->SetTitle("Average Temperature Difference (Jonkoping - Kiruna)");
    graph->GetXaxis()->SetTitle("Year");
    graph->GetYaxis()->SetTitle("Average Temperature Difference (Celsius)");
    graph->SetLineColor(kBlue);
    graph->Draw("AL");

    // fitting linear function (in this case it make sense to use one not Gaussian)
    TF1 *linearFit = new TF1("linearFit", "[0] + [1]*x", years.front(), years.back());
    graph->Fit(linearFit, "R");

    // Output the result of fitting
    std::cout << "Intercept: " << linearFit->GetParameter(0) << std::endl;
    std::cout << "Slope: " << linearFit->GetParameter(1) << std::endl;

    // save the graph as png file
    c1->SaveAs("simpleTemperatureDifference.png");

    // close file
    fileK->Close();
    fileJ->Close();
}
