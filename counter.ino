#define SEGMENT_A (1<<0)
#define SEGMENT_B (1<<1)
#define SEGMENT_C (1<<2)
#define SEGMENT_D (1<<3)
#define SEGMENT_E (1<<4)
#define SEGMENT_F (1<<5)
#define SEGMENT_G (1<<6)
//#define SEGMENT_DP (1<<2)

unsigned short segment_map[] = {
  SEGMENT_A | SEGMENT_B | SEGMENT_C |SEGMENT_D | SEGMENT_E | SEGMENT_F,
  SEGMENT_B | SEGMENT_C,
  SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G,
  SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G,
  SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,
  SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,
  SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,
  SEGMENT_A | SEGMENT_B | SEGMENT_C,
  SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,
  SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,
  SEGMENT_A | SEGMENT_B | SEGMENT_E | SEGMENT_F | SEGMENT_G,
  SEGMENT_B | SEGMENT_C | SEGMENT_E | SEGMENT_F | SEGMENT_D,
  SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,
  SEGMENT_B | SEGMENT_C | SEGMENT_E | SEGMENT_F | SEGMENT_G
};

#define LETTER_P 10
#define LETTER_U 11
#define LETTER_S 12
#define LETTER_H 13

unsigned char digits[4];

unsigned char state = 0;

void setup() {
  pinMode(2, INPUT_PULLUP);
  //määritetään jokaisen numeron minukset outputeiksi
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(7, OUTPUT); //segmentti
  pinMode(8, OUTPUT); //segmentti
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);

  }
unsigned long start;
unsigned long taim;
unsigned long randomi;
void loop() {
  int nappula = digitalRead(2);
  switch (state){
    case 0: //napun eka painallus
      digits[0] = segment_map[LETTER_H];
      digits[1] = segment_map[LETTER_S];
      digits[2] = segment_map[LETTER_U];
      digits[3] = segment_map[LETTER_P];
      if(nappula == 0){
        state = 1;
      }
      break;

    case 1: //nappu ylös
      if(nappula == 1){
        digits[0] = segment_map[0];
        digits[1] = segment_map[0];
        digits[2] = segment_map[0];
        digits[3] = segment_map[0];
        state = 11;
      }
      randomi = random(5000, 10000);
      taim = millis();
      break;

    case 11:
      
       if(taim+randomi < millis()){
          state = 2;
       }
       start = millis();
       break;
       
    case 2: //aika peli
      
      taim = millis();
      digits[0] = segment_map[(taim-start)%10];
      digits[1] = segment_map[((taim-start)/10)%10];
      digits[2] = segment_map[((taim-start)/100)%10];
      digits[3] = segment_map[((taim-start)/1000)%10];
      if(nappula == 0){
        state = 3;
      }
      break;
      
   case 3:
      if(nappula == 1){
        state = 4;
      }
      break;
      
   case 4: //nappu reaktio
      if(nappula == 0){
        state = 5;
      }
      break;

  case 5:
    if(nappula == 1){
      state = 0;
    }
    break;
    
   }
   display();
  
}

static unsigned int d = 0;
void display() {
  unsigned char s = digits[d];
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  
  for(unsigned int i = 0; i<7; i++){
    if (s & (1<<i)){
      digitalWrite(7+i, HIGH);
    }
    else {
      digitalWrite(7+i, LOW);
    }
  }
  digitalWrite(d+3, LOW);
  d++;  
  if (d > 3){
    d = 0;
  }
}
