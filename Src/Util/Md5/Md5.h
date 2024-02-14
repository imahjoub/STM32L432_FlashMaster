#ifndef MD5_2024_02_05_H
  #define MD5_2024_02_05_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/****************************** MACROS ******************************/
#define MD5_BLOCK_SIZE 16               // MD5 outputs a 16 byte digest

/*********************** FUNCTION DECLARATIONS **********************/
void Md5_Calculate(const uint8_t* DataPtr, const size_t Datalength, uint8_t* Md5Result);
bool Md5_Check(const uint8_t* Md5Result, const uint8_t* Md5Check);

#endif   /* MD5_2024_02_05_H */
