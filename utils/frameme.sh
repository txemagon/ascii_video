#!/bin/bash
# frameme.sh

# Converts a video to jpg files

filename=$0

function usage () {
   cat <<EOF

      Usage: $filename <video> <prefix>

         video:  Path to video file.

	 prefix: Prefix for the jpg output files.

      Example:

         user@hostname:~/ascii_video/bin/videos/my_video$ ../../../utils/frameme.sh ../../../artwork/my_video.mpg intro%4d.jpg

	 Where %d tells to set the number of the image whithin the name and %4d pads the number with necessary 0's to reach four digits.

EOF

  exit 1
}

which ffmpeg > /dev/null
if [ $? -ne 0 ]; then
  echo "Please install ffmpeg."
  exit 1
fi

if [ $# -lt 2 ]; then
  usage
fi

ffmpeg -i $1 -f image2 $2
