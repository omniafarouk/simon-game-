// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int score = 0;

Adafruit_LiquidCrystal lcd_1(0);
# define RED_LED      3
# define BLUE_LED     4
# define YELLOW_LED   5
# define GREEN_LED    6

# define RED_PUSH_BUTTON    7
# define BLUE_PUSH_BUTTON   8
# define YELLOW_PUSH_BUTTON   9
# define GREEN_PUSH_BUTTON    10

void display(int sequence[] , int level_delay)
  {  
    if(level_delay != 3000)
      { if(sequence[0])
          {digitalWrite(RED_LED,HIGH);
           delay(level_delay);
           digitalWrite(RED_LED,LOW);
          }
        delay(1000);
        if(sequence[1])
          {digitalWrite(BLUE_LED,HIGH);
           delay(level_delay);
         digitalWrite(BLUE_LED,LOW);
        }
        delay(1000);
        if(sequence[2])
          {digitalWrite(YELLOW_LED,HIGH);
           delay(level_delay);
           digitalWrite(YELLOW_LED,LOW);
          }
        delay(1000);
        if(sequence[3])
          {digitalWrite(GREEN_LED,HIGH);
           delay(level_delay);
           digitalWrite(GREEN_LED,LOW);
          }
      }
  }
const int SequenceLength = 4;
int sequence[SequenceLength];

int user_sequence[SequenceLength];

void setup()
{ Serial.begin(9600);
 
  lcd_1.begin(16, 2);
  lcd_1.print("Hello to simon's");
  lcd_1.setCursor(0,1);
  lcd_1.print("score :"); 
 
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
    
  pinMode(RED_PUSH_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_PUSH_BUTTON, INPUT_PULLUP);
  pinMode(YELLOW_PUSH_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_PUSH_BUTTON, INPUT_PULLUP);

}
void loop()
{
  unsigned long start_time;
  
  unsigned long current_time ;
  unsigned long elapsed_time = 0;
  
  int  red_button_state = HIGH ;
  int  blue_button_state = HIGH ;
  int  yellow_button_state = HIGH ;
  int  green_button_state = HIGH;
  
  int currentPosition = 0; 
  
  Serial.print("enter sequence :");
  while (Serial.available() > 0 && currentPosition < SequenceLength)
  {    
    char input = Serial.read();
      if (input == '\n') {
        break; 
      } else if (input == '0' || input == '1') {
        sequence[currentPosition++] = (int)input - '0';
      } 
    }
  if(currentPosition == SequenceLength)
  { 
    Serial.print("\nReceived sequence: ");
    for (int i = 0; i < currentPosition; i++) 
       { Serial.print(sequence[i]);  }
   
   char level = '0' ;
   Serial.println("\nplease choose a level 1.easy 2.medium 3.hard:");
   while(level == '0')
    {  char temp = Serial.read();
       if (temp == '1' || temp == '2' || temp == '3') 
           level = temp ;
    }      
    int level_delay = 3000;
    if(level == '1')
      level_delay = 1000;
    else if(level == '2')
       level_delay = 500;
    else if (level == '3')
       level_delay = 100;
     display(sequence , level_delay);
  }
  lcd_1.setCursor(8,1);
  lcd_1.print(score);
  
  start_time = millis();
  
  while ( elapsed_time < (5*1000)
         && red_button_state == HIGH 
         && blue_button_state == HIGH 
         && yellow_button_state == HIGH
         && green_button_state == HIGH
        ) 
   { 
    current_time = millis();
    elapsed_time = current_time - start_time;
   
    if(red_button_state == HIGH)
           red_button_state = digitalRead(RED_PUSH_BUTTON);
      if(blue_button_state == HIGH)
          blue_button_state = digitalRead(BLUE_PUSH_BUTTON);
      if(yellow_button_state == HIGH)
          yellow_button_state = digitalRead(YELLOW_PUSH_BUTTON);
      if(green_button_state == HIGH)
            green_button_state = digitalRead(GREEN_PUSH_BUTTON);

   
   }
  
  if(elapsed_time >= (5*1000))
  { Serial.println("Game Over"); }
  else 
  {
      start_time = millis();
     
    if(red_button_state == HIGH)
      {red_button_state = digitalRead(RED_PUSH_BUTTON);
        delay(1000);
      }
      if(blue_button_state == HIGH)
      {blue_button_state = digitalRead(BLUE_PUSH_BUTTON);
      delay(1000);
      }
       if(yellow_button_state == HIGH)
       {yellow_button_state = digitalRead(YELLOW_PUSH_BUTTON);
       delay(1000);
       }
        if(green_button_state == HIGH)
        {green_button_state = digitalRead(GREEN_PUSH_BUTTON);
        delay(1000);
        }

      for (int i = 0; i < SequenceLength; i++) {
        switch (i) {
          case 0:
            user_sequence[i] = !red_button_state;
            break;
          case 1:
            user_sequence[i] = !blue_button_state;
            break;
          case 2:
            user_sequence[i] = !yellow_button_state;
            break;
          case 3:
            user_sequence[i] = !green_button_state;
            break;
        } 
      }
      display(user_sequence , 1000); 
      int wrong = 0;
      for(int i = 0; i < 4 ; i++)
        {
          if(user_sequence[i] != sequence[i]) 
              { wrong =1;
                break; }
        }
      if(wrong == 0)
       score+=1;
      else if(wrong == 1) 
      {
        lcd_1.clear();
      lcd_1.println("Game Over");
      }
  }
}
