"""
Classes for measuring the performance of a command
"""
import abc
import subprocess

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

class guage_time(guage_abstract):
    """
    Concrete class using system time function for measuring performance.
    """

    def __init__( self, measured=time_cmd_name_codes.lst_names()):
        self.measured=measured
        self.format=reduce\
                    ( lambda fmt,name: fmt+name+"["+time_cmd_name_codes.fmtcode(name)+"]"
                    , measured
                    , ""
                    )
    def names(self):
        return self.measured

    def measure(self, command_exe, command_args, measure_out):
        compile_cmd=command_exe+command_args
        measure_cmd='time --format '+self.format+' '+compile_cmd
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

    def names():
        return []

    def measure(self, command_exe, command_args, measure_out):
        measure_cmd=command_exe+" -ftime-report "+command_args
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
