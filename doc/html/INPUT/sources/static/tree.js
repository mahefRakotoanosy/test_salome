foldersTree = gFld("<b>SALOME v.1.2 </b>", "", "")
     insDoc(foldersTree, gLnk("Main Page", "", "main.html"))

aux1 = insFld(foldersTree, gFld("TUI Reference Guide", ""))
  aux2 = insFld(aux1, gFld("Modules", ""))
    aux3 = insFld(aux2, gFld("SALOME STUDY module", ""))
	     insDoc(aux3, gLnk("Overview", "", "overview_Study.html"))
      aux4 = insFld(aux3, gFld("Packages", ""))     	
               insDoc(aux4, gLnk("SALOMEDS", "", "namespaceSALOMEDS.html"))
	     insDoc(aux3, gLnk("Examples", "", "examples_Study.html"))
    aux3 = insFld(aux2, gFld("SALOME KERNEL module", ""))
             insDoc(aux3, gLnk("Overview", "", "overview_Kernel.html"))
      aux4 = insFld(aux3, gFld("Packages", "")) 
               insDoc(aux4, gLnk("SALOME_ModuleCatalog", "", "namespaceSALOME__ModuleCatalog.html"))
               insDoc(aux4, gLnk("SALOME", "", "namespaceSALOME.html"))
               insDoc(aux4, gLnk("Engines", "", "namespaceEngines.html"))
             insDoc(aux3, gLnk("Examples", "", "examples_Kernel.html"))


/*! Data structures
*/
         insDoc(aux1, gLnk("Data Structures", "", "annotated.html"))

