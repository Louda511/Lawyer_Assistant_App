
// todocomponent.cpp
#include "todocomponent.h"

toDoComponent::toDoComponent(QWidget *parent) : QWidget(parent) {
    // Create the components
    checkbox = new QCheckBox("To Do", this);  // Set the text during creation
    description = new QTextBrowser(this);
    deadLine = new QLabel("Deadline:", this);
    supervisor = new QLabel("Supervisor:", this);

    // Create layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Add components to the main vertical layout
    mainLayout->addWidget(checkbox);
    mainLayout->addWidget(description);
    mainLayout->addWidget(deadLine);
    mainLayout->addWidget(supervisor);

    // Set the main layout for the widget
    //setLayout(mainLayout);
}
