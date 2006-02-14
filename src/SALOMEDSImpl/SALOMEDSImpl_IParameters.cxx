// Copyright (C) 2005  OPEN CASCADE, CEA/DEN, EDF R&D, PRINCIPIA R&D
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either 
// version 2.1 of the License.
// 
// This library is distributed in the hope that it will be useful 
// but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public  
// License along with this library; if not, write to the Free Software 
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
// See http://www.salome-platform.org/
//
#include "SALOMEDSImpl_IParameters.hxx"
#include <utilities.h>

#include <TCollection_AsciiString.hxx>

#include "SALOMEDSImpl_SObject.hxx"
#include "SALOMEDSImpl_ChildIterator.hxx"

using namespace std;

#define _AP_LISTS_LIST_ "AP_LISTS_LIST"
#define _AP_ENTRIES_LIST_ "AP_ENTRIES_LIST"
#define _AP_PROPERTIES_LIST_ "AP_PROPERTIES_LIST"
#define _AP_DUMP_PYTHON_ "AP_DUMP_PYTHON"

/*!
  Constructor
*/
SALOMEDSImpl_IParameters::SALOMEDSImpl_IParameters(const Handle(SALOMEDSImpl_AttributeParameter)& ap)
{
  if(ap.IsNull()) return;
  _ap = ap;
}

SALOMEDSImpl_IParameters::~SALOMEDSImpl_IParameters()
{}

int SALOMEDSImpl_IParameters::append(const string& listName, const string& value)
{
  if(_ap.IsNull()) return -1;
  vector<string> v;
  if(!_ap->IsSet(listName, PT_STRARRAY)) {
    if(!_ap->IsSet(_AP_LISTS_LIST_, PT_STRARRAY)) _ap->SetStrArray(_AP_LISTS_LIST_, v);
    if(listName != _AP_ENTRIES_LIST_ && 
       listName != _AP_PROPERTIES_LIST_) {
      append(_AP_LISTS_LIST_, listName);
    }
    _ap->SetStrArray(listName, v);
  }
  v = _ap->GetStrArray(listName);
  v.push_back(value);
  _ap->SetStrArray(listName, v);
  return (v.size()-1);
}

int SALOMEDSImpl_IParameters::nbValues(const string& listName)
{
  if(_ap.IsNull()) return -1;
  if(!_ap->IsSet(listName, PT_STRARRAY)) return 0;
  vector<string> v = _ap->GetStrArray(listName);
  return v.size();
}

vector<string> SALOMEDSImpl_IParameters::getValues(const string& listName)
{
  vector<string> v;
  if(_ap.IsNull()) return v;
  if(!_ap->IsSet(listName, PT_STRARRAY)) return v;
  return _ap->GetStrArray(listName);
}


string SALOMEDSImpl_IParameters::getValue(const string& listName, int index)
{
  if(_ap.IsNull()) return "";
  if(!_ap->IsSet(listName, PT_STRARRAY)) return "";
  vector<string> v = _ap->GetStrArray(listName);
  if(index >= v.size()) return ""; 
  return v[index];
}

vector<string> SALOMEDSImpl_IParameters::getLists()
{
  vector<string> v;
  if(!_ap->IsSet(_AP_LISTS_LIST_, PT_STRARRAY)) return v;
  return _ap->GetStrArray(_AP_LISTS_LIST_);
}

void SALOMEDSImpl_IParameters::setParameter(const string& entry, const string& parameterName, const string& value)
{
  if(_ap.IsNull()) return;
  vector<string> v;
  if(!_ap->IsSet(entry, PT_STRARRAY)) {
    append(_AP_ENTRIES_LIST_, entry); //Add the entry to the internal list of entries
    _ap->SetStrArray(entry, v);
  }
  v = _ap->GetStrArray(entry);
  v.push_back(parameterName);
  v.push_back(value);
  _ap->SetStrArray(entry, v);
}


string SALOMEDSImpl_IParameters::getParameter(const string& entry, const string& parameterName)
{
  if(_ap.IsNull()) return "";
  if(!_ap->IsSet(entry, PT_STRARRAY)) return "";
  vector<string> v = _ap->GetStrArray(entry);
  int length = v.size();
  for(int i = 0; i<length; i+=1) {
    if(v[i] == parameterName) return v[i+1];
  }
  return "";
}


