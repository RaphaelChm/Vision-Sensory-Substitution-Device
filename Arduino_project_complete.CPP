char Incoming_value = 0;                //Variable for storing Incoming_value


  int charMatrix[26][6] = {
    {1, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 0, 0},
    {1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 0, 0},
    {1, 0, 0, 1, 0, 0},
    {1, 1, 1, 0, 0, 0},
    {1, 1, 1, 1, 0, 0},
    {1, 0, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 0},
    {0, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 1, 0},
    {1, 0, 1, 0, 1, 0},
    {1, 1, 0, 0, 1, 0}, 
    {1, 1, 0, 1, 1, 0},
    {1, 0, 0, 1, 1, 0},
    {1, 1, 1, 0, 1, 0},
    {1, 1, 1, 1, 1, 0}, 
    {1, 0, 1, 1, 1, 0},
    {0, 1, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 0}, 
    {1, 0, 0, 0, 1, 1},
    {1, 0, 1, 0, 1, 1},
    {0, 1, 1, 1, 0, 1},
    {1, 1, 0, 0, 1, 1}, 
    {1, 1, 0, 1, 1, 1},
    {1, 0, 0, 1, 1, 1},
  };

  int pinMatrix[6] = {22,23,32,33,38,39};


//Buzzer and US Sensor setup
const int trigPin = 9;
const int echoPin = 10;

int buzzer = 8;
long duration;
int distance;
int d;

int distArray[5] = {0, 0, 0, 0, 0}; 

void setup() 
{
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(40, OUTPUT);
  pinMode(39, OUTPUT);    // sets the digital pin 5 as output
  pinMode(38, OUTPUT);    // sets the digital pin 4 as output
  pinMode(37, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(0, INPUT);
  pinMode(1, INPUT);

  //3 rows of 3 motors
  // Listed in descending order from finger tips:
  //Row 1: 22, 23, 24
  //Row 2: 32, 33, 34
  //Row 3: 38, 39, 40

  //22, 32, 38 = ring finger
  //23, 33, 39 = middle finger
  //24, 34, 40 = index finger

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(buzzer, OUTPUT);
}

void loop()
{

  // US Sensor and Buzzer Code:
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;

  d++;
  
  distArray[d] = distance;
  
  int dA;
  int dFA;
  for(int a = 0; a < d+1; a++){
  dA = dA + distArray[a];
  }
  dFA = dA/d;
  
  if(d >= 5){
    d = 0;
  }

  
  
  if(dFA < 400){
    tone(buzzer, dFA);
  }
  else if(dFA > 400){
    tone(buzzer, dFA);
  }
  

  //Text-to-Braille Code:
  int row;
  if(Serial.available() > 0)  
  {
    Incoming_value = Serial.read();      //Read the incoming data and store it into variable Incoming_value
    Serial.print(Incoming_value);        //Print Value of Incoming_value in Serial monitor
    Serial.print("\n");                  //New line 
    int intVal = (int)Incoming_value;
    
    if(isupper(Incoming_value)){
      row = Incoming_value - 65;
    }
    else if(islower(Incoming_value)){
      row = Incoming_value - 97;
    }
    
    for(int i = 0; i <6; i++){
      digitalWrite(pinMatrix[i], charMatrix[row][i]);
    }
    
    delay(500);
    
    for(int i = 0; i <6; i++){
    digitalWrite(pinMatrix[i], LOW);
    }
}   
}           
