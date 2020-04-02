#ifndef SETTINGS_H
#define SETTINGS_H

#include <DSettingsDialog>
#include <DKeySequenceEdit>

#include <qsettingbackend.h>

DCORE_USE_NAMESPACE
DWIDGET_USE_NAMESPACE

class DSettingsWidgetFactoryPrivate;
class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings *instance();

    void initConnection();

    qreal opacity() const;
    int cursorShape() const;
    bool cursorBlink() const;
    bool backgroundBlur() const;
    QString colorScheme() const;
    QString encoding() const;
    QString fontName();
    int fontSize();
    bool PressingScroll();
    bool OutputtingScroll();

    // 设置主题
    void setColorScheme(const QString &name);
    // 设置编码格式
    void setEncoding(const QString &name);
    // 通用设置
    void setKeyValue(const QString &name, const QString &value);

    DSettings *settings;
    /******** Modify by n014361 wangpeili 2020-01-04: 获取当前配置粘贴是否为选择内容 *************×****/
    bool IsPasteSelection();

public:
    QString getKeyshortcutFromKeymap(const QString &keyCategory, const QString &keyName);

    static QPair<QWidget *, QWidget *> createFontComBoBoxHandle(QObject *obj);
    // 新增自定义slider控件
    static QPair<QWidget *, QWidget *> createCustomSliderHandle(QObject *obj);
    // 新增自定义spinbutton控件
    static QPair<QWidget *, QWidget *> createSpinButtonHandle(QObject *obj);
    // 新增自定义ShortcutEdit控件处理
    static QPair<QWidget *, QWidget *> createShortcutEditOptionHandle(QObject *opt);
    /******** Modify by n014361 wangpeili 2020-01-04:              ****************/

signals:
    // void settingValueChanged(const QString &key, const QVariant &value);
    void windowSettingChanged(const QString &key);
    void terminalSettingChanged(const QString &key);
    void shortcutSettingChanged(const QString &key);

    void opacityChanged(qreal opacity);
    void cursorShapeChanged(int shape);
    void cursorBlinkChanged(bool blink);
    void backgroundBlurChanged(bool enabled);
    void pressingScrollChanged(bool enabled);
    void OutputScrollChanged(bool enabled);

    /******** Modify by n014361 wangpeili 2020-01-06:字体，字体大小修改功能 ******×****/
    void fontSizeChanged(int fontSize);
    void fontChanged(QString fontName);
    /********************* Modify by n014361 wangpeili End ************************/

private:
    Settings();
    void loadDefaultsWhenReinstall();

    static Settings *m_settings_instance;

    Dtk::Core::QSettingBackend *m_backend;
    QString m_configPath;
};
class KeySequenceEdit : public DKeySequenceEdit
{
public:
    KeySequenceEdit(DTK_CORE_NAMESPACE::DSettingsOption *opt, QWidget *parent = nullptr): DKeySequenceEdit(parent)
    {
        m_poption = opt;
    }
    DTK_CORE_NAMESPACE::DSettingsOption *option()
    {
        return m_poption;
    }
private:
    DTK_CORE_NAMESPACE::DSettingsOption *m_poption = nullptr;
};
QPair<QWidget *, QWidget *> createShortcutEditOptionHandle(DSettingsWidgetFactoryPrivate *p, QObject *opt);
#define SHORTCUT_VALUE "shortcut_null"
#endif  // SETTINGS_H