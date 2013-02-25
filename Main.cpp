#include "view/MainWindow.hpp"

using namespace std;

#include "io/Read3DS.hpp"
#include "rendering/TexturedMesh.hpp"
#include "io/SoundOutput.hpp"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QWidget>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QPixmap pixmap("res/models/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("Wait...");
    qApp->processEvents();//This is used to accept a click on the screen so that user can cancel the screen
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

    MainWindow mainWindow;
    mainWindow.show();

    SoundOutput sound;
    sound.playMusic();
    mainWindow.startLogic();

    splash.finish(&mainWindow);
    return app.exec();
}
