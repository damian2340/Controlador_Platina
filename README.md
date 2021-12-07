# Controlador_Platina

Controlador actuadores piezoelectricos basado en la placa Nucleo-F334R8 de ST e inversor de 150V

Usando el periferico HRTIM se consiguen 5 señales cuadradas de frecuencia fija de 80kHz y moduladas por ancho de pulso con una resolucion de 217pico segundos.

Para controlar las tensiones de salida de los actuadores que mueven los ejes x e y se uso  una topologia Buck Multifase con 2 señales desfasadas 180° en cada salida.

Para la medición de la posición por ahora se utilizaron los Strain Gauges que traen los actuadores piezoelectricos, los que mediante 3 canales ADC se miden para ser usados en un lazo de control.
La medición se hace de manera sincronica con las conmutaciones para evirat los ruidos electricos que estan pueden producir.
