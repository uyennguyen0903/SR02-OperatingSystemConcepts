#! /bin/bash
for k in $(seq 1 7)
do
  gcc tache3_auto.c -o tache3_auto -lm -lpthread
  sleep 2
  echo "N = 4 000 000 & k = $k" >> data.dat
  count=20
  for i in $(seq 1 20)
  do
    ./tache3_auto 4000000 $k >> data.dat
  done
done
