echo "" > output.txt
for i in examples/*.mas; do echo $i; ./src/a.out < $i; echo; done > output.txt