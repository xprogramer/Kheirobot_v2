#define RF24_CONFIG      0x00 // CONFIG register
#define RF24_EN_RXADDR   0x02 // EN_RXADDR register
#define RF24_SETUP_AW    0x03 // SETUP_AW register
#define RF24_SETUP_RETR  0x04
#define RF24_RF_CH       0x05
#define RF24_RF_SETUP    0x06 // SETUP register
#define RF24_STATUS      0x07

#define RF24_RX_ADDR_P0  0x0A
#define RF24_TX_ADDR     0x10
#define RF24_RX_PW_P0    0x11

// Command Name Mnemonics (Instructions)
#define RF24_W_REGISTER     0x20
#define RF24_FLUSH_TX       0xE1
#define RF24_FLUSH_RX       0xE2
#define RF24_R_RX_PAYLOAD   0x61
#define RF24_NOP            0xFF

// STATUS register bit definitions
#define RF24_STATUS_RX_DR                       0x40

#define RF24_CE      2
#define RF24_SCK     3
#define RF24_MISO    4
#define RF24_CSN     A4
#define RF24_MOSI    A5

#define LED A3

const byte addr[5] = {0x9A, 0xFE, 0xBF, 0xED, 0x0C};


/* 
 *  function to shift out a byte via SPI protocol.
 *  @param byte _mosi: the MOSI port (pin 11 by default)
 *  @param byte _sck: the SCK port (pin 13 by default)
 *  @param byte _miso: the MISO port (pin 12 by default)
 *  @param byte _val: the value to be shifted out
 */
byte shift(byte _mosi,byte _sck,byte _miso,byte _val)
{
   byte ret = 0;

   for(int i=7; i>=0; i--) {
    digitalWrite(_mosi, bitRead(_val, i));
    digitalWrite(_sck, HIGH);
    bitWrite(ret, i, digitalRead(_miso));
    digitalWrite(_sck, LOW);
   }

   return ret;
}


/* 
 *  function to configure a register value (_reg) with a single byte.
 *  @param byte _csn: the CSN port (pin 10 by default)
 *  @param byte _mosi: the MOSI port (pin 11 by default)
 *  @param byte _sck: the SCK port (pin 13 by default)
 *  @param byte _reg: the register address to be configured
 *  @param byte _val: the value of the register
 */
void writeReg(byte _csn, byte _mosi, byte _sck, byte _reg, byte _val)
{
  digitalWrite(_csn, LOW);
  // always add the register address to RF24_W_REGISTER 
  shiftOut(_mosi, _sck, MSBFIRST, RF24_W_REGISTER|_reg);  
  shiftOut(_mosi, _sck, MSBFIRST, _val);
  digitalWrite(_csn, HIGH);
  delay(10);
}


/* 
 *  function to configure a register value (_reg) with an array of bytes.
 *  @param byte _csn: the CSN port (pin 10 by default)
 *  @param byte _mosi: the MOSI port (pin 11 by default)
 *  @param byte _sck: the SCK port (pin 13 by default)
 *  @param byte _reg: the register address to be configured
 *  @param const byte* _data: the array of bytes
 *  @param byte _size: the array size
 */
void writeRegData(byte _csn,byte _mosi,byte _sck,byte _reg,const byte* _data,byte _size)
{
  digitalWrite(_csn, LOW);
  // always add the register address to RF24_W_REGISTER 
  shiftOut(_mosi, _sck, MSBFIRST, RF24_W_REGISTER|_reg);
  for(int i=0; i<_size; i++)
  {
    shiftOut(_mosi, _sck, MSBFIRST, _data[i]);
  }
  digitalWrite(_csn, HIGH);
  delay(10);
}


/* 
 *  function to configure the nRF24L01+ device as a receiver.
 *  @param byte PAYLOAD_SIZE: the size of the buffer to receive data
 *  @param byte CHANNEL_NO: the channel number to receive data
 */
