/*Pendeldemo 
 * 
 * Pendelen tussen 2 stations waarbij binnen 2,5 s geremd wordt op een trigger van één van de sensoren. Na 2 seconden wordt er weer binnen 2,5s opgetrokken, om het proces te herhalen.
 */
int pSensor_1 = 3;                              //sensor bij station A
int pSensor_2 = 4;                              //sensor bij station B
int pRichting_v = 5;                            //Vooruit rijden A->B, naar IN1 op L298
int pRichting_a = 6;                            //Achteruit rijden B->A, naar IN2 op L298
int pRijspanning = 9;                           //PWM-pin naar ENA op L298
bool bRichting = false;                          //Rijrichting, true = vooruit
int iRijSpanning = 0;                           //Waarde tussen 0 (0V) en 255 (5V)

enum States{
  stWachtenStation,
  stAanzetten,
  stRijden,
  stAfremmen
};

enum States states = stWachtenStation;

void setup() {
  // put your setup code here, to run once:
  pinMode(pSensor_1, INPUT); 
  pinMode(pSensor_2, INPUT); 
  pinMode(pRichting_v, OUTPUT); 
  pinMode(pRichting_a, OUTPUT); 
  pinMode(pRijspanning, OUTPUT); 
   Serial.begin(9600);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (states)
  {
    case stWachtenStation:                          //Wachten op station 
      
      Serial.print(bRichting);
        Serial.print('\n');
      setDirection(bRichting);                      //Richting naar pinnen wegschrijven 
      delay(2000);                                  //wacht 2 seconden
      states = stAanzetten;
    break;

    case stAanzetten:                               //Optrekken van 0 naar 250 in stapjes met 10 ms tussenpozen
      for(int i = 0; i < 250; i++)
      {
        iRijSpanning++;
        analogWrite(pRijspanning, iRijSpanning);    //Huidige rijstap naar PWM-pin wegschrijven
        //Serial.print(iRijSpanning);
        //Serial.print('\n');
        delay(10);
      }
      states = stRijden;
    break;

    case stRijden:
      if (bRichting == true)                        //Vooruit, dus van A naar B
      {
        if (digitalRead(pSensor_2))                 //Wacht totdat je de sensor bij station B ziet
        {
          states = stAfremmen;
          bRichting = false;                   //Richting veranderen
        }
      }
      else                                           //Achteruit, dus van B naar A
      {
        if (digitalRead(pSensor_1))                  //Wacht totdat je de sensor bij station A ziet
        {
          states = stAfremmen;
          bRichting = true;                    //Richting veranderen
        }
      }
    break;

    case stAfremmen:
       for(int i = 0; i < 250; i++)
       {
         iRijSpanning--;                               //Van 250 naar 0 in stapjes met 10 ms tussenpozen
         analogWrite(pRijspanning, iRijSpanning);      //Huidige rijstap naar PWM-pin wegschrijven
         //Serial.print(iRijSpanning);
         //Serial.print('\n');
         delay(10);
       }
       states = stWachtenStation; 
    break;
  }
}

void setDirection(bool richting){
  digitalWrite(pRichting_v, LOW);                       //Dode tijd (om kortsluiting in H-brug te vermijden)
  digitalWrite(pRichting_a, LOW);
  delay(100);
  if (richting == true)                                 //Vooruit
  {
    digitalWrite(pRichting_v, HIGH);
    digitalWrite(pRichting_a, LOW);
  }
  else                                                  //Achteruit
  {
    digitalWrite(pRichting_v, LOW);
    digitalWrite(pRichting_a, HIGH);
  }
}
