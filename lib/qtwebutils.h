#ifndef QTWEBUTILS_H
#define QTWEBUTILS_H

#include <QtCore/QString>
#include <QtCore/QString>
#include <QtQml/QQmlEngine>

namespace qtwebutils {
    
    bool loadFileToFileSystem(const QString &accept, const QString &destinationFilePath,
                                        std::function<void(const QString &, const QString &)> loaded);
    void saveFileFromFileSystem(const QString &sourceFilePath, const QString &fileNameHint);

    void toggleFullscreen();
    void enableTabCloseConfirmation(bool enable);

}

class QtWebUtils : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit QtWebUtils(QObject *parent = nullptr);

    Q_INVOKABLE bool loadFileToFileSystem(const QString &accept, const QString &destinationFilePath, const QJSValue &fileReady);
    Q_INVOKABLE void saveFileFromFileSystem(const QString &sourceFilePath, const QString &fileNameHint);

    Q_INVOKABLE void toggleFullscreen();
    Q_INVOKABLE void enableTabCloseConfirmation(bool enable);
};

#endif // QTWEBUTILS_H
