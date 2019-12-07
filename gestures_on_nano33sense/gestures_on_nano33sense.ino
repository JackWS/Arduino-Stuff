//Motion Sensor
#include <Arduino_APDS9960.h> 
//Temp and Barometer
#include <Arduino_HTS221.h> 

//Establish LED Constants
  const int ledPin1 = 22;
  const int ledPin2 = 23;
  const int ledPin3 = 24;



void setup() {
//Set up LEDs to receive signal
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  // below is code to turn off RGB led (they are fliped LOW means on )
  digitalWrite(ledPin1, HIGH); // red
  digitalWrite(ledPin2, HIGH); // green
  digitalWrite(ledPin3, HIGH); // blue

//Set up Serial
  Serial.begin(9600);
  while (!Serial);


  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }

if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
  

  // for setSensitivity(..) a value between 1 and 100 is required.
  // Higher values makes the gesture recognition more sensible but less accurate
  // (a wrong gesture may be detected). Lower values makes the gesture recognition
  // more accurate but less sensible (some gestures may be missed).
  // Default is 80
  //APDS.setSensitivity(80);
//  Serial.println("Detecting gestures ...");
}

// Establish vals for proximity and colors
  int proximity = 0;
//  int r = 0, g = 0, b = 0;
  unsigned long lastUpdate = 0;


void loop() {

  if (APDS.gestureAvailable()) {
    // a gesture was detected, read and print to serial monitor
    int gesture = APDS.readGesture();
    

    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        digitalWrite(ledPin1, LOW);
        delay(1000);
        digitalWrite(ledPin1, HIGH);
        break;

      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        digitalWrite(ledPin2, LOW);
        delay(1000);
        digitalWrite(ledPin2, HIGH);
        break;

      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        digitalWrite(ledPin3, LOW);
        delay(1000);
        digitalWrite(ledPin3, HIGH);
        break;

      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        break;

      default:
        // ignore
        break;
    }
  }

// check if a color reading is available
  while (! APDS.colorAvailable()) {
    delay(5);
  }
  int r, g, b;

  // read the color
  APDS.readColor(r, g, b);
    Serial.print("PR=");
    Serial.print(proximity);
    Serial.print(" rgb=");
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.println(b);
 
// Do Temp and Humidity
  float temperature = HTS.readTemperature();
  float humidity    = HTS.readHumidity();
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");
  // print an empty line
  Serial.println();
 
  delay(1000);  
}
