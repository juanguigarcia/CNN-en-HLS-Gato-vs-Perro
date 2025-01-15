CNN en HLS
=============
En este proyecto se ha realizado una red neuronal convolucional (CNN) en Vitis HLS que distingue entre perros y gatos. El objetivo es que pueda ser implementado en una FPGA *PYNQ-Z2*. Los entrenamientos de la CNN no son los óptimos ni las imagenes utilizadas ya que la FPGA tiene una serie de limitaciones de memoria y recursos y el objetivo del proyecto no es que sea de gran fiabilidad la CNN si no demostrar que se puede implementar en una FPGA. 

A continuación, se van a explicar los contenidos que hay en cada una de las carpetas de este repositorio.

Python
-------------
En este apartado se encuentra la CNN que distingue fotos de perros y gatos en *Python*, la cual ha sido implementada en *Google Colab*. La CNN consta de tres capas: la capa  El archivo subido se encuentra optimizado y con las imagenes con una resolución de 100x100, en el proyecto se ha utilizado imagenes de 25x25. De este código, se extrae el entrenamiento de la CNN. 
