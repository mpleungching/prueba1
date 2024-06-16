#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>
#include "MazeGenerator.h"

class MazeWidget : public QWidget {
    Q_OBJECT

public:
    explicit MazeWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    MazeGenerator mazeGenerator;
};

#endif // MAZEWIDGET_H
