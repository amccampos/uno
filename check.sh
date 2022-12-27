#!/bin/bash

dir=*/*
if [ $# -ne 0 ]; then
  dir=$1/*
fi

for file in $dir; do
  echo "=== Testando bot ${file} ============================="
  for v in {1..10}; do
    ./uno ${file} bot_A bot_B -q
    if [ $? -eq 0 ]; then
      echo OK
    else
      echo FAIL
    fi
  done
done
