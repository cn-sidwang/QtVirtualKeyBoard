#include <QPainter>
#include <QScreen>
#include <QGuiApplication>
#include <QApplication>
#include "virtualkeyboardwidget.h"

#define  TROG_AREA      (36)

CVirtualKeyBoardWidget::CVirtualKeyBoardWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip );
    this->setMouseTracking( true );
    mFocusKey           = nullptr;
    mBMousePressed      = false;
    mBIsCapsPress       = false;
    mBIsFnKeyPressed    = false;
    mBUseMouseFocus     = true;
    mBIsAltKeyPressed   = false;
    mBIsCtrlKeyPressed  = false;
    mBIsShiftKeyPressed = false;
    mIOldMouseX         = 0;
    mIOldMouseY         = 0;
    this->setFixedSize( 960, 320 );
    InitKeys();
    InitKeysSize();
    repaint();
    this->move( 10, QGuiApplication::primaryScreen()->availableGeometry().height()-this->height()-10 );
}

CVirtualKeyBoardWidget::~CVirtualKeyBoardWidget()
{
    for( int i=0; i<mVecKeys.size(); i++ )
    {
        delete mVecKeys[i];
    }
    mVecKeys.clear();
}

void CVirtualKeyBoardWidget::ShowVirtualKeyBoard()
{
    this->show();
}

void CVirtualKeyBoardWidget::UseMouseFocus(bool IsUsed)
{
    this->mBUseMouseFocus = IsUsed;
}

void CVirtualKeyBoardWidget::Hide()
{
    if( this->mFocusKey!=nullptr )
    {
        this->mFocusKey->isFocusIn = false;
        this->mFocusKey->isPressed = false;
    }
    this->mFocusKey             = nullptr;
    this->mBMousePressed        = false;
    this->mBIsShiftKeyPressed   = false;
    this->mBIsFnKeyPressed      = false;
    this->mBIsCtrlKeyPressed    = false;
    this->mBIsAltKeyPressed     = false;
    this->mIOldMouseX           = 0;
    this->mIOldMouseY           = 0;
    this->mBIsCapsPress         = false;
    this->close();
}

void CVirtualKeyBoardWidget::CreateEvent( SKey* key, QEvent::Type type )
{
    QWidget* mWidgetReceiver = QApplication::focusWidget();
    if( key!=nullptr && mWidgetReceiver!=nullptr )
    {
        QWidget* focusWidth = mWidgetReceiver->focusWidget();
        if( focusWidth!=nullptr )
        {
            Qt::Key  keyValue = key->norKey;
            QString  keyText  = "";
            Qt::KeyboardModifiers modifier = Qt::NoModifier;

            if( key->isTextKey )
            {
                keyText  = key->strNorKey;
            }

            if( key->norKey == Qt::Key_Tab )
            {
                keyText  = "\t";
            }

            if( mBIsCapsPress && key->isSupportCaps )
            {
                keyText  = key->strNorKey.toUpper();
            }

            if( mBIsShiftKeyPressed )
            {
                modifier =  modifier | Qt::ShiftModifier;
                if( key->isSupportShift )
                {
                    keyValue = key->shiftKey;
                    keyText  = key->strShiftKey;
                }

                if( key->isSupportCaps )
                {
                    keyValue = key->norKey;
                    keyText  = key->strNorKey.toUpper();
                }
            }

            if( mBIsCtrlKeyPressed )
            {
                modifier = modifier | Qt::ControlModifier;
            }

            if( mBIsAltKeyPressed )
            {
                modifier = modifier | Qt::AltModifier;
            }

            if( mBIsFnKeyPressed && key->isSupportFn )
            {
                keyValue = key->fnKey;
                keyText  = "";
            }

            QKeyEvent event( type, keyValue, modifier, keyText );
            QApplication::sendEvent( focusWidth, &event );
        }
    }
}

