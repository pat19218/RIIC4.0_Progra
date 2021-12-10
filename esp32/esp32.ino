/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server con acceso a SPIFFS
  Basándose en los ejemplos de:
  https://github.com/khoih-prog/WiFiWebServer
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://github.com/luisllamasbinaburo/ESP32-Examples
  https://www.luisllamas.es/esp8266-esp32/
**************************************************************************************************/
//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>


//************************************************************************************************
// Variables globales
//************************************************************************************************
byte val = 160;

// SSID & Password
const char* ssid = "tacu´s wifi";  // Enter SSID here
const char* password = "12345678";  //Enter Password here
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)


//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("password: ");
  Serial.println(password);

  server.on("/", handle_OnConnect); // página de inicio
  server.onNotFound([]() {                  // si el cliente solicita una uri desconocida
    if (!HandleFileRead(server.uri()))      // enviar archivo desde SPIFF, si existe
      handleNotFound();             // sino responder con un error 404 (no existe)
  });
  //server.onNotFound(handle_NotFound); //si no se encuentra el uri, responder con error 404 (no existe)

  server.begin(); // iniciar servidor
  Serial.println("HTTP server started");
  delay(100);

}
//************************************************************************************************
// loop principal
//************************************************************************************************
void loop() {

  server.handleClient(); // escuchar solicitudes de clientes

  server.send(200, "text/html", SendHTML(val,24.3,val,val)); //responde con un OK (200) y envía HTML

}
//************************************************************************************************
// Handler de página de inicio
//************************************************************************************************
void handle_OnConnect() {
  handle_8on(); // inicia LED apagado, por defecto
}
//************************************************************************************************
// Handler de handle_8on
//************************************************************************************************
void handle_8on() {
  Serial.println("Espacio disponibles: 8");
  float temp = 24.6;
  server.send(200, "text/html", SendHTML(val,temp,val,val)); //responde con un OK (200) y envía HTML
}

//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML(byte aire, float tempt, byte level, byte humedad) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += " <html>\n";
  ptr += " <head>\n";
  ptr += " <meta charset=\"utf-8\">\n";
  ptr += " <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  ptr += "<title> YAIMA, RIIC 4.0 val </title>\n";
  ptr += "<link rel=\"stylesheet\" href=\"index.css\">\n";
  ptr += " </head>\n";

  ptr += " <body onload=\"gettime()\"><center>";
  ptr += "     <h1>YAIMA PROJECT</h1>";
  ptr += " <table style=\"margin-top: 5%;\"><tr>";
  ptr += "     <td>";
  ptr += "         <div class=\"content-all\">";
  ptr += " <div class=\"content-img\">";

  ptr += "             <div class=\"content-txt\">";
  ptr += "                 <h2> Humedad <br> ";
  ptr += String(humedad);
  ptr += "% </h2>";
  ptr += "            </div>";
  ptr += "             <div class=\"content-1\"></div>";
  ptr += "             <div class=\"content-2\"></div>";
  ptr += "             <div class=\"content-3\"></div>";
  ptr += "             <div class=\"content-4\"></div>";
  ptr += "             <img src=\"humedad.jpg \">";
  ptr += "         </div>";
  ptr += " </div";
  ptr += "     </td>";
  ptr += " <td> <div class=\"content-all\">";
  ptr += " <div class=\"content-img\">";

  ptr += "             <div class=\"content-txt\">";
  ptr += "                 <h2> Temperatura <br>";
  ptr += String(tempt);
  ptr += "</h2>";
  ptr += "             </div>";
  ptr += "             <div class=\"content-1\"></div>";
  ptr += "             <div class=\"content-2\"></div>";
  ptr += "             <div class=\"content-3\"></div>";
  ptr += "             <div class=\"content-4\"></div>";
  ptr += "             <img src=\"temperatura.jpg \">";
  ptr += "         </div> ";
  ptr += "        </td>";
  ptr += "        <td> <div class=\"content-all\">";
  ptr += " <div class=\"content-img\">";

  ptr += "             <div class=\"content-txt\">";
  ptr += "                 <h2> Nivel de CO<sub>2</sub> <br> ";
  ptr += String(aire);
  ptr += "</h2>";

  ptr += "             </div>";

  ptr += "             <div class=\"content-1\"></div>";
  ptr += "             <div class=\"content-2\"></div>";
  ptr += "             <div class=\"content-3\"></div>";
  ptr += "             <div class=\"content-4\"></div>";
  ptr += "             <img src=\"co4.jpg \">";

  ptr += "         </div> </td> ";
  ptr += " </tr></table>";
  ptr += " <table>";
  ptr += " <tr>";
  ptr += " <td>";
  ptr += " <div class=\"content-all\">";
  ptr += " <div class=\"content-img\">";
  ptr += "             <div class=\"content-txt\">";
  ptr += "                 <h2> Mantenimiento<br> </h2>";
  ptr += "             </div>";
  ptr += "             <div class=\"content-1\"></div>";
  ptr += "             <div class=\"content-2\"></div>";
  ptr += "             <div class=\"content-3\"></div>";
  ptr += "             <div class=\"content-4\"></div>";
  ptr += "             <img src=\"settings.png \">";
  ptr += "         </div></td>";
  ptr += "         <td><div class=\"content-all\">";
  ptr += " <div class=\"content-img\">";
  ptr += "             <div class=\"content-txt\">";
  ptr += "                 <h2> Capacidad<br>";
  ptr += String(level);
  ptr += "</h2>";
  ptr += "             </div>";
  ptr += "             <div class=\"content-1\"></div>";
  ptr += "             <div class=\"content-2\"></div>";
  ptr += "             <div class=\"content-3\"></div>";
  ptr += "             <div class=\"content-4\"></div>";
  ptr += "             <img src=\"bat.jpg \">";
  ptr += " </div></td>";
  ptr += " </table>";
  ptr += " </center>";
  ptr += " <script language=\"JavaScript\">";
  ptr += " function gettime() {";
  ptr += "     var date= new Date();";
  ptr += "      var s = date.getSeconds();";
  ptr += "         if(s < 10){";
  ptr += "         s = \"0\" + s}";
  ptr += "     document.clockform.clock.value =  s;";
  ptr += "     setTimeout(\"gettime()\",100)}";
  ptr += " </script>";
  ptr += " <form name=\"clockform\">";
  ptr += " <input type=\"text\" name=\"clock\">";
  ptr += " </form>";
  ptr += " </body>";
  ptr += " </html>";
  
  return ptr;
}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}
//************************************************************************************************
// Obtener el tipo de contenido del archivo
//************************************************************************************************
String GetContentType(String filename)
{
  if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
//************************************************************************************************
// Enviar al servidor el archivo desde SPIFFS
//************************************************************************************************
void ServeFile(String path)
{
  File file = SPIFFS.open(path, "r");
  size_t sent = server.streamFile(file, GetContentType(path));
  file.close();
}
//************************************************************************************************
// Enviar al servidor el archivo desde SPIFFS
//************************************************************************************************
void ServeFile(String path, String contentType)
{
  File file = SPIFFS.open(path, "r");
  size_t sent = server.streamFile(file, contentType);
  file.close();
}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
bool HandleFileRead(String path)
{
  if (path.endsWith("/")) path += "index.html";
  Serial.println("handleFileRead: " + path);

  if (SPIFFS.exists(path))
  {
    ServeFile(path);
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;
}
