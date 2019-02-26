/*
###############################################################################
# If you use PhysiCell in your project, please cite PhysiCell and the version #
# number, such as below:                                                      #
#                                                                             #
# We implemented and solved the model using PhysiCell (Version x.y.z) [1].    #
#                                                                             #
# [1] A Ghaffarizadeh, R Heiland, SH Friedman, SM Mumenthaler, and P Macklin, #
#     PhysiCell: an Open Source Physics-Based Cell Simulator for Multicellu-  #
#     lar Systems, PLoS Comput. Biol. 14(2): e1005991, 2018                   #
#     DOI: 10.1371/journal.pcbi.1005991                                       #
#                                                                             #
# See VERSION.txt or call get_PhysiCell_version() to get the current version  #
#     x.y.z. Call display_citations() to get detailed information on all cite-#
#     able software used in your PhysiCell application.                       #
#                                                                             #
# Because PhysiCell extensively uses BioFVM, we suggest you also cite BioFVM  #
#     as below:                                                               #
#                                                                             #
# We implemented and solved the model using PhysiCell (Version x.y.z) [1],    #
# with BioFVM [2] to solve the transport equations.                           #
#                                                                             #
# [1] A Ghaffarizadeh, R Heiland, SH Friedman, SM Mumenthaler, and P Macklin, #
#     PhysiCell: an Open Source Physics-Based Cell Simulator for Multicellu-  #
#     lar Systems, PLoS Comput. Biol. 14(2): e1005991, 2018                   #
#     DOI: 10.1371/journal.pcbi.1005991                                       #
#                                                                             #
# [2] A Ghaffarizadeh, SH Friedman, and P Macklin, BioFVM: an efficient para- #
#     llelized diffusive transport solver for 3-D biological simulations,     #
#     Bioinformatics 32(8): 1256-8, 2016. DOI: 10.1093/bioinformatics/btv730  #
#                                                                             #
###############################################################################
#                                                                             #
# BSD 3-Clause License (see https://opensource.org/licenses/BSD-3-Clause)     #
#                                                                             #
# Copyright (c) 2015-2018, Paul Macklin and the PhysiCell Project             #
# All rights reserved.                                                        #
#                                                                             #
# Redistribution and use in source and binary forms, with or without          #
# modification, are permitted provided that the following conditions are met: #
#                                                                             #
# 1. Redistributions of source code must retain the above copyright notice,   #
# this list of conditions and the following disclaimer.                       #
#                                                                             #
# 2. Redistributions in binary form must reproduce the above copyright        #
# notice, this list of conditions and the following disclaimer in the         #
# documentation and/or other materials provided with the distribution.        #
#                                                                             #
# 3. Neither the name of the copyright holder nor the names of its            #
# contributors may be used to endorse or promote products derived from this   #
# software without specific prior written permission.                         #
#                                                                             #
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" #
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   #
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  #
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   #
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         #
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        #
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    #
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     #
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     #
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  #
# POSSIBILITY OF SUCH DAMAGE.                                                 #
#                                                                             #
###############################################################################
*/

#include "./custom.h"

// declare cell definitions here 

Cell_Definition motile_cell; 

