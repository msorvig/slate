#include <QtCore/QtCore>
#include <QtGui/QtGui>

Q_FORWARD_DECLARE_OBJC_CLASS(NSWindow);

class MacWindow
{
public:
    MacWindow(QWindow *contentWindow);
    
    void setGeometry(QRect geometry);
    QRect geometry() const;
    void setVisible(bool visible);
    void show();
protected:
    void createNSWindow();
private:
    QWindow *m_window;
    NSWindow *m_nsWindow;
};
