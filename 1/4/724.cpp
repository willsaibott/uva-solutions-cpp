#include<stdio.h>
#include<iostream>
int main(int argc,char** argv){
  FILE *fp;
  char*buffer=new char[10000];
  buffer[0]=EOF;
  fp=fopen(argv[0],"r");
  do{
    buffer++;
    *buffer=getc(fp);
    if(*buffer!=EOF) putchar(*buffer);
  } while(*buffer!=EOF);
  putchar('\n');
  while(*(--buffer)!=EOF)
  {
    putchar(*buffer);
  }
  fclose(fp);
  delete(buffer);
  return 0;
}