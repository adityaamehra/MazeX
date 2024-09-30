/*
* in3 (HIGH) := Is going backwards of right when looking from the perspective of ultrasonic
* in1 (HIGH) := Is going backwards of left when looking from the perspective of ultrasonic
*/

#define FRS A1
#define FLS A5
#define RS A2
#define MS A3
#define LS A4 // Pin where the IR sensor is connected
int ivm = 0;
int ivl = 0;
int ivr = 0;   // Variable to store the value from the sensor

int turn=0;

long dur;
int dis;
char TURN_TYPES[4]={'L','R','T','P'};
char TURN='f';
int a=0,b=1,k=0,t=0,j=0; //a means rows of matrix arr, b means column of matrix arr, k=0 then going forward along right path k=1 backpath k=2 only for plus 
char arr[10][10]={0};

const int ena = 5;
#define LM1 10
#define LM2 9

#define RM1 12
#define RM2 11
const int enb = 6;

const int tp = 3;
const int ep = 4;
void reset(void)
{
  analogWrite(ena,140);
  analogWrite(enb,160);
}
void sharp_left()
{
  analogWrite(ena,70);
  analogWrite(enb,90);
}
void sharp_right()
{
  analogWrite(ena,70);
  analogWrite(enb,90);
}

void setup() {
  // Define pin modes
  pinMode(MS, INPUT);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(FRS, INPUT);
  pinMode(FLS, INPUT);
  pinMode(tp,OUTPUT);
  pinMode(ep,INPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  analogWrite(ena,140);
  analogWrite(enb,160);

  Serial.begin(9600);
}
void left()
{
  reset(); 
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW); 
  digitalWrite(RM2, LOW);
  Serial.println("Left");
}
void right()
{     
  reset();
  digitalWrite(LM1, LOW); 
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  Serial.println("Right");
}
void forward()
{
reset();
  Serial.println("move forward");
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}
void u_turn()
{
  t++;
  reset();
  Serial.println("u_turn");
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH); 
  digitalWrite(RM2, LOW);
  k=t%2==0?0:1;
  j=t%2==0?0:1;
  reset();
}
//void check_i()
//{
//  if(j==1)
//  a++;
//  else
//  a--;
//}
void check_b()
{
  if(j==0)
  b++;
  else
  b--;
}
void loop() {
  if(!digitalRead(MS) && digitalRead(FLS) && !digitalRead(FRS))
  {
    TURN='l';
  }
  else if(!digitalRead(MS) && !digitalRead(FLS) && digitalRead(FRS))
  {
    TURN='r';
  }
  else if(digitalRead(MS) && digitalRead(FLS) && !digitalRead(FRS))
  {
    TURN='L';
  }
  else if(digitalRead(MS) && !digitalRead(FLS) && digitalRead(FRS))
  {
    TURN='R';
  }
  else if(!digitalRead(MS) && digitalRead(FLS) && digitalRead(FRS))
  {
    TURN='T';
  }
  else if(digitalRead(MS) && digitalRead(FLS) && digitalRead(FRS))
  {
    TURN='P';
  }
  else if(!digitalRead(MS) && !digitalRead(FLS) && !digitalRead(FRS))
  {
    TURN='U';
  }
  
  turn=digitalRead(FLS)+digitalRead(LS)-digitalRead(RS)-digitalRead(FRS);
 if(digitalRead(MS))     // Middle Sensor On Line
 {
  if(!digitalRead(LS) && !digitalRead(RS)) //LS and RS not on line
    {
    Serial.println("move forward");
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    }
    else if(digitalRead(LS) && !digitalRead(RS) || turn >0 ) //Sharp Left
    {
          analogWrite(ena,70);
    analogWrite(enb,90);
    Serial.println("Sharp Left");
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH); 
    digitalWrite(RM2, LOW);
    reset();
    }
    else if(!digitalRead(LS) && digitalRead(RS) || turn < 0) //Sharp Right
    {
          analogWrite(ena,70);
    analogWrite(enb,90);
    Serial.println("Sharp Right");
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
        reset();
    }
    else if(digitalRead(LS) && digitalRead(RS))
    {
      Serial.println("move forward");
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
    }}
    
    
 

    else
    {
      reset();
    digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      delay(5); 

     switch(TURN)
     {
      case 'l':left();
             
             arr[a][b]='l';
             check_b();
             
             break;
      case 'r':right();
      
             arr[a][b]='r';
             check_b();
             
             break;
      case 'L':
             if(j==0)
             k=0;
             if(k==0)
             {
              if(j==0)
              {
              for(int i=2;i<10;i++)
              {
                arr[a][i]='0';
              }
              a++;
              arr[a][0]='L';
              reset();
              forward();
              b=1;
              arr[a][b]='f';
              check_b();
              }
              else if(j==1)
              {
                if(arr[a][1]=='r')
                {
                  for(int i=2;i<10;i++)
                  arr[a][i]='0';
                  forward();
                  arr[a][1]='l';
                  b=2;
                  j=0;
                }
              }
             }
             else if(k==1)
             {
              forward();
              arr[a][1]='l';
              for(int i=2;i<10;i++)
              arr[a][i]='0';
              j=0;
              b=2;
             }
             else if(k==2)
             {
              forward();
              for(int i=0;i<10;i++)
              arr[a][i]='0';
              k=0;
              j=1;
              a--;
              for(int i=2;i<10;i++)
              {
                if(arr[a][i]=='0')
                {
                  b=i-1;break;
                }
              }
             }
             break;
      case 'R':
             if(j==0)
             k=0;
            
             if(k==0)
             {
              if(j==0)
              {
              a++;
              arr[a][0]='R';
              right();
              b=1;
              arr[a][b]='r';
              check_b();
              }
              else if(j==1)
              {
                if(arr[a][1]=='f')
                {
                  for(int i=2;i<10;i++)
                  arr[a][i]='0';
                  right();
                  arr[a][1]='l';
                  b=2;
                  j=0;
                }
              }
              
             }
             else if(k==1)
             {
              right();
              arr[a][1]='l';
              for(int i=2;i<10;i++)
              arr[a][i]='0';
              j=0;
              b=2;
             }
             else if(k==2)
             {
              right();
              for(int i=0;i<10;i++)
              arr[a][i]='0';
              k=0;
              j=1;
              a--;
              for(int i=2;i<10;i++)
              {
                if(arr[a][i]=='0')
                {
                  b=i-1;break;
                }
              }
             }
             break;
      case 'T':
             if(j==0)
             k=0;
             if(k==0)
             {
              if(j==0)
              {
              a++;
              arr[a][0]='T';
              right();
              b=1;
              arr[a][b]='r';
              check_b();
              }
              else if(j==1)
              {
                if(arr[a][1]=='r')
                {
                  for(int i=2;i<10;i++)
                  arr[a][i]='0';
                  right();
                  arr[a][1]='f';
                  b=2;
                  j=0;
                }
              }
             }
             else if(k==1)
             {
              right();
              arr[a][1]='f';
              for(int i=2;i<10;i++)
              arr[a][i]='0';
              j=0;
              b=2;
             }
             else if(k==2)
             {
              right();
              for(int i=0;i<10;i++)
              arr[a][i]='0';
              k=0;
              a--;
              j=1;
              for(int i=2;i<10;i++)
              {
                if(arr[a][i]=='0')
                {
                  b=i-1;break;
                }
              }
             }
             break;
//      case 'P':
//             check_i;
//             if(j==0)
//             k=0;
//             if(k==0)
//             {
//              a++;
//              arr[a][0]='P';
//              left();
//              b=1;
//              arr[a][b]='l';
//              check_b();
//             }
//             else if(k==1)
//             {
//              left();
//              arr[a][b]='f';
//              check_b();
//             }
//             else if(k==2)
//             {
//              check_b();
//              left();
//              arr[a][b]='r';
//             }
//             break;
      case 'U':
             u_turn();
             j=j?0:1;
             k++;
             b--;
             break;
            
     }}


  
  delay(5);
}
