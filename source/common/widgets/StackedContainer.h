#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzCommon.h"

class QStackedWidget;


namespace Quartz {

class QzScroller;
class IdButton;

enum class AutoSelectionPolicy {
    SelectFirstAdded,
    SelectLastAdded,
    DoNotSelectAny,
};

class QUARTZ_COMMON_API AbstractContainer : public QWidget
{
    Q_OBJECT
public:
    enum class SelectorPosition
    {
        Before,
        After
    };

    explicit AbstractContainer(int selectorDimention,
                               int buttonDimention,
                               SelectorPosition selectorPosition,
                               Qt::Orientation orientation,
                               QWidget *parent = nullptr);

    ~AbstractContainer();

public:
    QWidget * widget(const QString &id) const;

    QWidget * selectedWidget() const;

    QString currentId() const;

    QList<QString> allIds() const;

    int numWidgets() const;

    bool isEmpty();

    QStackedWidget * stackedWidget() const;

    QzScroller * selector() const;

    SelectorPosition selectorPosition() const;

    Qt::Orientation containerOrientation() const;

    Qt::Orientation buttonOrientation() const;

    int buttonWidth() const;

    int buttonHeight() const;

    AutoSelectionPolicy autoSelectionPolicy() const;

    virtual QString containerType() const = 0;

public Q_SLOTS:
    void addWidget(const QString &id,
                    const QString &displayName,
                    const QIcon &icon,
                    const QIcon &activeIcon,
                    QWidget *widget);

    void addWidget(const QString &id,
                    const QString &displayName,
                    QWidget *widget);

    void removeWidget(const QString &id);

    void removeWidget(QWidget *widget);

    void select(const QString &id);

    void hideAll();

    void setAutoSelectionPolicy(AutoSelectionPolicy policy);

Q_SIGNALS:
    void sigSelected(const QString &id, QWidget *widget);

    void sigAdded(const QString &id, QWidget *widget);

    void sigRemoved(const QString &id);


private Q_SLOTS:
    void updateIndeces();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};


class QUARTZ_COMMON_API StackedContainer : public AbstractContainer
{
    Q_OBJECT

public:
    explicit StackedContainer(int selectorDimention,
                               int buttonDimention,
                               SelectorPosition selectorPosition,
                               Qt::Orientation orientation,
                               QWidget *parent = nullptr);

    ~StackedContainer();

    QString containerType() const override;
};


}

