#ifndef MYCOMMAND_H
#define MYCOMMAND_H
#include<qundostack.h>

class myCommand: public QUndoCommand
{
public:
    myCommand(QString str,QString id, bool oldT, bool newT);
    void redo();
    void undo();
private:
    QString m_str, m_id;
    bool m_oldT, m_newT;
};

#endif // MYCOMMAND_H
