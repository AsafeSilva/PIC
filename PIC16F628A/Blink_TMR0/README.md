# Oscilador com Timer0

Simples oscilador de 1Hz (pode-se configurar qualquer valor) sendo gerado pelo Timer0.

Para facilitar o cálculo do Timer0 abra a [tabela](https://github.com/AsafeSilva/PIC/blob/master/PIC16F628A/Blink_TMR0/Timer0%20Config.xlsx) e insira os valores do `Fosc` (Frequência do oscilador) e do `TMR0_prescaler` (Prescaler do Timer0).
Feito isso, escolha o valor do registrado `TMR0` de acordo com o tempo de estouro (overflow) do Timer0.
Caso o tempo de estouro seja muito pequeno, insira o valor do intervalo em `Time` (Intervalo da interrupção [1/2F ou T/2, onde F é a frequência e T o período]) e escolha o multiplicador mais preciso para seu valor de `Time` (observe o valor do TMR0).

Para mais detalhes, consulte o datasheet!

![Screenshot](Simulação.jpg)

![Screenshot](Configuração.jpg)
