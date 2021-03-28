mkdir /scratch/q1/A1/myQ1
g++ q1_generator.cpp -o generate -std=c++11
for i in {0..9}
do
	./generate >/scratch/q1/A1/myQ1/$i.in
done
