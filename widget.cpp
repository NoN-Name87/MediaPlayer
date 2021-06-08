#include "widget.h"
#include "ui_widget.h"
#include "appstyle.h"
AudioPlayer::AudioPlayer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    itmodel = std::make_unique<QStandardItemModel>(this);//correct for C++14 and later
    ui->tableView->setModel(itmodel.get());
    itmodel->setHorizontalHeaderLabels(QStringList() << tr("Track:")
                                       << tr("Path"));

    //QTableView config
    ui->tableView->hideColumn(1);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setStyleSheet(AppStyle::getTableStyle());

    //configure the mediaplayer
    player = std::make_unique<QMediaPlayer>();
    playlist = std::make_unique<QMediaPlaylist>(player.get());
    player->setPlaylist(playlist.get());
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setVolume(20);

    //downloading file path
    load_saves();

    //
    ui->horizontalSlider->setRange(0, 100);
    ui->horizontalSlider->setValue(20);
    //Set button style
    ui->exit->setStyleSheet(AppStyle::getCloseBtnStyle());

    //
    start_timer();

    //Media tool buttons
    connect(ui->start_btn, &QPushButton::clicked, player.get(), &QMediaPlayer::play);
    connect(ui->start_btn, &QPushButton::clicked, this, &AudioPlayer::setPos);
    connect(ui->pause_btn, &QPushButton::clicked, player.get(), &QMediaPlayer::pause);
    connect(ui->pause_btn, &QPushButton::clicked, this, &AudioPlayer::stopTrack);
    connect(ui->stop_btn, &QPushButton::clicked, player.get(), &QMediaPlayer::stop);
    connect(ui->add_btn, &QPushButton::clicked, this, &AudioPlayer::add_track);
    connect(player.get(), &QMediaPlayer::durationChanged, this, &AudioPlayer::start_timer);
    connect(ui->tableView, &QTableView::clicked, [this](const QModelIndex &index){
        playlist->setCurrentIndex(index.row());
    });// lyambda-function (C++11)

    //Slider configuration
    connect(ui->horizontalSlider, &QSlider::valueChanged, player.get(), &QMediaPlayer::setVolume);
    connect(ui->time_track, &QSlider::sliderMoved, player.get(), &QMediaPlayer::setPosition);
    connect(player.get(), &QMediaPlayer::positionChanged, ui->time_track, &QSlider::setSliderPosition);
    connect(&t_track, &QTimer::timeout, this, &AudioPlayer::setPos);
    //exit and roll up buttons
    connect(ui->roll, &QToolButton::clicked, this, &QWidget::showMinimized);
    connect(ui->exit, &QToolButton::clicked, this, &QApplication::quit);
}

AudioPlayer::~AudioPlayer() = default;

void AudioPlayer::load_saves() {
    QFileInfo check;
    QString path_name = qApp->applicationDirPath();
    QString rewrite;
    qDebug() << path_name;
    path_name.append("/musicsaves.txt");
    QFile file(path_name);
    QString path;
    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);

    while(!in.atEnd()){
         QList<QStandardItem *> items;
         check = in.readLine();
         if(!check.exists()){ continue; }//file-path checker
         path = check.filePath();
         playlist->addMedia(QUrl(path));
         items.append(new QStandardItem(QDir(path).dirName()));
         items.append(new QStandardItem(path));
         itmodel->appendRow(items);
         rewrite.append(path + "\n");
         path.clear();
    }

    file.resize(0);
    in << rewrite;
    rewrite.clear();
    file.close();
}

void AudioPlayer::add_track() noexcept {
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open files"),
                                                  QString(),
                                                  tr("Audio Files (*.mp3 *.wav)"));

    QString path_name = qApp->applicationDirPath();
    qDebug() << path_name;
    path_name.append("/musicsaves.txt");
    QFile file(path_name);
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    foreach(QString path, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(path).dirName()));
        items.append(new QStandardItem(path));
        itmodel->appendRow(items);
        playlist->addMedia(QUrl(path));
        out << path << "\n";
        path.clear();
    }
    file.close();
}

void AudioPlayer::start_timer() noexcept {
    float duration = player->duration() / 1000.0f;
    ui->time_track->setRange(0, player->duration());
    ui->time_track->setValue(0);
    ui->end_time->setText(QDateTime::fromTime_t(duration).toString("mm:ss"));
}

void AudioPlayer::setPos() noexcept {
    t_track.start(0);
    ui->begin_time->setText(QDateTime::fromTime_t(player->position() / 1000.0f).toString("mm:ss"));
}

void AudioPlayer::stopTrack() noexcept {
    t_track.stop();
}
