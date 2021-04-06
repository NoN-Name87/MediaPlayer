#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStandardItemModel>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTime>
#include <QTimer>
#include <QFileInfo>
#include <memory>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void load_saves();
private slots:
    void add_track() noexcept;
    void start_timer() noexcept;
    void setPos() noexcept;
    void stopTrack() noexcept;
private:
    std::unique_ptr<Ui::Widget>         ui;//smart pointers for correct deleting
    std::unique_ptr<QMediaPlayer>       player;
    std::unique_ptr<QMediaPlaylist>     playlist;
    std::unique_ptr<QStandardItemModel> itmodel;
    QTimer                              t_track;
};
#endif // WIDGET_H