void CVirtualKeyBoardWidget::InitKeys()
{
    mVecKeys.push_back( new SKey( 1,    0,  0, Qt::Key_Escape,        "Esc" ) );
    mVecKeys.push_back( new SKey( 1,    0,  1, Qt::Key_QuoteDbl,      Qt::Key_AsciiTilde,   "`", "~",        true ) );
    mVecKeys.push_back( new SKey( 1,    0,  2, Qt::Key_1,             Qt::Key_exclamdown,   Qt::Key_F1,      "1",     "!",      "F1", true ) );
    mVecKeys.push_back( new SKey( 1,    0,  3, Qt::Key_2,             Qt::Key_At,           Qt::Key_F2,      "2",     "@",      "F2", true ) );
    mVecKeys.push_back( new SKey( 1,    0,  4, Qt::Key_3,             Qt::Key_NumberSign,   Qt::Key_F3,      "3",     "#",      "F3", true ) );
    mVecKeys.push_back( new SKey( 1,    0,  5, Qt::Key_4,             Qt::Key_Dollar,       Qt::Key_F4,      "4",     "$",      "F4", true ) );
    mVecKeys.push_back( new SKey( 1,    0,  6, Qt::Key_5,             Qt::Key_Percent,      Qt::Key_F5,      "5",     "%",      "F5", true ) );
    mVecKeys.push_back( new SKey( 1,    0,  7, Qt::Key_6,             Qt::Key_AsciiCircum,  Qt::Key_F6,      "6",     "^",      "F6", true ) );
    mVecKeys.push_back( new SKey( 1,    0,  8, Qt::Key_7,             Qt::Key_Ampersand,    Qt::Key_F7,      "7",     "&",      "F7", true ) );
    mVecKeys.push_back( new SKey( 1,    0,  9, Qt::Key_8,             Qt::Key_Asterisk,     Qt::Key_F8,      "8",     "*",      "F8", true ) );
    mVecKeys.push_back( new SKey( 1,    0, 10, Qt::Key_9,             Qt::Key_ParenLeft,    Qt::Key_F9,      "9",     "(",      "F9", true ) );
    mVecKeys.push_back( new SKey( 1,    0, 11, Qt::Key_0,             Qt::Key_ParenRight,   Qt::Key_F10,     "0",     ")",     "F10", true ) );
    mVecKeys.push_back( new SKey( 1,    0, 12, Qt::Key_Minus,         Qt::Key_Underscore,   Qt::Key_F11,     "-",     "_",     "F11", true ) );
    mVecKeys.push_back( new SKey( 1,    0, 13, Qt::Key_Equal,         Qt::Key_Plus,         Qt::Key_F12,     "=",     "+",     "F12", true ) );
    mVecKeys.push_back( new SKey( 1.5,  0, 14, Qt::Key_Backspace,     "Back" ) );
    mVecKeys.push_back( new SKey( 1,    0, 15, Qt::Key_PageUp,        "PgUp" ) );
    mVecKeys.push_back( new SKey( 1.5,  1,  0, Qt::Key_Tab,           "Tab"  ) );
    mVecKeys.push_back( new SKey( 1,    1,  1, Qt::Key_Q,             "q", true, true ) );
    mVecKeys.push_back( new SKey( 1,    1,  2, Qt::Key_W,             "w", true, true ) );
    mVecKeys.push_back( new SKey( 1,    1,  3, Qt::Key_E,             "e", true, true ) );
    mVecKeys.push_back( new SKey( 1,    1,  4, Qt::Key_R,             "r", true, true ) );
    mVecKeys.push_back( new SKey( 1,    1,  5, Qt::Key_T,             "t", true, true ) );
    mVecKeys.push_back( new SKey( 1,    1,  6, Qt::Key_Y,             "y", true, true ) );
    mVecKeys.push_back( new SKey( 1,    1,  7, Qt::Key_U,             "u", true, true ) );
    mVecKeys.push_back( new SKey( 1,    1,  8, Qt::Key_I,             "i", true, true ) );
    mVecKeys.push_back( new SKey( 1,    1,  9, Qt::Key_O,             "o", true, true ) );
    mVecKeys.push_back( new SKey( 1,    1, 10, Qt::Key_P,             "p", true, true ) );
    mVecKeys.push_back( new SKey( 1,    1, 11, Qt::Key_BracketLeft,   Qt::Key_BraceLeft,    "[", "{", true ) );
    mVecKeys.push_back( new SKey( 1,    1, 12, Qt::Key_BracketRight,  Qt::Key_BraceRight,   "]", "}", true ) );
    mVecKeys.push_back( new SKey( 1,    1, 13, Qt::Key_Backslash,     Qt::Key_Bar,          "\\","|", true ) );
    mVecKeys.push_back( new SKey( 1,    1, 14, Qt::Key_Delete,        "Del"  ) );
    mVecKeys.push_back( new SKey( 1,    1, 15, Qt::Key_PageDown,      "PgDn" ) );
    mVecKeys.push_back( new SKey( 2,    2,  0, Qt::Key_CapsLock,      "Caps" ) );
    mVecKeys.push_back( new SKey( 1,    2,  1, Qt::Key_A,             "a", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    2,  2, Qt::Key_S,             "s", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    2,  3, Qt::Key_D,             "d", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    2,  4, Qt::Key_F,             "f", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    2,  5, Qt::Key_G,             "g", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    2,  6, Qt::Key_H,             "h", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    2,  7, Qt::Key_J,             "j", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    2,  8, Qt::Key_K,             "k", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    2,  9, Qt::Key_L,             "l", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    2, 10, Qt::Key_Semicolon,     Qt::Key_Colon,        ";", ":" , true ) );
    mVecKeys.push_back( new SKey( 1,    2, 11, Qt::Key_Apostrophe,    Qt::Key_QuoteLeft,    "'", "\"", true ) );
    mVecKeys.push_back( new SKey( 2.5,  2, 12, Qt::Key_Return,        "Enter" ) );
    mVecKeys.push_back( new SKey( 1,    2, 13, Qt::Key_Home,          "Home"  ) );
    mVecKeys.push_back( new SKey( 2.5,  3,  0, Qt::Key_Shift,         "Shift" ) );
    mVecKeys.push_back( new SKey( 1,    3,  1, Qt::Key_Z,             "z", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    3,  2, Qt::Key_X,             "x", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    3,  3, Qt::Key_C,             "c", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    3,  4, Qt::Key_V,             "v", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    3,  5, Qt::Key_B,             "b", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    3,  6, Qt::Key_N,             "n", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    3,  7, Qt::Key_M,             "m", true, true  ) );
    mVecKeys.push_back( new SKey( 1,    3,  8, Qt::Key_Comma,         Qt::Key_Less,         ",", "<", true  ) );
    mVecKeys.push_back( new SKey( 1,    3,  9, Qt::Key_Period,        Qt::Key_Greater,      ".", ">", true  ) );
    mVecKeys.push_back( new SKey( 1,    3, 10, Qt::Key_Slash,         Qt::Key_Question,     "/", "?", true  ) );
    mVecKeys.push_back( new SKey( 1,    3, 11, Qt::Key_Up,            "↑"     ) );
    mVecKeys.push_back( new SKey( 2,    3, 12, Qt::Key_Shift,         "Shift" ) );
    mVecKeys.push_back( new SKey( 1,    3, 13, Qt::Key_End,           "End"   ) );
    mVecKeys.push_back( new SKey( 1,    4,  0, "Fn" ) );
    mVecKeys.push_back( new SKey( 1,    4,  1, Qt::Key_Control,       "Ctrl"  ) );
    mVecKeys.push_back( new SKey( 1,    4,  2, "Hide" ) );
    mVecKeys.push_back( new SKey( 1,    4,  3, Qt::Key_Alt,           "Alt"   ) );
    mVecKeys.push_back( new SKey( 5.5,  4,  4, Qt::Key_Space,         " ", false, true  ) );
    mVecKeys.push_back( new SKey( 1,    4,  5, Qt::Key_AltGr,         "Alt"   ) );
    mVecKeys.push_back( new SKey( 1,    4,  6, Qt::Key_Control,       "Ctrl"  ) );
    mVecKeys.push_back( new SKey( 1,    4,  7, Qt::Key_Left,          "←"     ) );
    mVecKeys.push_back( new SKey( 1,    4,  8, Qt::Key_Down,          "↓"     ) );
    mVecKeys.push_back( new SKey( 1,    4,  9, Qt::Key_Right,         "→"     ) );
    mVecKeys.push_back( new SKey( 1,    4, 10, Qt::Key_Menu,          "Menu"  ) );
    mVecKeys.push_back( new SKey( 1,    4, 11, Qt::Key_Insert,        "Ins"   ) );
}

