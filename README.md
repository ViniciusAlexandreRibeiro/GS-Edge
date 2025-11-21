# Office Sense - Global Solutions 2025 

## 📋 Descrição do Projeto
O **Office Sense** é uma solução IoT desenvolvida para a **Global Solutions 2025**, focada no tema **"O Futuro do Trabalho"**. A aplicação visa mitigar problemas críticos do ambiente corporativo moderno e do home office, como o esgotamento profissional (Burnout), má ergonomia e desconforto ambiental.

Utilizando o conceito de **Edge Computing**, o dispositivo monitora a saúde do colaborador e o ambiente em tempo real, fornecendo feedbacks instantâneos e gerando dados estratégicos para a gestão de RH.

## 🛠️ Componentes e Hardware
O sistema foi desenvolvido e simulado na plataforma Wokwi, utilizando:
* **ESP32 DevKit V1**: Unidade de processamento central e conectividade Wi-Fi.
* **Sensor DHT22**: Monitoramento de temperatura e umidade (Conforto Térmico).
* **Sensor Ultrassônico (HC-SR04)**: Monitoramento de distância para ergonomia (Postura frente à tela).
* **Potenciômetro**: Simulação de sensor de batimentos cardíacos (BPM/Estresse).
* **Atuadores (LED e Buzzer)**: Interface de feedback visual e sonoro para o usuário.

<img width="1267" height="630" alt="CleanShot 2025-11-20 at 21 49 53" src="https://github.com/user-attachments/assets/e8df5219-2520-4318-881b-465b05ea1f59" />


## 🚀 Funcionalidades (Edge Computing)
A solução implementa uma arquitetura de decisão local (sem depender da nuvem para alertas críticos):
1.  **Alerta de Estresse:** Aciona alarme se os batimentos cardíacos simulados ultrapassarem 110 BPM.
2.  **Correção Postural:** Notifica o usuário se a distância da tela for inferior a 30cm (risco visual e ergonômico).
3.  **Qualidade do Ar:** Monitora se a temperatura (>35°C) ou umidade (<30%) estão inadequadas para o trabalho.

## ☁️ Conectividade e IoT
Para gestão a longo prazo, o dispositivo conecta-se à internet via Wi-Fi e envia dados de telemetria a cada 15 segundos para a plataforma **ThingSpeak** utilizando requisições HTTP (API REST), permitindo a criação de dashboards analíticos para gestores.

## 🔧 Como Reproduzir
1.  Acesse a simulação no Wokwi: [INSIRA SEU LINK AQUI]
2.  Verifique as bibliotecas necessárias: `DHT sensor library`, `WiFi`, `HTTPClient`.
3.  No código fonte, insira suas credenciais de Wi-Fi e a **Write API Key** do seu canal ThingSpeak.
4.  Inicie a simulação para visualizar os dados no Serial Monitor e no Dashboard.

## 👨‍💻 Desenvolvedores
* Vinicius Alexandre Aureliano Ribeiro
* RM 561606
