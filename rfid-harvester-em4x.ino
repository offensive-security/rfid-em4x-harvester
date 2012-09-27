
HardwareSerial RFID = HardwareSerial();
const int led_pin = 6; // Teensy has LED on 11
void setup() {
	Serial.begin(9600);
	RFID.begin(9600);
	delay(1000); 
	Serial.println("[*] RFID EM4X Card Reader");
	Serial.println("[*] \"l\" - lists saved tags (up to 48).");
	Serial.println("[*] \"c\" - clears all tags.");
	Serial.println("[*] \"s\" - saves last recorded tag.");
	// RFID.print("ctl\r");
	delay(2000);
}

void loop() 
{
	int incomingByte;
	char c;
	if (Serial.available() > 0) 
	{
		incomingByte = Serial.read();
		if (incomingByte == 108) // l for "list"
		{ 
			Serial.println("[*] Listing Saved tags");
			RFID.print("ls\r");
			delay(5000);
		}

		if (incomingByte == 99) // c for "clear"
		{ 
			Serial.println("[*] Clearing All tags");
			RFID.print("ctl\r");
			delay(7000);
		}

		if (incomingByte == 115) // s for "save"
		{ 
			Serial.println("[*] Save Last tag");
			RFID.print("sv\r");
			delay(1000);
		}
           
	}  
	int check = 0;
	
	while (RFID.available() > 0) 
	{
		incomingByte = RFID.read();
		if ((incomingByte == 78)||(incomingByte == 84)) // Look for T and N (TNACK for unknown card)
		{
			check++;  
		}
		c = (char) incomingByte;
		Serial.print(c);

	}
	if (check == 2) 
	{
		delay(200);
		digitalWrite(led_pin, HIGH);
		Serial.println("[*] Saving tag!");
		RFID.print("sv\r");
		delay(200);
		digitalWrite(led_pin, LOW);
	}
	
	delay(200);
}

