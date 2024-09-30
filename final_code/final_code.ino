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

const int ENA = 5;
#define IN1 10
#define IN2 9

#define IN3 12
#define IN4 11
const int ENB = 6;
int f=1;

int x = 0; 

int arr[33][33];
int row = 31;
int coloumn = 1;
int dir = 0;

int path[100];
int index=0;



bool wall_left, wall_right, wall_str;

void move_str()
{
    analogWrite(ENA,140);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
analogWrite(ENB,160);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(330);
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENB, 0);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(1000);
}
void move_left()
{
    dir = (dir+3)%4;
analogWrite(ENA,140);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
analogWrite(ENB,160);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    delay(300);
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENB, 0);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(1000);
    move_str();
}
void move_right()
{
    dir = (dir+1)%4;
analogWrite(ENA,140);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
analogWrite(ENB,160);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(300);
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENB, 0);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(1000);
    move_str();
}
void move_back()
{
    if(wall_left && wall_right)
    {
      analogWrite(ENA,140);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
  analogWrite(ENB,160);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(360);
      analogWrite(ENA, 0);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENB, 0);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      delay(1000);
    }
    else
    {
    move_right();
    move_right();
    move_str();
    }
}

void celladd(int r, int c)
{
    if (r >= 1 && r <= 30 && c >= 1 && c <= 29)
    {
        if (arr[r + 2][c] == (-1))
        {
            arr[r + 2][c] = arr[r][c] + 1;
            celladd(r + 2, c);
        }
        if (arr[r][c + 2] == (-1))
        {
            arr[r][c + 2] = arr[r][c] + 1;
            celladd(r, c + 2);
        }
        if (arr[r][c - 2] == (-1))
        {
            arr[r][c - 2] = arr[r][c] + 1;
            celladd(r, c - 2);
        }
    }
}

void celladd1(int r, int c)
{
    if (r >= 0 && r <= 29 && c >= 1 && c <= 29)
    {
        if (arr[r - 2][c] == (-1))
        {
            arr[r - 2][c] = arr[r][c] + 1;
            celladd1(r - 2, c);
        }
        if (arr[r][c + 2] == (-1))
        {
            arr[r][c + 2] = arr[r][c] + 1;
            celladd1(r, c + 2);
        }
        if (arr[r][c - 2] == (-1))
        {
            arr[r][c - 2] = arr[r][c] + 1;
            celladd1(r, c - 2);
        }
    }
}

int min_val(int r, int c)
{
    int comp[4];
    
    if (arr[r + 1][c] != -2)
    {
        comp[0] = arr[r + 2][c];
    }else
    {
        comp[0] = 1000;
    }

    if (arr[r - 1][c] != -2)
    {
        comp[1] = arr[r - 2][c];
    }
    else
    {
        comp[1] = 1000;
    }

    if (arr[r][c + 1] != -2)
    {
        comp[2] = arr[r][c + 2];
    }
    else
    {
        comp[2] = 1000;
    }

    if (arr[r][c - 1] != -2)
    {
        comp[3] = arr[r][c - 2];
    }
    else
    {
        comp[3] = 1000;
    }

    return min(min(comp[2], comp[3]), min(comp[0], comp[1]));
}

void floodfill(int row, int coloumn)
{
    int r = row;
    int c = coloumn;
    if (arr[r][c] < min_val(r, c))
    {
        arr[r][c] = min_val(r, c) + 1;
        if (arr[r - 1][c] == -1)
        {
            floodfill(r - 2, c);
        }
        if (arr[r + 1][c] == -1)
        {
            floodfill(r + 2, c);
        }
        if (arr[r][c - 1] == -1)
        {
            floodfill(r, c - 2);
        }
        if (arr[r][c + 1] == -1)
        {
            floodfill(r, c + 2);
        }
    }
    else
    {
        return;
    }
}

void wall_sense()
{
    if (dir == 0)
    {
        // left
        if (wall_left)
        {
            arr[row][coloumn - 1] = -2;
        }
        // str
        if (wall_str)
        {
            arr[row - 1][coloumn] = -2;
        }
        // right
        if (wall_right)
        {
            arr[row][coloumn + 1] = -2;
        }
    }
    else if (dir == 1)
    {
        // left
        if (wall_left)
        {
            arr[row - 1][coloumn] = -2;
        }
        // str
        if (wall_str)
        {
            arr[row][coloumn + 1] = -2;
        }
        // right
        if (wall_right)
        {
            arr[row + 1][coloumn] = -2;
        }
    }
    else if (dir == 2)
    {
        // left
        if (wall_left)
        {
            arr[row][coloumn + 1] = -2;
        }
        // str
        if (wall_str)
        {
            arr[row + 1][coloumn] = -2;
        }
        // right
        if (wall_right)
        {
            arr[row][coloumn - 1] = -2;
        }
    }
    else if (dir == 3)
    {
        // left
        if (wall_left)
        {
            arr[row + 1][coloumn] = -2;
        }
        // str
        if (wall_str)
        {
            arr[row][coloumn - 1] = -2;
        }
        // right
        if (wall_right)
        {
            arr[row - 1][coloumn] = -2;
        }
    }
}