void CVirtualKeyBoardWidget::InitKeysSize()
{
    qreal key_margin = 4;
    qreal win_width  = this->width();
    qreal win_height = this->height() - TROG_AREA;
    qreal btn_width  = ( win_width - key_margin ) / 16;
    qreal btn_height = ( win_height - key_margin ) / 5;
    qreal  x   = 0;
    int    row = 0;

    btn_width -= ( btn_width/2/16 );
    for( int i=0; i<mVecKeys.size(); i++ )
    {
        SKey* key = mVecKeys[i];
        if( key->row != row )
        {
            row = key->row;
            x = 0;
        }
        key->x = x * btn_width + key_margin;
        key->y = TROG_AREA + key->row * btn_height + key_margin;
        key->width  = btn_width * key->weight - key_margin;
        key->height = btn_height - key_margin;
        x += key->weight;
    }
}

SKey *CVirtualKeyBoardWidget::FindKeys(int x, int y)
{
    SKey* retKey = nullptr;
    for( int i=0; i<mVecKeys.size(); i++ )
    {
        SKey* key = mVecKeys[i];
        if( x>key->x && x<(key->x+key->width)
              && y>key->y && y<(key->y+key->height) )
        {
            retKey = key;
            break;
        }
    }
    return retKey;
}

void CVirtualKeyBoardWidget::paintEvent(QPaintEvent*)
{
    QPainter  painter(this);
    QRectF    rectf;
    QColor    color;

    painter.fillRect( 0, 0, width(), height(), QColor(26,26,26) );  //  background.
    for( int i=0; i<mVecKeys.size(); i++ )
    {
        SKey* key = mVecKeys[i];
        rectf.setX( key->x );
        rectf.setY( key->y );
        rectf.setWidth(  key->width );
        rectf.setHeight( key->height );

        switch( key->norKey )
        {
            case Qt::Key_Alt:
            case Qt::Key_AltGr:     key->isPressed = mBIsAltKeyPressed;         break;
            case Qt::Key_Shift:     key->isPressed = mBIsShiftKeyPressed;       break;
            case Qt::Key_CapsLock:  key->isPressed = mBIsCapsPress;             break;
            case Qt::Key_Control:   key->isPressed = mBIsCtrlKeyPressed;        break;
            default:                key->strNorKey == "Fn" && ( key->isPressed = mBIsFnKeyPressed );
        }

        if( mBUseMouseFocus && key->isFocusIn )
        {
            color.setRgb( 229,229,229 );
            painter.setPen( QColor(51, 51, 51) );
        }
        else
        {
            color.setRgb( 51, 51, 51 );
            painter.setPen( Qt::white );
        }

        if( key->isPressed )
        {
            color.setRgb( 0, 97, 176 );
            painter.setPen( QColor( 229, 229, 229 ) );
        }

        painter.fillRect( rectf, color );       //  draw key button
        if( key->isSupportFn && mBIsFnKeyPressed )
        {
            painter.setPen( Qt::white );
            painter.drawText( QPointF(key->x + key->width/4, key->y + key->height/4 + 5), key->strFnKey );
        }
        else if( key->showShiftKey )
        {
           QPen pen;
           qreal x = key->x + key->width / 4;
           qreal y = key->y + key->height / 4 + 5;
           painter.setPen( mBIsShiftKeyPressed? Qt::white : Qt::gray );
           painter.drawText( QPointF( x, y ), key->strShiftKey );   //  draw shift key text
           mBIsShiftKeyPressed?
               pen.setColor(Qt::gray)
             : key->isFocusIn?
                   key->isPressed?
                       pen.setColor(QColor(229, 229, 229))
                     : pen.setColor(QColor(51,51,51))
                 : pen.setColor(QColor( 229, 229, 229 ));
           painter.setPen( pen );
           x = key->x + key->width  / 3 + key->width / 3;
           y = key->y + key->height / 3 + key->height / 3;
           painter.drawText( QPointF( x, y ), key->strNorKey );     //  draw unshift key text
        }
        else
        {
            qreal x = key->x + 10;
            qreal y = key->y + key->height / 3;
            QString text = "";
            text = mBIsShiftKeyPressed?
                      key->isSupportShift?
                          key->strShiftKey
                        : key->isSupportCaps?
                              key->strNorKey.toUpper()
                            : key->strNorKey
                    : mBIsCapsPress?
                          key->isSupportCaps?
                              key->strNorKey.toUpper()
                            : key->strNorKey
                       : key->strNorKey;
            painter.drawText( QPointF(x, y), text );                //  draw other key text
        }
    }
}

