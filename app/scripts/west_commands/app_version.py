'''app_version.py

West extension for managing the application version.'''

from textwrap import dedent            # just for nicer code indentation

from west.commands import WestCommand  # your extension must subclass this
from west import log                   # use this for user output

from os import path
import subprocess
from semver.version import Version

class AppVersion(WestCommand):

    def __init__(self):
        super().__init__(
            'app-version',  # gets stored as self.name
            'prints the application version based on the VERSION file',  # self.help
            # self.description:
            dedent('''
            Application Semantic Versioning.

            This command will print the application version using the VERSION
            file contents and the short hash of the HEAD.
            '''))

    def do_add_parser(self, parser_adder):
        # This is a bit of boilerplate, which allows you full control over the
        # type of argparse handling you want. The "parser_adder" argument is
        # the return value of an argparse.ArgumentParser.add_subparsers() call.
        parser = parser_adder.add_parser(self.name,
                                         help=self.help,
                                         description=self.description)

        # Add some example options using the standard argparse module API.
        parser.add_argument('dir', help='directory of the VERSION file')
        parser.add_argument('-r', '--release', action='store_true', help='prints the finalized release version only')

        return parser # gets stored as self.parser

    def do_run(self, args, unknown_args):
        # This gets called when the user runs the command, e.g.:
        #
        #   $ west app-version
        version = {}
        with open(path.join(args.dir, 'VERSION'), 'r', encoding='utf-8') as f:
            for line in f:
                name, sep, var = line.partition("=")
                version[name.strip()] = var.strip()

        git_hash = subprocess.run(['git', 'rev-parse', '--short', 'HEAD'],
                                  capture_output=True,
                                  check=True,
                                  encoding='ascii')

        sem_ver = Version(major=version['VERSION_MAJOR'],
                          minor=version['VERSION_MINOR'],
                          patch=version['PATCHLEVEL'],
                          prerelease=git_hash.stdout.strip(),
                          build=version['EXTRAVERSION'])

        if args.release:
            version_string = str(sem_ver.finalize_version())
        else:
            version_string = str(sem_ver)

        log.inf(version_string)
