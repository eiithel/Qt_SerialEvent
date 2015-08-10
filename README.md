
#Qt_SerialEvent

Qt_SerialEvent is A simple application which listens to the serialport in order to pick up a button state and react in consequences. 

The Framework used is `Qt`. 
Basically we use this libraries:
*  QtSerialPort
*  QtWebSockets

###**Arduino routine**
The arduino sends continiously a button state.
The Arrietta analyze the state and orders the Arduino to switch _ON_ or switch _OFF_ the led according to the button state.

```C
int led = 13;
String inData;

void setup() {
  digitalWrite(led, HIGH);
  Serial.begin(9600);
  
  Serial.println("HIGH");
  delay(100);
  Serial.println("LOW");
  delay(100);
}

void loop() {

   while (Serial.available() > 0)
    {
        char recieved = Serial.read();
        inData += recieved; 
        if (recieved == '\n')
        {
            Serial.print("Arduino Received: ");
            Serial.print(inData);
            if(inData == "LEDON\n"){
              digitalWrite(led, HIGH);
            }  
            if(inData == "LEDOFF\n"){
              digitalWrite(led, LOW);
            }
            inData = "";
        }
    }
     Serial.println("HIGH");
     delay(100);
     Serial.println("LOW");
     delay(100);
  }

```

> Written with [StackEdit](https://stackedit.io/).
