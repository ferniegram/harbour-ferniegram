#include "movieitem.h"

#include <QQmlFile>
#include <QSGSimpleTextureNode>
#include <QQuickWindow>

#define DEBUG_MODULE MovieItem
#include "debuglog.h"
#define LOG_(x) LOG(qPrintable(movie->fileName()) << x)

MovieItem::MovieItem()
    : QQuickItem(),
      movie(new QMovie(this)),
      paused(false),
      frame(-1),
      pauseScheduled(false),
      loop(true)
{
    setFlag(ItemHasContents);

    connect(movie, &QMovie::frameChanged, this, &MovieItem::handleFrameChanged);
    connect(movie, &QMovie::started, this, &MovieItem::updateSize);
    connect(movie, &QMovie::started, this, &MovieItem::frameChanged);
    connect(movie, &QMovie::stateChanged, this, &MovieItem::handleStateChanged);
}

QUrl MovieItem::source() const {
    return movie->fileName();
}

void MovieItem::setSource(QUrl source) {
    const QString fileName = QQmlFile::urlToLocalFileOrQrc(source);

    if (movie->fileName() != fileName) {
        movie->setFileName(fileName);
        emit sourceChanged();

        if (movie->isValid()) {
            movie->start();
            movie->setPaused(false);

            if (this->frame >= 0) {
                LOG_("Jumping to" << frame);
                movie->jumpToFrame(this->frame);
            }

            if (paused) {
                LOG_("Pausing newly started movie");
                if (isNull())
                    this->pauseScheduled = true;
                else
                    movie->setPaused(paused);
            }

            emit frameCountChanged();
            updateSize();
            update();
            LOG_(sourceSize() << movie->state() << movie->currentFrameNumber() << paused);
        }
    }
}

void MovieItem::setPaused(bool paused) {
    if (this->paused != paused) {
        LOG_((paused ? "Pausing" : "Unpausing") << "previous state" << movie->state());
        this->paused = paused;
        emit pausedChanged();

        movie->setPaused(paused);
        LOG_(movie->state());
    }
}

QSize MovieItem::sourceSize() const {
    return movie->currentImage().size();
}

QSize MovieItem::scaledSize() const {
    return movie->scaledSize();
}

void MovieItem::setScaledSize(QSize size) {
    if (movie->scaledSize() != size) {
        movie->setScaledSize(size);
        updateSize();
        LOG_("New scaled size" << size << sourceSize());
    }
}

int MovieItem::currentFrame() const {
    return movie->currentFrameNumber();
}

void MovieItem::setCurrentFrame(int frame) {
    this->frame = frame;
    if (frame >= 0)
        LOG_("Jumped" << movie->jumpToFrame(frame));
}

int MovieItem::frameCount() const {
    return movie->frameCount();
}

bool MovieItem::cache() const {
    return movie->cacheMode() == QMovie::CacheAll;
}

void MovieItem::setCache(bool cache) {
    QMovie::CacheMode mode = cache ? QMovie::CacheAll : QMovie::CacheNone;
    if (movie->cacheMode() != mode) {
        movie->setCacheMode(mode);
        emit cacheChanged();
    }
}

void MovieItem::setLoop(bool loop) {
    if (this->loop != loop) {
        this->loop = loop;
        LOG_("Looping" << (loop ? "enabled" : "disabled"));
    }
}

void MovieItem::handleStateChanged(QMovie::MovieState state) {
    LOG_("State:" << state);
}

void MovieItem::handleFrameChanged(int frameNumber) {
    LOG_("FRAME" << frameNumber << isNull());
    if (!loop && frameNumber >= (movie->frameCount() - 1)) {
        LOG_("Finished the loop, pausing");
        setPaused(true);
    }
    emit this->frameChanged();

    if (!isNull()) {
        this->update();

        if (this->pauseScheduled) {
            this->pauseScheduled = false;
            LOG("Scheduled pause triggered");
            movie->setPaused(paused);
            if (!this->paused) {
                this->paused = true;
                emit pausedChanged();
            }
        }
    }
}

void MovieItem::updateSize() {
    const QSize size = sourceSize();
    if (size.isValid()) {
        setImplicitSize(size.width(), size.height());
        emit sourceSizeChanged();
    }
}

QSGNode *MovieItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData*) {
    QImage frame = movie->currentImage();
    LOG_("PAINT" << movie->currentFrameNumber());

    if (frame.isNull()) {
        LOG_("IS NULL");
        delete oldNode;
        return nullptr;
    }

    QSGSimpleTextureNode *textureNode = static_cast<QSGSimpleTextureNode *>(oldNode);
    if (!textureNode) {
        textureNode = new QSGSimpleTextureNode();
        textureNode->setOwnsTexture(true);
    }

    QQuickWindow *window = this->window();
    if (window) {
        QSGTexture *texture = window->createTextureFromImage(frame);
        textureNode->setTexture(texture);
        textureNode->setRect(boundingRect());
    }

    return textureNode;
}
