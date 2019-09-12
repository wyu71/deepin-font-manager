#include "dsplitlistwidget.h"

#include <QPainter>
#include <QMouseEvent>

#include <DApplication>
#include <DLog>

#define FTM_IS_USE_ROUND_CORNER true
#define FTM_SPLIT_TOP_SPACE_TAG "_space_"
#define FTM_SPLIT_TOP_SPLIT_TAG "_split_"
#define FTM_SPLIT_LINE_INDEX    6

DNoFocusDelegate::DNoFocusDelegate(QAbstractItemView *parent)
    :DStyledItemDelegate(parent)
{
}

//用于去除选中项的边框
void DNoFocusDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (index.isValid()) {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);

        QVariant varDisplay = index.data(Qt::DisplayRole);

        QString strTitle = varDisplay.value<QString>();

        QStyleOptionViewItem viewOption(option);  //用来在视图中画一个item

        DPalette::ColorGroup cg = option.state & QStyle::State_Enabled
                                  ? DPalette::Normal : DPalette::Disabled;
        if (cg == DPalette::Normal && !(option.state & QStyle::State_Active)) {
            cg = DPalette::Inactive;
        }

        QRect rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width());
        rect.setHeight(option.rect.height());

        if (FTM_IS_USE_ROUND_CORNER) {

            QRect paintRect = QRect(rect.left()+10, rect.top(), rect.width()-20, rect.height());

            QPainterPath path;
            const int radius = 8;

            path.moveTo(paintRect.bottomRight() - QPoint(0, radius));
            path.lineTo(paintRect.topRight() + QPoint(0, radius));
            path.arcTo(QRect(QPoint(paintRect.topRight() - QPoint(radius * 2, 0)), QSize(radius * 2, radius * 2)), 0, 90);
            path.lineTo(paintRect.topLeft() + QPoint(radius, 0));
            path.arcTo(QRect(QPoint(paintRect.topLeft()), QSize(radius * 2, radius * 2)), 90, 90);
            path.lineTo(paintRect.bottomLeft() - QPoint(0, radius));
            path.arcTo(QRect(QPoint(paintRect.bottomLeft() - QPoint(0, radius * 2)), QSize(radius * 2, radius * 2)), 180, 90);
            path.lineTo(paintRect.bottomLeft() + QPoint(radius, 0));
            path.arcTo(QRect(QPoint(paintRect.bottomRight() - QPoint(radius * 2, radius * 2)), QSize(radius * 2, radius * 2)), 270, 90);

            if (option.state & QStyle::State_Selected) {
                QColor fillColor = option.palette.color(cg, DPalette::Highlight);
                painter->fillPath(path, fillColor);
            }

        } else {
            QRect paintRect = QRect(rect.left()+10, rect.top(), rect.width()-20, rect.height());

            QPainterPath path;
            path.moveTo(paintRect.topRight());
            path.lineTo(paintRect.topLeft());
            path.quadTo(paintRect.topLeft(), paintRect.topLeft());
            path.lineTo(paintRect.bottomLeft());
            path.quadTo(paintRect.bottomLeft(), paintRect.bottomLeft());
            path.lineTo(paintRect.bottomRight());
            path.quadTo(paintRect.bottomRight(), paintRect.bottomRight());
            path.lineTo(paintRect.topRight());
            path.quadTo(paintRect.topRight(), paintRect.topRight());

            if (option.state & QStyle::State_Selected) {
                QColor fillColor = option.palette.color(cg, DPalette::Highlight);
                painter->fillPath(path, fillColor);
            }
        }

        if (strTitle.startsWith(FTM_SPLIT_TOP_SPACE_TAG)) {
            //用于ListView顶部空白
        }
        else if (strTitle.startsWith(FTM_SPLIT_TOP_SPLIT_TAG)) {

            //绘制分割线
            QColor penColor = option.palette.color(cg, DPalette::Dark);
            QPen pen = QPen(penColor);
            pen.setWidth(2);
            painter->setPen(pen);
            painter->drawLine(10, rect.top()+rect.height()/2, rect.width()-20, rect.top()+rect.height()/2);
        }
        else {

            //绘制标题
            QRect fontNameRect = QRect(rect.left()+20, rect.top(), rect.width()-20, rect.height());

            QFont nameFont;
            nameFont.setPixelSize(14);
            painter->setFont(nameFont);

            if (option.state & QStyle::State_Selected) {
                painter->setPen(QPen(option.palette.color(DPalette::Text)));
                painter->drawText(fontNameRect, Qt::AlignLeft | Qt::AlignVCenter, strTitle);
            }
            else {
                painter->setPen(QPen(option.palette.color(DPalette::Text)));
                painter->drawText(fontNameRect, Qt::AlignLeft | Qt::AlignVCenter, strTitle);
            }
        }

        painter->restore();
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize DNoFocusDelegate::sizeHint(const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    Q_UNUSED(index)

    int rowIndex = index.row();
    if (0 == rowIndex) {
        return QSize(option.rect.width(), 10);
    }
    else if (FTM_SPLIT_LINE_INDEX == rowIndex) {
        return QSize(option.rect.width(), 25);
    }
    else {
        return QSize(option.rect.width(), 38);
    }
}

