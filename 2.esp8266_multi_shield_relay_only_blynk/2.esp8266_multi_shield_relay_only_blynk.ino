
//library
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


int MODE = 0;

/************************* Pin Definition *********************************/
//led
#define led1           15
#define led2           3 
//Relays for switching appliances
#define Relay1            14
#define Relay2            12
#define Relay3            4
#define Relay4            5


//buzzer to use it for alert
#define buzzer            16


//Analog pin to read the incoming analog value from different sensors.
#define analogpin         A0


const int dry = 765; // value sensor kering
const int wet = 385; //value sensor basah

//auth di blynk nya
char auth[] = "SL5_Bqv9HskOcnwT0oPrGFAyVn0KCofa";




BlynkTimer timer;
// ssid nama wifi
// pass diisi password
char ssid[] = "Kelg_Hadie"; // isi nama network
char pass[] = "Vitri1972" ; // isi pass wifi, kalau open network isi "";




void checkBlynk() { // memanggil setiap 3 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    MODE = 1;
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    Blynk.notify("smarthomev1.0 no wifi ") ;
  }
  if (isconnected == true) {
    MODE = 0;
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);

  }
}


void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(led1, INPUT);
  pinMode(led2, INPUT);
  pinMode(buzzer, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(3000L, checkBlynk); // check if connected to Blynk server every 3 seconds

}

void loop()
{

  timer.run();
}
