#  -*- coding: iso-8859-1 -*-
# Copyright (C) 2007-2012  CEA/DEN, EDF R&D, OPEN CASCADE
#
# Copyright (C) 2003-2007  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
# CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
#
# See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
#

import sys, os,signal,string,commands

def killNamingService():
    """
    kills omniORB4 Naming Service on local machine.
    Selects process corresponding to the port used in $OMNIORB_CONFIG file.
    Works only with a single line $OMNIORB_CONFIG like
    InitRef = NameService=corbaname::<hostname>:<port>
    """
    fic=os.environ['OMNIORB_CONFIG']
    f=open(fic,'r')
    line=f.readline()
    f.close()
    port=string.split(line,':')[-1][0:4]
    command='ps -eo pid,command | grep "omniNames -start '+str(port)+'"'
    pid=string.split(commands.getoutput(command))[0]
    os.kill(int(pid),signal.SIGKILL)


def killProcess(process_id):
    """
    kills process on local machine, given a dictionary of running process
    generated by runSalome.Server() class and derived, (method run).
    kills also local Naming server.
    """
    for pid, cmd in process_id.items():
        print "stop process %s : %s"% (pid, cmd[0])
        try:
            os.kill(int(pid),signal.SIGKILL)
        except:
            print "  ---- process %s : %s inexistant"% (pid, cmd[0])
            pass
        del process_id[pid]
        pass
    killNamingService()