/*!    insDoc(aux1, gLnk("SALOME_ModuleCatalog::Acomponent", "", "interfaceSALOME__ModuleCatalog_1_1Acomponent.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeComment", "", "interfaceSALOMEDS_1_1AttributeComment.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeDrawable", "", "interfaceSALOMEDS_1_1AttributeDrawable.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeExpandable", "", "interfaceSALOMEDS_1_1AttributeExpandable.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeInteger", "", "interfaceSALOMEDS_1_1AttributeInteger.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeIOR", "", "interfaceSALOMEDS_1_1AttributeIOR.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeLocalID", "", "interfaceSALOMEDS_1_1AttributeLocalID.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeName", "", "interfaceSALOMEDS_1_1AttributeName.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeOpened", "", "interfaceSALOMEDS_1_1AttributeOpened.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributePersistentRef", "", "interfaceSALOMEDS_1_1AttributePersistentRef.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributePixMap", "", "interfaceSALOMEDS_1_1AttributePixMap.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributePythonObject", "", "interfaceSALOMEDS_1_1AttributePythonObject.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeReal", "", "interfaceSALOMEDS_1_1AttributeReal.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeSelectable", "", "interfaceSALOMEDS_1_1AttributeSelectable.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeSequenceOfInteger", "", "interfaceSALOMEDS_1_1AttributeSequenceOfInteger.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeSequenceOfReal", "", "interfaceSALOMEDS_1_1AttributeSequenceOfReal.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeStudyProperties", "", "interfaceSALOMEDS_1_1AttributeStudyProperties.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfInteger", "", "interfaceSALOMEDS_1_1AttributeTableOfInteger.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfInteger::IncorrectArgumentLength", "", "exceptionSALOMEDS_1_1AttributeTableOfInteger_1_1IncorrectArgumentLength.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfInteger::IncorrectIndex", "", "exceptionSALOMEDS_1_1AttributeTableOfInteger_1_1IncorrectIndex.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfReal", "", "interfaceSALOMEDS_1_1AttributeTableOfReal.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfReal::IncorrectArgumentLength", "", "exceptionSALOMEDS_1_1AttributeTableOfReal_1_1IncorrectArgumentLength.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfReal::IncorrectIndex", "", "exceptionSALOMEDS_1_1AttributeTableOfReal_1_1IncorrectIndex.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfString", "", "interfaceSALOMEDS_1_1AttributeTableOfString.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfString::IncorrectArgumentLength", "", "exceptionSALOMEDS_1_1AttributeTableOfString_1_1IncorrectArgumentLength.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfString::IncorrectIndex", "", "exceptionSALOMEDS_1_1AttributeTableOfString_1_1IncorrectIndex.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTarget", "", "interfaceSALOMEDS_1_1AttributeTarget.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTextColor", "", "interfaceSALOMEDS_1_1AttributeTextColor.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTextHighlightColor", "", "interfaceSALOMEDS_1_1AttributeTextHighlightColor.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTreeNode", "", "interfaceSALOMEDS_1_1AttributeTreeNode.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeUserID", "", "interfaceSALOMEDS_1_1AttributeUserID.html"))
       insDoc(aux1, gLnk("SALOMEDS::Callback", "", "interfaceSALOMEDS_1_1Callback.html"))
       insDoc(aux1, gLnk("SALOMEDS::ChildIterator", "", "interfaceSALOMEDS_1_1ChildIterator.html"))
       insDoc(aux1, gLnk("SALOMEDS::Color", "", "structSALOMEDS_1_1Color.html"))
       insDoc(aux1, gLnk("Engines::Component", "", "interfaceEngines_1_1Component.html"))
       insDoc(aux1, gLnk("Engines::Container", "", "interfaceEngines_1_1Container.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::DefinitionInterface", "", "structSALOME__ModuleCatalog_1_1DefinitionInterface.html"))
       insDoc(aux1, gLnk("SALOMEDS::Driver", "", "interfaceSALOMEDS_1_1Driver.html"))
       insDoc(aux1, gLnk("SALOME::ExceptionStruct", "", "structSALOME_1_1ExceptionStruct.html"))
       insDoc(aux1, gLnk("SALOMEDS::GenericAttribute", "", "interfaceSALOMEDS_1_1GenericAttribute.html"))
       insDoc(aux1, gLnk("SALOMEDS::GenericAttribute::LockProtection", "", "exceptionSALOMEDS_1_1GenericAttribute_1_1LockProtection.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::IAPP_Affich", "", "structSALOME__ModuleCatalog_1_1IAPP__Affich.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::ModuleCatalog", "", "interfaceSALOME__ModuleCatalog_1_1ModuleCatalog.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::NotFound", "", "exceptionSALOME__ModuleCatalog_1_1NotFound.html"))
       insDoc(aux1, gLnk("SALOMEDS::NotImplemented", "", "exceptionSALOMEDS_1_1NotImplemented.html"))
       insDoc(aux1, gLnk("SALOME::SALOME_Exception", "", "exceptionSALOME_1_1SALOME__Exception.html"))
       insDoc(aux1, gLnk("SALOMEDS::SComponent", "", "interfaceSALOMEDS_1_1SComponent.html"))
       insDoc(aux1, gLnk("SALOMEDS::SComponentIterator", "", "interfaceSALOMEDS_1_1SComponentIterator.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::Service", "", "structSALOME__ModuleCatalog_1_1Service.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::ServicesParameter", "", "structSALOME__ModuleCatalog_1_1ServicesParameter.html"))
       insDoc(aux1, gLnk("SALOME::Session", "", "interfaceSALOME_1_1Session.html"))
       insDoc(aux1, gLnk("SALOME::Session::GUIActive", "", "exceptionSALOME_1_1Session_1_1GUIActive.html"))
       insDoc(aux1, gLnk("SALOME::Session::RunningStudies", "", "exceptionSALOME_1_1Session_1_1RunningStudies.html"))
       insDoc(aux1, gLnk("SALOMEDS::SObject", "", "interfaceSALOMEDS_1_1SObject.html"))
       insDoc(aux1, gLnk("SALOME::StatSession", "", "structSALOME_1_1StatSession.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study", "", "interfaceSALOMEDS_1_1Study.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyCommentError", "", "exceptionSALOMEDS_1_1Study_1_1StudyCommentError.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyInvalidComponent", "", "exceptionSALOMEDS_1_1Study_1_1StudyInvalidComponent.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyInvalidContext", "", "exceptionSALOMEDS_1_1Study_1_1StudyInvalidContext.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyInvalidDirectory", "", "exceptionSALOMEDS_1_1Study_1_1StudyInvalidDirectory.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyNameAlreadyUsed", "", "exceptionSALOMEDS_1_1Study_1_1StudyNameAlreadyUsed.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyNameError", "", "exceptionSALOMEDS_1_1Study_1_1StudyNameError.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyObjectAlreadyExists", "", "exceptionSALOMEDS_1_1Study_1_1StudyObjectAlreadyExists.html"))
       insDoc(aux1, gLnk("SALOMEDS::StudyBuilder", "", "interfaceSALOMEDS_1_1StudyBuilder.html"))
       insDoc(aux1, gLnk("SALOMEDS::StudyBuilder::LockProtection", "", "exceptionSALOMEDS_1_1StudyBuilder_1_1LockProtection.html"))
       insDoc(aux1, gLnk("SALOMEDS::StudyManager", "", "interfaceSALOMEDS_1_1StudyManager.html"))
       insDoc(aux1, gLnk("SALOMEDS::UseCaseBuilder", "", "interfaceSALOMEDS_1_1UseCaseBuilder.html"))
       insDoc(aux1, gLnk("SALOMEDS::UseCaseIterator", "", "interfaceSALOMEDS_1_1UseCaseIterator.html"))
*/
         insDoc(aux1, gLnk("Class Hierarchy", "", "hierarchy.html"))