void CVirtualKeyBoardWidget::resizeEvent(QResizeEvent*)
{
    InitKeysSize();
}

void CVirtualKeyBoardWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();   
    if( mBMousePressed && event->y()>0 && event->y()<TROG_AREA )
    {
        if( mFocusKey!=nullptr )
        {
            mFocusKey->isFocusIn = false;
            mFocusKey->isPressed = false;
            CreateEvent( mFocusKey, QEvent::KeyRelease );
            mFocusKey = nullptr;
            repaint();
        }
        this->move( event->globalX() - mIMarginLeft, event->globalY() - mIMarginTop );
        return;
    }

    if( mFocusKey==nullptr )
    {
        mFocusKey = FindKeys( x, y );
        if( mFocusKey != nullptr && mBUseMouseFocus )
        {
            mFocusKey->isFocusIn = true;
        }
        repaint();
    }
    else {
        if( !( x>mFocusKey->x && x<(mFocusKey->x + mFocusKey->width)
                && y>mFocusKey->y && y<(mFocusKey->y + mFocusKey->height) ) )
        {
            mFocusKey->isFocusIn = false;
            mFocusKey->isPressed = false;
            mFocusKey = FindKeys( x, y );
            if( mFocusKey!=nullptr && mBUseMouseFocus )
                mFocusKey->isFocusIn = true;
            repaint();
        }
    }
}

