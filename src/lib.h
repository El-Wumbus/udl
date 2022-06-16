#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

/**
 * If the message is not null, print the message to stderr, and if the code is not null, exit with the
 * code.
 *
 * @param message The error message to print.
 * @param code The exit code to use. If you don't specify one, the program will exit with a status of
 * 1.
 */
void die(char message[], int code)
{
  fprintf(stderr, "error: %s\n", message);
  
  exit(code);
}

/**
 * This function takes a file name as an argument and returns the contents of the file as a string
 *
 * @param filename The name of the file to open
 *
 * @return The contents of the file.
 */
char chars_from_file(char filename[])
{
  char contents;
  FILE *fileptr;
  fileptr = fopen(filename, "r");

  if (fileptr == NULL)
  {
    exit(1);
  }

  fscanf(fileptr, "%s", &contents);
  return (contents);
}

/**
 * It takes a URL as a parameter, and prints the contents of the URL to the screen
 *
 * @param url The URL to send the request to.
 */
int print_get_request(const char url[1000])
{
  if (url == NULL)
  {
    return (1);
  }

  CURL *curl = curl_easy_init();

  if (!curl)
  {
    fprintf(stderr, "Couldn't initialize curl\n");
    return (1);
  }

  curl_easy_setopt(curl, CURLOPT_URL, url);

  CURLcode response;
  response = curl_easy_perform(curl);

  if (response != CURLE_OK)
  {
    fprintf(stderr, "Couldn't get content from url \"%s\". Error: %s\n", url, curl_easy_strerror(response));
    return (1);
  }

  curl_easy_cleanup(curl);
  return (0);
}

int save_get_request(const char url[1000], const char *filename)
{
  CURL *curl = curl_easy_init();
  
  if (!curl)
  {
    fprintf(stderr, "Couldn't initialize curl\n");
    return (1);
  }

  curl_easy_setopt(curl, CURLOPT_URL, url);

  FILE *file = fopen(filename, "w");
  CURLcode response;
  response = curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
  if (response != CURLE_OK)
  {
    fprintf(stderr, "Couldn't get content from url \"%s\". Error: %s\n", url, curl_easy_strerror(response));
    return (1);
  }

  curl_easy_perform(curl);
  fclose(file);

  return (0);
}

#endif