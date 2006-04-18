# Check availability of Salome's KERNEL binary distribution
#
# Author : Jerome Roy (CEA, 2003)
#

AC_DEFUN([CHECK_KERNEL],[
AC_REQUIRE([AC_LINKER_OPTIONS])dnl

AC_CHECKING(for Kernel)

Kernel_ok=no

KERNEL_LDFLAGS=""
KERNEL_CXXFLAGS=""

AC_ARG_WITH(kernel,
	    [--with-kernel=DIR  root directory path of KERNEL build or installation],
	    [KERNEL_DIR="$withval"],
	    [KERNEL_DIR=""])

if test "x${KERNEL_DIR}" = "x" ; then
  AC_MSG_RESULT(for \${KERNEL_ROOT_DIR}: ${KERNEL_ROOT_DIR})
  # no --with-kernel-dir option used
  if test "x${KERNEL_ROOT_DIR}" != "x" ; then
    # KERNEL_ROOT_DIR environment variable defined
    KERNEL_DIR=${KERNEL_ROOT_DIR}
  else
    # search Kernel binaries in PATH variable
    AC_PATH_PROG(TEMP,runSalome)
    if test "x${TEMP}" != "x" ; then
      AC_MSG_RESULT(runSalome was found at : ${TEMP})
      KERNEL_BIN_DIR=`dirname ${TEMP}`
      KERNEL_DIR=`cd ${KERNEL_BIN_DIR}/../..; pwd`
    fi
  fi
fi

if test -f ${KERNEL_DIR}/bin/salome/runSalome ; then
   AC_MSG_RESULT(Using Kernel module distribution in ${KERNEL_DIR})
   Kernel_ok=yes

   if test "x${KERNEL_ROOT_DIR}" = "x" ; then
      KERNEL_ROOT_DIR=${KERNEL_DIR}
   fi

   if test "x${KERNEL_SITE_DIR}" = "x" ; then
      KERNEL_SITE_DIR=${KERNEL_ROOT_DIR}
   fi

   AC_SUBST(KERNEL_ROOT_DIR)
   AC_SUBST(KERNEL_SITE_DIR)

   KERNEL_LDFLAGS=-L${KERNEL_DIR}/lib${LIB_LOCATION_SUFFIX}/salome
   KERNEL_CXXFLAGS=-I${KERNEL_DIR}/include/salome

   AC_SUBST(KERNEL_LDFLAGS)
   AC_SUBST(KERNEL_CXXFLAGS)
else
   AC_MSG_WARN("Cannot find compiled Kernel module distribution")
fi

AC_MSG_RESULT(for Kernel: $Kernel_ok)
 
])dnl
 
