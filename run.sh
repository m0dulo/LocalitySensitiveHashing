rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
../bin/lsh -rawdata ../data/rawData.txt -hashdata ../data/hashData.txt > ../data/result.txt
