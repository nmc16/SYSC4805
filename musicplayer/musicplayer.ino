String message; //string that stores the incoming message

void setup()
{
  Serial.begin(9600); //set baud rate
  pinMode(4, OUTPUT);
}
//fm  =  2(m−69)/12(440 Hz)
void loop()
{
  while(Serial.available())
  {//while there is data available on the serial monitor
    
    message+=char(Serial.read());//store string from serial command
  }
  if(!Serial.available())
  {
    if(message!="")
    {//if data is available
      //Serial.println(message); //show the data
      float x = (message.toInt() - 69) / 12.0;
      int fm = pow(2.0, x) * 440; 
      tone(4, fm, 125);
      
      message=""; //clear the data
    }
  }
  delay(10); //delay
}
    