void CVirtualKeyBoardWidget::mouseReleaseEvent(QMouseEvent*)
{
    mBMousePressed = false;
    if( mFocusKey!=nullptr )
    {
        mFocusKey->isPressed = false;
        CreateEvent( mFocusKey, QEvent::KeyRelease );
        repaint();
        if( mFocusKey->isTextKey )
        {
            mBIsShiftKeyPressed = false;
            mBIsCtrlKeyPressed  = false;
            mBIsAltKeyPressed   = false;
            repaint();
        }
    }
}

void CVirtualKeyBoardWidget::mousePressEvent(QMouseEvent* event)
{
    mBMousePressed = true;
    mIMarginLeft = event->globalX() - this->geometry().x();
    mIMarginTop  = event->globalY() - this->geometry().y();
    mIOldMouseX  = event->globalX();
    mIOldMouseY  = event->globalY();
    if( mFocusKey!=nullptr )
    {
        mFocusKey->isPressed = true;
        if( !mFocusKey->isKey )
        {
            if( mFocusKey->strNorKey == "Hide" )
            {
                Hide();   return;
            }

            if( mFocusKey->strNorKey == "Fn" )
                mBIsFnKeyPressed = ! mBIsFnKeyPressed;
        }
        else
        {
            switch( mFocusKey->norKey )
            {
                case Qt::Key_AltGr:
                case Qt::Key_Alt:       mBIsAltKeyPressed   = !mBIsAltKeyPressed;       break;
                case Qt::Key_CapsLock:  mBIsCapsPress       = !mBIsCapsPress;           break;
                case Qt::Key_Shift:     mBIsShiftKeyPressed = !mBIsShiftKeyPressed;     break;
                case Qt::Key_Control:   mBIsCtrlKeyPressed  = !mBIsCtrlKeyPressed;      break;
                default:                CreateEvent( mFocusKey, QEvent::KeyPress );
            }
        }
        repaint();
    }
}
