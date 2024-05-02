#include <Servo.h>
const int servoPin = 7;
Servo myServo;

const int ledPin = 8;
const int trigPin = 5;
const int echoPin = 6;

long duree;
int distance1 = 0;
int distance2 = 0;
double vitesse = 0;
int distance = 1;
float temps = 1;
float temps_attente = 1000*temps;
float limite = 35;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(ledPin, OUTPUT);

    Serial.begin(9600);

    myServo.attach(servoPin);
    myServo.write(90);
}

void loop() {
    CalculVitesse();
}

float CalculDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duree = pulseIn(echoPin, HIGH);
    distance = (duree*0.034)/2;

    Serial.print("distance en cm : ");
    Serial.println(distance);

    return distance;
}

void CalculVitesse() {
    distance1 = CalculDistance();
    delay(temps_attente);
    distance2 = CalculDistance();
    vitesse = abs(distance1 - distance2)/temps;;

    Serial.print("vitesse en cm/s : ");
    Serial.println(vitesse);

    if (vitesse > limite) {
        digitalWrite(ledPin, HIGH);
        myServo.write(0);
        delay(1000);
        myServo.write(90);
    }
    else {
        digitalWrite(ledPin, LOW);
    }
}