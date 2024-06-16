#include "MazeWidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <stdexcept> // Para usar std::invalid_argument

#define CELL_SIZE 30
#define ROWS 13
#define COLS 13
#define MAX_WINDOW_WIDTH 800
#define MAX_WINDOW_HEIGHT 600

MazeWidget::MazeWidget(QWidget *parent)
    : QWidget(parent), mazeGenerator(ROWS, COLS) {
    // Verificar que CELL_SIZE, ROWS y COLS sean valores válidos
    if (CELL_SIZE <= 0) {
        throw std::invalid_argument("Error de Render: CELL_SIZE debe ser mayor que 0.");
    }
    if (ROWS <= 0) {
        throw std::invalid_argument("Error de Render: ROWS debe ser mayor que 0.");
    }
    if (COLS <= 0) {
        throw std::invalid_argument("Error de Render: COLS debe ser mayor que 0.");
    }

    // Verificar que el tamaño del laberinto no exceda el tamaño de la ventana
    int totalWidth = CELL_SIZE * COLS;
    int totalHeight = CELL_SIZE * ROWS;
    if (totalWidth > MAX_WINDOW_WIDTH) {
        throw std::invalid_argument("Error de Render: El ancho total del laberinto excede el tamaño máximo de la ventana.");
    }
    if (totalHeight > MAX_WINDOW_HEIGHT) {
        throw std::invalid_argument("Error de Render: El alto total del laberinto excede el tamaño máximo de la ventana.");
    }

    // Tamaño de la ventana basado en el tamaño de celda y número de celdas
    setFixedSize(totalWidth, totalHeight);
}

void MazeWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            Node* node = mazeGenerator.getNode(i, j);

            if (node->up == nullptr) {
                painter.drawLine(j * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, i * CELL_SIZE); // Línea superior
            }
            if (node->down == nullptr) {
                painter.drawLine(j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE); // Línea inferior
            }
            if (node->left == nullptr) {
                painter.drawLine(j * CELL_SIZE, i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE); // Línea izquierda
            }
            if (node->right == nullptr) {
                painter.drawLine((j + 1) * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE); // Línea derecha
            }
        }
    }

    QWidget::paintEvent(event);  // Llamada al método base para manejar otros eventos de pintura
}
