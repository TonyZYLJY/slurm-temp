# makefile for sjf scheduler plugin

AUTOMAKE_OPTIONS = foreign

AM_CXXFLAGS = -fexceptions

PLUGIN_FLAGS = -module -avoid-version --export-dynamic

AM_CPPFLAGS = -DSLURM_PLUGIN_DEBUG -I$(top_srcdir) -I$(top_srcdir)/src/common

pkglib_LTLIBRARIES = sched_sjf.la

sched_sjf_la_SOURCES =\
	sjf_wrapper.c \
	sjf.c         \
	sjf.h

sched_sjf_la_LDFLAGS = $(PLUGIN_FLAGS)