void create_cell_types( void )
{
	// use the same random seed so that future experiments have the 
	// same initial histogram of oncoprotein, even if threading means 
	// that future division and other events are still not identical 
	// for all runs 
	
	SeedRandom( parameters.ints("random_seed") ); // or specify a seed here 
	
	// housekeeping 
	
	initialize_default_cell_definition();
	cell_defaults.phenotype.secretion.sync_to_microenvironment( &microenvironment ); 
	
	// Name the default cell type 
	
	cell_defaults.type = 0; 
	cell_defaults.name = "bacterium"; 
	
	// set default cell cycle model 

	cell_defaults.functions.cycle_model = live; 
	
	
	// set default_cell_functions; 
	
	cell_defaults.functions.update_phenotype = NULL;//update_cell_and_death_parameters_O2_based; 
	
	// needed for a 2-D simulation: 
	
	/* grab code from heterogeneity */ 
	
	cell_defaults.functions.set_orientation = up_orientation; 
	cell_defaults.phenotype.geometry.polarity = 1.0;
	cell_defaults.phenotype.motility.restrict_to_2D = true; 
	
	// make sure the defaults are self-consistent. 
	
	cell_defaults.phenotype.secretion.sync_to_microenvironment( &microenvironment );
	cell_defaults.phenotype.sync_to_functions( cell_defaults.functions ); 

	// set the rate terms in the default phenotype 

	// first find index for a few key variables. 
	int apoptosis_model_index = cell_defaults.phenotype.death.find_death_model_index( "Apoptosis" );
	int necrosis_model_index = cell_defaults.phenotype.death.find_death_model_index( "Necrosis" );
	int q_substrate_index = microenvironment.find_density_index( "q" ); 

	

	// initially no necrosis 
	cell_defaults.phenotype.death.rates[necrosis_model_index] = 0.0; 

	 
	
	// add custom data here, if any 
	// // birth/death rates
	int biid = parameters.doubles.find_index("birth_interval");
	double birth_rate = 1./parameters.doubles(biid);//1./60.;
	
	cell_defaults.functions.cycle_model.transition_rate(0,0) = birth_rate;
	
	cell_defaults.phenotype.death.rates[apoptosis_model_index] = 0.01*birth_rate;
	
	// // volume:
	int vid = parameters.doubles.find_index("volume_total");
	double totalVolume =parameters.doubles(vid);
	
	cell_defaults.phenotype.volume.total = totalVolume;//1;
	cell_defaults.phenotype.volume.nuclear = 0.0;
	
	
	cell_defaults.phenotype.volume.cytoplasmic = totalVolume;//1;
	
	int fid = parameters.doubles.find_index("target_fluid_frac");
	double target_fluid_frac = parameters.doubles(fid);
	
	
	
	cell_defaults.phenotype.volume.fluid = target_fluid_frac*cell_defaults.phenotype.volume.total;
	cell_defaults.phenotype.volume.solid = cell_defaults.phenotype.volume.total - cell_defaults.phenotype.volume.fluid;
	
	cell_defaults.phenotype.volume.cytoplasmic_solid = cell_defaults.phenotype.volume.solid;
	cell_defaults.phenotype.volume.cytoplasmic_fluid = cell_defaults.phenotype.volume.fluid;
	
	
	cell_defaults.phenotype.volume.target_fluid_fraction = target_fluid_frac;
	cell_defaults.phenotype.volume.target_solid_cytoplasmic = 1.-target_fluid_frac;//cell_defaults.phenotype.volume.cytoplasmic_solid;
	
	int fcrid = parameters.doubles.find_index("fluid_change_rate");
	double fluid_change_rate = parameters.doubles(fcrid);
	
	int cbcrid = parameters.doubles.find_index("cytoplasmic_biomass_change_rate");
	double cytoplasmic_biomass_change_rate = parameters.doubles(cbcrid);
	
	cell_defaults.phenotype.volume.fluid_change_rate = fluid_change_rate;
	cell_defaults.phenotype.volume.cytoplasmic_biomass_change_rate = cytoplasmic_biomass_change_rate;
	
	cell_defaults.functions.volume_update_function = anuclear_volume_model;
	
	// // geometry
	const double PI  = 3.141592653589793238463;
	cell_defaults.phenotype.geometry.radius = pow((3./4.)*(1./PI)*cell_defaults.phenotype.volume.total,1./3.);
	cell_defaults.phenotype.geometry.nuclear_radius = 0.0;
	
	// // movement
	cell_defaults.phenotype.motility.is_motile = true; 
	cell_defaults.phenotype.motility.migration_bias = 0.0;
	cell_defaults.phenotype.motility.migration_speed = 2.0;
	// // custom
	cell_defaults.custom_data.add_variable("last_q", "dimensionless", 0.0);
	
	// // secrete q
	cell_defaults.phenotype.secretion.secretion_rates[0] = 5000.0;//increased from 100
	cell_defaults.phenotype.secretion.saturation_densities[0]= 1;
	
	//cell_defaults.phenotype.secretion.saturation_densities[1] = 1;
	cell_defaults.functions.update_phenotype = update_q_phenotype;
	
	
	
	return; 
}




//custom function 



void update_q_phenotype( Cell* pCell, Phenotype& phenotype, double dt )
{
	
	if( phenotype.death.dead == true )
	{
		// the cell death functions don't automatically turn off custom functions, 
		// since those are part of mechanics. 
		
		// Let's just fully disable now. 
		pCell->functions.update_phenotype = NULL; 
		return; 
	}
	
	static int id_q = microenvironment.find_density_index("q");
	
	int biid = parameters.doubles.find_index("birth_interval");
	double birth_rate = 1./parameters.doubles(biid);//1./60.;
	
	//sample q
	double q = pCell->nearest_density_vector()[ id_q ]; 
	
	if (q<0.1)
	{
		pCell->phenotype.motility.is_motile = false;
		pCell->functions.cycle_model.transition_rate(0,0) = birth_rate;
	}
	if (q>=0.1)
	{
		pCell->phenotype.motility.is_motile = true;
		pCell->functions.cycle_model.transition_rate(0,0) = .01*birth_rate;
	}
	
	return;
	
}


