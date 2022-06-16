#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <curl/curl.h>
#include "lib.h"
#include "config.h"

void usage()
{
  printf("options:\n\
-u provide url\n\
  example:\n\
    %s -u \"https://example.com\n\"\
-o provide a filename to save to\n\
  example:\n\
    %s -o filename -u \"https://example.com\"\n\
-O automatically determine filename from url provided\n\
  example:\n\
    %s -u \"https://example.com\" -O\n",
         PROGRAM_NAME, PROGRAM_NAME, PROGRAM_NAME);
}
static int verbose;

static struct option long_options[] =
    {
        /* These options set a flag. */
        {"verbose", no_argument, &verbose, 1},
        /* These options don’t set a flag.
           We distinguish them by their indices. */
        {"help", no_argument, 0, 'h'},
        {"url", required_argument, 0, 'u'},
        {"output-file", required_argument, 0, 'o'},
        {"remote-filename", no_argument, 0, 'O'},
        {0, 0, 0, 0}};

int main(int argc, char *argv[])
{
  char defualt_url_value[5] = "none";
  char url[MAX_URL_LENGTH] = "none";
  char output_file[256];

  int options;
  // put ':' at the starting of the string so compiler can distinguish between '?' and ':'
  while ((options = getopt(argc, argv, "hvOo:u:")) != -1)
  { // get option from the getopt() method
    switch (options)
    {
    // For option i, r, l, print that these are options
    case 'h':
    case 'v':
      printf("Given Option: %c\n", options);
      break;
    case 'u': // here f is used for some file name
      sprintf(url, "%s", optarg);
      break;
    case ':':
      fprintf(stderr, "option %c needs a value\n", options);
      break;
    case '?': // used for some unknown options
      fprintf(stderr, "unknown option: %c\n", optopt);
      break;
    }
  }

  if (strcmp(url, defualt_url_value) == 0)
  {
    die("No URL supplied!", 1);
  }

  print_get_request(url);
  return (EXIT_SUCCESS);
}