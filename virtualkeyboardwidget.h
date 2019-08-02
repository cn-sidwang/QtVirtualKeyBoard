#ifndef VIRTUALKEYBOARDWIDGET_H
#define VIRTUALKEYBOARDWIDGET_H

#include <QVector>
#include <QWidget>
#include <QPaintEvent>

struct SKey
{
    qreal       x;
    qreal       y;
    qreal       width;
    qreal       height;
    qreal       weight;
    int         row;
    int         col;
    bool        isKey;
    bool        showShiftKey;
    bool        isFocusIn;
    bool        isPressed;
    bool        isTextKey;
    bool        isSupportFn;
    bool        isSupportShift;
    bool        isSupportCaps;
    Qt::Key     norKey;
    Qt::Key     shiftKey;
    Qt::Key     fnKey;
    QString     strNorKey;
    QString     strShiftKey;
    QString     strFnKey;

    void Init()
    {
        this->row             = 0;                        this->col             = 0;
        this->x               = 0;                        this->y               = 0;
        this->width           = 0;                        this->height          = 0;
        this->isFocusIn       = false;                    this->isPressed       = false;
        this->isSupportFn     = false;                    this->weight          = 1;
        this->showShiftKey    = false;                    this->isKey           = true;
        this->norKey          = Qt::Key_unknown;          this->shiftKey        = Qt::Key_unknown;
        this->fnKey           = Qt::Key_unknown;          this->strNorKey       = "";
        this->strShiftKey     = "";                       this->strFnKey        = "";
        this->isSupportShift  = false;                    this->isSupportCaps   = false;
        this->isTextKey       = false;
    }

    SKey( const SKey& key )
    {
        this->row             = key.row;                  this->col           = key.col;
        this->x               = key.x;                    this->y             = key.y;
        this->width           = key.width;                this->height        = key.height;
        this->isFocusIn       = key.isFocusIn;            this->isPressed     = key.isPressed;
        this->isSupportFn     = key.isSupportFn;          this->weight        = key.weight;
        this->showShiftKey    = key.showShiftKey;         this->isKey         = key.isKey;
        this->norKey          = key.norKey;               this->shiftKey      = key.shiftKey;
        this->fnKey           = key.fnKey;                this->strNorKey     = key.strNorKey;
        this->strShiftKey     = key.strShiftKey;          this->strFnKey      = key.strFnKey;
        this->isSupportShift  = key.isSupportShift;       this->isSupportCaps = key.isSupportCaps;
        this->isTextKey       = key.isTextKey;
    }

    //  对于非标准按键构造函数，例如，隐藏对话框按钮等。
    SKey( qreal weight, int row, int col, const QString& strNorKey, bool isTextKey=false )
    {
        Init();
        this->row           = row;
        this->col           = col;
        this->isKey         = false;
        this->weight        = weight;
        this->strNorKey     = strNorKey;
        this->isTextKey     = isTextKey;
    }

    //  对于仅有单功能按键用，例如 字母键。
    SKey( qreal weight, int row, int col,  Qt::Key nk, const QString& strNorKey, bool isSupportCaps=false, bool isTextKey=false )
    {
        Init();
        this->row           = row;
        this->col           = col;
        this->weight        = weight;
        this->norKey        = nk;
        this->strNorKey     = strNorKey;
        this->isSupportCaps = isSupportCaps;
        this->isTextKey     = isTextKey;
    }

    //  对于有两种功能的按键构造用， 例如，常规符号键，按下shift即可启用上档键。切换符号。
    SKey( qreal weight, int row, int col, Qt::Key nk, Qt::Key sk, const QString& strNK, const QString& strSK, bool isTextKey=false )
    {
        Init();
        this->row             = row;
        this->col             = col;
        this->weight          = weight;
        this->norKey          = nk;
        this->shiftKey        = sk;
        this->showShiftKey    = true;
        this->strNorKey       = strNK;
        this->strShiftKey     = strSK;
        this->isSupportShift  = true;
        this->isTextKey       = isTextKey;
    }

    //  对于三功能按键构造用， 例如 数字键，除了作为数字输入，还能通过shift输入对应的符号，如果按下FN键，则变成 F1～F12键
    SKey( qreal weight, int row, int col, Qt::Key nk, Qt::Key sk, Qt::Key fk,
                                    const QString& strNK, const QString& strSK, const QString& strFnKey, bool isTextKey=false )
    {
        Init();
        this->row             = row;
        this->col             = col;
        this->weight          = weight;
        this->showShiftKey    = true;
        this->isSupportFn     = true;
        this->norKey          = nk;
        this->shiftKey        = sk;
        this->fnKey           = fk;
        this->strNorKey       = strNK;
        this->strShiftKey     = strSK;
        this->strFnKey        = strFnKey;
        this->isSupportShift  = true;
        this->isTextKey       = isTextKey;
    }
};

class CVirtualKeyBoardWidget : public QWidget
{
    Q_OBJECT

private:
    explicit CVirtualKeyBoardWidget(QWidget *parent = nullptr);

public:
    static CVirtualKeyBoardWidget& GetInstance()
    {
        static CVirtualKeyBoardWidget vkb;
        return vkb;
    }
    ~CVirtualKeyBoardWidget();

public:
    void  ShowVirtualKeyBoard();            //  显示虚拟软件盘界面
    void  UseMouseFocus( bool IsUsed );     //  鼠标移动时，是否高亮显示鼠标处的按钮, 默认显示
    void  Hide();                           //  隐藏虚拟软件盘界面

private:
    void  CreateEvent( SKey* key, QEvent::Type type );
    void  InitKeys();
    void  InitKeysSize();
    SKey *FindKeys( int x, int y );

protected:
    virtual void paintEvent( QPaintEvent* event );
    virtual void resizeEvent( QResizeEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );

private:
    SKey* mFocusKey;
    int   mIMarginLeft;
    int   mIMarginTop;
    int   mIOldMouseX;
    int   mIOldMouseY;
    bool  mBMousePressed;
    bool  mBIsCapsPress;
    bool  mBUseMouseFocus;
    bool  mBIsFnKeyPressed;
    bool  mBIsAltKeyPressed;
    bool  mBIsCtrlKeyPressed;
    bool  mBIsShiftKeyPressed;
    QVector<SKey*>   mVecKeys;

};

#endif // VIRTUALKEYBOARDWIDGET_H
