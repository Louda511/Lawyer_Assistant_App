#include "todosboardwindow.h"

toDosBoardWindow::toDosBoardWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setWindowTitle("To Do's Board");

    QWidget *centralWidget = new QWidget();
    QVBoxLayout *mainVBoxLayout = new QVBoxLayout(centralWidget);

    // Creating the horizontal layout
    QHBoxLayout *hLayout = new QHBoxLayout();
    title = new QLabel("To Do's Board", this);
    title->setVisible(true);
    addToDoPushButton = new QPushButton("Add a To Do", this);
    addToDoPushButton->setVisible(true);
    hLayout->addWidget(title);
    hLayout->addWidget(addToDoPushButton);

    // Set the alignment of hLayout to the top of the available space
    hLayout->setAlignment(Qt::AlignTop);

    // Creating another grid layout (toDosGridLayout)
    QGridLayout *toDosGridLayout = new QGridLayout();

    // Add your widgets and layout components for toDosGridLayout here

    // Add hLayout and toDosGridLayout to the main layout
    mainVBoxLayout->addLayout(hLayout);
    mainVBoxLayout->addLayout(toDosGridLayout);

    setCentralWidget(centralWidget);
    resize(400, 500);

    // Your additional initialization code here


}
