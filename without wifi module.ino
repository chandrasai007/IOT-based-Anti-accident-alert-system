const int trig = 12;
const int echo = 11;
const int leftForward = 6;
const int leftBackward = 7;
const int rightForward = 4;
const int rightBackward = 5;
const int buzzer = 10;



int duration = 0;
int distance = 0;

void setup() 
{
  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);
pinMode(buzzer, OUTPUT);


  
  Serial.begin(9600);

}

void loop()
{
  digitalWrite(trig , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig , LOW);


  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;
  Serial.println(distance);
  

  if ( distance > 20 )
  {
    digitalWrite(leftForward , LOW);
    digitalWrite(leftBackward , HIGH);//if the obstacle is greater than 20--moving forward
    digitalWrite(rightForward , HIGH);
    digitalWrite(rightBackward , LOW);
 digitalWrite(buzzer, LOW);

    delay(100);
  }
 else if( distance >10 ) 
 {
  digitalWrite(leftForward , HIGH);
    digitalWrite(leftBackward , LOW);
    digitalWrite(rightForward , HIGH);// if obstacle is greater than 10 and lessthan 20--moving left
    digitalWrite(rightBackward , LOW);
 digitalWrite(buzzer, HIGH);


 }
else 
  {
    digitalWrite(leftForward , LOW);
    digitalWrite(leftBackward , LOW);// if obstacle is less than 10--automatic braking stop
    digitalWrite(rightForward , LOW);
    digitalWrite(rightBackward , LOW);
    digitalWrite(buzzer, HIGH);

  }
}

