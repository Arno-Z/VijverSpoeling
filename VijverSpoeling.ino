// the setup function runs once when you press reset or power the board

int levelSensorClean=2;
int levelSensorAlarm=3;
int motorRelais=10;
int solenoirRelais=11;
int alarmRelais=4;

int pollingTime = 5000; //ms
int cycleTime = 30000; //ms

bool alarmState = false;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600); 
  pinMode(levelSensorClean, INPUT_PULLUP);
  pinMode(levelSensorAlarm, INPUT_PULLUP);
  pinMode(solenoirRelais, OUTPUT);
  pinMode(motorRelais, OUTPUT);    
  pinMode(alarmRelais,OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(solenoirRelais, HIGH);
  digitalWrite(motorRelais, HIGH);
}

// the loop function runs over and over again forever
void loop() {
  int sensorValClean = digitalRead(levelSensorClean);
  if (sensorValClean == HIGH) {
    //Initialize the flush cycle
        Serial.println("Reinigen");
        if (alarmState == false){
          performClean();
        } else {
          Serial.println("Reinigen negeren, laag niveau alarm");
        }
        //Check if level did not recuce during clean
        int sensorValAlarm = digitalRead(levelSensorAlarm); 
        if (sensorValAlarm == HIGH) {
            Serial.println("Laag niveau alarm");
            digitalWrite(alarmRelais,HIGH);
            alarmState = true;
        } else {
            digitalWrite(alarmRelais,LOW);
            alarmState = false;
        }
  } else {
       Serial.println("Wacht");
  };
  delay(pollingTime);
}

void performClean(){
      Serial.println("Start reinigen");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(solenoirRelais, LOW);
      digitalWrite(motorRelais, LOW);
      
      delay(cycleTime);
      Serial.println("Reinigen voltooid");
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(solenoirRelais, HIGH);
      digitalWrite(motorRelais, HIGH);
     
}

