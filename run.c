#include <stdio.h>

int main( int argc, char *argv[] )

{

  int i;

  printf( " Executing the main function of a simple program" );

//looping through command line variables
//argc is the number of command line variables
//argv is an array of the command line varibles as a strings
  for( i=0 ; i<=argc-1 ; i++ )
  {
	printf( "\n%d\t%s", i, argv[i] );
    /*
the first parameter is a place holder which meaning is explained below    
\n - new line
%d - first param integer
\t - tab space
%s - 2nd param string
     */  

  }

  return 0;

}