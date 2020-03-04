#ifndef DFONTINFODIALOG_H
#define DFONTINFODIALOG_H
#include "dfontbasedialog.h"

#include <QResizeEvent>

#include <DFrame>
#include <DLabel>
#include <QTextEdit>

DWIDGET_USE_NAMESPACE

struct DFontPreviewItemData;
class FontIconText;
class DFontInfoDialog : public DFontBaseDialog
{
    Q_OBJECT
public:
    explicit DFontInfoDialog(DFontPreviewItemData* fontInfo, QWidget* parent = nullptr);

    static constexpr int DEFAULT_WINDOW_W = 300;
    static constexpr int DEFAULT_WINDOW_H = 446;

protected:
    void initUI();
    void initConnections();
    void updateFontInfo();

    void resizeEvent(QResizeEvent* event) override;
signals:

public slots:

private:
    QWidget* m_mainFrame {nullptr};

    FontIconText *m_fontLogo {nullptr};
    DLabel* m_fontFileName {nullptr};

    DFrame* m_basicInfoFrame {nullptr};
    DLabel* m_fontSytleName {nullptr};
    DLabel* m_fontTypeName {nullptr};
    DLabel* m_fontVersion {nullptr};
    DLabel* m_fontDescription {nullptr};

    DFontPreviewItemData* m_fontInfo;
};

#endif  // DFONTINFODIALOG_H
