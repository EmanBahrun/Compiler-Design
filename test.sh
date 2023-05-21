cd src
make
cd ..
./src/parser test/test1.mas > test/test1.mil
# Print a line ----------
echo "---------------------"
./src/mil_run test/test1.mil