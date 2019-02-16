#include <stdio.h>
#include <wiringPi.h>

int main(int argc, char *argv[])
{
  int i;
  wiringPiSetup ();
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  while(1) {
  digitalWrite (1, HIGH);delay (500);
  digitalWrite (1,LOW); 
  printf("Waiting for reset\n");

  while(digitalRead(0) == 1){
  digitalWrite (2, HIGH); delay (500);
  printf("Alarm\n");
  }
  while(digitalRead(0) == 0){
  digitalWrite (1, HIGH); delay (500);
  digitalWrite (1,LOW); delay(500); 
  digitalWrite (2, LOW);
  printf("Wait for event\n");
  }
 }
  /*NOTREACHED*/
  return 0 ;
}
