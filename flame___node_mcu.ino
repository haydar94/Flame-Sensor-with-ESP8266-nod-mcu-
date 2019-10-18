/*
code BY: Haydar ElAmeer
*/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

int flame=D1;
int flag=0;
int relay=D0;

void notifyOnfirefighter()
{
  int is_flame_active = !digitalRead(flame);
  if (is_flame_active==1 && flag==0) {
    digitalWrite (relay, HIGH);
    Serial.println("Fire is Burning!!");

    // Note:
    //   We allow 1 notification per 15 seconds for now.
    Blynk.notify("Alert : Fire is Burning!!");
    flag=1;
  }
  else if (is_flame_active==0){
    flag=0;
    }
}

void setup()
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(relay , OUTPUT);
  // Setup notification button on pin D1
  pinMode(flame , INPUT_PULLUP);
  timer.setInterval (1000L,notifyOnfirefighter);
}

void loop()
{
  Blynk.run();
  timer.run();
}

