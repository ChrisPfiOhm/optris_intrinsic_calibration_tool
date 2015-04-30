#include "MainWindow.h"

#include <QApplication>
#include <QDebug>

#include <signal.h>



/**
 * Function to cleanly kill qt application by pressing ctrl + c
 * @param signum
 */
void sig_handler(int signum) {
    QCoreApplication::quit();
}



int main(int argc, char** argv)
{
    if (argc != 2)
    {
        qDebug() << "usage " << argv[0] << " <config file>";
        return 1;
    }

    // connect signal to sign_handler function for clean exit
    signal(SIGINT, sig_handler);

    QApplication app(argc, argv);

    MainWindow mw(argv[1]);
    mw.show();

    return app.exec();
}
