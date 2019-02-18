#pragma once

#include <QAbstractItemModel>

#include <core/logger/AbstractLogTarget.h>

#include <base/view_manager/QuartzView.h>



namespace Quartz {


struct LogData;

class LogModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit LogModel(QObject *parent = nullptr);

    ~LogModel();

    QModelIndex index(int row,
                       int column,
                       const QModelIndex &parent) const override;

    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    bool hasChildren(const QModelIndex &parent) const override;

    QVariant headerData(int section,
                         Qt::Orientation orientation,
                         int role) const override;

public slots:
    void add(std::shared_ptr<Quartz::LogData> msg);

    void clear();

private:
    QVector<std::shared_ptr<LogData>> m_msgs;

};


class LogView : public QuartzView
              , public Logger::AbstractLogTarget
{
    Q_OBJECT
public:
    explicit LogView(QWidget *parent);

    ~LogView() override;

    void flush() override;

    void write(const Logger::LogMessage *message) override;

    static const QString LOG_TARGET_ID;

    static const QString VIEW_ID;

    static const QString VIEW_DISPLAY_NAME;

    static const QString VIEW_CATEGORY;

public slots:
    void clear();

signals:
    void sigLogMessage(std::shared_ptr<Quartz::LogData> message);

protected:
    void write(QString &&logString) override;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}


