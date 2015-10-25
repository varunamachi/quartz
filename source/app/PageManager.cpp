/*******************************************************************************
 * ComponentManager.cpp
 *
 * Copyright (c) 2013, Varuna L Amachi. All rights reserved.
 *
 * This program/library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program/library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 ******************************************************************************/

#include <QHBoxLayout>
#include <QSplitter>
#include <QIcon>

#include "PageManager.h"

namespace Vam { namespace Quartz {

ComponentManager *ComponentManager::s_instance = 0;


void ComponentManager::destroy()
{
    if( s_instance ) {
        delete s_instance;
    }
}


ComponentManager* ComponentManager::get()
{
    return s_instance;
}



ComponentManager::ComponentManager( QWidget *parent )
    : QWidget( parent )
{
    setupUi();
    s_instance = this;
}



ComponentManager::~ComponentManager()
{
    m_nameToIndex.clear();
    qDeleteAll( m_components.begin(), m_components.end() );
}


void ComponentManager::setupUi()
{
    m_mainWidget = new QStackedWidget( this );
    m_buttonLayout = new QVBoxLayout();
    m_buttonLayout->addStretch();

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addLayout( m_buttonLayout );
    leftLayout->addStretch();


    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout( leftLayout );
    mainLayout->addWidget( m_mainWidget );
    mainLayout->setContentsMargins( QMargins() );
    mainLayout->setSpacing( 0 );

    m_mainWidget->setContentsMargins( 0, 0, 0, 0 );
    m_buttonLayout->setContentsMargins( 4, 2, 0, 0 );
    m_buttonLayout->setSpacing( 5 );
    this->setLayout( mainLayout );

}


QList< QuartzComponent *> ComponentManager::allComponents() const
{
    return m_components.values();
}


const QuartzComponent* ComponentManager::component( QString componentId )const
{
    return m_components.value( componentId );
}


const QuartzComponent *ComponentManager::currentComponent() const
{
    QWidget *widget = m_mainWidget->currentWidget();
    if( widget ) {
        return static_cast< QuartzComponent *>( widget );
    }
    return 0;
}


void ComponentManager::addComponent( QuartzComponent *component )
{
    if( component && ! m_components.contains( component->componentId() )) {
        m_components.insert( component->componentId(), component );
        IndexButton *button = new IndexButton( m_components.size() - 1,
                                               component->componentName(),
                                               this );
        m_buttons.append( button );
        m_nameToIndex.insert( component->componentId(),
                              m_components.size() - 1 );
        m_buttonLayout->insertWidget( m_buttonLayout->count() - 1, button );
        connect( button, SIGNAL( activated( int )),
                 this, SLOT( onIndexSelected( int )));
        m_mainWidget->addWidget( component );
        emit componentAdded( component );
        if( m_components.size() == 1 ) {
            button->setChecked( true );
             m_mainWidget->setCurrentIndex( 0 );
        }
    }
}


void ComponentManager::selectComponent( QString componentId )
{
    if( m_nameToIndex.contains( componentId )) {
        int index = m_nameToIndex.value( componentId );
        m_buttons.at( m_mainWidget->currentIndex() )->setChecked( false );
        m_buttons.at( index )->setChecked( true );
        m_mainWidget->setCurrentIndex( index );
        emit componentSelected( m_components.value( componentId ));
    }
}


void ComponentManager::onIndexSelected( int row )
{
    m_buttons.at( m_mainWidget->currentIndex() )->setChecked( false );
    m_mainWidget->setCurrentIndex( row );
}

} }
