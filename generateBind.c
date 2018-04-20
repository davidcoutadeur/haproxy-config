/* generateBind.c
 * generate a bind request with a DN + password
 * 20/04/2018
 * David Coutadeur
 */

/* Declaring using modern UNIX */
#define _POSIX_C_SOURCE 199309L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
  char bindDN[512];
  char bindDNH[1024];
  char bindPW[256];
  char bindPWH[512];

  char bindRequest[2048]; // store the bind request in hexadecimal
  char begin[]="3034020101602f0201030422"; // beginning of the bind request
  char middle[]="8006";

  int i=0, j=0;


  if( argc != 3) {
    printf("Error; argument missing\n");
    printf(" - DN: bind distinguished name for authentication\n");
    printf(" - PW: corresponding password\n\n");
    exit(1);
  }
  strcpy(bindDN, argv[1]);
  strcpy(bindPW, argv[2]);

  printf(" - DN: %s\n", bindDN);
  printf(" - PW: %s\n\n", bindPW);

  // Convert DN to hexadecimal string
  for(i=0,j=0;i<strlen(bindDN);i++,j+=2)
  {
    sprintf((char*)bindDNH+j,"%02x",bindDN[i]);
  }
  bindDNH[j]='\0';

  // Convert PW to hexadecimal string
  for(i=0,j=0;i<strlen(bindPW);i++,j+=2)
  {
    sprintf((char*)bindPWH+j,"%02x",bindPW[i]);
  }
  bindPWH[j]='\0';

  // assembly
  strcat(bindRequest, begin);
  strcat(bindRequest, bindDNH);
  strcat(bindRequest, middle);
  strcat(bindRequest, bindPWH);

  printf("%s\n\n",bindRequest);

  exit(0);
}
