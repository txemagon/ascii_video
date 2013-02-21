#!/bin/bash
# show.sh

for f in *.txt; do
  clear
  cat $f
  /bin/sleep 0.05
done
