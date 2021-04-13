#ifndef EXAMPLEVALIDATOR_H
#define EXAMPLEVALIDATOR_H

#include <QValidator>

class ExampleValidator : public QValidator
{
  Q_OBJECT
public:
  ExampleValidator(QObject *parent);
  ~ExampleValidator();

  QValidator::State validate(QString & string, int & pos) const;
};

#endif // EXAMPLEVALIDATOR_H
