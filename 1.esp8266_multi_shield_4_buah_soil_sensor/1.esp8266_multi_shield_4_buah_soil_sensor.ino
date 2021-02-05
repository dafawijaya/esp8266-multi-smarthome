
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

//Selection pins for multiplexer module to switch between different sensors and give data on a single analog pin.
#define S0                0
#define S1                2

//Analog pin to read the incoming analog value from different sensors.
#define analogpin         A0

int soilmoisture1 = 0;
int persentase1 = 0;
int soilmoisture2 = 0;
int persentase2 = 0;
int soilmoisture3 = 0;
int persentase3 = 0;
int soilmoisture4 = 0;
int persentase4 = 0;

const int dry = 765; // value sensor kering
const int wet = 385; //value sensor basah

//auth di blynk nya
char auth[] = "SL5_Bqv9HskOcnwT0oPrGFAyVn0KCofa";




BlynkTimer timer;
// ssid nama wifi
// pass diisi password
char ssid[] = "Kelg_Hadie"; // isi nama network
char pass[] = "Vitri1972" ; // isi pass wifi, kalau open network isi "";


// void sensor untuk definisi jenis sensor
void sendSensor()
{

  Blynk.virtualWrite(V10, soilmoisture1);
  Blynk.virtualWrite(V11, persentase1);
  Blynk.virtualWrite(V12, soilmoisture2);
  Blynk.virtualWrite(V13, persentase2);
  Blynk.virtualWrite(V14, soilmoisture3);
  Blynk.virtualWrite(V15, persentase3);
  Blynk.virtualWrite(V16, soilmoisture4);
  Blynk.virtualWrite(V17, persentase4);
}


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

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(led1, INPUT);
  pinMode(led2, INPUT);
  pinMode(buzzer, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(3000L, checkBlynk); // check if connected to Blynk server every 3 seconds
  timer.setInterval(1000L, sendSensor);
}

void loop()
{

  // Address 00
  // soil 1
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  soilmoisture1 = analogRead(analogpin);
  persentase1 = map(soilmoisture1, wet, dry, 100, 0);
  Serial.print("soil val - "); Serial.println(  soilmoisture1);
  Serial.print("persentase - "); Serial.println(persentase1);
  ;

  // Address 10
  // soil 2
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  soilmoisture2 = analogRead(analogpin);
  persentase2 = map(soilmoisture2, wet, dry, 100, 0);



  // Address 01
  // soil 3
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  soilmoisture3 = analogRead(analogpin);
  persentase3 = map(soilmoisture3, wet, dry, 100, 0);




  // Address 11
  // soil 4
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  soilmoisture4 = analogRead(analogpin);
  persentase4 = map(soilmoisture4, wet, dry, 100, 0);



  timer.run();
}
