#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

const int screen_width = 128;
const int screen_height = 64;

Adafruit_SSD1306 display(screen_width, screen_height, &Wire);



void setup() {
   Wire.begin();
   
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
   {  
     Serial.print("led not found");
   }


   display.clearDisplay();
   display.setTextSize(4);
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(0,0);
   display.println("Hi");
   display.println("Raspi");
   display.display(); // elements are first written to a buffer, this cmd pushes them to the OLED

}

void loop() {
}