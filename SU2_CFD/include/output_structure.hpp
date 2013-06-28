/*!
 * \file output_structure.hpp
 * \brief Headers of the main subroutines for generating the file outputs.
 *        The subroutines and functions are in the <i>output_structure.cpp</i> file.
 * \author Current Development: Stanford University.
 *         Original Structure: CADES 1.0 (2009).
 * \version 1.1.
 *
 * Stanford University Unstructured (SU2) Code
 * Copyright (C) 2012 Aerospace Design Laboratory
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <fstream>
#include <cmath>
#include <time.h>
#include <fstream>

#include "solution_structure.hpp"
#include "integration_structure.hpp"
#include "../../Common/include/geometry_structure.hpp"
#include "../../Common/include/config_structure.hpp"

using namespace std;

/*! 
 * \class COutput
 * \brief Class for writing the flow, adjoint and linearized solver 
 *        solution (including the history solution, and parallel stuff).
 * \author F. Palacios.
 * \version 1.1.
 */
class COutput {
protected:
	double Gamma;					   /*!< \brief Fluid's Gamma constant (ratio of specific heats). */
	double Gamma_Minus_One;			   /*!< \brief Fluids's Gamma - 1.0  . */


public:

	/*! 
	 * \brief Constructor of the class. 
	 */
	COutput(CConfig *config);

	/*! 
	 * \brief Destructor of the class. 
	 */
	~COutput(void);

	/*! 
	 * \brief Writes and organizes the all the output files, except the history one, for serial computations.
	 * \param[in] solution_container - Container vector with all the solutions.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iExtIter - Current external (time) iteration.
   * \param[in] val_nDomain - Total number of domains in the grid file.
	 */
	void SetResult_Files(CSolution ****solution_container, CGeometry ***geometry, CConfig *config, 
			unsigned long iExtIter, unsigned short val_nDomain);

	/*! 
	 * \brief Writes equivalent area.
	 * \param[in] solution_container - Container vector with all the solutions.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetEquivalentArea(CSolution *solution_container, CGeometry *geometry, CConfig *config, 
			unsigned long iExtIter);
	
	/*! 
	 * \brief Writes free surface, and functional.
	 * \param[in] solution_container - Container vector with all the solutions.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetFreeSurface(CSolution *solution_container, CGeometry *geometry, CConfig *config, 
												 unsigned long iExtIter);

	/*! 
	 * \brief Create and write the file with the conservative variables.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solution_container - Container vector with all the solutions.
	 * \param[in] iExtIter - Current external (time) iteration.
   * \param[in] val_nDomain - Total number of domains in the grid file.
	 */
	void SetDomain_Flow(CConfig *config, CGeometry ***geometry, CSolution ****solution_container, unsigned long iExtIter, unsigned short val_nDomain);

	/*!
	 * \brief Create and write the file with the conservative variables.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solution_container - Container vector with all the solutions.
	 * \param[in] val_filename - Name of the output file.
	 * \param[in] Quantity_Name - Name of the quantity to be plotted.
	 * \param[in] Scalar - Flag for scalar or vector quantity
	 * \param[in] iVar - index of the solution to be plotted
	 * \param[in] func - name of the method to call to output required value
	 * \param[in] config - Definition of the particular problem.
	 */
	void WriteInOutputFile(CGeometry *geometry, CSolution *solution_container, ofstream & val_filename, 
												 string Quantity_Name, bool Scalar,  short iVar, string func, CConfig *config);


	/*! 
	 * \brief Create and write the file with the conservative variables.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solution_container - Container vector with all the solutions.
	 * \param[in] ConsVar_file - Name of the output file.
	 */
	void WriteReactingOutputFile(CConfig *config, CGeometry *geometry,CSolution **solution_container, ofstream & ConsVar_file);

