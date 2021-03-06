#!/usr/bin/env python 

## \file shape_optimization.py
#  \brief Python script for performing the shape optimization.
#  \author T. Economon, T. Lukaczyk, F. Palacios
#  \version 3.2.7 "eagle"
#
# Copyright (C) 2012-2014 SU2 Core Developers.
#
# SU2 is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# SU2 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with SU2. If not, see <http://www.gnu.org/licenses/>.

import os, sys, shutil, copy
from optparse import OptionParser
sys.path.append(os.environ['SU2_RUN'])
import SU2

# -------------------------------------------------------------------
#  Main 
# -------------------------------------------------------------------

def main():

    parser=OptionParser()
    parser.add_option("-f", "--file", dest="filename",
                      help="read config from FILE", metavar="FILE")
    parser.add_option("-r", "--name", dest="projectname", default='',
                      help="try to restart from project file NAME", metavar="NAME")
    parser.add_option("-n", "--partitions", dest="partitions", default=1,
                      help="number of PARTITIONS", metavar="PARTITIONS")
    parser.add_option("-g", "--gradient", dest="gradient", default="Adjoint",
                      help="Method for computing the GRADIENT (ADJOINT, FINDIFF, NONE)", metavar="GRADIENT")
    parser.add_option("-q", "--quiet", dest="quiet", default="True",
                      help="True/False Quiet all SU2 output (optimizer output only)", metavar="QUIET")
    
    (options, args)=parser.parse_args()
    
    # process inputs
    options.partitions  = int( options.partitions )
    options.quiet       = options.quiet.upper() == 'TRUE'
    options.gradient    = options.gradient.upper()
    
    sys.stdout.write('\n-------------------------------------------------------------------------\n')
    sys.stdout.write('|    _____   _    _   ___                                               |\n')
    sys.stdout.write('|   / ____| | |  | | |__ \\    Release 3.2.7 \"eagle\"                     |\n')
    sys.stdout.write('|  | (___   | |  | |    ) |                                             |\n')
    sys.stdout.write('|   \\___ \\  | |  | |   / /                                              |\n')
    sys.stdout.write('|   ____) | | |__| |  / /_                                              |\n')
    sys.stdout.write('|  |_____/   \\____/  |____|   Aerodynamic Shape Optimization Script     |\n')
    sys.stdout.write('|                                                                       |\n')
    sys.stdout.write('-------------------------------------------------------------------------\n')
    sys.stdout.write('| Copyright (C) 2012-2014 SU2 Core Developers.                          |\n')
    sys.stdout.write('| SU2 is distributed in the hope that it will be useful,                |\n')
    sys.stdout.write('| but WITHOUT ANY WARRANTY; without even the implied warranty of        |\n')
    sys.stdout.write('| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU      |\n')
    sys.stdout.write('| Lesser General Public License (version 2.1) for more details.         |\n')
    sys.stdout.write('-------------------------------------------------------------------------\n\n')

    shape_optimization( options.filename    ,
                        options.projectname ,
                        options.partitions  ,
                        options.gradient    ,
                        options.quiet        )
    
#: main()

def shape_optimization( filename                , 
                        projectname = ''        ,
                        partitions  = 0         , 
                        gradient    = 'ADJOINT' ,
                        quiet       = False      ):
  
    # Config
    config = SU2.io.Config(filename)
    config.NUMBER_PART = partitions
    if quiet: config.CONSOLE = 'CONCISE'
    config.GRADIENT_METHOD = gradient
    
    its      = int ( config.OPT_ITERATIONS )
    accu     = float ( config.OPT_ACCURACY )
    bound_dv = float ( config.BOUND_DV )
    def_dv   = config.DEFINITION_DV
    n_dv     = len(def_dv['KIND'])
    x0       = [0.0]*n_dv # initial design
    xb_low   = [-float(bound_dv)]*n_dv # lower dv bound
    xb_up    = [float(bound_dv)]*n_dv # upper dv bound
    xb       = zip(xb_low,xb_up) # design bounds
    
    # State
    state = SU2.io.State()
    state.find_files(config)
    
    # Project
    if os.path.exists(projectname):
        project = SU2.io.load_data(projectname)
        project.config = config
    else:
        project = SU2.opt.Project(config,state)
    
    # Optimize
    SU2.opt.SLSQP(project,x0,xb,its,accu)
    
    # rename project file
    if projectname:
        shutil.move('project.pkl',projectname)
    
    return project

#: shape_optimization()


# -------------------------------------------------------------------
#  Run Main Program
# -------------------------------------------------------------------

# this is only accessed if running from command prompt
if __name__ == '__main__':
    main()

