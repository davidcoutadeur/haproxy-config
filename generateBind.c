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

  char first[]="30"; // 0x30
  char second[2+1]; // 12 + length(DN) + length(PW) (in hexa)
  char third[]="02010160";
  char fourth[2+1]; // 7 + length(DN) + length(PW) (in hexa)
  char fifth[]="02010304";
  char sixth[2+1]; // length(DN) (in hexa)
  // DN
  char eighth[]="80";
  char nineth[2+1]; // length(PW) (in hexa)
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

  // compute second
  sprintf((char*)second,"%02x",(int)(0xc+strlen(bindDN)+strlen(bindPW)));
  second[2]='\0';

  // compute fourth
  sprintf((char*)fourth,"%02x",(int)(7+strlen(bindDN)+strlen(bindPW)));
  fourth[2]='\0';

  // compute sixth
  sprintf((char*)sixth,"%02x",(int)strlen(bindDN));
  sixth[2]='\0';

  // compute nineth
  sprintf((char*)nineth,"%02x",(int)strlen(bindPW));
  nineth[2]='\0';

  // assembly
  strcat(bindRequest, first);
  strcat(bindRequest, second);
  strcat(bindRequest, third);
  strcat(bindRequest, fourth);
  strcat(bindRequest, fifth);
  strcat(bindRequest, sixth);
  strcat(bindRequest, bindDNH);
  strcat(bindRequest, eighth);
  strcat(bindRequest, nineth);
  strcat(bindRequest, bindPWH);

  printf("%s\n\n",bindRequest);

  exit(0);
}
