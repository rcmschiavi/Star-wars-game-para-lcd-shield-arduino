# Hands-on de arduino - Star Wars game

C�digos desenvolvidos para um Hands-on de Arduino ministrado por mim, oferecido e divulgado pela Empresa J�nior da Engenharia Mecatr�nica-IFSC.

## Bibliotecas

### StarWars
Essa biblioteca cont�m um c�digo simples que dinamiza a movimenta��o nas duas linhas do display de LCD, permitindo mais de duas posi��es pra nave.
Seus exemplos de funcionamento � o c�digo exemplo 3 e 4.

### StarWarsFull
Biblioteca que possue as fun��es anteriores e tamb�m cria naves inimigas e lida com os tiros da nave, acertar os tiros nos inimgos, marca pontos e verifica o fim do jogo.
O exemplo de funcionamento � o c�digo exemplo 5.

### Caracteres das bibliotecas
![Figura 1 - Caracteres criados](imagens/caracteres.jpg)

Figura 1 - Caracteres criados

## C�digos de exemplo

Este reposit�rio cont�m c�digos de exemplo para utiliza��o do shield arduino da figura figura 1. Os c�digos est�o em n�vel de complexidade.

![Figura 2 - Shield LCD](https://http2.mlstatic.com/display-lcd-keypad-shield-16x02-com-teclado-botoes-arduino-D_NQ_NP_513521-MLB20797065961_072016-F.jpg)

Figura 2 - Shield LCD

### C�digo exemplo 1
C�digo b�sico que inicializa o display, imprime "Hello world!" na tela e permite movimenta��o do mesmo com os bot�es.

### C�digo exemplo 2
Exemplo que cria um caracter e salva na mem�ria do display para manipula-lo na tela.
![Figura 3 - Caracteres sugeridos](imagens/caracteres1.jpg)

Figura 3 - Caracteres sugeridos no exemplo

### C�digo exemplo 3
Esse exemplo requer a instala��o da biblioteca dispon�vel nesse reposit�rio, basta instalar na pasta libraries do arduino, geralmente na pasta documentos

### C�digo exemplo 4
Aprimoramento do exemplo 3 com a utiliza��o de uma fun��o para deixar o c�digo mais limpo.

### C�digo exemplo 5
Para utilizar esse exemplo, � necess�rio instalar a biblioteca StarWarsFull. Esse exemplo tem como fun��o mostrar como bibliotecas mais completas e complexas podem facilitar a programa��o, mas causar erros que s�o dif�ceis de debugar sem um conhecimento consider�vel de como funcionam, al�m de limitar as opera��es dispon�veis.
A biblioteca cont�m bugs propositais como tiros atravessando as naves inimigas que n�o podem ser corrigidos no c�digo do arduino.

### C�digo sem biblioteca
C�digo criado inicialmente para gerar as bibliotecas. Cont�m alguns bugs, pois deixa-lo perfeito n�o era o foco. Sinta-se livre para contribuir e corrigi-los.

## Utiliza��o do proteus
Caso voc� n�o tenha a shield e/ou um arduino, � poss�vel utilizar o c�digo no projeto do proteus 7.1.
Basta compilar o projeto e copiar o endere�o da pasta tempor�ria gerada na compila��o, � poss�vel ve-la em vermelho nas informa��es de compila��o. Adicione o arquivo hex desta pasta no local indicado na figura 4.

![Figura 4 - Utilizando o arduino no proteus](imagens/proteus.jpg)

Figura 4 - Utilizando o arduino no proteus

### To-do:
- Corrigir bugs na biblioteca StarWarsFull;
- Corrigir bugs no c�digo "StarWarsSBiblioteca".

### Como contribuir:

1. Crie um Fork.
2. Para trabalhar em uma proposta, crie um branch (`git checkout -b proposta_x`)
3. Commit (`git commit -m "Descri��o da proposta"`)
4. Push para o branch da proposta (`git push origin proposta_x`)
5. Abra uma [Pull Request]
6. V� fazer outra coisa.