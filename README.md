# MNXB11-TeamE
Course final project for MNXB11
When estimating the temperature variations in Gothenburg, we use goteborg.csv file as the source data, which is download from SMHI website(https://www.smhi.se/data/meteorologi/ladda-ner-meteorologiska-observationer/airtemperatureMean24h).
Compiled data.cxx to arrange the goteborg.csv. The result stored as filtered_gote_temp.csv.
Used the filtered_gote_temp.csv to create scattorplot.cxx and tempgraph.cxx. The reslut of this two fiie can be seen in temp_scatterplot.png and temperature_histogram.png.
Used data_july.cxx to select the temperature of July from 2010-2020 based on the filtered_gote_temp.csv, the result is shows in filtered_july_temp.csv.
Used the filtered_july_temp.csv to create the julygraph.cxx and the result graph stored in july_temperature.png.