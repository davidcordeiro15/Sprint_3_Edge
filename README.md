# Projeto ESP32 com Sensor DHT22 e MQTT

## Descrição do Projeto

Este projeto utiliza um **ESP32** para monitorar a temperatura e umidade através de um sensor **DHT22**. Os dados coletados pelo sensor são enviados via protocolo **MQTT** para um **Broker MQTT**, permitindo a visualização remota dos dados.

O ESP32 se conecta a uma rede Wi-Fi para enviar as informações para o broker. Além disso, ele também recebe comandos via MQTT por meio de um tópico de **subscribe**.

## Membros do Grupo

- **556030** – Caio Venancio
- **557538** – David Cordeiro
- **555619** – Tiago Morais
- **556228** – Marcos Ferreira

## Funcionalidades

- Leitura de dados de **temperatura** e **umidade** utilizando o sensor **DHT22**.
- Conexão à rede Wi-Fi configurada pelo usuário.
- Envio dos dados coletados para um **Broker MQTT** em dois tópicos distintos.
- Reconexão automática ao Wi-Fi e ao Broker MQTT em caso de falha.
- Inscrição em um tópico MQTT para possíveis comandos externos.

## Componentes Utilizados

- **ESP32**: Microcontrolador com conectividade Wi-Fi e Bluetooth.
- **Sensor DHT22**: Sensor para medir a temperatura e umidade do ambiente.
- **Broker MQTT**: Responsável por receber e distribuir as mensagens enviadas pelo ESP32.

## Imagens do Projeto 

![Screenshot_1](https://github.com/user-attachments/assets/2c849f02-debd-46fb-9a50-a781c65b010e)

![Screenshot_2](https://github.com/user-attachments/assets/ca5a9990-e32e-45f9-896f-71a243502503)


## Link do projeto via Wokwi

https://wokwi.com/projects/410386989345244161

## Licença

Este projeto é de uso livre e pode ser utilizado para fins educacionais.

