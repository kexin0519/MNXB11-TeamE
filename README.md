# MNXB11-TeamE
Course final project for MNXB11

Source Data: goteborg.csv   
When estimating the temperature variations in Gothenburg, we use goteborg.csv file as the source data, which is download from SMHI website(https://www.smhi.se/data/meteorologi/ladda-ner-meteorologiska-observationer/airtemperatureMean24h).

Main file used and their purpose:    
data.cxx: use to filters the raw data (goteborg.csv). The output is stored in filtered_gote_temp.csv.   
scattorplot.cxx: Creates a scatter plot using the filtered data. The resulting image is temp_scatterplot.png.   
tempgraph.cxx: Creates a histogram of the temperature data. The resulting image is temperature_histogram.png.   
data_july.cxx: Filters the July temperature data from 2010-2020 using filtered_gote_temp.csv. The output is stored in filtered_july_temp.csv.   
julygraph.cxx: Creates a line graph of the July temperature data. The resulting image is july_temperature.png.

Run the program:   
1. Compile data.cxx to process the raw data file (goteborg.csv).   
in bash   
> g++ data.cxx -o data    
> ./data

2. Create the Scatter Plot and Histogram   
Compile and run scattorplot.cxx and tempgraph.cxx to generate visualizations.   
root> .L scattorpolt.cxx+   
root> CreateDataTempPlot()    
The result stored in temp_scatterplot.png   
Create histogram:   
root> .L tempgraph.cxx+   
root> createTempHistogram()   
The histogram image saved as temperature_histogram.png.

3. Filter July Temperature Data
Compile and run data_july.cxx to filter the July data from 2010-2020.   
in bash    
> g++ data_july.cxx -o data_july    
> ./data_july

4. Create the July Temperature Line Graph    
Compile and run julygraph.cxx to create a line graph of the July temperature data.    
root> .L julygraph.cxx+   
root> plotJulyTemp()     
The line graph image will be saved as july_temperature.png.
