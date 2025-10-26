## 🏓 Raylib Pong Game

>Uma recriação do famoso jogo Pong, desenvolvido em C com a biblioteca [Raylib](https://www.raylib.com/).
>[![Licença MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE) [![Linguagem C](https://img.shields.io/badge/Language-C-blue.svg?style=flat&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language)) [![Feito com Raylib](https://img.shields.io/badge/Made%20with-raylib-E6441E.svg)](https://www.raylib.com/)
>=
## Sobre o projeto:
Este projeto foi totalmente voltado para praticar a linguagem C e a biblioteca Raylib
* **Estrutura de Dados em C:** Uso de 'structs' para modelar os objetos do jogo (raquete e bola).
* **Física 2D:** Implementação de lógica, colisão e variação de ângulo.
* **Raylib:** Uso de funções básicas da biblioteca, como inicialização e detecção de colisão.

## 🎮 Como Jogar

O objetivo do jogo é rebater a bola para a parede do lado inimigo.

| **Raquete Esquerda (P1)** 
|  |`W` | Mover para cima |
|  | `S` | Mover para baixo |
| **Raquete Direita (P2)**
|  |`O` | Mover para cima |
|  | `L` | Mover para baixo |

## 🛠️ Como Compilar e Rodar
 ### Pré-requisitos Para compilar este jogo, você precisará: 
 1. Um compilador C (como **GCC**). 
 2. 2. A biblioteca **raylib** instalada e configurada em seu sistema. 
 3. ### Compilação (Linux / macOS) 
 4. Navegue até a pasta raiz do projeto no seu terminal e use o seguinte comando para compilar e linkar com a raylib e a biblioteca matemática (`-lm`): 
```bash
gcc -o pong_game main.c -lraylib -lm
```
5. Após compilar, execute o jogo: 
```bash 
./pong_game.exe //windows
./pong_game //linux
```

## Licença
Este projeto está licenciado sob a Licença **MIT**. Veja o arquivo LICENSE para detalhes.

## Autor
Gabriel Makiyama Nakashima
Github: [nakashima1231](https://github.com/nakashima1231)
Email para contato: gabrielmnakashima2@gmail.com

Muito obrigado por ler até aqui. :)
