//  SALOME PatchQt : patch for Qt
//
//  Copyright (C) 2003  CEA/DEN, EDF R&D
//
//
//
//  File   : qactionP.h
//  Author : Vadim SANDLER
//  Module : SALOME
//  $Header$

#ifndef QACTIONP_H
#define QACTIONP_H

#ifndef QT_H
#include <qobject.h>
#include <qiconset.h>
#include <qstring.h>
#include <qkeysequence.h>
#endif // QT_H

#ifndef QT_NO_ACTION

class QActionPPrivate;
class QActionPGroupPrivate;
class QStatusBar;
class QPopupMenu;

class Q_EXPORT QActionP : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool toggleAction READ isToggleAction WRITE setToggleAction)
    Q_PROPERTY( bool on READ isOn WRITE setOn )
    Q_PROPERTY( bool enabled READ isEnabled WRITE setEnabled )
    Q_PROPERTY( QIconSet iconSet READ iconSet WRITE setIconSet )
    Q_PROPERTY( QString text READ text WRITE setText )
    Q_PROPERTY( QString menuText READ menuText WRITE setMenuText )
    Q_PROPERTY( QString toolTip READ toolTip WRITE setToolTip )
    Q_PROPERTY( QString statusTip READ statusTip WRITE setStatusTip )
    Q_PROPERTY( QString whatsThis READ whatsThis WRITE setWhatsThis )
    Q_PROPERTY( QKeySequence accel READ accel WRITE setAccel )

public:
    QActionP( QObject* parent, const char* name = 0, bool toggle = FALSE  );
    QActionP( const QString& text, const QIconSet& icon, const QString& menuText, QKeySequence accel,
	     QObject* parent, const char* name = 0, bool toggle = FALSE );
    QActionP( const QString& text, const QString& menuText, QKeySequence accel, QObject* parent,
	     const char* name = 0, bool toggle = FALSE );
    ~QActionP();

    virtual void setIconSet( const QIconSet& );
    QIconSet iconSet() const;
    virtual void setText( const QString& );
    QString text() const;
    virtual void setMenuText( const QString& );
    QString menuText() const;
    virtual void setToolTip( const QString& );
    QString toolTip() const;
    virtual void setStatusTip( const QString& );
    QString statusTip() const;
    virtual void setWhatsThis( const QString& );
    QString whatsThis() const;
    virtual void setAccel( const QKeySequence& key );
    QKeySequence accel() const;
    virtual void setToggleAction( bool );
    bool isToggleAction() const;
    bool isOn() const;
    bool isEnabled() const;
    virtual bool addTo( QWidget* );
    virtual bool removeFrom( QWidget* );

protected:
    virtual void addedTo( QWidget *actionWidget, QWidget *container );
    virtual void addedTo( int index, QPopupMenu *menu );

public slots:
    void toggle();
    virtual void setOn( bool );
    virtual void setEnabled( bool );

signals:
    void activated();
    void toggled( bool );

private slots:
    void internalActivation();
    void toolButtonToggled( bool );
    void objectDestroyed();
    void menuStatusText( int id );
    void showStatusText( const QString& );
    void clearStatusText();

private:
    void init();

    QActionPPrivate* d;

};

class Q_EXPORT QActionPGroup : public QActionP
{
    Q_OBJECT
    Q_PROPERTY( bool exclusive READ isExclusive WRITE setExclusive )
    Q_PROPERTY( bool usesDropDown READ usesDropDown WRITE setUsesDropDown )

public:
    QActionPGroup( QObject* parent, const char* name = 0, bool exclusive = TRUE );
    ~QActionPGroup();
    void setExclusive( bool );
    bool isExclusive() const;
    void add( QActionP* a);
    void addSeparator();
    bool addTo( QWidget* );
    bool removeFrom( QWidget* );
    void setEnabled( bool );

    void setUsesDropDown( bool enable );
    bool usesDropDown() const;

    void setIconSet( const QIconSet& );
    void setText( const QString& );
    void setMenuText( const QString& );
    void setToolTip( const QString& );
    void setWhatsThis( const QString& );

protected:
    void childEvent( QChildEvent* );
    virtual void addedTo( QWidget *actionWidget, QWidget *container, QActionP *a );
    virtual void addedTo( int index, QPopupMenu *menu, QActionP *a );
    virtual void addedTo( QWidget *actionWidget, QWidget *container );
    virtual void addedTo( int index, QPopupMenu *menu );

signals:
    void selected( QActionP* );

private slots:
    void childToggled( bool );
    void childDestroyed();
    void internalComboBoxActivated( int );
    void internalToggle( QActionP* );
    void objectDestroyed();

private:
    QActionPGroupPrivate* d;

#ifndef QT_NO_COMPAT
public:
    void insert( QActionP* a ) { add( a ); }
#endif

};

#endif

#endif
