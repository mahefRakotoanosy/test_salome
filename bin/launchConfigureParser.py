# Copyright (C) 2005  OPEN CASCADE, CEA, EDF R&D, LEG
#           PRINCIPIA R&D, EADS CCR, Lip6, BV, CEDRAT
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License.
#
# This library is distributed in the hope that it will be useful
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

import os, glob, string, sys, re
import xml.sax
import optparse
import types

# names of tags in XML configuration file
doc_tag = "document"
sec_tag = "section"
par_tag = "parameter"

# names of attributes in XML configuration file
nam_att = "name"
val_att = "value"

# certain values in XML configuration file ("launch" section)
lanch_nam      = "launch"
help_nam       = "help"
gui_nam        = "gui"
splash_nam     = "splash"
logger_nam     = "logger"
xterm_nam      = "xterm"
file_nam       = "file"
portkill_nam   = "portkill"
killall_nam    = "killall"
modules_nam    = "modules"
embedded_nam   = "embedded"
standalone_nam = "standalone"
key_nam        = "key"
interp_nam     = "interp"
except_nam     = "noexcepthandler"
terminal_nam   = "terminal"

# values in XML configuration file giving specific module parameters (<module_name> section)
# which are stored in opts with key <module_name>_<parameter> (eg SMESH_plugins)
plugins_nam    = "plugins"

# values passed as arguments, NOT read from XML config file, but set from within this script
appname_nam    = "appname"
port_nam       = "port"
salomeappname  = "SalomeApp"
script_nam     = "pyscript"

# values of boolean type (must be '0' or '1').
# xml_parser.boolValue() is used for correct setting
boolKeys = ( gui_nam, splash_nam, logger_nam, file_nam, xterm_nam, portkill_nam, killall_nam, except_nam )
intKeys = ( interp_nam, )

# values of list type
listKeys = ( embedded_nam, key_nam, modules_nam, standalone_nam, plugins_nam )

###
# Get the application version
# Uses GUI_ROOT_DIR (or KERNEL_ROOT_DIR in batch mode) +/bin/salome/VERSION file
###
def version():
    try:
        filename = None
        root_dir = os.environ.get( 'KERNEL_ROOT_DIR', '' ) # KERNEL_ROOT_DIR or "" if not found
        if root_dir and os.path.exists( root_dir + "/bin/salome/VERSION" ):
            filename = root_dir + "/bin/salome/VERSION"
        root_dir = os.environ.get( 'GUI_ROOT_DIR', '' )    # GUI_ROOT_DIR "" if not found
        if root_dir and os.path.exists( root_dir + "/bin/salome/VERSION" ):
            filename = root_dir + "/bin/salome/VERSION"
        if filename:
            str = open( filename, "r" ).readline() # str = "THIS IS SALOME - SALOMEGUI VERSION: 3.0.0"
            match = re.search( r':\s+([a-zA-Z0-9.]+)\s*$', str )
            if match :
                return match.group( 1 )
    except:
        pass
    return ''

###
# Calculate and return configuration file unique ID
# For example: for SALOME version 3.1.0a1 the id is 300999701
###
def version_id( fname ):
    vers = fname.split(".")
    major   = int(vers[0])
    minor   = int(vers[1])
    mr = re.search(r'^([0-9]+)([A-Za-z]?)([0-9]*)',vers[2])
    release = dev = 0
    if mr:
        release = int(mr.group(1))
        dev1 = dev2 = 0
        if len(mr.group(2)): dev1 = ord(mr.group(2))
        if len(mr.group(3)): dev2 = int(mr.group(3))
        dev = dev1 * 100 + dev2
    else:
        return None
    ver = major
    ver = ver * 100 + minor
    ver = ver * 100 + release
    ver = ver * 10000
    if dev > 0: ver = ver - 10000 + dev
    return ver

