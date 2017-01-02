#include <SPI.h>

int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read
bool written = false;

void setup() {
  Serial.begin(9600);          //  setup serial
  Serial.println("started");

    // turn on SPI in slave mode
  SPCR |= bit (SPE);

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  
  val = 0;  

  // now turn on interrupts
  SPI.attachInterrupt();
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{

  SPDR = (byte)val;
  written = true;
      
}  // end of interrupt routine SPI_STC_vect

void loop() {

  if (written) {
    Serial.print("written: ");
    Serial.print(val);
    Serial.print("\n");
    written = false;
  }
  val = analogRead(analogPin) >> 2;    // read the input pin
//  Serial.println(val);             // debug value
}
