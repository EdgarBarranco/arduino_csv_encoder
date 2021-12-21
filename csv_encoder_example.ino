void setup() {
  Serial.begin(115200);
}

int bits;
char str[600];
char decoded[600];
uint8_t compStr[300];

int input_string(char *str, int max_len) {
  max_len--;
  int ctr;
  Serial.flush();
  ctr = 0;
  str[ctr] = 0;
  while (true) {
    if (Serial.available() > 0) {
        char c = Serial.read();
        if (ctr == 0 && (c == '\n' || c == '\r'))
          continue;
        if (c >= 32 && c <= 126) {
          str[ctr] = c;
          ctr++;
        }
        if (c < 0 || c == '\n' || c == '\r' || ctr >= max_len)
          break;
    }
  }
  str[ctr] = 0;
  Serial.println(str);
  return ctr;
}

void loop() {
  memset(decoded, '0xff', sizeof(decoded));
  Serial.write("Enter string to compress:\n");
  int len = input_string(str, sizeof(str));
 
  if (len > 0) {
    comp();
    deco();
    Serial.println(decoded);
  }
  delay(500);
}

uint8_t enc(char c)
{
  uint8_t tval = 0;
    switch(c) {
      case '0':
        tval = B00000001;
        break;
      case '1':
        tval = B00000010;
        break;
      case '2':
        tval = B00000011;
        break;
      case '3':
        tval = B00000100;
        break;
      case '4':
        tval = B00000101;
        break;
      case '5':
        tval = B00000110;
        break;
      case '6':
        tval = B00000111;
        break;
      case '7':
        tval = B00001000;
        break;
      case '8':
        tval = B00001001;
        break;
      case '9':
        tval = B00001010;
        break;
      case ',':
        tval = B00001011;
        break;
      case '"':
        tval = B00001100;
        break;
      case '-':
        tval = B00001101;
        break;        
      case '.':
        tval = B00001110;
        break;
      case ':':
        tval = B00001111;
        break;       
      default:
        tval = B00000000;
        break;
    }
  return tval;  
}

char dec(uint8_t tval){
    char c = '\0';
    switch(tval) {
      case B00000001:
        c = '0';
        break;
      case B00000010:
        c = '1';
        break;
      case B00000011:
        c = '2';
        break;
      case B00000100:
        c = '3';
        break;
      case B00000101:
        c = '4';
        break;
      case B00000110:
        c = '5';
        break;
      case B00000111:
        c = '6';
        break;
      case B00001000:
        c = '7';
        break;
      case B00001001:
        c = '8';
        break;
      case B00001010:
        c = '9';
        break;
      case B00001011:
        c = ',';
        break;
      case B00001100:
        c = '"';
        break;
      case B00001101:
        c = '-';
        break;        
      case B00001110:
        c = '.';
        break;
      case B00001111:
        c = ':';
        break;        
      default:
        c = '\0';
        break;
    }
  return c;
}

void deco()
{
  uint8_t tval;
  int chars=0;
  uint8_t temp;
  bool decode_last_bit = true;
  if (bits % 2)
    decode_last_bit = false;
  for (int i = 0; i <= bits; i++)  {
    tval = compStr[i];
    printBits(tval);
    Serial.println(" ");
    temp = (tval & 0b11110000) >> 4;  
    decoded[chars++] = dec(temp);
    temp = (tval & 0b00001111);
    decoded[chars++] = dec(temp);
  }
}

void printBits(long int n) {
  byte numBits = 8;  // 2^numBits must be big enough to include the number n
  char b;
  char c = ' ';   // delimiter character
  for (byte i = 0; i < numBits; i++) {
    // shift 1 and mask to identify each bit value
    b = (n & (1 << (numBits - 1 - i))) > 0 ? '1' : '0'; // slightly faster to print chars than ints (saves conversion)
    Serial.print(b);
    if (i < (numBits - 1) && ((numBits-i - 1) % 4 == 0 )) Serial.print(c); // print a separator at every 4 bits
  }
}

void comp() {
  int len = strlen(str);
  uint8_t tval, msb,lsb;
  memset(compStr, 0, sizeof(compStr));
  int count = 1;
  bits = 0;
  Serial.println(len);
  for (int i = 0; i <= len; i++)
  {
    tval = enc(str[i]);
    if (count++ % 2) {
     compStr[bits] = compStr[bits] | tval;
    }
    else {
     compStr[bits] = (compStr[bits] << 4) | tval;
     printBits(compStr[bits]);
     Serial.println(" ");
     bits++;
    }
  }
  Serial.println(bits);
}
