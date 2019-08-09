#include <ESP8266WiFi.h>
String a,b,c,d,e;
const char* ssid  = "TP-LINK_PIUMIU";
const char* password = "piumiu123#";

//const char* server="api.thingspeak.com";
const char* host="technoenginix.atspace.cc"; 
//const char* host="52.15.229.152";
//const char* host="staging.appx.co.in";
const int httpPort = 80;
WiFiClient client;

void setup() {
 Serial.begin(9600);

   WiFi.disconnect();//disconnect from previously connected Access points
  delay(10);
  WiFi.begin(ssid,password);//begin connecting to the given ssid and pass
Serial.println("Connecting to");
while(WiFi.status()!=WL_CONNECTED)//when not connected
{
  Serial.print(".");//print dots
  delay(500);
}
Serial.println("Connected");//show connected after connecting
Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());

}

void loop ()
{
  a=random(15,20);
  b=random(86,96);
  c=random(350,450);
  d=random(4,10);
  e=random(30,34); 
  sendDataToServer(a,b,c,d,e);
  delay(60000);
}

void sendDataToServer(String a, String b,String c,String d, String e)
{
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  String result="";
  String url="/sensor.php?volume="+a+"&moisture="+b+"&weight="+c+"&toxicity="+d+"&temperature="+e;
 //String url="/smartbin?volume="+a+"&moisture="+b+"&weight="+c+"&toxicity="+d+"&temperature="+e;
 
  //String url="/smartbin?log.php?test_2="+a+"&test_3="+b;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  Serial.println( String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");            
  delay(500);
  
  while(client.available()){
   result = client.readStringUntil('\r');
    Serial.print(result);
  }
  
  Serial.println();
  Serial.println("closing connection");
  delay(3000);



  client.stop(); //stop client
  //Serial.println(result);
  
}

