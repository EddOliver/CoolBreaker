/*
50A Current Sensor(AC/DC)(SKU:SEN0098) Sample Code
This code shows you how to get raw datas from the sensor through Arduino and convert the raw datas to the value of the current according to the datasheet;
Smoothing algorithm (http://www.arduino.cc/en/Tutorial/Smoothing) is used to make the outputting current value more reliable;
Created 27 December 2011
By Barry Machine 
www.dfrobot.com
Version:0.2
*/
#define LED_BUILTIN 25

const int numReadings = 30;
float readings[numReadings];      // the readings from the analog input
int index1 = 0;                  // the index of the current reading
float total = 0;                  // the running total
float average = 0;                // the average

float currentValue = 0;


void setup()
{
  Serial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;   
  
   
      
}

void loop()
{   
    total= total - readings[index1];          
    readings[index1] = analogRead(A0); //Raw data reading
    readings[index1] = (readings[index1]-2048)*3.3/4096/0.04+5.04;//Data processing:510-raw data from analogRead when the input is 0; 5-5v; the first 0.04-0.04V/A(sensitivity); the second 0.04-offset val;
    total= total + readings[index1];       
    index1 = index1 + 1;                    
    if (index1 >= numReadings)              
      index1= 0;                           
    average = total/numReadings;   //Smoothing algorithm (http://www.arduino.cc/en/Tutorial/Smoothing)    
    currentValue= average;
    Serial.println(currentValue);
    

    if (currentValue > 0.28) digitalWrite(LED_BUILTIN, LOW);
    
   
    delay(10);
    
}