void anuclear_volume_model( Cell* pCell, Phenotype& phenotype, double dt )
{
	
	if( phenotype.death.dead == true )
	{
		// the cell death functions don't automatically turn off custom functions, 
		// since those are part of mechanics. 
		
		// Let's just fully disable now. 
		pCell->functions.volume_update_function = NULL; 
		return; 
	}
	
	phenotype.volume.fluid += dt * phenotype.volume.fluid_change_rate * 
		( phenotype.volume.target_fluid_fraction * phenotype.volume.total - phenotype.volume.fluid );
		
	// if the fluid volume is negative, set to zero
	if( phenotype.volume.fluid < 0.0 )
	{ phenotype.volume.fluid = 0.0; }
		
	phenotype.volume.nuclear_fluid = 0;
	phenotype.volume.cytoplasmic_fluid = phenotype.volume.fluid;
	
	phenotype.volume.nuclear_solid  = 0;
	
	
	phenotype.volume.cytoplasmic_solid += dt * phenotype.volume.cytoplasmic_biomass_change_rate * 
		( phenotype.volume.target_solid_cytoplasmic - phenotype.volume.cytoplasmic_solid );	
	if( phenotype.volume.cytoplasmic_solid < 0.0 )
	{ phenotype.volume.cytoplasmic_solid = 0.0; }

	phenotype.volume.solid = phenotype.volume.cytoplasmic_solid;
	
	phenotype.volume.nuclear = 0; 
	phenotype.volume.cytoplasmic = phenotype.volume.cytoplasmic_solid + phenotype.volume.cytoplasmic_fluid; 
	
	phenotype.volume.total = phenotype.volume.cytoplasmic; 
   
	phenotype.geometry.update( pCell,phenotype,dt );
	
	
	
	
	
	
	
	
	
	/* 
	
	double fluidFrac_tg = pCell->phenotype.volume.target_fluid_fraction;
	double totalVolume = pCell->phenotype.volume.total;
	double fluidVolume = pCell->phenotype.volume.fluid;
	double fluidRate = pCell->phenotype.volume.fluid_change_rate;
	double nextFluidVolume;
	
	double solCyto_tg = pCell->phenotype.volume.target_solid_cytoplasmic;
	double solidCyto_volume = pCell->phenotype.volume.cytoplasmic_solid ; //totalVolume-fluidVolume;
	double solidRate = pCell->phenotype.volume.cytoplasmic_biomass_change_rate;
	double nextSolidVolume;
	
		
	
	
	nextFluidVolume = fluidVolume + dt * fluidRate * ( fluidFrac_tg * totalVolume - fluidVolume );
	
	
	nextSolidVolume = solidCyto_volume + dt*solidRate*(solCyto_tg - solidCyto_volume);
	
	
	if( nextFluidVolume <0)
	{
		nextFluidVolume = 0;
	}
	
	if( nextSolidVolume )
	{
		nextSolidVolume =0;
	}
	
	pCell->phenotype.volume.total = nextSolidVolume+nextFluidVolume;
	pCell->phenotype.volume.nuclear = 0.;
	pCell->phenotype.volume.cytoplasmic = nextSolidVolume+nextFluidVolume;	
	pCell->phenotype.volume.fluid = nextFluidVolume;
	pCell->phenotype.volume.solid = nextSolidVolume;	
	
	pCell->phenotype.volume.cytoplasmic_fluid = nextFluidVolume;	
	pCell->phenotype.volume.cytoplasmic_solid = nextSolidVolume;
	
	const double PI  = 3.141592653589793238463;
	
	pCell->phenotype.geometry.radius = pow((3./4.)*(1./PI)*(pCell->phenotype.volume.total),1./3.);
	pCell->phenotype.geometry.nuclear_radius = 0.0;
	 */
	
	
	
	return;
	
}

void setup_microenvironment( void )
{
	// set domain parameters 
	
/* now this is in XML 
	default_microenvironment_options.X_range = {-1000, 1000}; 
	default_microenvironment_options.Y_range = {-1000, 1000}; 
	default_microenvironment_options.simulate_2D = true; 
*/
	// make sure to override and go back to 2D 
	if( default_microenvironment_options.simulate_2D == false )
	{
		std::cout << "Warning: overriding XML config option and setting to 2D!" << std::endl; 
		default_microenvironment_options.simulate_2D = true; 
	}
	
	
	
	// no gradients need for this example 

	default_microenvironment_options.calculate_gradients = false; 
	
	default_microenvironment_options.use_oxygen_as_first_field = false;
	
	microenvironment.set_density(0, "q", "dimensionless" );
	microenvironment.diffusion_coefficients[0] = 1e5;
	microenvironment.decay_rates[0] = 10;	
	
	// set Dirichlet conditions 

	default_microenvironment_options.outer_Dirichlet_conditions = false;
	
	// if there are more substrates, resize accordingly 
	std::vector<double> bc_vector( 1 , 0.0 ); // 5% o2
	default_microenvironment_options.Dirichlet_condition_vector = bc_vector;
	
	
	
	// initialize BioFVM 
	
	initialize_microenvironment(); 	
	
	
	
	return; 
}

void setup_tissue( void )
{
	srand (static_cast <unsigned> (time(0)));
	
	// create some cells near the origin
	
	Cell* pC;

	
	
	for(int i=0; i<50; i++)
	{
		float x = (rand()%201)-100;
		float y = (rand()%201)-100;
		
		pC = create_cell(); 
		pC->assign_position( x, y, 0.0 );
		//x_rng = (rand() % (3000-300)) - 1350; //random position between -1350 and 1350
	}
	
	
	return; 
}

std::vector<std::string> my_coloring_function( Cell* pCell )
{
	// start with flow cytometry coloring 
	
	std::vector<std::string> output = false_cell_coloring_cytometry(pCell); 
		
	if( pCell->phenotype.death.dead == false && pCell->type == 1 )
	{
		 output[0] = "black"; 
		 output[2] = "black"; 
	}
	
	return output; 
}
