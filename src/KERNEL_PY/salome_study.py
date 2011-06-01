#  -*- coding: iso-8859-1 -*-
# Copyright (C) 2007-2011  CEA/DEN, EDF R&D, OPEN CASCADE
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

#  File   : salome_study.py
#  Author : Paul RASCLE, EDF
#  Module : SALOME
#  $Header$
#
import salome_kernel
import SALOMEDS
import salome_iapp
from launchConfigureParser import verbose

#--------------------------------------------------------------------------

def DumpComponent(Study, SO, Builder,offset):
  it = Study.NewChildIterator(SO)
  while it.More():
    CSO = it.Value()
    a=offset*"--" + ">" + CSO.GetID()
    find,AtName = Builder.FindAttribute(CSO, "AttributeName")
    if find:
      a=a+":"+AtName.Value()
    find,AtIOR = Builder.FindAttribute(CSO, "AttributeIOR")
    if find:
      a=a+":"+AtIOR.Value()
    find,RefSO = CSO.ReferencedObject()
    if find:
      a=a+":"+RefSO.GetID()
    print a
    DumpComponent(Study, CSO, Builder,offset+2)
    it.Next()

#--------------------------------------------------------------------------

def DumpStudy(Study):
    """
    Dump a study, given the ior
    """
    itcomp = Study.NewComponentIterator()
    Builder = Study.NewBuilder()
    while itcomp.More():
      SC = itcomp.Value()
      name = SC.ComponentDataType()
      print "-> ComponentDataType is " + name
      DumpComponent(Study, SC,Builder, 1)
      itcomp.Next()

def DumpStudies():
  """
    Dump all studies in a StudyManager
  """
  for name in myStudyManager.GetOpenStudies():
    s=myStudyManager.GetStudyByName(name)
    print "study:",name, s._get_StudyId()
    DumpStudy(s)


#--------------------------------------------------------------------------

def IDToObject(id):
    myObj = None
    mySO = myStudy.FindObjectID(id);
    if mySO is not None:
        ok, anAttr = mySO.FindAttribute("AttributeIOR")
        if ok:
            AtIOR = anAttr._narrow(SALOMEDS.AttributeIOR)
            if AtIOR.Value() != "":
                myObj = orb.string_to_object(AtIOR.Value())
    return myObj

def ObjectToSObject(obj):
    mySO = None
    if obj is not None:
        ior =  orb.object_to_string(obj)
        if ior != "":
            mySO = myStudy.FindObjectIOR(ior)
    return mySO

def ObjectToID(obj):
    mySO = ObjectToSObject(obj)
    if mySO:
        return mySO.GetID()
    return ""

def IDToSObject(id):
    mySO = myStudy.FindObjectID(id);
    return mySO

    #--------------------------------------------------------------------------

def generateName(prefix = None):
    import random;
    int = random.randint(1,1000);
    if prefix is None:
        return "Study" + str(int)
    else :
        return prefix + str(int)

    #--------------------------------------------------------------------------

