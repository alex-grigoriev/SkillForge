#include <QtGui/QtGui>
#include <QApplication>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QFileDialog>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget playerWindow;
    QVBoxLayout vbox(&playerWindow);
    QHBoxLayout buttons;

    auto *videoWidget = new QVideoWidget(&playerWindow);
    vbox.addWidget(videoWidget);
    QSlider *songSlider = new QSlider(&playerWindow);
    songSlider->setOrientation(Qt::Horizontal);
    vbox.addWidget(songSlider);


    auto *openFileButton = new QPushButton("Open", &playerWindow);
    auto *playMediaButton = new QPushButton("Play", &playerWindow);
    auto *pauseMediaButton = new QPushButton("Pause", &playerWindow);

    buttons.addWidget(openFileButton);
    buttons.addWidget(playMediaButton);
    buttons.addWidget(pauseMediaButton);

    vbox.addLayout(&buttons);

    QString filePath;

    auto *player = new QMediaPlayer(&playerWindow);

    QAudioOutput* myMediaAudioOutput = new QAudioOutput;
    myMediaAudioOutput->setVolume(1.f);
    player->setAudioOutput(myMediaAudioOutput);

    player->setVideoOutput(videoWidget);
    bool isPlaying = false;

    QObject::connect(openFileButton, &QPushButton::clicked, [&filePath, &player, &isPlaying]()
     {
         filePath = QFileDialog::getOpenFileName(nullptr,
                                                 "Open media",
                                                 "C:/",
                                                 "video files (*.mp4, *.avi)");
         player->stop();
         isPlaying = false;
     });

    QObject::connect(playMediaButton, &QPushButton::clicked, [&isPlaying, songSlider, player, &filePath]()
     {
         if(!isPlaying)
         {
             player->setSource(QUrl::fromLocalFile(filePath));

             QObject::connect(player, &QMediaPlayer::durationChanged, [songSlider](qint64 duration)
              {
                  songSlider->setMinimum(0);
                  songSlider->setMaximum(duration);
              });

             QObject::connect(player, &QMediaPlayer::positionChanged, [songSlider](qint64 pos)
              {
                  songSlider->setValue(pos);
              });
             isPlaying = true;
         }
         player->play();
     });

    qint64 balance = 0,  buffer = 0;
    QObject::connect(songSlider, &QSlider::valueChanged, [player, &balance, &buffer](qint64 position)
    {
         balance = position - buffer;
         if(balance > 500 || balance < 0)
             player->setPosition(position);
         buffer = position;
    });

    QObject::connect(pauseMediaButton, &QPushButton::clicked, player, &QMediaPlayer::pause);

    playerWindow.show();

    return a.exec();
}


#include <main.moc>
