#include <iostream>
#include <sys/time.h>
#include <ctime>

const unsigned int MICROSECONDS = 1000000;
unsigned long getMicroseconds()
{
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return MICROSECONDS * tv.tv_sec + tv.tv_usec; 
}

unsigned char * getRandomPlain(unsigned int length)
{
  unsigned char *plain = new unsigned char[length];
  for (unsigned int i = 0; i < length; i++) {
    plain[i] = rand() % 256;
  }

  return plain;
}
