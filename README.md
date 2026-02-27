# ESP Smart Gate 🚪⚡

---

# English

Smart and resilient access control system developed by [@JoaoVitorSBarbosa](https://github.com/JoaoVitorSBarbosa) in collaboration with the [Team TROIA](https://github.com/teamTroia) study group.

### 📌 About the Project
The goal of this repository is to develop the firmware for an autonomous electronic lock. The system's main feature is its fault tolerance: it will continue to operate and log accesses locally (via RTC and flash memory) even during power outages or lack of internet connectivity, syncing the data to the cloud later.

### 🚧 Development Status
The project is in its early staging phase. Hardware architecture, schematics, and software dependencies will be documented here as development progresses.

### 📝 Initial Roadmap
- [ ] Base environment setup (PlatformIO)
- [ ] Access Point (AP) and Async Web Server setup
- [ ] RFID hardware integration
- [ ] Local database implementation (LittleFS)
- [ ] Cloud synchronization routine (Store & Forward)

---

# Português

Sistema de controle de acesso inteligente e resiliente desenvolvido por [@JoaoVitorSBarbosa](https://github.com/JoaoVitorSBarbosa) em conjunto com o Núcleo de Estudos [Team TROIA](https://github.com/teamTroia).

### 📌 Sobre o Projeto
O objetivo deste repositório é desenvolver o firmware para uma tranca eletrônica autônoma. O grande diferencial do sistema é a tolerância a falhas: ele continuará operando e registrando acessos localmente (via RTC e memória flash) mesmo em cenários de queda de energia ou falta de internet, sincronizando os dados com a nuvem posteriormente.

### 🚧 Status do Desenvolvimento
O projeto está em fase inicial de estruturação. Arquitetura de hardware, esquemáticos e dependências de software serão documentados aqui conforme o avanço do desenvolvimento.

### 📝 Roadmap Inicial
- [X] Configuração do ambiente base (PlatformIO)
- [X] Subida do modo Access Point (AP) e Web Server Assíncrono
- [ ] Integração do hardware de leitura RFID
- [ ] Implementação do banco de dados local (LittleFS)
- [ ] Rotina de sincronização na nuvem (Store & Forward)
- [ ] Módulo OTA



