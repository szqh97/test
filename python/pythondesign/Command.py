#!/usr/bin/env python
import abc
import os
history = []
class Command(object):
    """ THe comand interfaces. """
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def execute(self):
        """ Method to execute to the command. """
        pass

    @abc.abstractmethod
    def undo(self):
        """ A method to undo the commmand. """
        pass

class LsCommand(Command):
    """ Concrete command that emulates ls unix command behavior."""

    def __init__(self, receiver):
        self.receiver = receiver

    def execute(self):
        """ The command delegates the call to its receiver. """
        self.receiver.show_current_dir()
    
    def undo(self):
        """ Can not undo ls command. """
        pass

class LsReceiver(object):
    def show_current_dir(self):
        """ The receiver knows how to execute the command. """
        cur_dir = './'
        filenames = []
        for filename in os.listdir(cur_dir):
            if os.path.isfile(os.path.join(cur_dir, filename)):
                filenames.append(filename)
        print 'Content of dir: ', ' '.join(os.path.join(filenames))

class TouchCommand(Command):
    """ Concrete command that emulates touch unix command
    behavior."""
    def __init__(self, receiver):
        self.receiver = receiver

    def execute(self):
        self.receiver.create_file()

    def undo(self):
        self.receiver.delete_file()

import os
class TouchReceiver(object):
    def __init__(self, filename):
        self.filename = filename

    def create_file(self):
        """Actual implementation of unix touch command. """
        with file(self.filename, 'a'):
            os.utime(self.filename, None)

    def delete_file(self):
        """Undo unix touch command. Here we simply delete the file. """
        os.remove(self.filename)

class RmCommand(Command):
    def __init__(self, receiver):
        self.receiver = receiver

    def execute(self):
        self.receiver.delete_file()
    
    def undo(self):
        self.receiver.undo()

class RmReceiver(object):
    def __init__(self, filename):
        self.filename = filename
        self.backup_name = None
    
    def delete_file(self):
        """ Delete file with creating backup to resore to it in undo method ."""
        self.backup_name =  self.filename + ".bk"
        os.rename(self.filename, self.backup_name)

    def undo(self):
        """ Restore the deleted file . """
        original_name = self.backup_name[0:-3]
        os.rename(self.backup_name, original_name)
        self.backup_name = None

class Invoker(object):
    def __init__(self, create_file_commands, delete_file_commands):
        self.create_file_commands = create_file_commands
        self.delete_file_commands = delete_file_commands
        self.history = []

    def create_file(self):
        print 'Creating file...'
        for cmd in self.create_file_commands:
            cmd.execute()
            self.history.append(cmd)
        print 'File created.'
    
    def delete_file(self):
        print "Deleting file..."
        for cmd in self.delete_file_commands:
            cmd.execute()
            self.history.append(cmd)
        print "File deleted."
    
    def undo_all(self):
        print "Undo all..."
        for cmd in reversed(self.history):
            cmd.undo()
        print "Undo all..."

if __name__ == '__main__':
    ls_receiver = LsReceiver()
    ls_command = LsCommand(ls_receiver)

    touch_receiver = TouchReceiver("test_file")
    touch_command = TouchCommand(touch_receiver)

    rm_receiver = RmReceiver("test_file")
    rm_cmd = RmCommand(rm_receiver)

    create_file_cmds = [ls_command, touch_command,ls_command]
    delete_file_cmds = [ls_command, rm_cmd, ls_command]

    invoker = Invoker(create_file_cmds, delete_file_cmds)

    invoker.create_file()
    invoker.delete_file()
    invoker.undo_all()
