ascii_video
===========

Converts normal videos into ascii streaming to display in a [pseudo]terminal.

##Quick view

Uncompress videos under bin/videos directory. Then go to bin dir and type:

```bash
user@host:~/ascii_video/bin$ ./show videos/ace/440 2694 
```

It is advisable to reduce font size (typically ctrl+-).

If the _.txt_ files don't begin with the _intro_ prefix you can specify it after the second parameter (_2694_ in the example).


##Converting videos

 1. Download a video inside the _artwork_ directory (ie. *my_video.mpg*).
 2. Go to bin/videos and make *my_video* directory (*mkdir my_video*).
 3. Invoke the _frameme.sh_  shell script (*../../../utils/frameme.sh ../../../artwork/my_video.mpg intro%4d.jpg*).
 4. Invoke the *asciifyme.hs* shell script  *../../../utils/asciifyme.sh 400* with the desired resolution (_400_ characters per row in the example).
 5. Go back to the _bin_ directory and execute _show_ program as in the example above.

##Aditional notes

 This player/converter relies on _ffmpeg_ and _jp2a_ commands, so please install them before start working with *ascii_video*.
 Invoke commands without parameters for additional information.