def PersistentPresentation(theStudy, theSO, theWithID):
    # put the sobject's content (with subchildren) to the string
    aResult = ""
    attrs = theSO.GetAllAttributes()
    aLen = len(attrs)
    anUncopied = 0
    for a in range(0,aLen):
        attr = attrs[a]
        if isinstance(attr,SALOMEDS._objref_AttributeTreeNode):
            anUncopied += 1
        elif isinstance(attr,SALOMEDS._objref_AttributeTarget):
            anUncopied += 1
        elif isinstance(attr,SALOMEDS._objref_AttributeReal) or \
             isinstance(attr,SALOMEDS._objref_AttributeInteger) or \
             isinstance(attr,SALOMEDS._objref_AttributeName) or \
             isinstance(attr,SALOMEDS._objref_AttributeComment) or \
             isinstance(attr,SALOMEDS._objref_AttributePersistentRef) or \
             isinstance(attr,SALOMEDS._objref_AttributeLocalID) or \
             isinstance(attr,SALOMEDS._objref_AttributeUserID):
            aResult += " attribute value: " + str(attr.Value())
        elif isinstance(attr,SALOMEDS._objref_AttributeIOR):
            aResult += " attribute: IOR"
        elif isinstance(attr,SALOMEDS._objref_AttributeSequenceOfReal) or \
             isinstance(attr,SALOMEDS._objref_AttributeSequenceOfInteger):
            aResult += " Sequence: " + str(attr.CorbaSequence())
        elif isinstance(attr,SALOMEDS._objref_AttributeDrawable):
            aResult += " Drawable: " + str(attr.IsDrawable())
        elif isinstance(attr,SALOMEDS._objref_AttributeSelectable):
            aResult += " Selectable: " + str(attr.IsSelectable())
        elif isinstance(attr,SALOMEDS._objref_AttributeExpandable):
            aResult += " Expandable: " + str(attr.IsExpandable())
        elif isinstance(attr,SALOMEDS._objref_AttributeOpened):
            aResult += " Opened: " + str(attr.IsOpened())
        elif isinstance(attr,SALOMEDS._objref_AttributeTextColor):
            aResult += " TextColor: " + str(attr.TextColor())
        elif isinstance(attr,SALOMEDS._objref_AttributeTextHighlightColor):
            aResult += " TextHighlightColor: " + str(attr.TextHighlightColor())
        elif isinstance(attr,SALOMEDS._objref_AttributePixMap):
            aResult += " PixMap: " + str(attr.GetPixMap())
        elif isinstance(attr,SALOMEDS._objref_AttributeTableOfInteger) or \
             isinstance(attr,SALOMEDS._objref_AttributeTableOfReal):
            aResult += " Table with title: " + attr.GetTitle()
        elif isinstance(attr,SALOMEDS._objref_AttributePythonObject):
            aResult += " PythonObject: " + attr.GetObject()

    if theWithID:
        aResult = "sobject: " + theSO.GetID() + " nbattrs: " + str(aLen - anUncopied) + aResult + '\n'
    else:
        aResult = " nbattrs: " + str(aLen - anUncopied) + aResult + '\n'
    anIter = theStudy.NewChildIterator(theSO)
    while anIter.More():
        aResult += PersistentPresentation(theStudy, anIter.Value(), theWithID)
        anIter.Next()
    return aResult

    #--------------------------------------------------------------------------

def GetTree(theSO):
    # returns the document list tree (as list)
    aResult = [theSO.GetID()]
    anIter = myStudy.NewChildIterator(theSO)
    while anIter.More():
        aResult += GetTree(anIter.Value())
        anIter.Next()
    return aResult

    #--------------------------------------------------------------------------

def CheckCopyPaste(theSO, theInfo ,theComponentPaste):
    aRoot = theSO
    while aRoot.GetID() != "0:":
        aRoot = aRoot.GetFather()
    aTree = GetTree(aRoot)
    aStudyPersist = PersistentPresentation(myStudy, aRoot, 1)

    if not myStudyManager.CanCopy(theSO):
        raise RuntimeError, "<CanCopy> for "+theInfo+" returns false"
    
    if not myStudyManager.Copy(theSO):
        raise RuntimeError, "<Copy> for "+theInfo+" returns false"

    
    if not myStudyManager.CanPaste(theSO):
        raise RuntimeError, "<CanPaste> for "+theInfo+" returns false"

    # check: before paste study is not changed check
    if aStudyPersist != PersistentPresentation(myStudy, aRoot, 1):
        raise RuntimeError, "Study is changed before Paste calling for "+theInfo
    
    aSObj = theSO
    if theComponentPaste:
        aSObj = theSO.GetFatherComponent()
        theInfo = theInfo + "(paste for component)"
    if myStudyManager.Paste(aSObj) == None:
        raise RuntimeError, "<Paste> for "+theInfo+" returns None object"
    aNewTree = GetTree(aRoot)
    aLen = len(aTree)
    for a in range(0,aLen):
        if aTree[a] != aNewTree[a]:
            return myStudy.FindObjectID(aNewTree[a])
        
    if aLen < len(aNewTree):
        return myStudy.FindObjectID(aNewTree[aLen])
    
    raise RuntimeError, "After Copy calling the tree is not changed"
    
    #--------------------------------------------------------------------------