/*!    insDoc(aux1, gLnk("SALOME_ModuleCatalog::Acomponent", "", "interfaceSALOME__ModuleCatalog_1_1Acomponent.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfInteger::IncorrectArgumentLength", "", "exceptionSALOMEDS_1_1AttributeTableOfInteger_1_1IncorrectArgumentLength.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfInteger::IncorrectIndex", "", "exceptionSALOMEDS_1_1AttributeTableOfInteger_1_1IncorrectIndex.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfReal::IncorrectArgumentLength", "", "exceptionSALOMEDS_1_1AttributeTableOfReal_1_1IncorrectArgumentLength.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfReal::IncorrectIndex", "", "exceptionSALOMEDS_1_1AttributeTableOfReal_1_1IncorrectIndex.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfString::IncorrectArgumentLength", "", "exceptionSALOMEDS_1_1AttributeTableOfString_1_1IncorrectArgumentLength.html"))
       insDoc(aux1, gLnk("SALOMEDS::AttributeTableOfString::IncorrectIndex", "", "exceptionSALOMEDS_1_1AttributeTableOfString_1_1IncorrectIndex.html"))
       insDoc(aux1, gLnk("SALOMEDS::Callback", "", "interfaceSALOMEDS_1_1Callback.html"))
       insDoc(aux1, gLnk("SALOMEDS::ChildIterator", "", "interfaceSALOMEDS_1_1ChildIterator.html"))
       insDoc(aux1, gLnk("SALOMEDS::Color", "", "structSALOMEDS_1_1Color.html"))
  aux2 = insFld(aux1, gFld("Engines::Component", "", "interfaceEngines_1_1Component.html"))
       insDoc(aux1, gLnk("Engines::Container", "", "interfaceEngines_1_1Container.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::DefinitionInterface", "", "structSALOME__ModuleCatalog_1_1DefinitionInterface.html"))
  aux2 = insFld(aux1, gFld("SALOMEDS::Driver", "", "interfaceSALOMEDS_1_1Driver.html"))
       insDoc(aux1, gLnk("SALOME::ExceptionStruct", "", "structSALOME_1_1ExceptionStruct.html"))
  aux2 = insFld(aux1, gFld("SALOMEDS::GenericAttribute", "", "interfaceSALOMEDS_1_1GenericAttribute.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeComment", "", "interfaceSALOMEDS_1_1AttributeComment.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeDrawable", "", "interfaceSALOMEDS_1_1AttributeDrawable.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeExpandable", "", "interfaceSALOMEDS_1_1AttributeExpandable.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeInteger", "", "interfaceSALOMEDS_1_1AttributeInteger.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeIOR", "", "interfaceSALOMEDS_1_1AttributeIOR.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeLocalID", "", "interfaceSALOMEDS_1_1AttributeLocalID.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeName", "", "interfaceSALOMEDS_1_1AttributeName.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeOpened", "", "interfaceSALOMEDS_1_1AttributeOpened.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributePersistentRef", "", "interfaceSALOMEDS_1_1AttributePersistentRef.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributePixMap", "", "interfaceSALOMEDS_1_1AttributePixMap.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributePythonObject", "", "interfaceSALOMEDS_1_1AttributePythonObject.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeReal", "", "interfaceSALOMEDS_1_1AttributeReal.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeSelectable", "", "interfaceSALOMEDS_1_1AttributeSelectable.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeSequenceOfInteger", "", "interfaceSALOMEDS_1_1AttributeSequenceOfInteger.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeSequenceOfReal", "", "interfaceSALOMEDS_1_1AttributeSequenceOfReal.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeStudyProperties", "", "interfaceSALOMEDS_1_1AttributeStudyProperties.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeTableOfInteger", "", "interfaceSALOMEDS_1_1AttributeTableOfInteger.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeTableOfReal", "", "interfaceSALOMEDS_1_1AttributeTableOfReal.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeTableOfString", "", "interfaceSALOMEDS_1_1AttributeTableOfString.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeTarget", "", "interfaceSALOMEDS_1_1AttributeTarget.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeTextColor", "", "interfaceSALOMEDS_1_1AttributeTextColor.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeTextHighlightColor", "", "interfaceSALOMEDS_1_1AttributeTextHighlightColor.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeTreeNode", "", "interfaceSALOMEDS_1_1AttributeTreeNode.html"))
         insDoc(aux2, gLnk("SALOMEDS::AttributeUserID", "", "interfaceSALOMEDS_1_1AttributeUserID.html"))
       insDoc(aux1, gLnk("SALOMEDS::GenericAttribute::LockProtection", "", "exceptionSALOMEDS_1_1GenericAttribute_1_1LockProtection.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::IAPP_Affich", "", "structSALOME__ModuleCatalog_1_1IAPP__Affich.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::ModuleCatalog", "", "interfaceSALOME__ModuleCatalog_1_1ModuleCatalog.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::NotFound", "", "exceptionSALOME__ModuleCatalog_1_1NotFound.html"))
       insDoc(aux1, gLnk("SALOMEDS::NotImplemented", "", "exceptionSALOMEDS_1_1NotImplemented.html"))
       insDoc(aux1, gLnk("SALOME::SALOME_Exception", "", "exceptionSALOME_1_1SALOME__Exception.html"))
       insDoc(aux1, gLnk("SALOMEDS::SComponentIterator", "", "interfaceSALOMEDS_1_1SComponentIterator.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::Service", "", "structSALOME__ModuleCatalog_1_1Service.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog::ServicesParameter", "", "structSALOME__ModuleCatalog_1_1ServicesParameter.html"))
       insDoc(aux1, gLnk("SALOME::Session", "", "interfaceSALOME_1_1Session.html"))
       insDoc(aux1, gLnk("SALOME::Session::GUIActive", "", "exceptionSALOME_1_1Session_1_1GUIActive.html"))
       insDoc(aux1, gLnk("SALOME::Session::RunningStudies", "", "exceptionSALOME_1_1Session_1_1RunningStudies.html"))
  aux2 = insFld(aux1, gFld("SALOMEDS::SObject", "", "interfaceSALOMEDS_1_1SObject.html"))
         insDoc(aux2, gLnk("SALOMEDS::SComponent", "", "interfaceSALOMEDS_1_1SComponent.html"))
       insDoc(aux1, gLnk("SALOME::StatSession", "", "structSALOME_1_1StatSession.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study", "", "interfaceSALOMEDS_1_1Study.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyCommentError", "", "exceptionSALOMEDS_1_1Study_1_1StudyCommentError.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyInvalidComponent", "", "exceptionSALOMEDS_1_1Study_1_1StudyInvalidComponent.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyInvalidContext", "", "exceptionSALOMEDS_1_1Study_1_1StudyInvalidContext.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyInvalidDirectory", "", "exceptionSALOMEDS_1_1Study_1_1StudyInvalidDirectory.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyNameAlreadyUsed", "", "exceptionSALOMEDS_1_1Study_1_1StudyNameAlreadyUsed.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyNameError", "", "exceptionSALOMEDS_1_1Study_1_1StudyNameError.html"))
       insDoc(aux1, gLnk("SALOMEDS::Study::StudyObjectAlreadyExists", "", "exceptionSALOMEDS_1_1Study_1_1StudyObjectAlreadyExists.html"))
       insDoc(aux1, gLnk("SALOMEDS::StudyBuilder", "", "interfaceSALOMEDS_1_1StudyBuilder.html"))
       insDoc(aux1, gLnk("SALOMEDS::StudyBuilder::LockProtection", "", "exceptionSALOMEDS_1_1StudyBuilder_1_1LockProtection.html"))
       insDoc(aux1, gLnk("SALOMEDS::StudyManager", "", "interfaceSALOMEDS_1_1StudyManager.html"))
       insDoc(aux1, gLnk("SALOMEDS::UseCaseBuilder", "", "interfaceSALOMEDS_1_1UseCaseBuilder.html"))
       insDoc(aux1, gLnk("SALOMEDS::UseCaseIterator", "", "interfaceSALOMEDS_1_1UseCaseIterator.html"))
*/
         insDoc(aux1, gLnk("Class methods list", "", "functions.html"))
