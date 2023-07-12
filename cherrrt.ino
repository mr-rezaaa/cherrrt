o#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
int ledState = LOW; 
/* Put your SSID & Password */
const char* ssid = "Mohammad Reza";  // Enter SSID here
const char* password = "19216811";  //Enter Password here
 
/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);
 
ESP8266WebServer server(80);
 
uint8_t LED1pin = D7;
bool LED1status = LOW;
 
uint8_t LED2pin = D6;
bool LED2status = LOW;
 
uint8_t LED3pin = D5;
bool LED3status = LOW;
 
uint8_t LED4pin = D4;
bool LED4status = LOW;

uint8_t LED5pin = D9;
bool LED5status = LOW;
////////////////////////////////////////
const int ledPin = LED_BUILTIN; 
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000; 
////////////////////////////////////////
int rat = 0;
int senter = 0;
int left = 0;
int canter = 0;
void setup()
 {
  pinMode(D13, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D8, INPUT); 
  pinMode(ledPin, OUTPUT);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  pinMode(LED3pin, OUTPUT);
  pinMode(LED4pin, OUTPUT);
  pinMode(LED5pin, OUTPUT);
  Serial.print("Setting soft-AP ... ");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
 
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);

  server.on("/led3on", handle_led3on);
  server.on("/led3off", handle_led3off);
  server.on("/led4on", handle_led4on);
  server.on("/led4off", handle_led4off);

  server.on("/led5on", handle_led5on);
  server.on("/led5off", handle_led5off);

  server.onNotFound(handle_NotFound); 
  
  server.begin();
 //////////////////////////////////////
}
void loop() 
{ 
if(D13 == 1)  
  {canter=canter+1}
  server.handleClient();
  ////////////////////////////////////////////
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;
    if (ledState == LOW) {ledState = HIGH;} 
    else {ledState = LOW;}
    digitalWrite(ledPin, ledState);
  }
  ////////////////////////////    mohammad Reza   ////////////
 if(LED1status)      back();
 else if(LED2status) fyont();
 else if(LED3status) right();
 else if(LED4status) LEFT();
 else                stop();
 /////////////////////////////////////////////////////// 
if((LED5status)||(canter%2))
{
if(rat==LOW & rat==LOW)  fyont();
if(left)    {right();}
if(rat)     {LEFT();}
if(left==1&rat==1)   stop(); 
}
 
  //////////////////////////////////////////////////////////////
left=digitalRead(D2);
senter=digitalRead(D3);
rat=digitalRead(D8);
}
 
 void fyont()
  {
  digitalWrite(LED1pin, LOW);
  digitalWrite(LED2pin, HIGH);
  digitalWrite(LED3pin, LOW);
  digitalWrite(LED4pin, HIGH);
  }
void stop()
 {
  digitalWrite(LED1pin, LOW);
  digitalWrite(LED2pin, LOW);
  digitalWrite(LED3pin, LOW);
  digitalWrite(LED4pin, LOW);
 }
 void back()
  {
  digitalWrite(LED1pin, HIGH);
  digitalWrite(LED2pin, LOW);
  digitalWrite(LED3pin, HIGH);
  digitalWrite(LED4pin, LOW);
 }
 void right() 
 {
  digitalWrite(LED1pin, HIGH);
  digitalWrite(LED2pin, LOW);
  digitalWrite(LED3pin, LOW);
  digitalWrite(LED4pin, HIGH);
 }
 void LEFT() 
 {
  digitalWrite(LED1pin, LOW);
  digitalWrite(LED2pin, HIGH);
  digitalWrite(LED3pin, HIGH);
  digitalWrite(LED4pin, LOW);
 }
 
 //////////////////////////////////////////////////
void handle_OnConnect()
 {
  LED1status = LOW;
  LED2status = LOW;
  LED3status = LOW;
  LED4status = LOW;
  LED5status = LOW;  
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status,LED5status)); 
 }
 
void handle_led1on() 
{
  LED1status = HIGH;
  server.send(200, "text/html", SendHTML(true,LED2status,LED3status,LED4status,LED5status)); 
}
 
void handle_led1off() 
{
  LED1status = LOW;
  server.send(200, "text/html", SendHTML(false,LED2status,LED3status,LED4status,LED5status)); 
}
 
void handle_led2on()
{
  LED2status = HIGH;
  server.send(200, "text/html", SendHTML(LED1status,true,LED3status,LED4status,LED5status)); 
}
 
void handle_led2off() 
{
  LED2status = LOW;
  server.send(200, "text/html", SendHTML(LED1status,false,LED3status,LED4status,LED5status)); 
}
 //////////////////////////////////////////////////////////////////////////////////
