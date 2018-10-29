#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <mutex>
#include <fstream>
#include <thread>

#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QMutex>
#include <QQueue>
#include <QFileInfo>
#include <QTcpSocket>
#include <QDir>

#include <Windows.h>
#include <atlbase.h>
#include "C:\\Users\\Student\\Downloads\\Detours-master\\include\\detours.h"
#pragma comment(lib, "C:\\Users\\Student\\Downloads\\Detours-master\\lib.X64\\detours.lib")

#pragma comment(lib,"OpenGL32.lib")
#include <gl\GL.h>
#include <gl\GLU.h>
#pragma comment(lib,"Gdi32.lib")

#include "client.h"
#include "debugwidget.h"

enum class ImageFlow
{
    Request,
    FillFinish,
    End,
};

static QMutex g_mutex;
static QImage g_image;
static ImageFlow g_imageFlow = ImageFlow::End;
static DebugWidget *g_debugWidget = nullptr;

void MessageHandle(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    g_debugWidget->MessageHandle(type, context, msg);
}

void thread_main()
{
    int argc = 0;
    QApplication app(argc, nullptr);

    DebugWidget debugWidget;
    if(QFileInfo( QCoreApplication::applicationDirPath() + "/debug.txt").exists())
    {
        qInstallMessageHandler(MessageHandle);
        g_debugWidget = &debugWidget;
        debugWidget.show();
    }

    Client client;
    QObject::connect(&client, &Client::requestScreenshot, []{
        g_mutex.lock();
        if(g_imageFlow == ImageFlow::End)
        {
            g_imageFlow = ImageFlow::Request;
            qInfo("g_imageFlow End --> Request");
        }
        g_mutex.unlock();
    });
    client.connectToHost();

    QTimer t;
    QObject::connect(&t, &QTimer::timeout, [&client]{
        g_mutex.lock();
        if(g_imageFlow == ImageFlow::FillFinish)
        {
            client.responseScreenshot(g_image);
            g_imageFlow = ImageFlow::End;
        }
        g_mutex.unlock();
    });
    t.start(1);


    qInfo("main thread initial success");
    app.exec();
}

void updata_screen()
{
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);

    int x, y, w, h;
    x = vp[0];
    y = vp[1];
    w = vp[2];
    h = vp[3];

    int j;

    int fix_w = (((w * 24) + 31) & (~31)) / 8;

    unsigned char *bottomup_pixel = (unsigned char *)malloc(w*h * 3 * sizeof(unsigned char));
    //unsigned char *topdown_pixel = (unsigned char *)malloc(w*h * 3 * sizeof(unsigned char));


    //Byte alignment (that is, no alignment)
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(x, y, w, h, GL_RGB, GL_UNSIGNED_BYTE, bottomup_pixel);

    QImage img(w,h, QImage::Format_RGB888);
    for (j = 0; j < h; j++)
        memcpy(&img.bits()[j*fix_w], &bottomup_pixel[(h - j - 1)*w * 3], w * 3 * sizeof(unsigned char));

    delete[] bottomup_pixel;

    //img.save("D:\123.png");
    g_image = img;
    //g_label->setPixmap(QPixmap::fromImage(img));

    //g_mutex.lock();
    //g_image = img;
    //g_mutex.unlock();
}

static std::thread g_thread;

static BOOL(WINAPI *true_SwapBuffers)(HDC hdc) = SwapBuffers;
BOOL WINAPI My_SwapBuffers(HDC hdc)
{
    if(g_thread.joinable() == false)
    {
        g_thread = std::move(std::thread(thread_main));
    }

    g_mutex.lock();
    if(g_imageFlow == ImageFlow::Request)
    {
        updata_screen();
        g_imageFlow = ImageFlow::FillFinish;
    }
    g_mutex.unlock();

    return true_SwapBuffers(hdc);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (DetourIsHelperProcess()) {
        return TRUE;
    }

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DetourRestoreAfterWith();

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)true_SwapBuffers, My_SwapBuffers);
        DetourTransactionCommit();
    }
    break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)true_SwapBuffers, My_SwapBuffers);
        DetourTransactionCommit();
    }
    break;
    }
    return TRUE;
}
