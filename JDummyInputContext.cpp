#include "JDummyInputContext.h"

JDummyInputContext::JDummyInputContext(QObject *parent) :
    QInputContext(parent)
{
}

QString JDummyInputContext::identifierName()
{
    return QString("JDummyInputContext");
}

bool JDummyInputContext::isComposing() const
{
    return false;
}

QString JDummyInputContext::language()
{
    return QString();
}

void JDummyInputContext::reset()
{
}
