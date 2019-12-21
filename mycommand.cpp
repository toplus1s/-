#include "mycommand.h"

myCommand::myCommand(QString str, QString id, bool oldT, bool newT)
{
              m_str = str;
              m_id = id;
              m_oldT = oldT;
              m_newT = newT;

        }

void myCommand::redo()
{

}

void myCommand::undo()
{
    if(m_str == "add")
        undoadd(m_id);
}
