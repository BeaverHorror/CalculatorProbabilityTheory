#include "examplevalidator.h"

ExampleValidator::ExampleValidator(QObject* parent)
    : QValidator (parent)
{
}
ExampleValidator::~ExampleValidator()
{
}

QValidator::State ExampleValidator::validate(QString &string, int &pos) const
{
  if(pos > 0 && !string[pos - 1].isLetterOrNumber()) return QValidator::Invalid;                   //

  if(pos == 1 && !string[0].isDigit()) return QValidator::Invalid;                                 //

  if(pos == 2 && !string[1].isLetterOrNumber()) return QValidator::Invalid;                        //
  if(pos == 2 && string[0].isLetter() && string[1].isLetterOrNumber()) return QValidator::Invalid; //

  if(pos == 3 && !string[2].isLetterOrNumber()) return QValidator::Invalid;                        //
  if(pos == 3 && string[1].isLetter() && string[2].isLetterOrNumber()) return QValidator::Invalid; //

  if(pos == 4 && !string[3].isLetterOrNumber()) return QValidator::Invalid;                        //
  if(pos == 4 && string[2].isLetter() && string[3].isLetterOrNumber()) return QValidator::Invalid; //

  if(pos == 5 && !string[4].isLetterOrNumber()) return QValidator::Invalid;                        //
  if(pos == 5 && string[3].isLetter() && string[4].isLetterOrNumber()) return QValidator::Invalid; //

  if(pos == 6 && !string[5].isLetterOrNumber()) return QValidator::Invalid;                        //
  if(pos == 6 && string[4].isLetter() && string[5].isLetterOrNumber()) return QValidator::Invalid; //

  if(pos == 7 && !string[6].isLetterOrNumber()) return QValidator::Invalid;                        //
  if(pos == 7 && string[5].isLetter() && string[6].isLetterOrNumber()) return QValidator::Invalid; //

  if(pos == 8 && !string[7].isLetterOrNumber()) return QValidator::Invalid;                        //
  if(pos == 8 && string[6].isLetter() && string[7].isLetterOrNumber()) return QValidator::Invalid; //

  if(pos == 9 && !string[8].isLetterOrNumber()) return QValidator::Invalid;                        //
  if(pos == 9 && string[7].isLetter() && string[8].isLetterOrNumber()) return QValidator::Invalid; //

  return QValidator::Acceptable;
}
