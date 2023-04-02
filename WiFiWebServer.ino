#include <ESP8266WiFi.h>

const char* ssid = "嘻嘻";   //网络的名称
const char* password = "88888888";   //网络密码
int ledPin = 2;
WiFiServer server(80);   //将webserver端口号设置为80

void setup()
{
  Serial.begin(115200);  //串口监视器号
  pinMode(ledPin, OUTPUT);   //控制输入的引脚为2,即开发板上的D4接口
  digitalWrite(ledPin, LOW);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)   //等待连接网络
  {
    delay(100);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to WiFi");
  Serial.print("IP: "); Serial.println(WiFi.localIP());  //输出具体的IP地址
  server.begin();   //用于启动web服务器
}

void loop()
{
  WiFiClient client = server.available();   //检测客户端接入
  if (!client) 
  {
    return;
  }
  while(!client.available())    //等待客户端发送请求
  {
  }

  String request = client.readStringUntil('\r');   //读取请求，并在串口监视器上打印
  Serial.println(request);
  client.flush();

  int value = LOW;
  if (request.indexOf("/LED=OFF") != -1)   //开灯
  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
  if (request.indexOf("/LED=ON") != -1)   //关灯
  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");    //控制WiFi灯的网页
  client.println("<html>");
  client.println("<br><br>");
  client.println("<p style='text-align:center;width=30px;height=30px' ><a  href=\"/LED=ON\"><img src='https://bpic.588ku.com/element_origin_min_pic/19/04/09/d13f75fe216332bd73cdfef22e619d0e.jpg' ></a></p><h4 style='color:green;text-align:center;font-size:40px'><B><i>Turn ON</i></B></h4><br>");
  client.println("<p style='text-align:center;width=30px;height=30px' ><a  href=\"/LED=OFF\"><img src='https://bpic.588ku.com/element_origin_min_pic/19/04/09/d13f75fe216332bd73cdfef22e619d0e.jpg' ></a></p><h4 style='color:black;text-align:center;font-size:40px'><B><i>Turn OFF</i></B></h4><br>");
  client.println("</html>");
  Serial.println("");
}