#!/bin/bash

players=()
for file in */*; do
  players+=($file)
done

len=${#players[@]}
for (( i=0; i<$len-2; i++ )); do
  for (( j=i+1; j<$len-1; j++ )); do
    for (( k=j+1; k<$len; k++ )); do
      # for v in {1..5}; do
        echo "=== ${players[$i]} vs ${players[$j]} vs ${players[$k]} ==="
        ./uno ${players[$i]} ${players[$j]} ${players[$k]} -q -csv result.csv
      # done
    done
  done
done

