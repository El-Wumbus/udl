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
  char defualt_output_file_value[21] = "NULL_NOFILE_PROVIDED";
  char url[MAX_URL_LENGTH] = "none";
  char output_file[256] = "NULL_NOFILE_PROVIDED";

  int options;
  int options_index;
  // put ':' at the starting of the string so compiler can distinguish between '?' and ':'

  /* Parsing the command line arguments. */
  while ((options = getopt_long(argc, argv, ":hOo:u:", long_options, &options_index)) != -1)
  {
    switch (options)
    {
    case 'h':
      usage();
      return (0);
      break;
    case 'o':
      sprintf(output_file, "%s", optarg);
      break;
    case 'u': 
      sprintf(url, "%s", optarg);
      break;
    case ':':
      fprintf(stderr, "option %c needs a value\n", options);
      return (2);
      break;
    case '?': // used for some unknown options
      fprintf(stderr, "unknown option: %c\n", optopt);
      break;
    }
  }

  /* Checking if the url is the default value, if it is then it will die with the message "No URL
  supplied!" and exit with a status of 1. */
  if (strcmp(url, defualt_url_value) == 0)
  {
    die("No URL supplied!", 1);
  }

  /* Checking if the output_file is the default value, if it is not then it will call the
  save_get_request function. */
  if (strcmp(output_file, defualt_output_file_value) != 0)
  {
    return (save_get_request(url, output_file));
  }

  return (print_get_request(url));
}


