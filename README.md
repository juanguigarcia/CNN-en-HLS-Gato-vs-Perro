CNN en HLS
=============
En este proyecto se ha realizado una red neuronal convolucional (CNN) en Vitis HLS que distingue entre perros y gatos. El objetivo es que pueda ser implementado en una FPGA *PYNQ-Z2*. Los entrenamientos de la CNN no son los óptimos ni las imagenes utilizadas ya que la FPGA tiene una serie de limitaciones de memoria y recursos y el objetivo del proyecto no es que sea de gran fiabilidad la CNN si no demostrar que se puede implementar en una FPGA. 

A continuación, se van a explicar los contenidos que hay en cada una de las carpetas de este repositorio.

Python
-------------
En este apartado se encuentra la CNN que distingue fotos de perros y gatos en *Python*, la cual ha sido implementada en *Google Colab*. La CNN consta de tres capas convolucionales y de *MaxPooling* y finalmente de una capa densa.  El archivo subido se encuentra optimizado y con las imagenes con una resolución de 100x100, en el proyecto se ha utilizado imagenes de 25x25. De este código, se extrae el entrenamiento de la CNN y la imagen que se va a introducir en la FPGA en formato *.h*.

Datos
-------------
En esta carpeta se encuentran los entrenamientos de la CNN. Se encuentran los datos de las tres capas convolucionales, de las tres capas de *MaxPooling* y de la capa densa. También, se encuentra la imagen en formato *.h*.

C++
-------------
Esta carpeta contiene la implementación de la red neuronal convolucional en C++ haciendo uso de los archivos de entrenamiento. En el archivo `cnn.cpp`se encuentran las distintas funciones que implementan las funciones de las distintas capas de la CNN, una función de activación *ReLu* que introduce no linealidad y descarta valores negativos, una función *sigmoide* y finalmente la implementación de la CNN. También cuenta con un archivo en el que se declaran las funciones y se incluyen los archivos de entrenamiento, `cnn.h` y un *test bench*, `test_bench.cpp`para comprobar que la red funciona correctamente.

Vitis HLS
-------------
En esta otra carpeta, se encuentran los códigos mencionados en la carpeta *C++* pero implementados en *Vitis HLS* e indicando como va a ser el componente que se va a crear a partir de ellos para luego ser utilizado en *Vivado*. Este componente hace uso de `s_axilite`para indicar el autobus a través del cual se introduce la imagen en el componente y del que se devuelve el resultado de la CNN. También se declara que los archivos de los entrenamientos se guardan en la DDR haciendo uso de `m_axi`.

Vivado
-------------
En esta carpeta se encuentra el *bitstream* generado con *Vivado* en formato *.xsa*. La conexión de los componentes en *Vivado* es como se muestra en la siguiente imagen:


Xilink Vitis
-------------
En esta última carpeta, se encuentra un archivo `test_bench.cc`que implementa un código de prueba para comprobar que la CNN funciona correctamente en la FPGA una vez ha sido cargado y ejecutado. También cuenta con un archivo `xparameters.h`en el que se muestran las conexiones del componente que implementa la CNN y un archivo `xcnn.h`en el que se encuentran las funciones con las que ha sido implementado el código de prueba, las cuales se han generado con *Vivado* al realizar el *bitstream*
