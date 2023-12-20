
// todocomponent.cpp
#include "todocomponent.h"

toDoComponent::toDoComponent(QWidget *parent) : QWidget(parent) {
    // Create the components
    checkbox = new QCheckBox("To Do", this);  // Set the text during creation
    description = new QTextBrowser(this);
    deadLine = new QLabel("Deadline:", this);
    supervisor = new QLabel("Supervisor:", this);

    // Create layouts
    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    // Add components to the main vertical layout
    mainLayout->addWidget(checkbox);
    mainLayout->addWidget(description);
    hLayout->addWidget(supervisor);
    hLayout->addWidget(deadLine);
    mainLayout->addLayout(hLayout);




    // Set the main layout for the widget
    setLayout(mainLayout);
}
