# Simple 'ian' counter in c++
Loops through a group of CSVs and looks for the word 'ian'.

## Architecture
Docker container running Alipine Linux and a c++ application.

## How to run

1. Build the image:
docker build -t ian-counter .

2. Run the image:
docker run --rm -v "<YOUR_FILE_PATH>" ian-counter /data

where your file path is the path of the directory containing all the CSV files.