void handle_led3on() 
{
  LED3status = HIGH;
  server.send(200, "text/html", SendHTML(LED1status,LED2status,true,LED4status,LED5status)); 
}
 
void handle_led3off() 
{
  LED3status = LOW;
  server.send(200, "text/html", SendHTML(LED1status,LED2status,false,LED4status,LED5status)); 
}
 
void handle_led4on() 
{
  LED4status = HIGH;
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,true,LED5status)); 
}
 
void handle_led4off() 
{
  LED4status = LOW;
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,false,LED5status)); 
}
void handle_led5on()
{
 LED5status = HIGH;  
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status,true)); 
}

void handle_led5off() 
{
  LED5status = LOW;
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status,false)); 
}

 //////////////////////////////////////////////////////////////////////////////////
void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}
 
String SendHTML(uint8_t led1stat,uint8_t led2stat,uint8_t led3stat,uint8_t led4stat,uint8_t led5stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Robbot Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 30px;} h1 {color: #444444;margin: 30px auto 20px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";

   if(led1stat)
  {ptr +="<p>RUN FRONT: RUN</p><a class=\"button button-off\" href=\"/led1off\">STOP</a>\n";}
  else
  {ptr +="<p>RUN FRONT: STOP</p><a class=\"button button-on\" href=\"/led1on\">RUN</a>\n";}
 
  if(led2stat)
  {ptr +="<p>LED2 Status: RUN</p><a class=\"button button-off\" href=\"/led2off\">STOP</a>\n";}
  else
  {ptr +="<p>LED2 Status: STOP</p><a class=\"button button-on\" href=\"/led2on\">RUN</a>\n";}
 ////////////////////////////////////////////
   if(led3stat)
  {ptr +="<p>LED3 Status: RUN</p><a class=\"button button-off\" href=\"/led3off\">STOP</a>\n";}
  else
  {ptr +="<p>LED3 Status: STOP</p><a class=\"button button-on\" href=\"/led3on\">RUN</a>\n";}
 
  if(led4stat)
  {ptr +="<p>LED4 Status: RUN</p><a class=\"button button-off\" href=\"/led4off\">STOP</a>\n";}
  else
  {ptr +="<p>LED4 Status: STOP</p><a class=\"button button-on\" href=\"/led4on\">RUN</a>\n";}

  if(led5stat)
  {ptr +="<p>LED5 Status: runinferadet</p><a class=\"button button-off\" href=\"/led5off\">stop inferadet</a>\n";}
  else
  {ptr +="<p>LED4 Status: stopinferadet</p><a class=\"button button-on\" href=\"/led5on\">runinferadet</a>\n";}

 ///////////////////////////////////////////
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}









{
  "dns": {
    "hosts": {
      "domain:googleapis.cn": "googleapis.com"
    },
    "servers": [
      "1.1.1.1"
    ]
  },
  "inbounds": [
    {
      "listen": "127.0.0.1",
      "port": 10808,
      "protocol": "socks",
      "settings": {
        "auth": "noauth",
        "udp": true,
        "userLevel": 8
      },
      "sniffing": {
        "destOverride": [
          "http",
          "tls"
        ],
        "enabled": true
      },
      "tag": "socks"
    },
    {
      "listen": "127.0.0.1",
      "port": 10809,
      "protocol": "http",
      "settings": {
        "userLevel": 8
      },
      "tag": "http"
    }
  ],
  "log": {
    "loglevel": "warning"
  },
  "outbounds": [
    {
      "mux": {
        "concurrency": 8,
        "enabled": false
      },
      "protocol": "vless",
      "settings": {
        "vnext": [
          {
            "address": "rel.j1.jahany.online",
            "port": 80,
            "users": [
              {
                "encryption": "none",
                "flow": "",
                "id": "7f66f7e2-47b6-4ccf-d9d5-30737b4bfb2c",
                "level": 8,
                "security": "auto"
              }
            ]
          }
        ]
      },
      "streamSettings": {
        "network": "ws",
        "security": "none",
        "wsSettings": {
          "headers": {
            "Host": ""
          },
          "path": "/q"
        }
      },
      "tag": "proxy"
    },
    {
      "protocol": "freedom",
      "settings": {},
      "tag": "direct"
    },
    {
      "protocol": "blackhole",
      "settings": {
        "response": {
          "type": "http"
        }
      },
      "tag": "block"
    }
  ],
  "routing": {
    "domainStrategy": "IPIfNonMatch",
    "rules": [
      {
        "ip": [
          "1.1.1.1"
        ],
        "outboundTag": "proxy",
        "port": "53",
        "type": "field"
      }
    ]
  }
}