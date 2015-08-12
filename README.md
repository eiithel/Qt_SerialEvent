
#Qt_SerialEvent

Qt_SerialEvent is A simple application which listens to the serialport in order to pick up a button state and react in consequences. 

The Framework used is `Qt`. 
Basically we use these libraries:
+     `QtSerialPort`
+ `QtWebSockets`
	+  _(`QNetworkAccessManager` and `QNetworkRequest` classes seem more accurate)_ 

###**Arduino routine**
The arduino sends continiously the state of a button.
The Arrietta analyse the state and orders the Arduino to switch _ON_ or switch _OFF_ the led according to the button's state.

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
>There is still a problem even though. Even if datas coming from the Arduino are well processed by the application, the processing is stopped after 20s. This issue comes from:

###**serialportlistenner.cpp**
```cpp
connect(&m_timer, SIGNAL(timeout()),SLOT(handleTimeout()));


m_timer.start(20000);//program stops after 20s
```

![image2](https://github.com/eiithel/Qt_SerialEvent/blob/master/Images/Qt_pro2.png)
> A little display of the shell

