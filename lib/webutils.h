#ifndef WEBUTILS_H
#define WEBUTILS_H

#include "qtwebutils.h"
#include "slate-global.h"

// This class does not do anything except exporting the API
class SLATE_EXPORT WebUtils: public QtWebUtils
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    explicit WebUtils(QObject *parent = nullptr);           
};

#endif