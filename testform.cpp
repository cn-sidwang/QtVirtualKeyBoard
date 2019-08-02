
#include "testform.h"
#include "ui_testform.h"
#include "virtualkeyboardwidget.h"

TestForm::TestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);
}

TestForm::~TestForm()
{
    if( CVirtualKeyBoardWidget::GetInstance().isVisible() )
        CVirtualKeyBoardWidget::GetInstance().close();
    delete ui;
}

void TestForm::on_pushButton_clicked()
{
    CVirtualKeyBoardWidget::GetInstance().ShowVirtualKeyBoard();
}

void TestForm::on_pushButton_2_clicked()
{
    this->close();
}
