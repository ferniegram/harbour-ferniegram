#ifndef GSTAUDIORECORDER_H
#define GSTAUDIORECORDER_H

#include <QObject>
#include <QThread>

typedef struct _GstElement GstElement;
typedef struct _GstMessage GstMessage;

class GstAudioRecorder : public QThread {
    Q_OBJECT

public:
    enum GstRecordingState {
        Ready,
        Paused,
        Recording,
        Starting,
        Stopping,
        Unavailable
    };
    Q_ENUM(GstRecordingState);

    explicit GstAudioRecorder(int argc, char **argv, bool *error = nullptr, QObject *parent = nullptr);
    ~GstAudioRecorder();

    void record(const QString &location);
    void pause();
    void stop();

    inline GstRecordingState getState() { return state; }
    inline QString getLocation() { return location; }
    inline qlonglong getDuration() { return duration; }
    void setVolume(qreal newVolume);

signals:
    void durationChanged();
    void stateChanged();
    void locationChanged();

private:
    void run() Q_DECL_OVERRIDE;
    void handleMessage(GstMessage *msg);

private:
    GstElement *pipeline;

    bool needTerminate;
    GstRecordingState state;
    qlonglong duration; // duration means duration recorded so far
    QString location;
};

#endif // GSTAUDIORECORDER_H