def FindFileInDataDir(filename):
    import os
    datadir = os.getenv("DATA_DIR")
    if datadir is not None:
        import string
        dirs = string.split(datadir, ":")
        for dir in dirs:
            file = dir + "/" + filename
            if os.path.exists(file):
                return file;
    datadir = os.getenv("KERNEL_ROOT_DIR") + "/examples/"
    file = datadir + filename
    if os.path.exists(file):
        return file;

    return None

    #--------------------------------------------------------------------------

salome_study_ID = -1

def getActiveStudy(theStudyId=0):
    global salome_study_ID

    if verbose(): print "getActiveStudy"
    if salome_study_ID == -1:
        if salome_iapp.hasDesktop():
            if verbose(): print "---in gui"
            salome_study_ID = salome_iapp.sg.getActiveStudyId()
        else:
            if verbose(): print "---outside gui"
            if theStudyId:
                aStudy=myStudyManager.GetStudyByID(theStudyId)
                if aStudy:
                    if verbose(): print "connection to existing study ", theStudyId
                    salome_study_ID = theStudyId
            if salome_study_ID == -1:
                salome_study_ID = createNewStudy()
            if verbose(): print"--- Study Id ", salome_study_ID
    return salome_study_ID

    #--------------------------------------------------------------------------

def setCurrentStudy(theStudy):
    """
    Change current study : an existing one given by a study object.

    :param theStudy: the study CORBA object to set as current study
    """
    global myStudyId, myStudy, myStudyName
    global salome_study_ID
    myStudy=theStudy
    myStudyId=theStudy._get_StudyId()
    myStudyName=theStudy._get_Name()
    return myStudyId, myStudy, myStudyName

    #--------------------------------------------------------------------------

def setCurrentStudyId(theStudyId=0):
    """
    Change current study : an existing or new one.
    optional argument : theStudyId
        0      : create a new study (default).
        n (>0) : try connection to study with Id = n, or create a new one
                 if study not found.
    """
    global myStudyId, myStudy, myStudyName
    global salome_study_ID
    salome_study_ID = -1
    myStudyId = getActiveStudy(theStudyId)
    if verbose(): print "myStudyId",myStudyId
    myStudy = myStudyManager.GetStudyByID(myStudyId)
    myStudyName = myStudy._get_Name()

    return myStudyId, myStudy, myStudyName

    #--------------------------------------------------------------------------

def createNewStudy():
    print "createNewStudy"
    i=1
    aStudyName = "noName"
    nameAlreadyInUse = 1
    listOfOpenStudies = myStudyManager.GetOpenStudies()
    print listOfOpenStudies
    while nameAlreadyInUse:
        aStudyName = "extStudy_%d"%i
        if aStudyName not in listOfOpenStudies:
            nameAlreadyInUse=0
        else:
            i = i+1

    theStudy = myStudyManager.NewStudy(aStudyName)
    theStudyId = theStudy._get_StudyId()
    print aStudyName, theStudyId
    return theStudyId

    #--------------------------------------------------------------------------

salome_study_initial = 1

def salome_study_init(theStudyId=0):
    """
    Performs only once study creation or connection.
    optional argument : theStudyId
      When in embedded interpreter inside IAPP, theStudyId is not used
      When used without GUI (external interpreter)
        0      : create a new study (default).
        n (>0) : try connection to study with Id = n, or create a new one
                 if study not found.
    """

    global salome_study_initial
    global myStudyManager, myStudyId, myStudy, myStudyName
    global orb, lcc, naming_service, cm

    if salome_study_initial:
        salome_study_initial = 0

        orb, lcc, naming_service, cm = salome_kernel.salome_kernel_init()

        # get Study Manager reference
        if verbose(): print "looking for studyManager ..."
        obj = naming_service.Resolve('myStudyManager')
        myStudyManager = obj._narrow(SALOMEDS.StudyManager)
        if verbose(): print "studyManager found"

        # get active study Id, ref and name
        myStudyId = getActiveStudy(theStudyId)
        if verbose(): print "myStudyId",myStudyId
        myStudy = myStudyManager.GetStudyByID(myStudyId)
        myStudyName = myStudy._get_Name()

    return myStudyManager, myStudyId, myStudy, myStudyName

