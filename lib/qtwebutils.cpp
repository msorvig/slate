#include "qtwebutils.h"

#include <QtCore/qfile.h>
#include <QtGui/private/qwasmlocalfileaccess_p.h>

#include <emscripten/val.h>
#include <emscripten/bind.h>

/*!
    Displays a native file dialog where the user can select a file from
    the local file system.

    The file is copied \a destinationFilePath, which must be a valid file
    path on the file system provided by Emscripten. This will typicallly
    be an in-memory temporary file system. Files on this file system can
    be access using standard file API such as QFile.

    The \a fileReady callback will be called when file load is complete. It
    provides two arguments: the first on is the destination file path (identical
    to the destinationFilePath argument), the second is name of the file
    selected by the user.
*/
bool qtwebutils::loadFileToFileSystem(const QString &accept, const QString &destinationFilePath,
                                    std::function<void(const QString &, const QString &)> fileReady)
{
    struct LoadFileData {
        QString name;
        QByteArray buffer;
    };
    auto fileData = new LoadFileData();

    QWasmLocalFileAccess::openFile(accept.toStdString(),
        [](int fileCount) { Q_ASSERT(fileCount == 1); },
        [fileData](uint64_t size, const std::string name) -> char * {
            fileData->name = QString::fromStdString(name);
            fileData->buffer.resize(size);
            return fileData->buffer.data();
        },
        [fileData, destinationFilePath, fileReady](){
            QFile destinationFile(destinationFilePath);
            destinationFile.open(QIODevice::WriteOnly);
            destinationFile.write(fileData->buffer);
            destinationFile.close();
            fileReady(destinationFilePath, fileData->name);
            delete fileData;
        }
    );
    return true;
}

/*!
    Saves a file to the local file system.

    The \a sourceFilePath is on the in-sandbox file system provided by Emscripten.
*/
void qtwebutils::saveFileFromFileSystem(const QString &sourceFilePath, const QString &fileNameHint)
{
    QFile sourceFile(sourceFilePath);
    sourceFile.open(QIODevice::ReadOnly);
    QByteArray content = sourceFile.readAll();
    QWasmLocalFileAccess::saveFile(content.constData(), size_t(content.size()), fileNameHint.toStdString());
}

/*!
    Toggles fullscreen state for the global document.

    This function can be used to toggle a browser window
    or tab between the normal state and fullscreen state.

    On Qt for WebAssembly the application window is embedded
    in the web document. This means that it does not control
    any native window, and that it may allready be in fullscreen
    state where it does not have window decorations. Using
    e.g. QWindow::setWindowState() will not change the state
    of the browser window.

    Qt for WebAssembly
*/
void qtwebutils::toggleFullscreen()
{
    using emscripten::val;
    const val document = val::global("document");
    const val fullscreenElement = document["fullscreenElement"];
    if (fullscreenElement.isUndefined() || fullscreenElement.isNull())
        document["documentElement"].call<void>("requestFullscreen");
    else
        document.call<void>("exitFullscreen");
}

/*!
    Enables or disables tab close confirmation.

    Setting this to true will make the browser display a popup on tab close,
    asking the user to confirm that they want to prceeed. The wording of
    the dialog is determined by the browser, but will typically include
    a statement to the effect that there are unsaved changes which will be
    lost.

    This is implemented by setting a beforeunload handler on the window.
*/
void qtwebutils::enableTabCloseConfirmation(bool enable)
{
    using emscripten::val;
    const val window = val::global("window");
    const bool capture = true;
    const val eventHandler = val::module_property("qt_webutils_beforeUnloadHandler");
    if (enable) {
        window.call<void>("addEventListener", std::string("beforeunload"), eventHandler, capture);
    } else {
        window.call<void>("removeEventListener", std::string("beforeunload"), eventHandler, capture);
    }
}

namespace {
     emscripten::val beforeUnloadhandler(emscripten::val event) {
         // Adding this event handler is sufficent to make the browsers display
         // the confirmation dialog, provided the calls below are also made:
         event.call<void>("preventDefault"); // call preventDefault as required by standard
         event.set("returnValue", std::string(" ")); // set returnValue to something, as required by Chrome
    }
}

EMSCRIPTEN_BINDINGS(qt_webutils) {
    function("qt_webutils_beforeUnloadHandler", &beforeUnloadhandler);
}

QtWebUtils::QtWebUtils(QObject *parent)
:QObject(parent)
{

}

bool QtWebUtils::loadFileToFileSystem(const QString &accept, const QString &destinationFilePath, const QJSValue &fileReady)
{
    auto ready = [destinationFilePath, fileReady](const QString &filePath, const QString &fileName) {
        QJSValueList args = { QJSValue(destinationFilePath), QJSValue(fileName) };
        fileReady.call(args);
    };
    return qtwebutils::loadFileToFileSystem(accept, destinationFilePath, ready);
}

void QtWebUtils::saveFileFromFileSystem(const QString &sourceFilePath, const QString &fileNameHint)
{
    qtwebutils::saveFileFromFileSystem(sourceFilePath, fileNameHint);
}

void QtWebUtils::toggleFullscreen()
{
    qtwebutils::toggleFullscreen();
}

void QtWebUtils::enableTabCloseConfirmation(bool enable)
{
    qtwebutils::enableTabCloseConfirmation(enable);
}