void configRX(byte PAYLOAD_SIZE, byte CHANNEL_NO)
{
  // configure the pins mode
  pinMode(RF24_CE, OUTPUT);
  pinMode(RF24_CSN, OUTPUT);
  pinMode(RF24_SCK, OUTPUT);
  pinMode(RF24_MOSI, OUTPUT);
  pinMode(RF24_MISO, INPUT_PULLUP);
  
  digitalWrite(RF24_CE,  LOW); // CE high: do not send or receive data
  digitalWrite(RF24_CSN,  HIGH); // CSN low: do not send commands to the device

  writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   RF24_STATUS, 0x70);
  writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   RF24_CONFIG,     0x1D);
  writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   RF24_SETUP_AW,     0x03);
  writeReg(RF24_CSN, RF24_MOSI, RF24_SCK, RF24_EN_RXADDR, 0x01);
  writeRegData(RF24_CSN, RF24_MOSI, RF24_SCK, RF24_RX_ADDR_P0, addr, 5);
  writeRegData(RF24_CSN, RF24_MOSI, RF24_SCK, RF24_TX_ADDR, addr, 5);
  writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   RF24_RX_PW_P0,   PAYLOAD_SIZE);
  writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   RF24_RF_CH,      CHANNEL_NO);
  writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   RF24_SETUP_RETR, 0xFF);
  writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   RF24_RF_SETUP,   0x26);
  writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   0x1C,   0x00); 
  writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   RF24_CONFIG,     0x1F);  
  
  digitalWrite(RF24_CSN, LOW);
  shiftOut(RF24_MOSI, RF24_SCK, MSBFIRST, RF24_FLUSH_RX); // flush RX
  shiftOut(RF24_MOSI, RF24_SCK, MSBFIRST, RF24_FLUSH_TX); // flush TX 
  digitalWrite(RF24_CSN, HIGH);
}


/* 
 *  function to read the received data.
 *  @param byte* rec: the buffer to keep the received data
 */
bool receiv(byte* rec)
{
  // erase the previous received data
  memset(rec, 0, 6);
  
  digitalWrite(RF24_CE,  HIGH); // listen for packets 
  digitalWrite(LED,  LOW); // light-off the communication indicator LED
  byte status;
  // check the device status if there is a received data
  do
  {
      digitalWrite(RF24_CSN, LOW);
      status = shift(RF24_MOSI, RF24_SCK, RF24_MISO, RF24_NOP);
      digitalWrite(RF24_CSN, HIGH);
  }
  while(!(status & RF24_STATUS_RX_DR));
    
  // if there is a received data
  if (status & RF24_STATUS_RX_DR)
  {
      digitalWrite(RF24_CE,  LOW); // disable RX mode during reading data

      digitalWrite(RF24_CSN, LOW);
      shiftOut(RF24_MOSI, RF24_SCK, MSBFIRST, RF24_R_RX_PAYLOAD);
      
      rec[0] = shift(RF24_MOSI, RF24_SCK, RF24_MISO, RF24_NOP);//throttle
      rec[1] = shift(RF24_MOSI, RF24_SCK, RF24_MISO, RF24_NOP);//pitch
      rec[2] = shift(RF24_MOSI, RF24_SCK, RF24_MISO, RF24_NOP);//roll
      rec[3] = shift(RF24_MOSI, RF24_SCK, RF24_MISO, RF24_NOP);//yaw
      rec[4] = shift(RF24_MOSI, RF24_SCK, RF24_MISO, RF24_NOP);//left commands
      rec[5] = shift(RF24_MOSI, RF24_SCK, RF24_MISO, RF24_NOP);//right commands
      
      writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   RF24_CONFIG,     0x1D);
      writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   RF24_STATUS, 0x70);
      writeReg(RF24_CSN, RF24_MOSI, RF24_SCK,   RF24_CONFIG,     0x1F); 

      digitalWrite(RF24_CSN, LOW);
      shiftOut(RF24_MOSI, RF24_SCK, MSBFIRST, RF24_FLUSH_RX); // flush RX
      shiftOut(RF24_MOSI, RF24_SCK, MSBFIRST, RF24_FLUSH_TX); // flush TX 
      digitalWrite(RF24_CSN, HIGH);

      digitalWrite(RF24_CSN, HIGH);

      if(rec[0]==0xFF && rec[1]==0xFF && rec[2]==0xFF && rec[3]==0xFF && rec[4]==0xFF && rec[5]==0xFF) return false;

      #ifdef __DEBUG_
        Serial.println();
        Serial.print(rec[0],HEX);Serial.print(" ");
        Serial.print(rec[1],HEX);Serial.print(" ");
        Serial.print(rec[2],HEX);Serial.print(" ");
        Serial.print(rec[3],HEX);Serial.print(" ");
        Serial.print(rec[4],HEX);Serial.print(" ");
        Serial.println(rec[5],HEX);
      #endif

      // light-on the LED to show that data is successfully received
      digitalWrite(LED,  HIGH);
      
      return true;
  }
  
  digitalWrite(LED,  LOW); // light-off the communication indicator LED

  return false;
}
