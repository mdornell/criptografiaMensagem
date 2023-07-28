# criptografiaMensagem
Trabalho feito na disciplina de Programação 2 no qual fomos desafiados a criar um código no qual deveria criptografar e descriptografar uma mensagem

**Especificação**

**Contextualização:**
 A Guerra do Iêmem, conhecida como a “Guerra Esquecida”, é a guerra entre os
Houthi, grupo xiita apoiado pelo Iran, e o governo de Abd-Rabbu Mansour Hadi, sunita,
apoiado pela Arábia Saudita. Você foi contratado para fazer um sistema de comunicação de
mensagens entre tropas do exército do governo de Abd-Rabbu. O sistema, a ser elaborado,
deve ter a possibilidade de criar mensagens e decodifica-las.
 As mensagens enviadas são sempre em formato de string, ou seja, consistem num
vetor de caracteres.

**A lei de formação para a criptografia das mensagens é a seguinte:**
1. A criptografia é aplicada a cada substring da string definida. Sendo que uma
substring é dada pelo conjunto de caracteres até que se encontre um espaço em
branco ou o final da string. Ex: “O rato roeu a roupa do rei de Roma” existem 9
substrings.
2. Existem 5 padrões de criptografia que serão aplicados nas substrings:

a. Tudo é Abd: Todo caractere especial (#, @ ou $) deve ser substituído pela substring Abd.
Ex: Ol@T#$xx#  OlAbdTAbdAbdxxAbd

b. Sufixo Rabbu: conta o número de caracteres pares e o número de caracteres
ímpares. O valor a ser avaliado é o referenciado na tabela ASCII para cada
letra. Se tiver mais caracteres pares deve acrescentar Rabbu no final da
substring caso contrário não.
Ex: Amor  A (65) m (109) o (111) r (114)  3 ímpares e 1 par  Amor
Ex: raror  r (114) a (97) r (114) o (111) r (114)  3 pares e 2 ímpares 
rarorRabbu
Ex: raro  r (114) a (97) r (114) o (111)  2 pares e 2 ímpares  raro

c. Inversão quase total: a substring é redefinida sendo escrita de trás para
frente, além disso, garante que o número de letras da nova substring será
impar inserindo o caractere ‘#’ em strings de tamanho par.
Ex: “abcd” será transformado em “dc#ba”.
 “abc” será transformado em “cba”.

d. Inversão 2 a 2: promove a troca entre pares de caracteres.
Ex1: “abcd” será transformado em “badc”.
Ex2: “abc” será transformado em “bac”.

e. Junção: primeiro é aplicado o Tudo é Abd, depois o Sufixo Rabbu, em
seguida a Inversão quase total e finalmente a Inversão 2 a 2.
Ex: @morr  Abdmorr  A (65) b (98) d (100) m (109) o (111) r (114) r
(114)  3 ímpares e 4 pares  AbdmorrRabbu  ubbaRr#romdbA 
buabrRr#mobdA

3. A ordem de aplicação dos padrões de criptografia nas substrings da string principal
é: Tudo é Abd, Sufixo Rabbu, Inversão quase total, Inversão 2 a 2 e Junção, em
seguida começa-se o processo novamente.
Ex1: “Ol@T#$xx# Amor abcd abcd @morr An@ raror abc abc” 
OlAbdTAbdAbdxxAbd Amor dc#ba badc buabrRr#mobdA AnAbd cba bac
Ex2: “Ol@T#$xx# Amor abcd”
OlAbdTAbdAbdxxAbd Amor dc#ba 

