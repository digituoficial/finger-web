#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int getFingerprintID();

SoftwareSerial mySerial(2, 3);


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  Serial.begin(9600);


  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Sensor encontrado!");
  } else {
    Serial.println("O sensor não pode ser encontrado :(");
    while (1);
  }
  Serial.println("COLOQUE SEU DEDO :)");
}

void loop()
{
  getFingerprintID();
  delay(50);
}

int getFingerprintID() {
  uint8_t p = finger.getImage(); // search erros
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  Serial.print("SUA ID FOI ENCONTRADA. ESSA --> ");
  Serial.print(finger.fingerID); // print finger id
  Serial.print(" Dado de confidencia ");
  Serial.println(finger.confidence); // confiderence number
  return finger.fingerID; 
}
