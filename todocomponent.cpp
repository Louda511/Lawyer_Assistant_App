
// todocomponent.cpp
#include "todocomponent.h"
#include "todo.h"

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
    //QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Add components to the main vertical layout
    mainLayout->addWidget(checkbox);
    mainLayout->addWidget(description);
    mainLayout->addWidget(deadLine);
    //mainLayout->addLayout(hLayout);

    if(userType != nullptr && userType == "supervisor")
    {
        lawyerOrSupervisorLabel->setText("Lawyer: ");
        deleteButton = new QPushButton("Delete", this);
        mainLayout->addWidget(lawyerOrSupervisorLabel);
        mainLayout->addWidget(deleteButton);
    }
    else if(userType != nullptr)
    {
        mainLayout->addWidget(lawyerOrSupervisorLabel);
        lawyerOrSupervisorLabel->setText("Supercisor: ");
    }



    // Set the main layout for the widget
    setLayout(mainLayout);
}

toDoComponent::toDoComponent(toDo *td, QWidget *parent)
    : QWidget(parent),
      userType(user::getInstance()->getType()),
      todo(td),
      checkbox(new QCheckBox(this)),
      description(new QTextBrowser(this)),
      deadLine(new QLabel(this)),
      lawyerOrSupervisorLabel(new QLabel(this))

{
    //NOTE
    description->acceptRichText();
    checkbox->setText(todo->getTitle());
    checkbox->setChecked(todo->isDone());
    description->setText(todo->getDescription());
    deadLine->setText("Deadline: " + todo->getDeadline());

    // Create layouts
    //QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Add components to the main vertical layout
    mainLayout->addWidget(checkbox);
    mainLayout->addWidget(description);
    mainLayout->addWidget(deadLine);
    //mainLayout->addLayout(hLayout);

    if(userType != nullptr && userType == "supervisor")
    {
        lawyerOrSupervisorLabel->setText("Lawyer: "+ getInitials(todo->getToDoAuthorName()));
        //deleteButton = new QPushButton("Delete", this);
        mainLayout->addWidget(lawyerOrSupervisorLabel);
        //mainLayout->addWidget(deleteButton);
    }
    else if(userType != nullptr)
    {
        mainLayout->addWidget(lawyerOrSupervisorLabel);
        lawyerOrSupervisorLabel->setText("Supervisor: " + getInitials(todo->getToDoAuthorName()));
    }
    setMaximumSize(300,200);

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

toDoComponent::~toDoComponent() {
    // Perform necessary cleanup, delete dynamically allocated objects
    delete checkbox;
    delete description;
    delete deadLine;
    delete lawyerOrSupervisorLabel;
    if(userType == "supervisor")
    {
    delete deleteButton;
    }
}

QString toDoComponent::getInitials(const QString& fullName)  {
    QStringList nameParts = fullName.split(' ', Qt::SkipEmptyParts);

    if (nameParts.size() >= 2) {
        // Get the first character of the first name
        QChar initial = nameParts[0].at(0);

        // Concatenate the initial with the last name
        return QString("%1. %2").arg(QString(initial).toUpper()).arg(nameParts[1]);
    } else {
        // Handle the case where there are not enough parts
        return fullName;
    }
}
