//biblioteca wifi do esp8266
#include <ESP8266WiFi.h>
//porta http
WiFiServer server(80);

//configuração rede wifi
#define SSID "SSID"
#define SENHA "senha"

//configuração de saídas digitais
const byte npin = 10;
byte pinout[npin] =  {5,      4,      0,      2,      14,     12,     13,     15,     3,      1};
byte pinmode[npin] = {OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT};

void setup()
{
  Serial.begin(115200);

  //Configura o modo dos pinos
  for (int nP=0; nP < npin; nP++) {
      pinMode(pinout[nP], pinmode[nP]);
      digitalWrite(pinout[nP], LOW);
  }

  Serial.print("Conectando");
  WiFi.begin(SSID, SENHA);

  //Aguarda conectar rede
  while (WiFi.status() != WL_CONNECTED)
  {
    //Esperamos 100 milisegundos
    delay(100);
    Serial.print(".");
  }

  //Se chegou aqui Ã© porque conectou Ã  rede, entÃ£o mostramos no monitor serial para termos um feedback
  Serial.println("");
  Serial.println("Conectou");

  //ConfiguraÃ§Ãµes do IP fixo. VocÃª pode alterar conforme a sua rede
  IPAddress ip(192, 168, 1, 111);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  Serial.print("Configurando IP fixo para : ");
  Serial.println(ip);

  //Envia a configuraÃ§Ã£o
  WiFi.config(ip, gateway, subnet);

  //Inicializa o server que criamos na porta 80
  server.begin();

  //Mostramos no monitor serial o IP que o ESP possui para verificarmos se Ã© o mesmo que configuramos
  Serial.print("Server em: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  //Verifica se algum cliente estÃ¡ tentando se conectar
  WiFiClient client = server.available();
  if (!client)
  {
    //Se nÃ£o houver nenhum cliente podemos retornar pois nÃ£o hÃ¡ nada a fazer
    return;
  }
  Serial.println("Novo cliente conectou");
  //Fazemos a leitura da requisição
  String req = client.readStringUntil('\r');
  Serial.print("RequisiÃ§Ã£o: ");
  Serial.println(req);

  String html = 
  "<html>"
    "<head>"
      "<meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'/>"
      "<title>Automação Residencial</title>"
      "<style>"
        "body{"
          "text-align: center;"
          "font-family: sans-serif;"
          "font-size:14px;"
          "padding: 25px;"
          "background-color:#000;"
        "}"
        "p{color:#fff;}"
        "button{"
          "outline: none;"
          "border: 2px solid #1fa3ec;"
          "border-radius:18px;"
          "background-color:#fff;"
          "color: #1fa3ec;"
          "padding: 10px 35px;"
        "}"
        "button:active{"
          "color: #fff;"
          "background-color:#1fa3ec;"
        "}"
      "</style>"
    "</head>"
    "<body>"
    "<center>"
    "<p>SW1</p>"//----------------------------------------------------SW1
    "<table><tr>"
    "<td><a href='?acao=A'><button>ON</button></td>"
    "<td><a href='?acao=a'><button>OFF</button></td>"
    "</tr></table>"
    "<p>SW2</p>"//----------------------------------------------------SW2
    "<table><tr>"
    "<td><a href='?acao=B'><button>ON</button></td>"
    "<td><a href='?acao=b'><button>OFF</button></td>"
    "</tr></table>"
    "<p>SW3</p>"//----------------------------------------------------SW3
    "<table><tr>"
    "<td><a href='?acao=C'><button>ON</button></td>"
    "<td><a href='?acao=c'><button>OFF</button></td>"
    "</tr></table>"
    "<p>SW4</p>"//----------------------------------------------------SW4
    "<table><tr>"
    "<td><a href='?acao=D'><button>ON</button></td>"
    "<td><a href='?acao=d'><button>OFF</button></td>"
    "</tr></table>"
    "<p>SW5</p>"//----------------------------------------------------SW5
    "<table><tr>"
    "<td><a href='?acao=E'><button>ON</button></td>"
    "<td><a href='?acao=e'><button>OFF</button></td>"
    "</tr></table>"
    "<p>SW6</p>"//----------------------------------------------------SW6
    "<table><tr>"
    "<td><a href='?acao=F'><button>ON</button></td>"
    "<td><a href='?acao=f'><button>OFF</button></td>"
    "</tr></table>"
    "<p>SW7</p>"//----------------------------------------------------SW7
    "<table><tr>"
    "<td><a href='?acao=G'><button>ON</button></td>"
    "<td><a href='?acao=g'><button>OFF</button></td>"
    "</tr></table>"
    "<p>SW8</p>"//----------------------------------------------------SW8
    "<table><tr>"
    "<td><a href='?acao=H'><button>ON</button></td>"
    "<td><a href='?acao=h'><button>OFF</button></td>"
    "</tr></table>"
    "<p>SW9</p>"//----------------------------------------------------SW9
    "<table><tr>"
    "<td><a href='?acao=I'><button>ON</button></td>"
    "<td><a href='?acao=i'><button>OFF</button></td>"
    "</tr></table>"
    "<p>SW10</p>"//----------------------------------------------------SW10
    "<table><tr>"
    "<td><a href='?acao=J'><button>ON</button></td>"
    "<td><a href='?acao=j'><button>OFF</button></td>"
    "</tr></table>"
    "</center>"
    "</body>"
  "</html>";

  client.print(html);
  client.flush();

  //------------------------------------------------------------Altera estado de SW1
  if (req.indexOf("acao=A") != -1)
  {digitalWrite(pinout[0], HIGH);}
  else if (req.indexOf("acao=a") != -1)
  {digitalWrite(pinout[0], LOW);}
  //------------------------------------------------------------Altera estado de SW2
  else if (req.indexOf("acao=B") != -1)
  {digitalWrite(pinout[1], HIGH);}
  else if (req.indexOf("acao=b") != -1)
  {digitalWrite(pinout[1], LOW);}
  //------------------------------------------------------------Altera estado de SW3
  else if (req.indexOf("acao=C") != -1)
  {digitalWrite(pinout[2], HIGH);}
  else if (req.indexOf("acao=c") != -1)
  {digitalWrite(pinout[2], LOW);}
  //------------------------------------------------------------Altera estado de SW4
  else if (req.indexOf("acao=D") != -1)
  {digitalWrite(pinout[3], HIGH);}
  else if (req.indexOf("acao=d") != -1)
  {digitalWrite(pinout[3], LOW);}
  //------------------------------------------------------------Altera estado de SW5
  else if (req.indexOf("acao=E") != -1)
  {digitalWrite(pinout[4], HIGH);}
  else if (req.indexOf("acao=e") != -1)
  {digitalWrite(pinout[4], LOW);}
  //------------------------------------------------------------Altera estado de SW6
  else if (req.indexOf("acao=F") != -1)
  {digitalWrite(pinout[5], HIGH);}
  else if (req.indexOf("acao=f") != -1)
  {digitalWrite(pinout[5], LOW);}
  //------------------------------------------------------------Altera estado de SW7
  else if (req.indexOf("acao=G") != -1)
  {digitalWrite(pinout[6], HIGH);}
  else if (req.indexOf("acao=g") != -1)
  {digitalWrite(pinout[6], LOW);}
  //------------------------------------------------------------Altera estado de SW8
  else if (req.indexOf("acao=H") != -1)
  {digitalWrite(pinout[7], HIGH);}
  else if (req.indexOf("acao=h") != -1)
  {digitalWrite(pinout[7], LOW);}
  //------------------------------------------------------------Altera estado de SW9
  else if (req.indexOf("acao=I") != -1)
  {digitalWrite(pinout[8], HIGH);}
  else if (req.indexOf("acao=i") != -1)
  {digitalWrite(pinout[8], LOW);}
  //------------------------------------------------------------Altera estado de SW10
  else if (req.indexOf("acao=J") != -1)
  {digitalWrite(pinout[9], HIGH);}
  else if (req.indexOf("acao=j") != -1)
  {digitalWrite(pinout[9], LOW);}

  //Fecha a conexão com o cliente
  client.stop();
  Serial.println("Cliente desconectado");
}
