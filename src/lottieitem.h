#ifndef LOTTIEITEM_H
#define LOTTIEITEM_H

#include <QQuickItem>
#include <QTimer>
#include "tgsplugin.h"

class LottieItem : public QQuickItem {
    // No network support here (can be added later if needed)
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool autoLoad MEMBER autoLoad WRITE setAutoLoad NOTIFY autoLoadChanged)
    Q_PROPERTY(bool error MEMBER error NOTIFY errorChanged)
    Q_PROPERTY(bool paused MEMBER paused WRITE setPaused NOTIFY pausedChanged)
    Q_PROPERTY(int currentFrame READ currentFrame WRITE setCurrentFrame NOTIFY currentFrameChanged)
    Q_PROPERTY(QSize sourceSize READ sourceSize NOTIFY sourceSizeChanged)
    Q_PROPERTY(QSize scaledSize READ scaledSize WRITE setScaledSize NOTIFY scaledSizeChanged)
    Q_PROPERTY(int frameCount READ frameCount NOTIFY frameCountChanged)
    Q_PROPERTY(bool loop MEMBER loop WRITE setLoop NOTIFY loopChanged)

public:
    LottieItem();
    ~LottieItem();

    QUrl source() const;
    void setSource(QUrl source);
    void setAutoLoad(bool value);
    Q_INVOKABLE void begin();

    void setPaused(bool value);

    int currentFrame() const;
    void setCurrentFrame(int frame);

    QSize sourceSize() const;
    QSize scaledSize() const;
    void setScaledSize(QSize size);

    int frameCount() const;

    void setLoop(bool value);

signals:
    void sourceChanged();
    void autoLoadChanged();
    void errorChanged();
    void pausedChanged();
    void currentFrameChanged();
    void sourceSizeChanged();
    void scaledSizeChanged();
    void frameCountChanged();
    void loopChanged();

protected:
    virtual QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData*) override;

private:
    void updateSize();
    void setError();
    void reset();
    void loadNextFrame();

private:
    QFile *file;
    TgsIOHandler *handler;
    QImage currentImage;
    QTimer nextImageTimer;
    QMap<QImageIOHandler::ImageOption, QVariant> pendingOptions;
    int pendingFrameJump;
    bool jumpedToFrame;
    bool autoLoad;
    bool error;
    bool paused;
    bool loop;
};

#endif // LOTTIEITEM_H
