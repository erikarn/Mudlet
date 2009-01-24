
#ifndef _TIMER_H_
#define _TIMER_H_

/***************************************************************************
 *   Copyright (C) 2008 by Heiko Koehn                                     *
 *   KoehnHeiko@googlemail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/



#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <QMutex>
#include <QTimer>
#include <QString>
#include <QRegExp>
#include "Tree.h"
#include <QDataStream>
#include "Host.h"
#include <QTextBlock>
#include <QTime>

using namespace std;



class TTimer : public Tree<TTimer>
{
        
public:
    
    virtual         ~TTimer();
                     TTimer( TTimer * parent, Host * pHost ); 
                     TTimer( QString name, QTime time, Host * pHost ); 
    
    QString          getName()                       { QMutexLocker locker(& mLock); return mName; }
    void             setName( QString name )         { QMutexLocker locker(& mLock); mName = name; }
    QTime &          getTime()                       { QMutexLocker locker(& mLock); return mTime; }
    void             compile();
    void             execute();
    void             setTime( QTime time );         
    QString          getCommand()                    { QMutexLocker locker(& mLock); return mCommand; }
    void             setCommand( QString & cmd )     { QMutexLocker locker(& mLock); mCommand = cmd; }
    QString          getScript()                     { QMutexLocker locker(& mLock); return mScript; }
    void             setScript( QString & script )   { QMutexLocker locker(& mLock); mScript = script; mNeedsToBeCompiled=true; }
    bool             isActive()                      { QMutexLocker locker(& mLock); return mIsActive; }  
    bool             isFolder()                      { QMutexLocker locker(& mLock); return mIsFolder; }
    void             setIsTempTimer( bool b )        { QMutexLocker locker(& mLock); mIsTempTimer = b; }    
    bool             isTempTimer()                   { QMutexLocker locker(& mLock); return mIsTempTimer; }
    
    void             setIsActive( bool b );           
    void             setIsFolder( bool b )           { QMutexLocker locker(& mLock); mIsFolder = b; }
    bool             registerTimer();
    void             stop();
    void             start();
    void             enableTimer( QString & );
    void             disableTimer( QString & );
    TTimer *         killTimer( QString & );
    bool             serialize( QDataStream & );
    bool             restore( QDataStream & fs );
    void             slot_timer_fires();
    
private:
    
                     TTimer(){};
    QString          mName;
    QString          mScript;
    QTime            mTime;
    QTimer           mTimer;
    QString          mCommand;
    bool             mIsActive;
    bool             mIsFolder;
    Host *           mpHost;
    bool             mNeedsToBeCompiled;
    bool             mIsTempTimer;
    QMutex           mLock;
        
};

#endif

