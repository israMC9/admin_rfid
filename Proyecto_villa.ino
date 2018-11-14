//RST           D9
//SDA(SS)      D10
//MOSI         D11
//MISO         D12
//SCK          D13

#include <SPI.h>
#include <MFRC522.h>
#define DEBUG(a) Serial.println(a);
const int RST_PIN = 9;            // Pin 9 para el reset del RC522
const int SS_PIN = 10;            // Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Crear instancia del MFRC522
byte tarjetaint [4] = { 0x45, 0x33, 0x3F, 0xBE };
byte tarjeta1[4] = { 0xF0, 0xD3, 0x03, 0x18 };  // Ejemplo de clave valida
byte tarjeta2[4] = { 0x90, 0xFE, 0x00, 0x74 };
byte tarjeta3[4] = { 0xE6, 0xBB, 0x70, 0x7B };
byte tarjeta4[4] = { 0xC0, 0x7C, 0xC1, 0x80 };
char str[32] = "";
int cont=0;

bool Estado=true;
void setup() {
  Serial.begin(9600); // Iniciar serial
  SPI.begin();        // Iniciar SPI
  mfrc522.PCD_Init(); // Iniciar MFRC522

}
 // cargo a start con el valor +60mil milisegundos
unsigned long previousMillis = 0;
unsigned long interval = 1000;
void loop() {
  
if (Serial.available())
   {
      String credencial = Serial.readStringUntil('\n');

  while(credencial=="si"){
      // Detectar tarjeta
      unsigned long currentMillis = millis();
if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    
  
  if (mfrc522.PICC_IsNewCardPresent())
  {

    //Seleccionamos una tarjeta
    if (mfrc522.PICC_ReadCardSerial())
    {
      
      
      array_to_string(mfrc522.uid.uidByte, 4, str);
      Serial.print(str);
      Serial.print(" ");
      Estado=entrada_salida(str);
      if(Estado==false){
        Serial.println("Salida");
        }else{
         Serial.print("Entrada"); 
        }
        Serial.println();
      

      

      //Finalizar lectura actual
      mfrc522.PICC_HaltA();
      
    }
  }
  }
  
  }
   }
}
void array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}
bool entrada_salida(String str){
  cont++;
  if(cont==1){
      return(false);
    }else if(cont==2){
      cont=0;
        return(true);
      }

  }
