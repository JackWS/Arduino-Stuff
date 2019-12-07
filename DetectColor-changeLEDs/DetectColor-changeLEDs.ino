/* Code to set LEDs to RGB based on RGB values.
 * There is no approximate here, we are being arbitrary. The result depends on what color 
 * the sensor thinks is predominate. 
 *  Warning: Depending on your lighting, one of the Led pins may show a color constantly 
 *  depending on what it detects
 *  
 */

#include <Arduino_APDS9960.h>

//Establish LED Constants
  const int ledPin1 = 22;
  const int ledPin2 = 23;
  const int ledPin3 = 24;


void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }

//Set up LEDs to receive signal
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  // below is code to turn off RGB led (they are fliped LOW means on )
  digitalWrite(ledPin1, HIGH); // red
  digitalWrite(ledPin2, HIGH); // green
  digitalWrite(ledPin3, HIGH); // blue
  
}

void loop() {
  // check if a color reading is available
  while (! APDS.colorAvailable()) {
    delay(5);
  }
  int r, g, b;

  // read the color
  APDS.readColor(r, g, b);

  // print the values
  Serial.print("r = ");
  Serial.println(r);
  Serial.print("g = ");
  Serial.println(g);
  Serial.print("b = ");
  Serial.println(b);
  Serial.println();

int detectedColor;

//Figure out the color

if( (r >= g) & (r >= b)){
   detectedColor = 1;
};

if ((g >= r) & (g >= b)){
  detectedColor = 2;
};

if ((b >= r) & (b >= g)){
   detectedColor = 3;
};


switch (detectedColor) {
      case 1:
        digitalWrite(ledPin1, LOW);
        
          Serial.print("red");
          Serial.println();
        delay(2500);
        digitalWrite(ledPin1, HIGH);
        break;

      case 2:
        digitalWrite(ledPin2, LOW);
        
          Serial.print("green");
          Serial.println();
        delay(2500);
        digitalWrite(ledPin2, HIGH);
        break;

      case 3:
        digitalWrite(ledPin3, LOW);
        
          Serial.print("blue");
          Serial.println();
        delay(2500);
        digitalWrite(ledPin3, HIGH);
        break;
        
      default:
        // ignore
        
        break;
    }
// Reset LEDs
digitalWrite(ledPin1, HIGH);
digitalWrite(ledPin2, HIGH);
digitalWrite(ledPin3, HIGH);
 
}
