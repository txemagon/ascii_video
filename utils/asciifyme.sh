#!/bin/bash
# asciifyme.sh

echo "Converting jpeg files into ascii."
if [ -d $1 ]; then
  echo "Removing existing directory $1."
  rm -rf $1
fi

echo "New $1 created."
mkdir $1

for i in *.jpg; do 
  cat $i | jp2a --width=$1 - > $1/$i.txt 
done

echo "Conversions jobs in $1 are terminated."
