 /*---------- COMMANDES ----------
  - tourne gauche
  - tourne droite
  - marche avant gauche
  - marche avant droite
  - recule gauche
  - recule droite
  - stop
  - marche
  - clignotant gauche
  - clignotant droite */
 
 #include <SoftwareSerial.h>
 #include <AFMotor.h>
 #include <Servo.h >


SoftwareSerial BT(3,2);
Servo servo;

char voice;
String test ="\0";
const int clignotGauche = 12;
const int clignotDroite = 13;
bool isClignotGauche = false;
bool isClignotDroite = false;

int servoPos = 45;

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BT.begin (9600);
  pinMode(clignotGauche, OUTPUT);
  pinMode(clignotDroite, OUTPUT);

  servo.attach(10);
  servo.write(servoPos);

  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void loop() {  
  while (BT.available()>0)
  {
    voice = BT.read();
    delay(10);
    test += voice;
    Serial.print(test);
    Serial.print("\n");
  
  }
  
  if (test.length() > 0)
  {
    if (test == "tourne gauche")
    {
      test ='\0';
      turnLeft(&servo);
    }
    else if (test == "tourne droite")
    {
      test ='\0';
      turnRight(&servo);
    }
    else if (test == "marche avant gauche")
    {
      test ='\0';
      turnLeft(&servo);
      run(&motor1, FORWARD);
      run(&motor2, FORWARD);
    }
    else if (test == "marche avant droite")
    {
      test ='\0';
      turnRight(&servo);
      run(&motor1, FORWARD);
      run(&motor2, FORWARD);
    }
    else if (test == "recule gauche")
    {
      test ='\0';
      turnLeft(&servo);
      run(&motor1, BACKWARD);
      run(&motor2, BACKWARD);
    }
    else if (test == "recule droite")
    {
      test ='\0';
      turnRight(&servo);
      run(&motor1, BACKWARD);
      run(&motor2, BACKWARD);
    }
    else if (test = "stop")
    {
      test ='\0';
      turnRight(&servo);
      run(&motor1, RELEASE);
      run(&motor2, RELEASE);
    }
    else if (test == "marche")
    {
      test = '\0';
      servo.write(45);
      run(&motor1, RELEASE);
      run(&motor2, RELEASE);
    }
    else if (test = "clignotant gauche")
    {
      isClignotGauche = !isClignotGauche;
    }
    else if (test = "clignotant droite")
    {
      isClignotDroite = !isClignotDroite;
    }
    else { test='\0';}
  }

  if (isClignotGauche) {
    digitalWrite(clignotGauche, HIGH);
    delay(200);
    digitalWrite(clignotGauche, LOW);
    delay(200);
  }

  if (isClignotDroite) {
    digitalWrite(clignotDroite, HIGH);
    delay(200);
    digitalWrite(clignotDroite, LOW);
    delay(200);
  }
}

/*
* Fonction pour l'accélération d'un moteur
* Exemple: accelerate(&motor1);
*/
void accelerate(AF_DCMotor * motor) {
  uint8_t i;
  for (i = 0; i < 255; i++) {
    motor->setSpeed(i);
    delay(10);
  }
}

/*
* Fonction pour la décélération d'un moteur
* Exemple: decelerate(&motor1);
*/
void decelerate(AF_DCMotor * motor) {
  uint8_t i;
  for (i = 255; i >= 0; i--) {
    motor->setSpeed(i);
    delay(10);
  }
}

/*
* Fonction pour mettre le moteur
* marche avant/arrière ou en arrêt
* Exemple:
*   - run(&motor1, FORWARD);
*   - run(&motor2, BACKWARD);
*/
void run(AF_DCMotor * motor, int direction) {
  switch (direction) {
    case FORWARD:
      motor->run(FORWARD);
      accelerate(motor);
      break;
    case BACKWARD:
      motor->run(BACKWARD);
      accelerate(motor);
      break;
    case RELEASE:
      motor->run(RELEASE);
      decelerate(motor);
      break;
    default:
      break;
  }
}

void turnRight(Servo * _servo) {
  if (!_servo->attached())
    _servo->attach(10);
  servoPos = 90;
  for (servoPos; servoPos >= 0; servoPos--) {
    _servo->write(servoPos);
   // delay(10);
  }
}

/*
* Fonction qui sert à faire tourner les roues vers la droite
* Exemple:  turnRight(&servo);
*/
void turnLeft(Servo * _servo) {
  if (!_servo->attached())
    _servo->attach(10);
  servoPos = 45;
  for (servoPos; servoPos <= 90; servoPos++) {
    _servo->write(servoPos);
    //delay(10);
  }
}
