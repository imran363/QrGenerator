#include "maindialog.h"
#include "ui_maindialog.h"
#include <qrencode.h>
#include <string>
#include <QPainter>
#include <QPixmap>
#include <QClipboard>
#include <QPicture>
#include <QFileDialog>

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{

    ui->setupUi(this);
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::on_generateButton_clicked()
{
    QString s = ui->textEdit->toPlainText();
    std::string str = s.toStdString();
    if(s.length()<=4000){
    QRcode *qr = QRcode_encodeString(str.c_str(), 1, QR_ECLEVEL_L, QR_MODE_8, 1);
    const int width = ui->qrCodeLabel->width();
    const int height = ui->qrCodeLabel->height();


    QPixmap *pix = new QPixmap(width, height);

    QPainter *painter = new QPainter(pix);
    if(0!=qr){
        QColor fg("black");
        QColor bg("white");
        painter->setBrush(bg);
        painter->setPen(Qt::NoPen);
        painter->drawRect(0,0,width,height);
        painter->setBrush(fg);
        const int s=qr->width>0?qr->width:1;
        const double w=width;
        const double h=height;
        const double aspect=w/h;
        const double scale=((aspect>1.0)?h:w)/s;
        for(int y=0;y<s;y++){
            const int yy=y*s;
            for(int x=0;x<s;x++){
                const int xx=yy+x;
                const unsigned char b=qr->data[xx];
                if(b &0x01){
                    const double rx1=x*scale, ry1=y*scale;
                    QRectF r(rx1, ry1, scale, scale);
                    painter->drawRects(&r,1);
                }
            }
        }
        pix->scaled(width, height);
        ui->qrCodeLabel->setScaledContents(true);
        ui->qrCodeLabel->setPixmap(*pix);
        QRcode_free(qr);
    }
    else{
        QColor error("red");
        painter->setBrush(error);
        painter->drawRect(0,0,width,height);
    }
    qr=0;
    }
    else{
        ui->qrCodeLabel->setText("Input too large, Cannot create QR Code!");
    }
}

void mainDialog::on_resetButton_clicked()
{
    ui->qrCodeLabel->setText("QR Code Generator");
    ui->textEdit->setText("");
}

void mainDialog::on_saveButton_clicked()
{
    if(ui->qrCodeLabel->pixmap()){
    QString fileName = QFileDialog::getSaveFileName(
       this,
       tr("Output Image file"),
       (""),
       tr("PNG (*.png);;JPEG (*.JPEG);;Windows Bitmap (*.bmp);;All Files (*.*)")
    );

    if(fileName != "")
    {
        QPixmap *qrImage = new QPixmap(*ui->qrCodeLabel->pixmap());

       bool isOk = qrImage->save(fileName);

       if(!isOk)
       {
          QString msgText = tr("Failed to write into ") + fileName;
          ui->qrCodeLabel->setText(msgText);

       }
    }
    }
    else{
        ui->qrCodeLabel->setText("Please Generate QR Code before Saving!");
    }

}

void mainDialog::on_pasteButton_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();

    ui->textEdit->setText(clipboard->text());
}
