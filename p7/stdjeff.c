#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

void printBool(int64_t c){
	if (c == 0){
		fprintf(stdout, "false");
	} else{
		fprintf(stdout, "true");
	}
	fflush(stdout);
}

FILE * stdjeff_openFP(const char * s, int mode){
  if (mode == 1)
  {
    return fopen(s, "w");
  }
  else
  {
    return fopen(s, "r");
  }
}

FILE * stdjeff_closeFP(const char * s, int mode){
  if (mode == 1)
  {
    return fclose(s, "w");
  }
  else
  {
    return fclose(s, "r");
  }
}

void stdJeff_readInt(long int num, FILe * f){
    if (f == 0)
    {
      fprintf(stdin, "%ld", num);
      fflush(stdin);
    }
    else 
    {
      fprintf(f, "%ld", num);
      fflush(f);
    }
}

void stdJeff_writeInt(long int num, FILe * f){
    if (f == 0)
    {
      fprintf(stdout, "%ld", num);
      fflush(stdout);
    }
    else 
    {
      fprintf(f, "%ld", num);
      fflush(f);
    }
}

void printInt(long int num){
	fprintf(stdout, "%ld", num);
	fflush(stdout);
}

void printString(const char * str){
	fprintf(stdout, "%s", str);
	fflush(stdout);
}

int64_t getBool(){
	char c;
	scanf("%c", &c);
	getchar(); // Consume trailing newline
	if (c == '0'){
		return 0;
	} else {
		return 1;
	}
}

int64_t getInt(){
	char buffer[32];
	fgets(buffer, 32, stdin);
	long int res = atol(buffer);
	return res;
}
