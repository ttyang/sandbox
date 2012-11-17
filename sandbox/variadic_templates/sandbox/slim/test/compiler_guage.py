"""
Classes for measuring the performance of a compiler
"""
import abc
import subprocess

class guage_abstract:
    """
    Abstract class for measuring compiler performance.
    """
    __metaclass__=abc.ABCMeta

    @abc.abstractmethod
    def names():
        """
        Names of performances measured by method, measure.
        """
        pass

    @abc.abstractmethod
    def measure(self,compiler_exe, compiler_args, measure_out):
        """
        Measure the performance of 
          compiler, compiler_exe,
          with args, compiler_args,
          while appending the measurements on file, measure_out.
        """
        pass

class guage_time(guage_abstract):
    """
    Concrete class using system time function for measuring performance.
    """

    def names():
        return ["user","system","elapsed"]

    def measure(self, compiler_exe, compiler_args, measure_out):
        compile_cmd=compiler_exe+compiler_args
        time_format='"user:%U system:%S elapsed:%e"'
        measure_cmd='time --format '+time_format+' '+compile_cmd
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
    Concrete class using -ftime-report compiler flag for measuring performance.
    """

    def names():
        return []

    def measure(self, compiler_exe, compiler_args, measure_out):
        measure_cmd=compiler_exe+" -ftime-report "+compiler_args
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
