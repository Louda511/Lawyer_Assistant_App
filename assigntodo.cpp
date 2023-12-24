#include "assigntodo.h"

assignToDo* assignToDo::instance = nullptr;

assignToDo* assignToDo::getInstance()
{
    if (assignToDo::instance == nullptr)
    {
        instance = new assignToDo();
    }
    return instance;
}

assignToDo::assignToDo(QWidget *parent)
    : QDialog(parent),
    titleLabel(new QLabel("Title", this)),
    descriptionLabel(new QLabel("Description", this)),
    deadLineLabel(new QLabel("Deadline: ", this)),
    asigneeLabel(new QLabel("Asignee", this)),
    titleLineEdit(new QLineEdit(this)),
    descriptionTextEdit(new QTextEdit(this)),
    deadLineDateEdit(new QDateEdit(this)),
    asigneeComboBox(new QComboBox(this)),
    buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this)),
    calendarWidget(new QCalendarWidget(this))
{
    QVBoxLayout *mainVLayout = new QVBoxLayout(this);

    deadLineDateEdit->setCalendarPopup(true);
    deadLineDateEdit->setCalendarWidget(calendarWidget);
    // Add widgets to the layout
    mainVLayout->addWidget(titleLabel);
    mainVLayout->addWidget(titleLineEdit);
    mainVLayout->addWidget(descriptionLabel);
    mainVLayout->addWidget(descriptionTextEdit);
    mainVLayout->addWidget(deadLineLabel);
    mainVLayout->addWidget(deadLineDateEdit);
    mainVLayout->addWidget(asigneeLabel);
    mainVLayout->addWidget(asigneeComboBox);


    // Set QDateEdit readOnly to allow only calendar input

    mainVLayout->addWidget(buttonBox);

    // Connect the button signals to slots
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, &assignToDo::updateDate);
    connect(buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &assignToDo::onOkButtonClicked);

}
void assignToDo::updateDate()
{
    // Get the selected date from the QCalendarWidget and set it in QDateEdit
    QDate selectedDate = calendarWidget->selectedDate();
    deadLineDateEdit->setDate(selectedDate);

    // Do any additional processing or update UI elements here if needed
    qDebug() << "Selected Date: " << selectedDate;
}
void assignToDo::onOkButtonClicked()
{
    QString title = this->titleLineEdit->text();
    QString description = this->descriptionTextEdit->toPlainText();
    QString deadLine = this->deadLineDateEdit->text();
    QString asignee = this->asigneeComboBox->currentText();




    toDo *td = new toDo(0,title, description, deadLine,0,false,asignee);
    toDoComponent *component1 = new toDoComponent (td);
    toDosBoardWindow::getInstance()->addToDoComponents(component1);
    boardWindowApi::getInstance()->postToDo(title,description,deadLine,39);

    QMessageBox::information(this,"Message", "To Do Added Successfully");
    qDebug() << deadLine;
}