	/*!
	 * \brief Create and write the file with the adjoint variables.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solution_container - Container vector with all the solutions.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetDomain_Adjoint(CConfig *config, CGeometry *geometry, CSolution ***solution_container, unsigned long iExtIter);

	/*! 
	 * \brief Create and write the file with the linearized variables.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solution_container - Container vector with all the solutions.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetLinearized_Variables(CConfig *config, CGeometry *geometry, CSolution ***solution_container, unsigned long iExtIter);

	/*! 
	 * \brief Create and write the file with the flow coefficient on the surface.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] FlowSolution - Flow solution.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetSurface_Flow(CConfig *config, CGeometry *geometry, CSolution *FlowSolution, unsigned long iExtIter);
	
	/*! 
	 * \brief Create and write the file with the adjoint coefficients on the surface for serial computations.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] AdjSolution - Adjoint solution.
	 * \param[in] FlowSolution - Flow solution.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetSurface_Adjoint(CConfig *config, CGeometry *geometry, CSolution *AdjSolution, CSolution *FlowSolution, unsigned long iExtIter);
	
	/*! 
	 * \brief Create and write the file with linearized coefficient on the surface for serial computations
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] LinSolution - Linearized solution.
	 * \param[in] val_filename - Name of the output file.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetSurface_Linearized(CConfig *config, CGeometry *geometry, CSolution *LinSolution, string val_filename, 
																			 unsigned long iExtIter);
	
	/*! 
	 * \brief Create and write the file with the flow coefficient on the surface.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] FlowSolution - Flow solution.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetSurfaceCSV_Flow(CConfig *config, CGeometry *geometry, CSolution *FlowSolution, unsigned long iExtIter);

	/*! 
	 * \brief Create and write the file with the adjoint coefficients on the surface for serial computations.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] AdjSolution - Adjoint solution.
	 * \param[in] FlowSolution - Flow solution.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetSurfaceCSV_Adjoint(CConfig *config, CGeometry *geometry, CSolution *AdjSolution, CSolution *FlowSolution, unsigned long iExtIter);

	/*! 
	 * \brief Create and write the file with linearized coefficient on the surface for serial computations
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] LinSolution - Linearized solution.
	 * \param[in] val_filename - Name of the output file.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetSurfaceCSV_Linearized(CConfig *config, CGeometry *geometry, CSolution *LinSolution, string val_filename, unsigned long iExtIter);

	/*! 
	 * \brief Write restart file.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solution - Flow, adjoint or linearized solution.
	 * \param[in] mesh_filename - Name of the restart file.
	 */
	void SetReStart(CConfig *config, CGeometry *geometry, CSolution **solution, string mesh_filename);

	/*! 
	 * \brief Write the header of the history file.
	 * \param[in] ConvHist_file - Pointer to the convergence history file (which is defined in the main subroutine).
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetHistory_Header(ofstream *ConvHist_file, CConfig *config);

	/*! 
	 * \brief Write the history file and the convergence on the screen for serial computations.
	 * \param[in] ConvHist_file - Pointer to the convergence history file (which is defined in the main subroutine).
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solution_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] integration - Generic subroutines for space integration, time integration, and monitoring.
	 * \param[in] iExtIter - Current external (time) iteration.
	 * \param[in] timeused - Current number of clock tick in the computation (related with total time).
	 * \param[in] val_nDomain - Total number of domains in the grid file.
	 */
	void SetHistory_MainIter(ofstream *ConvHist_file, CGeometry ***geometry, CSolution ****solution_container, CConfig *config,
													 CIntegration **integration, unsigned long iExtIter, unsigned long timeused, unsigned short val_nDomain);

	/*! 
	 * \brief Write the history file and the convergence of the dual time algorithm for parallel computations.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solution_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] integration - Generic subroutines for space integration, time integration, and monitoring.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetHistory_DualTime(CGeometry **geometry, CSolution ***solution_container, CConfig *config, CIntegration **integration, unsigned long iExtIter);

};