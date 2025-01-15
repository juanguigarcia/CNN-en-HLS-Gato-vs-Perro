#include "cnn.h"
#include "cnn.cpp"
#include <iostream>
#include <cmath>

#include "imagen.h"

// Función para probar una imagen
void test_image(const unsigned char image[100][100]) {
    // Crear una matriz bidimensional para pasarla a la CNN
    float image_matrix[IMG_SIZE][IMG_SIZE];
    for (int i = 0; i < IMG_SIZE; ++i) {
        for (int j = 0; j < IMG_SIZE; ++j) {
            image_matrix[i][j] = (float) image[i][j];
        }
    }

    // Llamar a la función CNN
    float result = cnn(image_matrix);

    // Imprimir el resultado
    std::cout << "Predicción: " << (result > 0.5 ? "Perro" : "Gato")
              << " (Probabilidad: " << result << ")\n";
}

int main() {
    std::cout << "Prueba de la CNN con una imagen...\n";

    // Ejecutar la predicción para la imagen incluida
    test_image(imagen);

    std::cout << "Prueba completada.\n";
    return 0;
}