###
# Get user configuration file name
###
def userFile(appname):
    v = version()
    if not v:
        return ""        # not unknown version
    filename = "%s/.%src.%s" % (os.environ['HOME'], appname, v)
    if os.path.exists(filename):
        return filename  # user preferences file for the current version exists
    # initial id
    id0 = version_id( v )
    # get all existing user preferences files
    files = glob.glob( os.environ['HOME'] + "/." + appname + "rc.*" )
    f2v = {}
    for file in files:
        match = re.search( r'\.%src\.([a-zA-Z0-9.]+)$'%appname, file )
        if match: f2v[file] = match.group(1)
    last_file = ""
    last_version = 0
    for file in f2v:
        ver = version_id( f2v[file] )
        if ver and abs(last_version-id0) > abs(ver-id0):
            last_version = ver
            last_file = file
    return last_file

# --

_verbose = None

def verbose():
    global _verbose
    # verbose has already been called
    if _verbose is not None:
        return _verbose
    # first time
    try:
        from os import getenv
        _verbose = int(getenv('SALOME_VERBOSE'))
    except:
        _verbose = 0
        pass
    #
    return _verbose

def setVerbose(level):
    global _verbose
    _verbose = level
    return

# -----------------------------------------------------------------------------

###
# XML reader for launch configuration file usage
###

section_to_skip = ""

class xml_parser:
    def __init__(self, fileName, _opts ):
        if verbose(): print "Configure parser: processing %s ..." % fileName
        self.space = []
        self.opts = _opts
        self.section = section_to_skip
        parser = xml.sax.make_parser()
        parser.setContentHandler(self)
        parser.parse(fileName)
        pass

    def boolValue( self, str ):
        strloc = str
        if isinstance(strloc, types.UnicodeType):
            strloc = strloc.encode().strip().lower()
        if isinstance(strloc, types.StringType):
            if strloc in   ("1", "yes", "y", "on", "true", "ok"):
                return True
            elif strloc in ("0", "no", "n", "off", "false", "cancel"):
                return False
            else:
                return None
        else:
            return strloc
        pass

    def intValue( self, str ):
        strloc = str
        if isinstance(strloc, types.UnicodeType):
            strloc = strloc.encode().strip().lower()
        if isinstance(strloc, types.StringType):
            if strloc in   ("1", "yes", "y", "on", "true", "ok"):
                return 1
            elif strloc in ("0", "no", "n", "off", "false", "cancel"):
                return 0
            else:
                return string.atoi(strloc)
        else:
            return strloc
        pass

    def startElement(self, name, attrs):
        self.space.append(name)
        self.current = None

        # if we are analyzing "section" element and its "name" attribute is
        # either "launch" or module name -- set section_name
        if self.space == [doc_tag, sec_tag] and nam_att in attrs.getNames():
            section_name = attrs.getValue( nam_att )
            if section_name == lanch_nam:
                self.section = section_name # launch section
            elif self.opts.has_key( modules_nam ) and \
                 section_name in self.opts[ modules_nam ]:
                self.section = section_name # <module> section
            else:
                self.section = section_to_skip # any other section
            pass

        # if we are analyzing "parameter" elements - children of either
        # "section launch" or "section "<module>"" element, then store them
        # in self.opts assiciative array (key = [<module>_ + ] value of "name" attribute)
        elif self.section != section_to_skip           and \
             self.space == [doc_tag, sec_tag, par_tag] and \
             nam_att in attrs.getNames()               and \
             val_att in attrs.getNames():
            nam = attrs.getValue( nam_att )
            val = attrs.getValue( val_att )
            if self.section == lanch_nam: # key for launch section
                key = nam
            else:                         # key for <module> section
                key = self.section + "_" + nam
            if nam in boolKeys:
                self.opts[key] = self.boolValue( val )  # assign boolean value: 0 or 1
            elif nam in intKeys:
                self.opts[key] = self.intValue( val )  # assign integer value
            elif nam in listKeys:
                self.opts[key] = val.split( ',' )       # assign list value: []
            else:
                self.opts[key] = val;
            pass
        pass

    def endElement(self, name):
        p = self.space.pop()
        self.current = None
        if self.section != section_to_skip and name == sec_tag:
            self.section = section_to_skip
        pass

    def characters(self, content):
        pass

    def processingInstruction(self, target, data):
        pass

    def setDocumentLocator(self, locator):
        pass

    def startDocument(self):
        self.read = None
        pass

    def endDocument(self):
        self.read = None
        pass

# -----------------------------------------------------------------------------

