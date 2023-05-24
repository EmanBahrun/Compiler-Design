cd src
make
cd ..
./src/parser phase3examples/test1.mas > phase3examples/test1.mil
# Print a line ----------
echo "---------------------"
./src/mil_run phase3examples/test1.mil