vector<string> SALOMEDSImpl_IParameters::getAllParameterNames(const string& entry)
{
  vector<string> v, names;
  if(_ap.IsNull()) return v; 
  if(!_ap->IsSet(entry, PT_STRARRAY)) return v;
  v = _ap->GetStrArray(entry);
  int length = v.size();
  for(int i = 0; i<length; i+=2) {
    names.push_back(v[i]);
  }
  return names;
}

vector<string> SALOMEDSImpl_IParameters::getAllParameterValues(const string& entry)
{
  vector<string> v, values;
  if(_ap.IsNull()) return v; 
  if(!_ap->IsSet(entry, PT_STRARRAY)) return v;
  v = _ap->GetStrArray(entry);
  int length = v.size();
  for(int i = 1; i<length; i+=2) {
    values.push_back(v[i]);
  }
  return values; 
}

int SALOMEDSImpl_IParameters::getNbParameters(const string& entry)
{
  if(_ap.IsNull()) return -1;
  if(!_ap->IsSet(entry, PT_STRARRAY)) return -1;
  return  _ap->GetStrArray(entry).size()/2;
}

vector<string> SALOMEDSImpl_IParameters::getEntries()
{
  vector<string> v;
  if(_ap.IsNull()) return v;
  if(!_ap->IsSet(_AP_ENTRIES_LIST_, PT_STRARRAY)) return v;
  return _ap->GetStrArray(_AP_ENTRIES_LIST_);
}

void SALOMEDSImpl_IParameters::setProperty(const string& name, const std::string& value)
{
  if(_ap.IsNull()) return;
  if(!_ap->IsSet(name, PT_STRING)) {
    append(_AP_PROPERTIES_LIST_, name); //Add the property to the internal list of properties
  }
  _ap->SetString(name, value);
}

string SALOMEDSImpl_IParameters::getProperty(const string& name)
{
  if(_ap.IsNull()) return "";
  if(!_ap->IsSet(name, PT_STRING)) return "";
  return _ap->GetString(name);
}

vector<string> SALOMEDSImpl_IParameters::getProperties()
{
  vector<string> v;
  if(_ap.IsNull()) return v;
  if(!_ap->IsSet(_AP_PROPERTIES_LIST_, PT_STRARRAY)) return v;
  return _ap->GetStrArray(_AP_PROPERTIES_LIST_);
}


bool SALOMEDSImpl_IParameters::isDumpPython(const Handle(SALOMEDSImpl_Study)& study, const string& theID)
{
  string anID;
  if(theID == "") anID = getDefaultVisualComponent();
  else anID = theID;

  Handle(SALOMEDSImpl_AttributeParameter) ap = study->GetCommonParameters((char*)anID.c_str(), 0);
  if(ap.IsNull()) return false;
  if(!ap->IsSet(_AP_DUMP_PYTHON_, PT_BOOLEAN)) return false;
  return (bool)ap->GetBool(_AP_DUMP_PYTHON_);
}


int SALOMEDSImpl_IParameters::getLastSavePoint(const Handle(SALOMEDSImpl_Study)& study, const string& theID)
{
  string anID;
  if(theID == "") anID = getDefaultVisualComponent();
  else anID = theID;


  Handle(SALOMEDSImpl_SObject) so = study->FindComponent((char*)anID.c_str());
  if(so.IsNull()) return -1;

  Handle(SALOMEDSImpl_StudyBuilder) builder = study->NewBuilder();
  Handle(SALOMEDSImpl_ChildIterator) anIter ( study->NewChildIterator( so ) );
  int tag = -1;
  for(; anIter->More(); anIter->Next())
  {
    Handle(SALOMEDSImpl_SObject) val( anIter->Value() );
    Handle(SALOMEDSImpl_GenericAttribute) genAttr;
    if(builder->FindAttribute(val, genAttr, "AttributeParameter")) tag = val->Tag();
  }

  return tag;
}



