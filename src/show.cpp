#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

#define MAXSTR        0x100
#define current_frame (i+1)
#define BASEFILENAME  "./%s/%s%04i.jpg.txt"  /* directory/base_name#number.jpg.txt */


char images_directory[MAXSTR];
char image_prefix[MAXSTR];

void print_usage(const char *executable){
  fprintf(stderr, "Usage: \t%s <images directory> <final frame> [<prefix of the image files>]\n\n", executable);
  exit(EXIT_FAILURE);
}

void load_frame(int frame_number, char **video){
  char filename[MAXSTR];
  FILE *pf = NULL;
  long filesize;
  int bytes_read;

  sprintf(filename, BASEFILENAME, images_directory, image_prefix, frame_number);
  #ifndef NDEBUG
  printf("Loading into frame %i.\n", frame_number);
  printf("About to open %s\n", filename);
  #endif
  if (!(pf = fopen(filename, "rb"))){
    fprintf(stderr, "Missing frame number %i\n", frame_number);
    exit(EXIT_FAILURE);
  }

  fseek(pf, 0, SEEK_END);
  filesize = ftell(pf); 
  fseek(pf, 0, SEEK_SET);
  #ifndef NDEBUG
  printf("File size: %li\n", filesize);
  #endif
  *video = (char *) malloc((filesize + 1) * sizeof(char));  // Extra space for sentinel value.
  #ifndef NDEBUG
  printf("Memory allocated at: %p\n", *video);
  #endif
  bytes_read = fread(*video, 1, filesize, pf);
  #ifndef NDEBUG
  printf("%i bytes have been read.\n", bytes_read);
  #endif
  video[0][filesize] = (char) 0;  // Sentinel value
  fclose(pf);
}

int main(int argc, char *argv[]){

  int final_frame;
  char **video = NULL;
  clock_t start_time, end_time;

  if (argc < 3)
    print_usage(argv[0]);

  if (argc > 3)
    strncpy(image_prefix, argv[3], MAXSTR);
  else
    strcpy(image_prefix, "intro");
  
  strncpy(images_directory, argv[1], MAXSTR);
  final_frame = atoi(argv[2]);

  printf("Loading frames...\n");
  start_time = clock();
  
  for (int i=0; i<final_frame; i++){
    #ifndef NDEBUG
    printf("Frame %4i: ", current_frame);
    #endif
    video = (char **) realloc(video, current_frame * sizeof(char *));
    load_frame(current_frame, &video[i]);
  }

  end_time = clock();
  printf("Loading time %.2lf seconds.\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);
  initscr();
  curs_set(0);
  for (int frame=0; frame<final_frame; frame++){
    mvprintw(0, 0, "Frame %i\n%s", frame, video[frame]);
    refresh();
  }
  curs_set(1);
  endwin();
  
  #ifndef NDEBUG
  printf("Releasing pointers.\n");
  #endif
  for (int i=0; i<final_frame; i++){
  #ifndef NDEBUG
  printf("Releasing pointer %i at %p.\n", i, video[i]);
  #endif
    free(video[i]);
  }
  free(video);
  #ifndef NDEBUG
  printf("%i pointers have benn released.\n", final_frame);
  #endif

  return EXIT_SUCCESS;
}

