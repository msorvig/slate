
#include "webutils.h"

#ifdef Q_OS_WASM

WebUtils::WebUtils(QObject *parent)
:QtWebUtils(parent)
{
    qDebug() << "WebUtils";
}

#endif