string SALOMEDSImpl_IParameters::getStudyScript(const Handle(SALOMEDSImpl_Study)& study, int savePoint, const std::string& theID)
{
  string anID;
  if(theID == "") anID = getDefaultVisualComponent();
  else anID = theID;

  Handle(SALOMEDSImpl_AttributeParameter) ap = study->GetCommonParameters((char*)anID.c_str(), savePoint);
  SALOMEDSImpl_IParameters ip(ap);

  string dump("");

  dump += "import iparameters\n";
  dump += "ipar = iparameters.IParameters(salome.myStudy.GetCommonParameters(\""+anID+"\", 1))\n\n";
  
  
  vector<string> v = ip.getProperties();
  if(v.size() > 0) {
    dump += "#Set up visual properties:\n";
    for(int i = 0; i<v.size(); i++) {
      string prp = ip.getProperty(v[i]);
      dump += "ipar.setProperty(\""+v[i]+"\", \""+prp+"\")\n";
    }
  }

  v = ip.getLists();
  if(v.size() > 0) {
    dump += "#Set up lists:\n";
    for(int i = 0; i<v.size(); i++) {
      vector<string> lst = ip.getValues(v[i]);
      dump += "# fill list "+v[i]+"\n";
      for(int j = 0; j < lst.size(); j++)
	dump += "ipar.append(\""+v[i]+"\", \""+lst[j]+"\")\n";
    }
  }

  return dump;
}

string SALOMEDSImpl_IParameters::getDefaultScript(const Handle(SALOMEDSImpl_Study)& study, 
					      const string& moduleName, 
					      const string& shift, 
					      const string& theID)
{
  string anID;
  if(theID == "") anID = getDefaultVisualComponent();
  else anID = theID;

  string dump("");

  int savePoint = SALOMEDSImpl_IParameters::getLastSavePoint(study, anID);
  if(savePoint < 0) return dump;
  SALOMEDSImpl_IParameters ip = SALOMEDSImpl_IParameters(study->GetCommonParameters(anID.c_str(), savePoint));
  if(!isDumpPython(study)) return dump;

  Handle(SALOMEDSImpl_AttributeParameter) ap = study->GetModuleParameters(anID.c_str(), moduleName.c_str(), savePoint);
  ip = SALOMEDSImpl_IParameters(ap);


  dump += shift +"import iparameters\n";
  dump += shift + "ipar = iparameters.IParameters(theStudy.GetModuleParameters(\""+anID+"\", \""+moduleName+"\", 1))\n\n";
  
  vector<string> v = ip.getProperties();
  if(v.size() > 0) {
    dump += shift +"#Set up visual properties:\n";
    for(int i = 0; i<v.size(); i++) {
      string prp = ip.getProperty(v[i]);
      dump += shift +"ipar.setProperty(\""+v[i]+"\", \""+prp+"\")\n";
    }
  }

  v = ip.getLists();
  if(v.size() > 0) {
    dump +=  shift +"#Set up lists:\n";
    for(int i = 0; i<v.size(); i++) {
      vector<string> lst = ip.getValues(v[i]);
      dump += shift +"# fill list "+v[i]+"\n";
      for(int j = 0; j < lst.size(); j++)
	dump += shift +"ipar.append(\""+v[i]+"\", \""+lst[j]+"\")\n";
    }
  }

  v = ip.getEntries();
  if(v.size() > 0) {
    dump += shift + "#Set up entries:\n";
    for(int i = 0; i<v.size(); i++) {
      vector<string> names = ip.getAllParameterNames(v[i]);
      vector<string> values = ip.getAllParameterValues(v[i]);
      Handle(SALOMEDSImpl_SObject) so = study->FindObjectID((char*)v[i].c_str());
      string so_name("");
      if(!so.IsNull()) so_name = so->GetName().ToCString();
      dump += shift + "# set up entry " + v[i] +" ("+so_name+")" + " parameters" + "\n";
      for(int j = 0; j < names.size() && j < values.size(); j++)
	dump += shift + "ipar.setParameter(\"" + v[i] + "\", \"" + names[j] + "\", \"" + values[j] + "\")\n";
    }
  }
  
  return dump;  
}


string SALOMEDSImpl_IParameters::getDefaultVisualComponent()
{
  return "Interface Applicative";
}


