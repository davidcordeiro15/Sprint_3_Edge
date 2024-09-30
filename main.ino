#include <DHT.h>  
#include <WiFi.h>
#include <PubSubClient.h>

// Configuração do sensor DHT
DHT dht(15, DHT22);  
float temperature;
float humidity;
int counter = 0;  // Inicializando contador para facilitar no momento de gerar os dados

// Configurações da rede Wi-Fi e Broker MQTT
const char* default_SSID = "Wokwi-GUEST"; // Nome da rede Wi-Fi, importante a sua rede wi-fi ter suporte a dispositivos de 2,4GHz devido ao ESP32 utilizar essa frequência 
const char* default_PASSWORD = ""; // Senha da rede Wi-Fi
const char* default_BROKER_MQTT = "52.250.13.188"; // IP do Broker MQTT
const int default_BROKER_PORT = 1883; // Porta do Broker MQTT
const char* default_TOPICO_SUBSCRIBE = "/TEF/device019/cmd"; // Tópico MQTT de escuta
const char* default_TOPICO_PUBLISH_1 = "/TEF/device019/attrs"; // Tópico MQTT de envio de informações para Broker
const char* default_TOPICO_PUBLISH_2 = "/TEF/device019/attrs/p"; // Tópico MQTT de envio de informações para Broker
const char* default_ID_MQTT = "device019"; // ID MQTT

// Declaração da variável para o prefixo do tópico
const char* topicPrefix = "device019";

// Variáveis para configurações editáveis
char* SSID = const_cast<char*>(default_SSID);
char* PASSWORD = const_cast<char*>(default_PASSWORD);
char* BROKER_MQTT = const_cast<char*>(default_BROKER_MQTT);
int BROKER_PORT = default_BROKER_PORT;
char* TOPICO_SUBSCRIBE = const_cast<char*>(default_TOPICO_SUBSCRIBE);
char* TOPICO_PUBLISH_1 = const_cast<char*>(default_TOPICO_PUBLISH_1);
char* TOPICO_PUBLISH_2 = const_cast<char*>(default_TOPICO_PUBLISH_2);
char* ID_MQTT = const_cast<char*>(default_ID_MQTT);


// Configuração das bibliotecas WiFi e MQTT
WiFiClient espClient;
PubSubClient MQTT(espClient);


// Função para inicializar a Serial
void initSerial() {
    Serial.begin(115200);
}

// Função para conectar-se à rede Wi-Fi
void initWiFi() {
    delay(10);
    Serial.println("------Conexão WI-FI------");
    Serial.print("Conectando-se à rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde...");
    reconectWiFi();

}

void reconectWiFi() {
    
    WiFi.begin(SSID, PASSWORD, 6);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Conectado com sucesso!");
    Serial.print("IP obtido: ");
    Serial.println(WiFi.localIP());

}

// Função para inicializar a conexão MQTT
void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);  // Configura o broker
    
}

// Função para reconectar ao broker MQTT se necessário
void reconnectMQTT() {
    while (!MQTT.connected()) {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE);  // Inscreve no tópico, se necessário
        } else {
            Serial.println("Falha ao reconectar. Tentando novamente em 2 segundos...");
            delay(2000);
        }
    }
    
    
}
void VerificaConexoesWiFIEMQTT() {
    if (!MQTT.connected())
        reconnectMQTT();
    reconectWiFi();
}
// Função para ler os dados do sensor DHT e publicar no broker MQTT
void temp() {
    temperature = dht.readTemperature();  // Lê a temperatura
    humidity = dht.readHumidity();  // Lê a umidade

    // Exibe os valores no serial monitor
    Serial.println("Data: " + String(counter));
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" °C");
    
    Serial.print("Umidade: ");
    Serial.println(humidity);
    Serial.println(" ");

    // Publica os dados de temperatura e umidade nos tópicos MQTT
    MQTT.publish(TOPICO_PUBLISH_1, String(temperature).c_str());
    MQTT.publish(TOPICO_PUBLISH_2, String(humidity).c_str());

    counter++;  // Incrementa o contador de envios
    delay(1000);  // Delay para evitar envios constantes
}

void setup() {
    initSerial();  // Inicializa a comunicação serial
    initWiFi();  // Conecta à rede Wi-Fi
    initMQTT();  // Inicializa o MQTT
}

void loop() {
    VerificaConexoesWiFIEMQTT();
    temp();  // Lê e publica os dados do sensor
    MQTT.loop();  // Mantém o loop MQTT ativo
}
