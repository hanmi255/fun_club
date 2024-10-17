#ifndef RESULT_H
#define RESULT_H

#include <QString>

class Result {
public:
    enum Status {
        Success,
        Failure
    };

    Result(Status status, const QString &message)
        : status(status), message(message) {}

    Status getStatus() const { return status; }
    QString getMessage() const { return message; }

private:
    Status status;
    QString message;
};

#endif // RESULT_H
