
#include "effects.h"

#include <EmbAJAX.h>
#include <EmbAJAXValidatingTextInput.h> // Fancier text input in a separate header file
#include <EmbAJAXScriptedSpan.h>

#include <ESP8266HTTPUpdateServer.h>
ESP8266HTTPUpdateServer webUpdater;

// Set up web server, and register it with EmbAJAX. Note: EmbAJAXOutputDriverWebServerClass is a
// convenience #define to allow using the same example code across platforms
EmbAJAXOutputDriverWebServerClass server(80);
EmbAJAXOutputDriver driver(&server);

#define BUFLEN 30

EmbAJAXCheckButton check("check", "Some option");
EmbAJAXMutableSpan check_d("check_d");

const char* radio_opts[] = {"Option1", "Option2", "Option3"};
EmbAJAXRadioGroup<3> radio("radio", radio_opts);
EmbAJAXMutableSpan radio_d("radio_d");

EmbAJAXOptionSelect<3> optionselect("optionselect", radio_opts);
EmbAJAXMutableSpan optionselect_d("optionselect_d");

EmbAJAXSlider slider("slider", 0, 1000, 500);
EmbAJAXMutableSpan slider_d("slider_d");
char slider_d_buf[BUFLEN];

EmbAJAXColorPicker color("color", 0, 255, 255);
EmbAJAXMutableSpan color_d("color_d");
char color_d_buf[BUFLEN];

EmbAJAXTextInput<BUFLEN> text("text");  // Text input, width BUFLEN
EmbAJAXMutableSpan text_d("text_d");
char text_d_buf[BUFLEN];

EmbAJAXValidatingTextInput<16> valtext("valtext");
EmbAJAXMutableSpan valtext_d("valtext_d");
char valtext_d_buf[BUFLEN];

int button_count = 0;
void buttonPressed(EmbAJAXPushButton*) { button_count++; }
EmbAJAXPushButton button("button", "I can count", buttonPressed);
EmbAJAXMutableSpan button_d("button_d");
char button_d_buf[BUFLEN];

EmbAJAXMomentaryButton m_button("m_button", "Press and hold");
EmbAJAXMutableSpan m_button_d("m_button_d");

EmbAJAXScriptedSpan m_script_s("m_script_s", "this.receiveValue = function(value) { this.innerHTML = value + ' + 1 = ' + (Number(value)+1); };");

EmbAJAXStatic nextCell("</td><td>&nbsp;</td><td><b>");
EmbAJAXStatic nextRow("</b></td></tr><tr><td>");

// Define a page (named "page") with our elements of interest, above, interspersed by some uninteresting
// static HTML. Note: MAKE_EmbAJAXPage is just a convenience macro around the EmbAJAXPage<>-class.
MAKE_EmbAJAXPage(page, "RGB Strip Controler", "",
  new EmbAJAXStatic("<style>\n"
  ".footer {position: fixed; left: 0; bottom: 0; width: 100%; background-color: red; color: white; text-align: center; }\n"
  "</style>"),
    new EmbAJAXStatic("<center><table cellpadding=\"10\"><tr><td>"),
    /*
    &check,
    &nextCell,  // Static elements can safely be inserted into the same page more than once!
    &check_d,
    &nextRow,

    &radio,
    &nextCell,
    &radio_d,
    &nextRow,

    &optionselect,
    &nextCell,
    &optionselect_d,
    &nextRow,
    
    &slider,
    &nextCell,
    &slider_d,
    &nextRow,
*/  
    &nextRow,
    &color,
    &nextCell,
    &color_d,
    &nextRow,
/*
    &text,
    &nextCell,
    &text_d,
    &nextRow,

    &valtext,
    &nextCell,
    &valtext_d,
    &nextRow,

    &button,
    &nextCell,
    &button_d,
    &nextRow,

    &m_button,
    &nextCell,
    &m_button_d,
    &nextRow,

    new EmbAJAXStatic("A client side script:"),
    &nextCell,
    &m_script_s,
    &nextRow,
    */
    /*
    &nextRow,
    new EmbAJAXStatic("Server status:"),
    &nextCell,
    new EmbAJAXConnectionIndicator(),
    new EmbAJAXStatic("</b></td></tr></table></center>"),
    */

    
    
    
    new EmbAJAXStatic("<div class=\"footer\">\n"),
    //"<p>Footer</p>\n"
    new EmbAJAXStatic("Server status:"),
    new EmbAJAXConnectionIndicator(),
    new EmbAJAXStatic("</div>")
)
effect ledStrip = effect(100, D8);


void setup() {
  Serial.begin(115200);
  pinMode(D8, OUTPUT);

  pinMode(BUTTON,INPUT_PULLUP);  // internal pull-up resistor
  //attachInterrupt (digitalPinToInterrupt (BUTTON), ledStrip.changeEffect, CHANGE); // pressed



  //The SSID must be >8 characters and <64 characters
  //I'm adding the chip ID onto the end to get a unique (ish) name
  //String ssid = "ESP8266 " + String(ESP.getChipId(), HEX);
  String ssid = "LED AP";
 
  //The password must be <64 characters and can be left blank for no password
  String pass = "password";
 
  Serial.printf("WiFiSSID: '%s'\n", ssid.c_str());
  Serial.printf("Password: '%s'\n", pass.c_str());
 
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid.c_str(), pass.c_str());
  
//  http://192.168.4.1/update
//  http://192.168.4.1/LED_button
//  http://192.168.4.1/Slider
  

  /*
  server.on("/", [](){
    server.send(200, "text/plain", "Successfullly wifi updated");
  });
*/
  webUpdater.setup(&server);
  
  driver.installPage(&page, "/", updateUI);
  
  server.begin();
  
  valtext.setPlaceholder("192.168.1.1");
  valtext.setPattern("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");

  updateUI(); // init displays

  ledStrip.setEffect(12);
}


void loop() { 
//ledStrip.setEffect(12);
/*
  for(int i = 0; i < 10; i ++){
    server.handleClient();
    delay(1);
  }    
  ledStrip.setEffect(ledStrip.getEffect());
  ledStrip.setAll(0,0,0);
  */
 // server.handleClient();
     // handle network. loopHook() simply calls server.handleClient(), in most but not all server implementations.
  driver.loopHook();
}

void updateUI() {
    // Update UI. Note that you could simply do this inside the loop. However,
    // placing it here makes the client UI more responsive (try it).
    check_d.setValue(check.isChecked() ? "checked" : "not checked");
    radio_d.setValue(radio_opts[radio.selectedOption()]);
    optionselect_d.setValue(radio_opts[optionselect.selectedOption()]);
    slider_d.setValue(itoa(slider.intValue(), slider_d_buf, 10));
    color_d.setValue(strncpy(color_d_buf, color.value(), BUFLEN));  // r, g, b, are also available, numerically.
    text_d.setValue(strncpy(text_d_buf, text.value(), BUFLEN));
    valtext_d.setValue(strncpy(valtext_d_buf, valtext.value(), BUFLEN));
    button_d.setValue(itoa(button_count, button_d_buf, 10));
    m_button_d.setValue((m_button.status() == EmbAJAXMomentaryButton::Pressed) ? "pressed" : "not pressed");
    m_script_s.setValue(button_d_buf);
}