booleans = { '1': True , 'yes': True , 'y': True , 'on' : True , 'true' : True , 'ok'     : True,
             '0': False, 'no' : False, 'n': False, 'off': False, 'false': False, 'cancel' : False }

boolean_choices = booleans.keys()

def store_boolean (option, opt, value, parser, *args):
    if isinstance(value, types.StringType):
        try:
            value_conv = booleans[value.strip().lower()]
            for attribute in args:
                setattr(parser.values, attribute, value_conv)
        except KeyError:
            raise optparse.OptionValueError(
                "option %s: invalid boolean value: %s (choose from %s)"
                % (opt, value, boolean_choices))
    else:
        for attribute in args:
            setattr(parser.values, attribute, value)

def CreateOptionParser (theAdditionalOptions=[]):
    # GUI/Terminal. Default: GUI
    help_str = "Launch without GUI (in the terminal mode)."
    o_t = optparse.Option("-t",
                          "--terminal",
                          action="store_false",
                          dest="gui",
                          help=help_str)

    help_str = "Launch in GUI mode [default]."
    o_g = optparse.Option("-g",
                          "--gui",
                          action="store_true",
                          dest="gui",
                          help=help_str)

    # Show Desktop (inly in GUI mode). Default: True
    help_str  = "1 to activate GUI desktop [default], "
    help_str += "0 to not activate GUI desktop (Session_Server starts, but GUI is not shown). "
    help_str += "Ignored in the terminal mode."
    o_d = optparse.Option("-d",
                          "--show-desktop",
                          metavar="<1/0>",
                          #type="choice", choices=boolean_choices,
                          type="string",
                          action="callback", callback=store_boolean, callback_args=('desktop',),
                          dest="desktop",
                          help=help_str)
    help_str  = "Do not activate GUI desktop (Session_Server starts, but GUI is not shown). "
    help_str += "The same as --show-desktop=0."
    o_o = optparse.Option("-o",
                          "--hide-desktop",
                          action="store_false",
                          dest="desktop",
                          help=help_str)

    # Use logger or log-file. Default: nothing.
    help_str = "Redirect messages to the CORBA collector."
    #o4 = optparse.Option("-l", "--logger", action="store_true", dest="logger", help=help_str)
    o_l = optparse.Option("-l",
                          "--logger",
                          action="store_const", const="CORBA",
                          dest="log_file",
                          help=help_str)
    help_str = "Redirect messages to the <log-file>"
    o_f = optparse.Option("-f",
                          "--log-file",
                          metavar="<log-file>",
                          type="string",
                          action="store",
                          dest="log_file",
                          help=help_str)

    # Execute python scripts. Default: None.
    help_str  = "Python script(s) to be imported. Python scripts are imported "
    help_str += "in the order of their appearance. In GUI mode python scripts "
    help_str += "are imported in the embedded python interpreter of current study, "
    help_str += "otherwise in an external python interpreter"
    o_u = optparse.Option("-u",
                          "--execute",
                          metavar="<script1,script2,...>",
                          type="string",
                          action="append",
                          dest="py_scripts",
                          help=help_str)

    # Configuration XML file. Default: $(HOME)/.SalomeApprc.$(version).
    help_str  = "Parse application settings from the <file> "
    help_str += "instead of default $(HOME)/.SalomeApprc.$(version)"
    o_r = optparse.Option("-r",
                          "--resources",
                          metavar="<file>",
                          type="string",
                          action="store",
                          dest="resources",
                          help=help_str)

    # Use own xterm for each server. Default: False.
    help_str = "Launch each SALOME server in own xterm console"
    o_x = optparse.Option("-x",
                          "--xterm",
                          action="store_true",
                          dest="xterm",
                          help=help_str)

    # Modules. Default: Like in configuration files.
    help_str  = "SALOME modules list (where <module1>, <module2> are the names "
    help_str += "of SALOME modules which should be available in the SALOME session)"
    o_m = optparse.Option("-m",
                          "--modules",
                          metavar="<module1,module2,...>",
                          type="string",
                          action="append",
                          dest="modules",
                          help=help_str)

    # Embedded servers. Default: Like in configuration files.
    help_str  = "CORBA servers to be launched in the Session embedded mode. "
    help_str += "Valid values for <serverN>: registry, study, moduleCatalog, "
    help_str += "cppContainer [by default the value from the configuration files is used]"
    o_e = optparse.Option("-e",
                          "--embedded",
                          metavar="<server1,server2,...>",
                          type="string",
                          action="append",
                          dest="embedded",
                          help=help_str)

    # Standalone servers. Default: Like in configuration files.
    help_str  = "CORBA servers to be launched in the standalone mode (as separate processes). "
    help_str += "Valid values for <serverN>: registry, study, moduleCatalog, "
    help_str += "cppContainer, pyContainer, [by default the value from the configuration files is used]"
    o_s = optparse.Option("-s",
                          "--standalone",
                          metavar="<server1,server2,...>",
                          type="string",
                          action="append",
                          dest="standalone",
                          help=help_str)

    # Kill with port. Default: False.
    help_str = "Kill SALOME with the current port"
    o_p = optparse.Option("-p",
                          "--portkill",
                          action="store_true",
                          dest="portkill",
                          help=help_str)

    # Kill all. Default: False.
    help_str = "Kill all running SALOME sessions"
    o_k = optparse.Option("-k",
                          "--killall",
                          action="store_true",
                          dest="killall",
                          help=help_str)

    # Additional python interpreters. Default: 0.
    help_str  = "The number of additional external python interpreters to run. "
    help_str += "Each additional python interpreter is run in separate "
    help_str += "xterm session with properly set SALOME environment"
    o_i = optparse.Option("-i",
                          "--interp",
                          metavar="<N>",
                          type="int",
                          action="store",
                          dest="interp",
                          help=help_str)

    # Splash. Default: True.
    help_str  = "1 to display splash screen [default], "
    help_str += "0 to disable splash screen. "
    help_str += "This option is ignored in the terminal mode. "
    help_str += "It is also ignored if --show-desktop=0 option is used."
    o_z = optparse.Option("-z",
                          "--splash",
                          metavar="<1/0>",
                          #type="choice", choices=boolean_choices,
                          type="string",
                          action="callback", callback=store_boolean, callback_args=('splash',),
                          dest="splash",
                          help=help_str)

    # Catch exceptions. Default: True.
    help_str  = "1 (yes,true,on,ok) to enable centralized exception handling [default], "
    help_str += "0 (no,false,off,cancel) to disable centralized exception handling."
    o_c = optparse.Option("-c",
                          "--catch-exceptions",
                          metavar="<1/0>",
                          #type="choice", choices=boolean_choices,
                          type="string",
                          action="callback", callback=store_boolean, callback_args=('catch_exceptions',),
                          dest="catch_exceptions",
                          help=help_str)

    # All options
    opt_list = [o_t,o_g, # GUI/Terminal
                o_d,o_o, # Desktop
                o_l,o_f, # Use logger or log-file
                o_u,     # Execute python scripts
                o_r,     # Configuration XML file
                o_x,     # xterm
                o_m,     # Modules
                o_e,     # Embedded servers
                o_s,     # Standalone servers
                o_p,     # Kill with port
                o_k,     # Kill all
                o_i,     # Additional python interpreters
                o_z,     # Splash
                o_c]     # Catch exceptions

    #std_options = ["gui", "desktop", "log_file", "py_scripts", "resources",
    #               "xterm", "modules", "embedded", "standalone",
    #               "portkill", "killall", "interp", "splash",
    #               "catch_exceptions"]

    opt_list += theAdditionalOptions

    a_usage = "%prog [options] [STUDY_FILE]"
    version_str = "Salome %s" % version()
    pars = optparse.OptionParser(usage=a_usage, version=version_str, option_list=opt_list)

    return pars