/*!
aux1 = insFld(foldersTree, gFld("Namespace List", "", "namespaces.html"))
       insDoc(aux1, gLnk("Engines", "", "namespaceEngines.html"))
       insDoc(aux1, gLnk("SALOME", "", "namespaceSALOME.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog", "", "namespaceSALOME__ModuleCatalog.html"))
       insDoc(aux1, gLnk("SALOMEDS", "", "namespaceSALOMEDS.html"))
*/
         insDoc(aux1, gLnk("Namespace Members", "", "namespacemembers.html"))

         insDoc(aux1, gLnk("File List", "", "files.html"))
      
/*!
       insDoc(aux1, gLnk("SALOME_Component.idl", "", "SALOME__Component_8idl.html"))
       insDoc(aux1, gLnk("SALOME_Exception.idl", "", "SALOME__Exception_8idl.html"))
       insDoc(aux1, gLnk("SALOME_ModuleCatalog.idl", "", "SALOME__ModuleCatalog_8idl.html"))
       insDoc(aux1, gLnk("SALOME_Session.idl", "", "SALOME__Session_8idl.html"))
       insDoc(aux1, gLnk("SALOMEDS.idl", "", "SALOMEDS_8idl.html"))
       insDoc(aux1, gLnk("SALOMEDS_Attributes.idl", "", "SALOMEDS__Attributes_8idl.html"))
*/

aux1 = insFld(foldersTree, gFld("IDL/Python mapping", ""))
         insDoc(aux1, gLnk("Mapping of IDL definitions to Python language", "", "mapping.html"))
         insDoc(aux1, gLnk("Mapping of SALOME IDL definitions to Python language", "", "page2.html"))
 
/*!  insDoc(foldersTree, gLnk("Graphical Class Hierarchy", "", "inherits.html"))
*/
aux1 = insFld(foldersTree, gFld("Naming service", ""))
         insDoc(aux1, gLnk("Naming Service Description ", "", "overview_Naming.html"))
         insDoc(aux1, gLnk("Salome_NamingService Class Reference", "", "classSALOME__NamingService.html"))
         insDoc(aux1, gLnk("Examples", "", "examples_Naming.html"))
aux1 = insFld(foldersTree, gFld("Life Cycle", ""))
         insDoc(aux1, gLnk("Life Cycle Service Description ", "", "overview_Life_Cycle.html"))
         insDoc(aux1, gLnk("Salome_LifeCycleCorba Class Reference", "", "classSALOME__LifeCycleCORBA.html"))
         insDoc(aux1, gLnk("Examples", "", "examples_Life_cycle.html"))


