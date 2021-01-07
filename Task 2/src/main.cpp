#include <Arduino.h>

//Define op_codes
uint8_t LNC_OP_TCP_START = 2;
uint8_t LNC_OP_TCP_STOP = 3;
uint8_t LNC_OP_TCP_HOST = 4;
uint8_t LNC_OP_TCP_PORT = 5;
uint8_t LNC_OP_TCP_CONN = 6;
uint8_t LNC_OP_TCP_SEND = 7;
uint8_t LNC_OP_TCP_AVAILABLE = 8;
uint8_t LNC_OP_TCP_RECV = 9;


void tcpStart(){
  uint8_t i = LNC_OP_TCP_START;
  i = i << 4;

  Serial.print("> Lnc_tcp_start: ");
  Serial.println(i);
  Serial2.write(i);
  Serial2.flush();

  while (!Serial2.available()){

  }

  uint8_t r = Serial2.read();
  Serial.println(r);
}



void  tcpHost(const char* host){
   uint8_t i = LNC_OP_TCP_HOST;
   i = i << 4;
   i = i + strlen(host);

   Serial.print(">Lnc_tcp_host: ");
   Serial.println(i);
   Serial2.write(i);
   Serial2.flush();

   Serial.write(host, strlen(host));
   Serial2.flush();

   while (!Serial2.available()){

   }
   uint8_t r = Serial2.read();
   Serial.println(r);

}

void  tcpPort(const char* port){
   uint8_t i = LNC_OP_TCP_HOST;
   i = i << 4;
   i = i + strlen(port);

   Serial.print(">Lnc_tcp_port: ");
   Serial.println(i);
   Serial2.write(i);
   Serial2.flush();

   Serial.write(port, strlen(port));
   Serial2.flush();

   while (!Serial2.available()){

   }
   uint8_t r = Serial2.read();
   Serial.println(r);
   
}

void  tcpConnect(){
   uint8_t i = LNC_OP_TCP_HOST;
   i = i << 4;

   Serial.print(">Lnc_tcp_conn: ");
   Serial.println(i);
   Serial2.write(i);
   Serial2.flush();

   while (!Serial2.available()){

   }
   uint8_t r = Serial2.read();
   Serial.println(r);
   
}

void  tcpReceive(char* buffer, size_t* len){
   char* read_buffer = buffer;
   size_t total = 0;
   while(true){
      uint8_t i = LNC_OP_TCP_HOST;
      i = i << 4;
      i = i + 15; //MAX_TCP AVAILABLE

      Serial.print(">Lnc_tcp_rcv: ");
      Serial.println(i);
      Serial2.write(i);
      Serial2.flush();

      while (!Serial2.available()){

      }
      uint8_t r = Serial2.read();
      Serial.print("<-");
      Serial.println(r);

      if(r == 0){
        Serial.print("No data to read");
        return;
      }
      if(r > 15){
        Serial.print("Error receiving");
        return;
      }
      for(uint8_t i=0; i < r; ++i){
        while(!Serial2.available()){

        }
        int c = Serial2.read();
        if(c < 15){
          Serial.print("Error receiveing");
          return;
        }
        *buffer = char(c);
        *len += 1;
        read_buffer ++;
      }
      total += r;
   }
   return;
}

void setup() {
  //Set baudrate
  Serial.begin(115200);
  Serial2.begin(115200);
}

void loop() {
  tcpStart();
}