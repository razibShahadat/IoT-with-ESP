#include <FirebaseESP8266.h>  //https://github.com/mobizt/Firebase-ESP8266
#include <ESP8266WiFi.h>
#include <DHT.h>

#define FIREBASE_HOST "https://nodemcu-dht22-99f4c.firebaseio.com"
#define FIREBASE_AUTH "LHj8LrnHFbZvjqOHIMHsVSHiyJfoYdGiRUUkLL0y"
#define WIFI_SSID "Robo71"
#define WIFI_PASSWORD "11235813"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseJson json;

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  if (Firebase.setFloat(firebaseData, "/sensorData/Temperature", temp))
  {
    print_ok();
  }
  else
  {
    print_fail();
  }
  if (Firebase.setFloat(firebaseData, "/sensorData/Humidity", humidity))
  {
    print_ok();
  }
  else
  {
    print_fail();
  }
  
  if (isnan(humidity) || isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  delay(2000);
}

void print_ok()
{
  Serial.println("----------------");
  Serial.println("OK");
  Serial.println("PATH: " + firebaseData.dataPath());
  Serial.println("TYPE: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.println("----------------");
  Serial.println();
}

void print_fail()
{
  Serial.println("------------------------------------");
  Serial.println("FAILED");
  Serial.println("REASON: " + firebaseData.errorReason());
  Serial.println("------------------------------------");
  Serial.println();
}

void firebaseReconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