void move()
{
    wall_sense();
    if (dir == 0)
    {
        // left
        if ((arr[row][coloumn - 1] == -1) && (arr[row][coloumn - 2] == (arr[row][coloumn] - 1)))
        {
            move_left();
            coloumn -=2;
            Serial.println("left");
        }
        // str
        else if ((arr[row - 1][coloumn] == -1) && (arr[row - 2][coloumn] == (arr[row][coloumn] - 1)))
        {
            move_str();
            row -= 2;
            Serial.println("str");
        }
        // right
        else if ((arr[row][coloumn + 1] == -1) && (arr[row][coloumn + 2] == (arr[row][coloumn] - 1)))
        {
            move_right();
            coloumn += 2;
            Serial.println("right");
        }
        // back
        else if ((arr[row + 1][coloumn] == -1) && (arr[row + 2][coloumn] == (arr[row][coloumn] - 1)))
        {
            move_back();
            row += 2;
            Serial.println("back");
        }
        else
        {
            floodfill(row, coloumn);
        }
    }
    else if (dir == 1)
    {
        // left
        if (arr[row][coloumn - 1] == -1 && arr[row][coloumn - 2] == (arr[row][coloumn] - 1))
        {
            move_back();
            coloumn -= 2;
            Serial.println("left");
        }
        // str
        else if (arr[row][coloumn + 1] == -1 && arr[row][coloumn + 2] == (arr[row][coloumn] - 1))
        {
            move_str();
            coloumn += 2;
            Serial.println("right");
        }
        else if (arr[row - 1][coloumn] == -1 && arr[row - 2][coloumn] == (arr[row][coloumn] - 1))
        {
            move_left();
            row -= 2;
            Serial.println("str");
        }
        else if (arr[row + 1][coloumn] == -1 && arr[row + 2][coloumn] == (arr[row][coloumn] - 1))
        {
            move_right();
            row += 2;
            Serial.println("back");
        }
        else
        {
            floodfill(row,coloumn);
        }
    }
    else if (dir == 2)
    {
        // left
        if (arr[row][coloumn - 1] == -1 && arr[row][coloumn - 2] == (arr[row][coloumn] - 1))
        {
            move_right();
            coloumn -= 2;
            Serial.println("left");
        }
        // str
        else if (arr[row - 1][coloumn] == -1 && arr[row - 2][coloumn] == (arr[row][coloumn] - 1))
        {
            move_back();
            row -= 2;
            Serial.println("str");
        }
        // right
        else if (arr[row][coloumn + 1] == -1 && arr[row][coloumn + 2] == (arr[row][coloumn] - 1))
        {
            move_left();
            coloumn += 2;
            Serial.println("right");
        }
        // back
        else if (arr[row + 1][coloumn] == -1 && arr[row + 2][coloumn] == (arr[row][coloumn] - 1))
        {
            move_str();
            row += 2;
            Serial.println("back");
        }
        else
        {
            floodfill(row,coloumn);
        }
    }
    else if (dir == 3)
    {
        // left
        if (arr[row][coloumn - 1] == -1 && arr[row][coloumn - 2] == (arr[row][coloumn] - 1))
        {
            move_str();
            coloumn -= 2;
            Serial.println("left");
        }
        // str
        else if (arr[row - 1][coloumn] == -1 && arr[row - 2][coloumn] == (arr[row][coloumn] - 1))
        {
            move_right();
            row -= 2;
            Serial.println("str");
        }
        // right
        else if (arr[row][coloumn + 1] == -1 && arr[row][coloumn + 2] == (arr[row][coloumn] - 1))
        {
            move_back();
            coloumn += 2;
            Serial.println("right");
        }
        // back
        else if (arr[row + 1][coloumn] == -1 && arr[row + 2][coloumn] == (arr[row][coloumn] - 1))
        {
            move_left();
            row += 2;
            Serial.println("back");
        }
        else
        {
            floodfill(row,coloumn);
        }
    }
}

