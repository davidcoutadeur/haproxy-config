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

  char first[4+1]; // 0x3009 + length(DN) + length(PW)
  char second[]="02010160";
  char third[2+1]; // length(DN) + length(PW) - 11
  char fourth[]="02010304";
  char fifth[2+1]; // length(DN) - 12
  // DN
  char seventh[]="80";
  char eighth[2+1]; // length(PW)
  // PW

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

  // compute first
  sprintf((char*)first,"%04x",(int)(0x3009+strlen(bindDN)+strlen(bindPW)));
  first[4]='\0';

  // compute third
  sprintf((char*)third,"%02x",(int)(strlen(bindDN)+strlen(bindPW)-0xb));
  third[2]='\0';

  // compute fifth
  sprintf((char*)fifth,"%02x",(int)(strlen(bindDN)-0xc));
  fifth[2]='\0';

  // compute eighth
  sprintf((char*)eighth,"%02x",(int)strlen(bindPW));
  eighth[2]='\0';

  // assembly
  strcat(bindRequest, first);
  strcat(bindRequest, second);
  strcat(bindRequest, third);
  strcat(bindRequest, fourth);
  strcat(bindRequest, fifth);
  strcat(bindRequest, bindDNH);
  strcat(bindRequest, seventh);
  strcat(bindRequest, eighth);
  strcat(bindRequest, bindPWH);

  printf("%s\n\n",bindRequest);

  exit(0);
}
