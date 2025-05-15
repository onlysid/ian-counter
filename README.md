# Simple 'ian' counter in c++
Loops through a group of CSVs and looks for the word 'ian'.

## Architecture
Docker container running Alipine Linux and a c++ application.

## How to run (docker)

1. Build the image:
docker build -t ian-counter .

2. Run the image:
docker run --rm -v "<YOUR_CSV_DIRECTORY>" ian-counter /data

ALTERNATIVELY, use the bash script (sh run.sh "<YOUR_CSV_DIRECTORY>").

## How to run (without docker)

Use cmake, cmake --build . (or, cmake with Ninja using -G Ninja). Add -DCMAKE_BUILD_TYPE=Release for optimisations