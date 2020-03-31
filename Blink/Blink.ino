/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
/* ///////////////////////////////////////////////////////////////////////////////////////////////////
GPIO code
D0 = GPIO16;
D1 = GPIO5;
D2 = GPIO4;
D3 = GPIO0;
D4 = GPIO2;
D5 = GPIO14;
D6 = GPIO12;
D7 = GPIO13;
LED_PIN = GPIO15;
D9 = GPIO3;
D10 = GPIO1;

PERIPHS_IO_MUX_GPIO0_U,   /* 0 - D3 
PERIPHS_IO_MUX_U0TXD_U,   /* 1 - uart 
PERIPHS_IO_MUX_GPIO2_U,   /* 2 - D4 
PERIPHS_IO_MUX_U0RXD_U,   /* 3 - uart 
PERIPHS_IO_MUX_GPIO4_U,   /* 4 - D2 
PERIPHS_IO_MUX_GPIO5_U,   /* 5 - D1 
Z, /* 6 
Z, /* 7 
Z, /* 8 
PERIPHS_IO_MUX_SD_DATA2_U, /* 9 - D11 (SD2) 
PERIPHS_IO_MUX_SD_DATA3_U, /* 10 - D12 (SD3) 
Z, /* 11 
PERIPHS_IO_MUX_MTDI_U,    /* 12 - D6 
PERIPHS_IO_MUX_MTCK_U,    /* 13 - D7 
PERIPHS_IO_MUX_MTMS_U,    /* 14 - D5 
PERIPHS_IO_MUX_MTDO_U     /* 15 - D8
*/ //////////////////////////////////////////////////9/////////////////////////////////////////////////
#define Z 0
static const int func[] = { 0, 3, 0, 3, 0, 0, Z, Z, Z, 3, 3, Z, 3, 3, 3, 3 };
void setup() {
    Serial.begin(112500);
    //pinMode(D4, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    //PIN_FUNC_SELECT(0x60000838,0); //Initialize the GPIO2/D4 pin as an output

    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, func[2]);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(D4, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(D4, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
  Serial.println(FUNC_GPIO4);
}
