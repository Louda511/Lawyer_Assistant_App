
// todocomponent.cpp
#include "todocomponent.h"

toDoComponent::toDoComponent(QWidget *parent) : QWidget(parent) {

    // Get user type (lawyer or supervisor)
     userType = user::getInstance()->getType();

    // Create the components
    checkbox = new QCheckBox("To Do", this);  // Set the text during creation
    checkbox->setEnabled(true);
    description = new QTextBrowser(this);
    deadLine = new QLabel("Deadline:", this);
    lawyerOrSupervisorLabel = new QLabel(this);


    // Create layouts
    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Add components to the main vertical layout
    mainLayout->addWidget(checkbox);
    mainLayout->addWidget(description);
    hLayout->addWidget(deadLine);
    mainLayout->addLayout(hLayout);

    if(userType == "supervisor")
    {
        lawyerOrSupervisorLabel->setText("Supervisor");
        deleteButton = new QPushButton("Delete", this);
        hLayout->addWidget(lawyerOrSupervisorLabel);
        mainLayout->addWidget(deleteButton);
    }
    else if(userType != nullptr)
    {
        hLayout->addWidget(lawyerOrSupervisorLabel);
        lawyerOrSupervisorLabel->setText("Lawyer");
    }



    // Set the main layout for the widget
    setLayout(mainLayout);
}

bool toDoComponent::performDeleteToDo()
{
    deleteLater();
    return true;
}
void toDoComponent::setTextBrowserDescription(QString text) {
    description->setText(text);
}

void toDoComponent::setDeadLineLabel(QString deadline) {
    deadLine->setText("Deadline: " + deadline);
}

void toDoComponent::setLawyerOrSupervisorLabel(QString label) {
    lawyerOrSupervisorLabel->setText(label);
}
