#include "todosboardwindow.h"



toDosBoardWindow::toDosBoardWindow(QWidget *parent)
    : QMainWindow(parent),
    title(new QLabel("To Do's Board", this)),
    addToDoPushButton(new QPushButton("Add a To Do", this)),
    toDosGridLayout(new QGridLayout()),
    row(0),
    column(0)

{
    setWindowTitle("To Do's Board");
    //resize(1200, 500);

    QWidget *centralWidget = new QWidget();
    QVBoxLayout *mainVBoxLayout = new QVBoxLayout(centralWidget);


    // Creating the horizontal layout
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(title);
    hLayout->addWidget(addToDoPushButton);


    title->setVisible(true);
    if(user::getInstance()->getType() == "supervisor")
    {

         addToDoPushButton->setVisible(true);
    }
    else
    {

         addToDoPushButton->setVisible(false);
    }
    connect(addToDoPushButton, &QPushButton::clicked,this, &toDosBoardWindow::onAddToDoButtonClicked);


    // Set the alignment of hLayout to the top of the available space
    hLayout->setAlignment(Qt::AlignTop);

    // Add hLayout and toDosGridLayout to the main layout
    mainVBoxLayout->addLayout(hLayout);
    mainVBoxLayout->addLayout(toDosGridLayout);

    setCentralWidget(centralWidget);
    hLayout->setAlignment(Qt::AlignTop);
    // Your additional initialization code here
    qDebug() << "Layout Size: " << hLayout->sizeHint();
    //qDebug() << "Layout Size: " << mainGridLayout->sizeHint();



}


void toDosBoardWindow::addToDoComponents(const QList<toDoComponent *> &toDoComponents)
{
    // Add ToDoComponents to the main grid layout

    for (toDoComponent *component : toDoComponents) {
         toDosGridLayout->addWidget(component, row, column,1,1,Qt::AlignLeft);

        // Adjust the row and column for the next component
        column++;
        if (column >= 3) {
            column = 0;
            row++;
        }
    }
}


void toDosBoardWindow::addToDoComponents(toDoComponent *component)
{
    int rowCount = toDosGridLayout->rowCount();
    int columnCount = toDosGridLayout->columnCount();
    qDebug() << rowCount;
    qDebug() << columnCount;
    // Add the component to the current position
    toDosGridLayout->addWidget(component, row, column, 1, 1, Qt::AlignLeft);

    // Move to the next column
    column++;

    // Set column stretch to make sure items are added horizontally
    for (int c = 0; c < 3; ++c) {
        toDosGridLayout->setColumnStretch(c, 1);
    }

    // Check if the maximum columns in a row is reached
    if (column >= 3) {
        // Move to the next row
        row++;
        column = 0;
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

toDosBoardWindow* toDosBoardWindow::instance = nullptr;

toDosBoardWindow* toDosBoardWindow::getInstance() {
    // Create the instance if it doesn't exist yet
    if (instance == nullptr) {
        instance = new toDosBoardWindow();
    }
    return instance;
}
QGridLayout* toDosBoardWindow::getToDosGridLayout()
{
    return toDosGridLayout;
}
void toDosBoardWindow::onAddToDoButtonClicked()
{
    // Emit the signal when the button is clicked
    assignToDo::getInstance()->show();

    // Additional logic for handling the button click can be added here if needed
}
