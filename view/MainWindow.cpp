#include "MainWindow.hpp"

using std::cout;
using std::endl;

MainWindow::MainWindow(QMainWindow *parent)
{
    // Set window title an size
    setWindowTitle("3D-Viewer");
    resize(800, 600);

    // Create a new render frame and set as central widget.
    // If we don't want to use a full screen widget, we would
    // need to setup a proper parent (i.e. Frame object) here.
    m_renderFrame = new RenderFrame();

    setCentralWidget(m_renderFrame);

    m_logic = new Logic(m_renderFrame);
    
    // Create a file menu and add action. For larger projects
    // it would we more comfortable to use the QTDesigner tool
    // to create the GUI code for us
    m_fileMenu = menuBar()->addMenu("File");
    QAction* quitAction = m_fileMenu->addAction("Quit");
    
    // Connect the activation signals of the created actions
    // with the proper slots.
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::startLogic()
{
    m_logic->start();
}

MainWindow::~MainWindow()
{
    // Free resources (just the render frame).
    delete m_renderFrame;
    delete m_fileMenu;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_logic->stop();
    delete m_logic;

    close();
}
