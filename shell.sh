#!/bin/bash
for i in {i,2,3,4,5,6,7,8,9,10}
do

	for j in {50000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000}
	do
		mpirun -hostfile hosts --prefix /home/cluster/mirror/mpi -np 3 dbmpi1 $j >> dbmpi1.csv
	done
done
