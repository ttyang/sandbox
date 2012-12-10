"""
Classes for measuring the performance of a command
"""
import abc
import subprocess
import shlex

class guage_abstract:
    """
    Abstract class for measuring command performance.
    """
    __metaclass__=abc.ABCMeta

    @abc.abstractmethod
    def names():
        """
        Names of performances measured by method, measure.
        """
        pass

    @abc.abstractmethod
    def measure(self,command_exe, command_args, measure_out):
        """
        Measure the performance of 
          command, command_exe,
          with args, command_args,
          while appending the measurements on file, measure_out.
        """
        pass

import time_cmd_name_codes
import functools

class guage_time(guage_abstract):
    """
    Concrete class using system time function for measuring performance.
    """

    def __init__( self, measured=time_cmd_name_codes.lst_names()):
        self.measured=measured
        self.format=functools.reduce\
                    ( lambda fmt,name: fmt+" "+time_cmd_name_codes.fmtcode(name)
                    , measured
                    , ""
                    )+"'"#just space delimited values.
        self.format="'"+self.format[1:]
    def names(self):
        return self.measured

    def measure(self, command_exe, command_args, measure_out):
        measure_cmd=command_exe+command_args
        measure_cmd='time --format '+self.format+' '+measure_cmd
        print(":measure_cmd=",measure_cmd)
        if True:
          rc=subprocess.call(
              measure_cmd
            , shell=True
            , stdout=measure_out
            , stderr=subprocess.STDOUT
            )
          print(":rc=",rc)
          return rc
        return 0

class guage_ftime(guage_abstract):
    """
    Concrete class using -ftime-report command flag for measuring performance.
    This, of course, requires the command to take the -ftime-report flag.
    """

    def names(self):
        return []

    def measure(self, command_exe, command_args, measure_out):
        measure_cmd=command_exe+" -ftime-report "+command_args
        print(":measure_cmd=",measure_cmd)
        if True:
          measure_lst=shlex.split(measure_cmd)  
          rc=subprocess.call(
              measure_lst
            , stdout=measure_out
            , stderr=subprocess.STDOUT
            )
          print(":rc=",rc)
          return rc
        return 0

import os.path, re

class guage_gprof(guage_abstract):
    """
    Concrete class using gprof for measuring performance.
    This requires that the command_exe arg to be measured
    has been compiled with the -pg flag.
    """

    def __init__(self):
        if False:
          errmsg="guage_gprof not implemented yet.  Try another guage."
          print(errmsg)
          raise NotImplementedError
        self.re_clang=re.compile(".*Profile.*/bin/clang")

    def names(self):
        return []

    def measure(self, command_exe, command_args, measure_out):
        found=self.re_clang.search(command_exe)
        if not found:
          print(":command_exe=",command_exe,"not clang profiled compiler")
          rc=1
          print(":rc=",rc)
          return rc
        measure_cmd=command_exe+" -### "+command_args
        print(":measure_cmd(to get compiler front-end args)=",measure_cmd)
        if True:
          measure_lst=shlex.split(measure_cmd)  
          pipe=subprocess.Popen(
              measure_lst
            , stderr=subprocess.PIPE
            )
          lines=pipe.stderr.readlines()
          rc=pipe.wait()
          print(":rc=",rc)
          if rc != 0:
            print(":measure_cmd(with -###).",rc)  
            return rc
          measure_cmd=lines.pop().decode("utf-8")
            #frontend_cmd should include 'clang -cc1'.
            #This invokes just the compiler front-end (no driver).
          print(":measure_cmd=",measure_cmd)
          measure_cmd=shlex.split(measure_cmd)
          pipe=subprocess.Popen(
              measure_lst
            , stderr=subprocess.PIPE
            )
          lines=pipe.stderr.readlines()
          rc=pipe.wait()
          print(":rc=",rc)
          if rc != 0:
            print(":frontend command failed.",rc)
            print(":stderr=\n",lines)
            return rc
          data_out="./gmon.out"
          if not os.path.exists(data_out):
            print(data_out,"does not exist, as required by guage_prof.measure(...)\n")
            return 1
          measure_cmd="gprof "+command_exe+" "+data_out
          print(":gprof_cmd=",measure_cmd)
          measure_lst=shlex.split(measure_cmd)
          rc=subprocess.call(
              measure_lst
            , stdout=measure_out
            , stderr=subprocess.STDOUT
            )
          print(":gprof rc=",rc)
          return rc
        return 0

class guage_heapprof(guage_abstract):
    """
    Concrete class for porfiling heap usage.
    This requires that the command_exe arg to be measured
    has been compiled with the -g flag.
    """

    def __init__(self):
        if False:
          errmsg="guage_heapprof not implemented yet.  Try another guage."
          print(errmsg)
          raise NotImplementedError
        self.re_clang=re.compile(".*Debug.*/bin/clang")

    def names(self):
        return []

    def measure(self, command_exe, command_args, measure_out):
        found=self.re_clang.search(command_exe)
        if not found:
          print(":command_exe=",command_exe,"not clang created with debugging.")
          rc=1
          print(":rc=",rc)
          return rc
        data_out="./massif.out"
        measure_cmd="valgrind --tool=massif --massif-out-file="+data_out+".%p "+command_exe+" "+command_args
        print(":valgrind_cmd(to profile heap)=",measure_cmd)
        if True:
          measure_lst=shlex.split(measure_cmd)  
          proc=subprocess.Popen(
              measure_lst
            )
          rc=proc.wait();
          print(":valgrind rc=",rc)
          if rc != 0:
            return rc
          data_pid=data_out+"."+str(proc.pid)
          if not os.path.exists(data_pid):
            print(data_pid,"does not exist, as required by guage_helpprof.measure(...)\n")
            return 1
          measure_cmd="ms_print "+data_pid
          print(":ms_print_cmd=",measure_cmd)
          measure_lst=shlex.split(measure_cmd)
          rc=subprocess.call(
              measure_lst
            , stdout=measure_out
            , stderr=subprocess.STDOUT
            )
          print(":ms_print rc=",rc)
          return rc
        return 0
