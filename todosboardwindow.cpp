#include "todosboardwindow.h"



toDosBoardWindow::toDosBoardWindow(QWidget *parent)
    : QMainWindow(parent),
    title(new QLabel("To Do's Board", this)),
    addToDoPushButton(new QPushButton("Add a To Do", this)),
    toDosGridLayout(new QGridLayout())
{
    setWindowTitle("To Do's Board");

    QWidget *centralWidget = new QWidget();
    QVBoxLayout *mainVBoxLayout = new QVBoxLayout(centralWidget);

    // Creating the horizontal layout
    QHBoxLayout *hLayout = new QHBoxLayout();
    title->setVisible(true);
    addToDoPushButton->setVisible(true);
    hLayout->addWidget(title);
    hLayout->addWidget(addToDoPushButton);

    // Set the alignment of hLayout to the top of the available space
    hLayout->setAlignment(Qt::AlignTop);

    // Add hLayout and toDosGridLayout to the main layout
    mainVBoxLayout->addLayout(hLayout);
    mainVBoxLayout->addLayout(toDosGridLayout);

    setCentralWidget(centralWidget);
    resize(1200, 500);

    // Your additional initialization code here
}

void toDosBoardWindow::addToDoComponents(const QList<toDoComponent *> &toDoComponents)
{
    // Add ToDoComponents to the main grid layout
    int row = 0;
    int col = 0;

    for (toDoComponent *component : toDoComponents) {
        toDosGridLayout->addWidget(component, row, col);

        // Adjust the row and column for the next component
        col++;
        if (col >= 3) {
            col = 0;
            row++;
        }
    }
}

QGridLayout* toDosBoardWindow::getToDosGridLayout() const {
    return toDosGridLayout;
}
void toDosBoardWindow::addSingleToDoComponent(toDoComponent *td)
{
    if (toDosGridLayout && td) {
        getToDosGridLayout()->addWidget(td);
    } else {
        // Handle the case where toDosGridLayout or td is not initialized
        qDebug() << "Error: toDosGridLayout or toDoComponent is not initialized!";
    }
}
