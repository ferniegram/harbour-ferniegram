#include "lottieitem.h"

#include <QQmlFile>
#include <QSGSimpleTextureNode>
#include <QQuickWindow>
#include <QFile>

#define DEBUG_MODULE LottieItem
#include "debuglog.h"
#define LOG_(x) LOG(qPrintable(file ? file->fileName() : "") << x)

LottieItem::LottieItem() :
    QQuickItem(),
    file(nullptr),
    handler(nullptr),
    pendingFrameJump(-1),
    jumpedToFrame(false),
    autoLoad(true),
    error(false),
    paused(false),
    loop(false)
{
    setFlag(ItemHasContents);

    nextImageTimer.setSingleShot(true);
    connect(&nextImageTimer, &QTimer::timeout, this, &LottieItem::loadNextFrame);
}

LottieItem::~LottieItem() {
    delete handler;
}

QSize LottieItem::sourceSize() const {
    if (handler)
        return handler->option(QImageIOHandler::Size).toSize();
    return QSize();
}

QSize LottieItem::scaledSize() const {
    if (handler)
        return handler->option(QImageIOHandler::ScaledSize).toSize();
    return pendingOptions.value(QImageIOHandler::ScaledSize).toSize();
}

void LottieItem::setScaledSize(QSize size) {
    if (scaledSize() != size) {
        if (handler) {
            handler->setOption(QImageIOHandler::ScaledSize, size);
            updateSize();
        } else
            pendingOptions.insert(QImageIOHandler::ScaledSize, size);
        emit scaledSizeChanged();
    }
}

void LottieItem::updateSize() {
    QSize size = scaledSize();
    if (size.isEmpty())
        size = sourceSize();
    if (!size.isEmpty()) {
        setImplicitSize(size.width(), size.height());
        emit sourceSizeChanged();
    }
    LOG_("Implicit size set to" << implicitWidth() << implicitHeight());
}

QUrl LottieItem::source() const {
    if (file)
        return file->fileName();
    return QUrl();
}

void LottieItem::reset() {
    delete handler;
    handler = nullptr;
    if (file) {
        file->close();
        file->deleteLater();
        file = nullptr;
    }
}

void LottieItem::setSource(QUrl source) {
    const QString fileName = QQmlFile::urlToLocalFileOrQrc(source);
    if (this->file && this->file->fileName() == fileName)
        return;

    reset();

    if (fileName.isEmpty())
        return;

    this->file = new QFile(fileName, this);
    if (!file->isOpen() && !file->open(QFile::ReadOnly)) {
        setError();
        return;
    }

    handler = new TgsIOHandler(this->file, TgsIOHandler::NAME);
    for (QImageIOHandler::ImageOption option : pendingOptions.keys())
        handler->setOption(option, pendingOptions.value(option));
    pendingOptions.clear();
    updateSize();
    LOG_(sourceSize() << scaledSize());
    if (autoLoad)
        begin();
}

void LottieItem::setAutoLoad(bool value) {
    if (autoLoad != value) {
        autoLoad = value;
        emit autoLoadChanged();
    }
}

void LottieItem::begin() {
    if (pendingFrameJump >= 0) {
        setCurrentFrame(pendingFrameJump);
        pendingFrameJump = -1;
    } else
        loadNextFrame();
    setAutoLoad(true);
}

void LottieItem::setPaused(bool value) {
    if (paused != value) {
        paused = value;
        LOG_((paused ? "Pausing" : "Unpausing"));
        if (paused && !jumpedToFrame)
            nextImageTimer.stop();
        else
            loadNextFrame();
        emit pausedChanged();
    }
}

int LottieItem::currentFrame() const {
    if (handler)
        return handler->currentImageNumber();
    return 0;
}

void LottieItem::setCurrentFrame(int frame) {
    if (frame < 0)
        return;

    if (handler) {
        if (handler->jumpToImage(frame)) {
            jumpedToFrame = true;
            nextImageTimer.stop();
            loadNextFrame();
            LOG_("Jumped to frame" << frame);
        } else
            LOG_("Couldn't jump to frame" << frame);
    } else {
        LOG_("Pending frame jump");
        pendingFrameJump = frame;
    }
}

int LottieItem::frameCount() const {
    if (handler)
        return handler->imageCount();
    return 0;
}

void LottieItem::setLoop(bool value) {
    if (loop != value) {
        loop = value;
        emit loopChanged();
    }
}

void LottieItem::setError() {
    if (!error) {
        error = true;
        emit errorChanged();
    }
}

void LottieItem::loadNextFrame() {
    if (!handler) return;

    if (jumpedToFrame && paused) {
        if (!handler->currentRenderReady()) {
            // wait for the frame to be loaded, don't skip it
            nextImageTimer.start(handler->nextImageDelay());
            return;
        } else
            jumpedToFrame = false;
    }

    if (!handler->read(&currentImage)) {
        setError();
        return;
    }

    update();
    emit currentFrameChanged();

    if (!paused && (loop || handler->currentImageNumber() < (handler->imageCount() - 1)))
        nextImageTimer.start(handler->nextImageDelay());
}

QSGNode *LottieItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData*) {
    if (currentImage.isNull()) {
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
        //QPixmap pixmap = QPixmap::fromImage(currentImage);
        QSGTexture *texture = window->createTextureFromImage(currentImage);
        textureNode->setTexture(texture);
        textureNode->setRect(boundingRect());
    }

    return textureNode;
}