DSplitListWidget::DSplitListWidget(QWidget *parent)
    : DListView(parent)
{
    //去除选中项的边框
    this->setItemDelegate(new DNoFocusDelegate(this));
    this->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
    this->setAutoScroll(false);

    initListData();
}

DSplitListWidget::~DSplitListWidget() {}

void DSplitListWidget::initListData()
{
    m_titleStringList << DApplication::translate("Category", "All Fonts")
                      << DApplication::translate("Category", "System Fonts")
                      << DApplication::translate("Category", "User Fonts")
                      << DApplication::translate("Category", "My Favorite")
                      << DApplication::translate("Category", "Active Fonts")
                      << DApplication::translate("Category", "Chinese")
                      << DApplication::translate("Category", "Monospace");

    for(int i=0; i<m_titleStringList.size(); i++)
    {
        QString titleString = m_titleStringList.at(i);
        m_titleStringIndexMap.insert(titleString, i);
    }

    m_categoryItemModell = new QStandardItemModel;

    int iTitleIndex = 0;
    for (int i = 0; i < m_titleStringList.size()+2; i++) {
        QStandardItem *item = new QStandardItem;
        if (0 == i) {
            item->setFlags(item->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEnabled);
            item->setData(QVariant::fromValue(QString(FTM_SPLIT_TOP_SPACE_TAG)), Qt::DisplayRole);
        }
        else if (FTM_SPLIT_LINE_INDEX == i) {
            item->setFlags(item->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEnabled);
            item->setData(QVariant::fromValue(QString(FTM_SPLIT_TOP_SPLIT_TAG)), Qt::DisplayRole);
        }
        else {
            QString titleString = m_titleStringList.at(iTitleIndex++);
            item->setData(QVariant::fromValue(titleString), Qt::DisplayRole);
        }

        m_categoryItemModell->appendRow(item);
    }

    this->setModel(m_categoryItemModell);

    //默认选中列表中的第一个
    QModelIndex index = m_categoryItemModell->index(0, 0);
    selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
}

void DSplitListWidget::mouseReleaseEvent(QMouseEvent *event)
{
    DListView::mouseReleaseEvent(event);

    QPoint selectionPoint = event->pos();

    QModelIndex modelIndex = indexAt(selectionPoint);

    if (modelIndex.row() <=0 || FTM_SPLIT_LINE_INDEX == modelIndex.row()){
        return;
    }

    QStandardItem *item = m_categoryItemModell->item(modelIndex.row());
    QVariant varUserData = item->data(Qt::DisplayRole).value<QVariant>();
    qDebug() << "varUserData" << varUserData << endl;
    int realIndex = m_titleStringIndexMap.value(varUserData.toString());

    emit onListWidgetItemClicked(realIndex);
}