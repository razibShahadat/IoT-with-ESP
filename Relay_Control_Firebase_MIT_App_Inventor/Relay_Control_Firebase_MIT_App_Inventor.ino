#include <FirebaseESP8266.h>  //https://github.com/mobizt/Firebase-ESP8266
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "https://esptest-5ebcd-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "U2xnbs8x5ZP7ItUqaLbsYkUrMIIiVUU2BUVuvcCM"
#define WIFI_SSID "Robo71"
#define WIFI_PASSWORD "11235813"

#define LED4 2 //D6
#define LED3 0
#define LED2 4
#define LED1 5

int value1, value2, value3, value4, State;

FirebaseData firebaseData;

void setup()
{
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void firebasereconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop()
{

  if (Firebase.get(firebaseData, "/S1")) {
    if (firebaseData.dataType() == "string") {
      value1 = firebaseData.stringData().toInt();
    }
  }

  if (Firebase.get(firebaseData, "/S2")) {
    if (firebaseData.dataType() == "string") {
      value2 = firebaseData.stringData().toInt();
    }
  }

  if (Firebase.get(firebaseData, "/S3")) {
    if (firebaseData.dataType() == "string") {
      value3 = firebaseData.stringData().toInt();
    }
  }

  if (Firebase.get(firebaseData, "/S4")) {
    if (firebaseData.dataType() == "string") {
      value4 = firebaseData.stringData().toInt();
    }
  }

  if (value1 == 1)
  {
    digitalWrite(LED1, LOW);
    Serial.println("LED1 ON");
  }
  else if (value1 == 0)
  {
    digitalWrite(LED1, HIGH);
    Serial.println("LED1 OFF");
  }

  if (value2 == 1)
  {
    digitalWrite(LED2, LOW);
    Serial.println("LED2 ON");
  }
  else if (value2 == 0)
  {
    digitalWrite(LED2, HIGH);
    Serial.println("LED2 OFF");
  }

  if (value3 == 1)
  {
    digitalWrite(LED3, LOW);
    Serial.println("LED3 ON");
  }
  else if (value3 == 0)
  {
    digitalWrite(LED3, HIGH);
    Serial.println("LED3 OFF");
  }

  if (value4 == 1)
  {
    digitalWrite(LED4, LOW);
    Serial.println("LED4 ON");
  }
  else if (value4 == 0)
  {
    digitalWrite(LED4, HIGH);
    Serial.println("LED4 OFF");
  }

}
