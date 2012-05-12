#ifndef JDUMMYINPUTCONTEXT_H
#define JDUMMYINPUTCONTEXT_H

#include <QInputContext>

class JDummyInputContext : public QInputContext
{
    Q_OBJECT

public:
    explicit JDummyInputContext(QObject *parent = 0);

    virtual QString identifierName();
    virtual bool isComposing() const;
    virtual QString language();
    virtual void reset();
};

#endif
