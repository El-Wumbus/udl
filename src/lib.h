/*
  Copyright (C) 2022 Aidan Neal

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>. 
*/

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
void die(const char message[], const int code)
{
  /* Printing the error message to the standard error output and exiting the program with the exit code. */
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
char chars_from_file(const char filename[])
{
  char contents;

  /* Opening the file and assigning it to the file pointer. */
  FILE *fileptr;
  fileptr = fopen(filename, "r");

  if (fileptr == NULL)
  {
    exit(1);
  }

  /* Reading the contents of the file and assigning it to the variable 'contents.' */
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

  /* Initializing the curl library. */
  CURL *curl = curl_easy_init();

  /* Checking if the curl library is initialized. If it is not, it prints an error message and returns 1. */
  if (!curl)
  {
    fprintf(stderr, "Couldn't initialize curl\n");
    return (1);
  }

  curl_easy_setopt(curl, CURLOPT_URL, url);

  /* Setting the response to the curl request. */
  CURLcode response;
  response = curl_easy_perform(curl);

  /* Checking if the response is not equal to CURLE_OK. If it is not, it prints an error message and returns 1. */
  if (response != CURLE_OK)
  {
    fprintf(stderr, "Couldn't get content from url \"%s\". Error: %s\n", url, curl_easy_strerror(response));
    return (1);
  }

  /* Clean up the curl library. */
  curl_easy_cleanup(curl);
  return (0);
}

/**
 * It takes a URL and a filename as arguments, and saves the content of the URL to the file
 * 
 * @param url The URL to get the content from.
 * @param filename The name of the file to save the response to.
 * 
 * @return the status of the curl request.
 */
int save_get_request(const char url[1000], const char *filename)
{
  /* Initializing the curl lib
  /* Checking if the response is not equal to CURLE_OK. If irary. */
  CURL *curl = curl_easy_init();
  
  /* Checking if the curl library is initialized. If it is not, it prints an error message and returns 1. */
  if (!curl)
  {
    fprintf(stderr, "Couldn't initialize curl\n");
    return (1);
  }

  /* Setting the URL to the curl request. */
  curl_easy_setopt(curl, CURLOPT_URL, url);

  /* Opening the file and assigning it to the file pointer. */
  FILE *file = fopen(filename, "w");

  /* Setting the response to the curl request. */
  CURLcode response;
  response = curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

  if (response != CURLE_OK)
  {
    fprintf(stderr, "Couldn't get content from url \"%s\". Error: %s\n", url, curl_easy_strerror(response));
    return (1);
  }

  /* Closing the file and performing the curl request. */
  curl_easy_perform(curl);
  fclose(file);

  return (0);
}

#endif