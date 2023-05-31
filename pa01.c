/*=============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Vigenere cipher
|
| Author: Antonio Acosta
| Language: c, c++, Java, go, python
|
| To Compile: javac pa01.java
|                   gcc -o pa01 pa01.c
|                   g++ -o pa01 pa01.cpp
|                   go build pa01.go
|                   python pa01.py
|
| To Execute: java -> java pa01 kX.txt pX.txt
|          or c++ -> ./pa01 kX.txt pX.txt
|          or c -> ./pa01 kX.txt pX.txt
|           or go -> ./pa01 kX.txt pX.txt
|           or python -> python pa01.py kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Fall 2022
| Instructor: McAlpin
| Due Date: Oct20th Grace Period.
|
+=============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 513



char* cipher(char key[MAX],char plainText [MAX], int plainLen, int keyLen)
{
  char *cipher = malloc(plainLen * sizeof(char));
  int cipherVal, i = 0;
  
  for(i = 0;i < plainLen;i++)
    {
      int c = (plainText[i] - 97 + key[i] - 97) % 26  + 97;
      cipher[i] = c;
      printf("%c",cipher[i]);
    }
    cipher[i] = '\0';
  return cipher;
}

void Format(char * text)
{

  for(int i = 0;i < strlen(text); i++)
    {
      if(i % 80 == 0)
      {
        printf("\n");
      }
      printf("%c", text[i]);
    }
  
}



int main(int argi, char **argv)
{
  FILE *keyFile, *plainFile;
  char key[513], plainText[513], *cipher;
  int i = 0, j = 0, c=0;
  keyFile = fopen(argv[1], "r");
  plainFile = fopen(argv[2], "r");

  if(!keyFile)
  {
    printf("Key not found\n");
  }
  if(!plainFile)
  {
    printf("PlainText not found\n");
  }


  

  while((c = fgetc(keyFile)) != EOF && i < 512)
  {
    if(isalpha(c))
      {
        key[i] = tolower(c);
        i++;
      }

  }  
  key[i] = '\0';
    
  
  while((c = fgetc(plainFile)) != EOF && j < 512)
  {
      if(isalpha(c))
      {
        plainText[j] = tolower(c);
        j++;
      }
  }
      for(j;j<512;j++)
      {
        plainText[j] = 'x';
      }
      plainText[512] = '\0';

   Format(key);
  
    int strEnd = strlen(key)-1;
    int copy = 0;
    while(strEnd < 512) 
    {
      key[strEnd] = key[copy];
      strEnd++;
      copy++;
    }
  

    int plainLen = strlen(plainText);
    int keyLen = strlen(key);



  
  Format(plainText);
  
  cipher = cipher(plainText, key, plainLen, keyLen);
  Format(cipher);
  printf("\n");

}









/*=============================================================================
| I [Antonio Acosta] ([5124851]) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/