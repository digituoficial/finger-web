#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int getFingerprintID();

SoftwareSerial mySerial(2, 3);


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  Serial.begin(9600);

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Sensor encontrado!");
  } else {
    Serial.println("O sensor não pode ser encontrado :(");
    while (1);
  }
  Serial.println("COLOQUE SEU DEDO :)");
}

void loop()                     // run over and over again
{
  getFingerprintID();
  delay(50);            //don't ned to run this at full speed.
}

int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("SUA ID FOI ENCONTRADA. ESSA --> ");
  Serial.print(finger.fingerID); // print finger id
  Serial.print(" Dado de confidencia ");
  Serial.println(finger.confidence); // confiderence number
  return finger.fingerID; 
}