void path_finder()
{
    int r = 31;
    int c = 1;

    while (arr[r][c] != 0)
    {
        if ((arr[r][c - 1] == -1) && (arr[r][c - 2] == (arr[r][c] - 1)))
        {
            //left
            c -= 2;
            path[index++] = -10;
        }
        else if ((arr[r - 1][c] == -1) && (arr[r - 2][c] == (arr[r][c] - 1)))
        {
            //str
            r -= 2;
            path[index++] = -11;
        }
        else if ((arr[r][c + 1] == -1) && (arr[r][c + 2] == (arr[r][c] - 1)))
        {
            //right 
            c += 2;
            path[index++] = -12;
        }
        else if (arr[r + 1][c] == -1 && (arr[r + 2][c] == (arr[r][c] - 1)))
        {
            //back
            r += 2;
            path[index++] = -13;
        }
    }
}

void sh_path()
{

  if (path[index]==0)
  {
    f=3;
    return;
  }
    if(dir == 0)
    {
        if ( path[index] == -10)
        {
            move_left();
        }
        else if( path[index] == -11)
        {
            move_str();
        }
        else if( path[index] == -12)
        {
            move_right();
        }

    }
    else if(dir == 1)
    {
        if ( path[index] == -11)
        {
            move_left();
        }
        else if( path[index] == -12)
        {
            move_str();
        }
        else if( path[index] == -13)
        {
            move_right();
        }

    }
    else if(dir == 2)
    {
        if ( path[index] == -12)
        {
            move_left();
        }
        else if( path[index] == -13)
        {
            move_str();
        }
        else if( path[index] == -10)
        {
            move_right();
        }

    }
    else if(dir == 3)
    {
        if ( path[index] == -13)
        {
            move_left();
        }
        else if( path[index] == -10)
        {
            move_str();
        }
        else if( path[index] == -11)
        {
            move_right();
        }

    }
    index++;
}
//////

void reverse(){
  index--;
  if(index==-1){
    f=2;
    Serial.println("fini");
    return;
  }
    if(dir == 0)
    {   
        if ( path[index] == -10)
        {
            move_right();
        }
        else if( path[index] == -11)
        {

            move_back();
        }
        else if( path[index] == -12)
        {

            move_left();

        }
        else{
            move_str();
        }
      
    }
    if(dir == 1)
    {

        if ( path[index] == -10)
        {
            move_str();
        }
        else if( path[index] == -11)
        {
            move_right();
        }
        else if( path[index] == -12)
        {

            move_back();

        }
        else{
            move_left();
        }
     
    }
    else if(dir == 2)
    {    


        if ( path[index] == -10)
        {
            move_left();
        }
        else if( path[index] == -11)
        {
            move_str();
        }
        else if( path[index] == -12)
        {

            move_right();

        }
        else{
            move_back();
        }
    

    }
    else if(dir == 3)
    {
  
        if ( path[index] == -10)
        {
            move_back();
        }
        else if( path[index] == -11)
        {
            move_left();
        }
        else if( path[index] == -12)
        {

            move_str();

        }
        else{
            move_right();
        }
    }
    
}

void setup()
{
  Serial.begin(9600);

    ////sensors////
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    //pinMode(led, OUTPUT);

    ////initial array////
    for (int i = 0; i < 33; i++)
    {
        for (int j = 0; j < 33; j++)
        {
            arr[i][j] = -1;
        }
    }
    arr[17][17] = 0;
    celladd(17, 17);
    celladd1(17, 17);

    ////boundry walls////
    for (int x = 0; x < 33; x++)
    {
        arr[0][x] = -2;
        arr[32][x] = -2;
        arr[x][0] = -2;
        arr[x][32] = -2;
    }

    
}

void loop()
{

  if(digitalRead(MS) && digitalRead(RS) && digitalRead(LS) && digitalRead(FRS)  && digitalRead(FLS) && f==2)
  {
    sh_path();
  }
  else if(f==1 && (row!=17 || coloumn!=17))
  {
    Serial.println(row);
    Serial.println(coloumn);
    // distance left
    if (!digitalRead(FLS))
    {
        wall_left = true;
    }
    else{
        wall_left = false;
    }
    delay(100);
    
    // distance right
    if (!digitalRead(FRS))
    {
        wall_right = true;
    }
    else{
        wall_right = false;
    }
    delay(100);

    // distance straight
    if (!digitalRead(MS))
    {
        wall_str = true;
    }
    else{
        wall_str = false;
    }

    delay(100);
    move();
    delay(100);
  }
  else if(f==1 && row==17 && coloumn==17)
  {
    path_finder();
    f=0;
  }
  else if(f==0)
  {
    reverse();
    Serial.println(index);
  }
  else 
  {
    digitalWrite(ENA, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

}
