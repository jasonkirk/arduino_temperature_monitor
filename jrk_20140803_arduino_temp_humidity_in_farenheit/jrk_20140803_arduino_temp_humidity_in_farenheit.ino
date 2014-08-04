#include <DHT22.h>
// Only used for sprintf
#include <stdio.h>

// Data wire is plugged into port 7 on the Arduino
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)
#define DHT22_PIN 7
float ctemp, chumidity, otemp, ohumidity;

// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);

void setup(void)
{
  // start serial port
  Serial.begin(9600);
}

void loop(void)
{ 
  DHT22_ERROR_t errorCode;
  
  // The sensor can only be read from every 1-2s, and requires a minimum
  // 2s warm-up after power-on.
  delay(2000);
  
  errorCode = myDHT22.readData();
  switch(errorCode)
  {
    case DHT_ERROR_NONE:
      ctemp = myDHT22.getTemperatureC()*9/5+32;
      ohumidity = myDHT22.getHumidity();

      if (ctemp != otemp ) {
      Serial.print("Temp: ");

        Serial.print(ctemp); 
      Serial.print(" ");   
      Serial.print("Humidity: ");
      
      Serial.print(ohumidity); 
               Serial.println();
      }
      otemp = ctemp;
      ohumidity = chumidity;
      // Alternately, with integer formatting which is clumsier but more compact to store and
	  // can be compared reliably for equality:
	  //	  

      break;
    case DHT_ERROR_CHECKSUM:
      Serial.print("check sum error ");
      Serial.print(myDHT22.getTemperatureC()*9/5+32);
      Serial.print("C ");
      Serial.print(myDHT22.getHumidity());
      Serial.println("%");
      break;
    case DHT_BUS_HUNG:
      Serial.println("BUS Hung ");
      break;
    case DHT_ERROR_NOT_PRESENT:
      Serial.println("Not Present ");
      break;
    case DHT_ERROR_ACK_TOO_LONG:
      Serial.println("ACK time out ");
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
      Serial.println("Sync Timeout ");
      break;
    case DHT_ERROR_DATA_TIMEOUT:
      Serial.println("Data Timeout ");
      break;
    case DHT_ERROR_TOOQUICK:
      Serial.println("Polled to quick ");
      break;
  }
}
