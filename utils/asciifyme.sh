#!/bin/bash
# asciifyme.sh

# Converts jpg files into ascii

function usage () {
cat <<-EOF

   Usage: asciifyme <resolution>

          Use this command in the directory where jpg 
          files are: typically videos/<video_name>

   Example: 

      user@hostname:~/ascii_video/bin/videos/my_video$ ../../../utils/asciifyme.sh 260

EOF
   exit 1 
}

which jp2a > /dev/null
if [ $? -ne 0 ]; then
  echo "Please install jp2a."
  exit 1
fi

if [ $# -lt 1 ]; then
  usage
fi

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
