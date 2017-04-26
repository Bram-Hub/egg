#include "stepitem.h"
#include "ui_clickableframe.h"
#include "hspacer.h"
#include "stepoverview.h"

#include <QLabel>
#include <QFrame>
#include <QDebug>

StepItem::StepItem( QWidget* parent, int c, QString s, TreeState* state ) :
    ClickableFrame( parent ),
    correspondingTree( state )
{
    numLabel = new QLabel( QString::number(c) );
    numLabel->setMinimumWidth(20);
    numLabel->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    ui->contentsLayout->addWidget( numLabel );

    QWidget* vert = new QWidget;
    vert->setFixedWidth(2);
    vert->setSizePolicy( QSizePolicy::Fixed,
                         QSizePolicy::Expanding );
    vert->setStyleSheet( QString( "background-color: #c0c0c0;" ) );
    ui->contentsLayout->addWidget( vert );

    text = new QLabel( s );
    ui->contentsLayout->addWidget( text );

    QSpacerItem* spacer = HSpacer::makeSpacer();
    ui->contentsLayout->addSpacerItem( spacer );
}

void StepItem::onSuccessfulClick()
{
    //ClickableFrame::onSuccessfulClick();
    ((StepOverview*)overViewWidget)->selectStepItem(this);

    qDebug() << "Clicked on step" << numLabel->text();
    qDebug() << "Tree is " << correspondingTree->toOutputString();
}