# -----------------------------------------------------------------------------

###
# Get the environment
###

# this attribute is obsolete
args = []
def get_env(theAdditionalOptions=[], appname="SalomeApp"):
    ###
    # Collect launch configuration files:
    # - The environment variable "<appname>Config" (SalomeAppConfig) which can
    #   define a list of directories (separated by ':' or ';' symbol) is checked
    # - If the environment variable "<appname>Config" is not set, only
    #   ${GUI_ROOT_DIR}/share/salome/resources/gui is inspected
    # - ${GUI_ROOT_DIR}/share/salome/resources/gui directory is always inspected
    #   so it is not necessary to put it in the "<appname>Config" variable
    # - The directories which are inspected are checked for files "<appname?salomeappname>.xml"
    #  (SalomeApp.xml) which define SALOME configuration
    # - These directories are analyzed beginning from the last one in the list,
    #   so the first directory listed in "<appname>Config" environment variable 
    #   has higher priority: it means that if some configuration options
    #   is found in the next analyzed cofiguration file - it will be replaced
    # - The last configuration file which is parsed is user configuration file
    #   situated in the home directory: "~/.<appname>rc[.<version>]" (~/SalomeApprc.3.2.0)
    #   (if it exists)
    # - Command line options have the highest priority and replace options
    #   specified in configuration file(s)
    ###

    global args
    config_var = appname+'Config'

    # check KERNEL_ROOT_DIR
    try:
        kernel_root_dir=os.environ["KERNEL_ROOT_DIR"]
    except:
        print """
        For each SALOME module, the environment variable <moduleN>_ROOT_DIR must be set.
        KERNEL_ROOT_DIR is mandatory.
        """
        sys.exit(1)
        pass

    ############################
    # parse command line options
    pars = CreateOptionParser(theAdditionalOptions)
    (cmd_opts, cmd_args) = pars.parse_args(sys.argv[1:])
    ############################

    # set resources variable SalomeAppConfig if it is not set yet 
    dirs = []
    if os.getenv(config_var):
        dirs += re.split('[;|:]', os.getenv(config_var))
    if os.getenv("GUI_ROOT_DIR") and os.path.isdir( os.getenv("GUI_ROOT_DIR") + "/share/salome/resources/gui" ):
        dirs += [os.getenv("GUI_ROOT_DIR") + "/share/salome/resources/gui"]
    os.environ[config_var] = ":".join(dirs)

    dirs.reverse() # reverse order, like in "path" variable - FILO-style processing

    try:
        dirs.remove('') # to remove empty dirs if the variable terminate by ":" or if there are "::" inside
    except:
        pass
    
    _opts = {} # associative array of options to be filled

    # parse SalomeApp.xml files in directories specified by SalomeAppConfig env variable
    for dir in dirs:
        #filename = dir+'/'+appname+'.xml'
        filename = dir+'/'+salomeappname+'.xml'
        if not os.path.exists(filename):
            print "Configure parser: Warning : could not find configuration file %s" % filename
        else:
            try:
                p = xml_parser(filename, _opts)
                _opts = p.opts
            except:
                print "Configure parser: Error : can not read configuration file %s" % filename
            pass

    # parse user configuration file
    # It can be set via --resources=<file> command line option
    # or is given by default from ${HOME}/.<appname>rc.<version>
    # If user file for the current version is not found the nearest to it is used
    user_config = cmd_opts.resources
    if not user_config:
        user_config = userFile(appname)
    if not user_config or not os.path.exists(user_config):
        print "Configure parser: Warning : could not find user configuration file"
    else:
        try:
            p = xml_parser(user_config, _opts)
            _opts = p.opts
        except:
            print 'Configure parser: Error : can not read user configuration file'
            user_config = ""

    args = _opts

    args['user_config'] = user_config
    #print "User Configuration file: ", args['user_config']

    # set default values for options which are NOT set in config files
    for aKey in listKeys:
        if not args.has_key( aKey ):
            args[aKey]=[]

    for aKey in boolKeys:
        if not args.has_key( aKey ):
            args[aKey]=0

    if args[file_nam]:
        afile=args[file_nam]
        args[file_nam]=[afile]

    args[appname_nam] = appname

    # get the port number
    my_port = 2809
    try:
      file = open(os.environ["OMNIORB_CONFIG"], "r")
      s = file.read()
      while len(s):
        l = string.split(s, ":")
        if string.split(l[0], " ")[0] == "ORBInitRef" or string.split(l[0], " ")[0] == "InitRef" :
          my_port = int(l[len(l)-1])
          pass
        s = file.read()
        pass
    except:
      pass

    args[port_nam] = my_port

    ####################################################
    # apply command-line options to the arguments
    # each option given in command line overrides the option from xml config file
    #
    # Options: gui, desktop, log_file, py_scripts, resources,
    #          xterm, modules, embedded, standalone,
    #          portkill, killall, interp, splash,
    #          catch_exceptions

    # GUI/Terminal, Desktop, Splash, STUDY_HDF
    args["session_gui"] = False
    args["study_hdf"] = None
    if cmd_opts.gui is not None:
        args[gui_nam] = cmd_opts.gui
    if args[gui_nam]:
        args["session_gui"] = True
        if cmd_opts.desktop is not None:
            args["session_gui"] = cmd_opts.desktop
            args[splash_nam]    = cmd_opts.desktop
        if args["session_gui"]:
            if cmd_opts.splash is not None:
                args[splash_nam] = cmd_opts.splash
        if len(cmd_args) > 0:
            args["study_hdf"] = cmd_args[0]
    else:
        args["session_gui"] = False
        args[splash_nam] = False

    # Logger/Log file
    if cmd_opts.log_file is not None:
        if cmd_opts.log_file == 'CORBA':
            args[logger_nam] = True
        else:
            args[file_nam] = cmd_opts.log_file

    # Python scripts
    args[script_nam] = []
    if cmd_opts.py_scripts is not None:
        listlist = cmd_opts.py_scripts
        for listi in listlist:
            args[script_nam] += re.split( "[:;,]", listi)

    # xterm
    if cmd_opts.xterm is not None: args[xterm_nam] = cmd_opts.xterm

    # Modules
    if cmd_opts.modules is not None:
        args[modules_nam] = []
        listlist = cmd_opts.modules
        for listi in listlist:
            args[modules_nam] += re.split( "[:;,]", listi)
    else:
        # if --modules (-m) command line option is not given
        # try SALOME_MODULES environment variable
        if os.getenv( "SALOME_MODULES" ):
            args[modules_nam] = re.split( "[:;,]", os.getenv( "SALOME_MODULES" ) )
            pass

    # Embedded
    if cmd_opts.embedded is not None:
        args[embedded_nam] = []
        listlist = cmd_opts.embedded
        for listi in listlist:
            args[embedded_nam] += re.split( "[:;,]", listi)

    # Standalone
    if cmd_opts.standalone is not None:
        args[standalone_nam] = []
        listlist = cmd_opts.standalone
        standalone = []
        for listi in listlist:
            standalone += re.split( "[:;,]", listi)
        for serv in standalone:
            if args[embedded_nam].count(serv) <= 0:
                args[standalone_nam].append(serv)

    # Kill
    if cmd_opts.portkill is not None: args[portkill_nam] = cmd_opts.portkill
    if cmd_opts.killall  is not None: args[killall_nam]  = cmd_opts.killall

    # Interpreter
    if cmd_opts.interp is not None:
        args[interp_nam] = cmd_opts.interp

    # Exceptions
    if cmd_opts.catch_exceptions is not None:
        args[except_nam] = not cmd_opts.catch_exceptions

    ####################################################
    # Add <theAdditionalOptions> values to args
    for add_opt in theAdditionalOptions:
        cmd = "args[\"%s\"] = cmd_opts.%s"%(add_opt.dest,add_opt.dest)
        exec(cmd)
    ####################################################

    # disable signals handling
    if args[except_nam] == 1:
        os.environ["NOT_INTERCEPT_SIGNALS"] = "1"
        pass

    # now modify SalomeAppConfig environment variable
    # to take into account the SALOME modules
    dirs = re.split('[;|:]', os.environ[config_var] )

    for m in args[modules_nam]:
        if m not in ["KERNEL", "GUI", ""] and os.getenv("%s_ROOT_DIR"%m):
            d1 = os.getenv("%s_ROOT_DIR"%m) + "/share/salome/resources/" + m.lower()
            d2 = os.getenv("%s_ROOT_DIR"%m) + "/share/salome/resources"
            #if os.path.exists( "%s/%s.xml"%(d1, appname) ):
            if os.path.exists( "%s/%s.xml"%(d1, salomeappname) ):
                dirs.append( d1 )
            #elif os.path.exists( "%s/%s.xml"%(d2, appname) ):
            elif os.path.exists( "%s/%s.xml"%(d2, salomeappname) ):
                dirs.append( d2 )
    os.environ[config_var] = ":".join(dirs)

    # return arguments
    #print "Args: ", args
    return args
