# Automato-Celular-Simples
Algoritmo desenvolvido por mim para ser apresentado como projeto final da disciplina de Programação I na Universidade Federal de Rondônia (UNIR)

O Jogo da Vida é um automato celular criado por John Horton, a minha versão é mais simples e menos adaptativa, feita completamente na linguagem C

O conceito é muito simples, células de uma matriz 10x10 passam por verificações de requisitos para definir se terão seus estados alterados ou mantidos, no caso, os requisitos são:
- Células 1 (vivas), caso tenham ao redor 2 ou 3 células vivas, se mantém vivas na próxima geração;
- Células 0 (mortas), case tenham ao redor 3 células vivas, se tornam células vivas na próxima geração;
- Caso não tenham os requisitos, morrem ou permanecem mortas até que aja alteração na sua situação

O jogo funciona de maneira autonoma após a inicialização da matriz, que é feita pelo próprio jogador, inserindo os estados de todas as células e após isso resta apenas a obersvação de como o algoritmo se comporta.
