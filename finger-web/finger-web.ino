#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Ethernet config
byte mac[] = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
//IPAddress ip(, , , );
//IPAddress server(, , , );

// MQTT config

//EthernetClient ethClient;
//PubSubClient client(ethClient);
#define PORT 1883

// sensor config
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


int getFingerprintID();
int reconnect();

void setup()  
{
  Serial.begin(57600);


  finger.begin(57600);
  //client.setServer(server, PORT);

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
