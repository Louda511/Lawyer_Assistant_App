#ifndef USER_H
#define USER_H

#include <QString>

class user {
private:
    int id;
    QString name;
    QString password;
    QString job_title;
    QString type;
    QString email;
    int sup_id;
    static user *instance;

    // Private constructor to prevent external instantiation
    user();

public:


    // Setters
    void setId(int newId);
    void setName(const QString& newName);
    void setPassword(const QString& newPassword);
    void setJobTitle(const QString& newJobTitle);
    void setType(const QString& newType);
    void setEmail(const QString& newEmail);
    void setSupervisorId(int newSupId);

    // Getters
    int getId() const;
    const QString& getName() const;
    const QString& getPassword() const;
    const QString& getJobTitle() const;
    const QString& getType() const;
    const QString& getEmail() const;
    int getSupervisorId() const;

    // Function to get the instance of the singleton class
    static user* getInstance();


};

#endif // USER_H
