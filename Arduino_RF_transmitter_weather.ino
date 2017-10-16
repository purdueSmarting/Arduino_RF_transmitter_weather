#include <DHT.h>
#include <DHT_U.h>
#include <RCSwitch.h>
#define DHTPIN 4 
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);
RCSwitch mySwitch = RCSwitch();

void setup() {
    Serial.begin(9600);
    // Transmitter is connected to Arduino Pin #12  
    Serial.println("Ready to transmit messages!");
    mySwitch.enableTransmit(12);
    dht.begin();
 
    // Optional set pulse length.
    // mySwitch.setPulseLength(320);
 
    // Optional set protocol (default is 1, will work for most outlets)
    // mySwitch.setProtocol(2);
 
    // Optional set number of transmission repetitions.
    // mySwitch.setRepeatTransmit(15);
}
void loop() {
    delay(2000);
    
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true); 
    
   // Check if any reads failed and exit early (to try again).
   if (isnan(h) || isnan(t) || isnan(f)) {
       Serial.println("Failed to read from DHT sensor!");
       return;
}

    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
 
   // Compute heat index in Celsius (isFahreheit = false)
   float hic = dht.computeHeatIndex(t, h, false);

    /* Same switch as above, but using decimal code */
    mySwitch.send(h, 24);
    delay(7000);  
    mySwitch.send(t, 24);  

    delay(20000);
}
