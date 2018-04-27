#include "macwindow.h"

#import <AppKit/AppKit.h>

MacWindow::MacWindow(QWindow *window)
:m_window(window)
{
    createNSWindow();
}

void MacWindow::createNSWindow()
{
    auto styleMask = NSTitledWindowMask | NSClosableWindowMask |
                     NSMiniaturizableWindowMask | NSResizableWindowMask |
                     NSFullSizeContentViewWindowMask;

    NSRect frame = NSMakeRect(100, 100, 640, 480);
    m_nsWindow =
        [[NSWindow alloc] initWithContentRect:frame
                                    styleMask:styleMask
                                      backing:NSBackingStoreBuffered
                                        defer:NO];
    // Hide the title bar
    m_nsWindow.titlebarAppearsTransparent = YES;
    m_nsWindow.movableByWindowBackground = YES;

    // Make title bar area larger
    NSToolbar *toolbar = [[NSToolbar alloc] initWithIdentifier:@"main"];
    toolbar.showsBaselineSeparator = NO;
    m_nsWindow.toolbar = toolbar;
    m_nsWindow.titleVisibility = NSWindowTitleHidden;
    
    m_nsWindow.contentView = (__bridge NSView *)reinterpret_cast<void *>(m_window->winId());
//    m_window->show();
}

void MacWindow::setGeometry(QRect geometry)
{
    
}

QRect MacWindow::geometry() const
{
    return QRect();
}

void MacWindow::setVisible(bool visible)
{
    if (visible) {
        [m_nsWindow makeKeyAndOrderFront:nil];
    } else {
        
    }
}

void MacWindow::show()
{
    setVisible(true);
}

